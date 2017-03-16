#include "provided.h"
#include <string>
#include<iostream>
#include<fstream>
#include <vector>
#include "MyMap.h"

using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    size_t m_segmentNumber;
    MyMap<size_t, StreetSegment> mainMap;
};

MapLoaderImpl::MapLoaderImpl()
{
    m_segmentNumber = 0;
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream infile(mapFile);
    
    if(!infile)
        return false;
    
    StreetSegment finalOne;
    
    string streetName;
    
    while(getline(infile, streetName))
    {
        finalOne.attractions.clear();
        finalOne.streetName = streetName;
        
        m_segmentNumber++;
        
        string latLongString;
        getline(infile, latLongString);
        
        string firstLat = "";
        string firstLon = "";
        string secondLat = "";
        string secondLon = "";
        
        int i = 0;
        
        while(latLongString[i] != ',')
        {
            firstLat += latLongString[i];
            i++;
        }
        
        i++;
        i++;
        
        while(latLongString[i] != ' ')
        {
            firstLon += latLongString[i];
            i++;
        }
        
        i++;
        
        while(latLongString[i] != ',')
        {
            secondLat += latLongString[i];
            i++;
        }
        
        i++;
        
        while(i < latLongString.size())
        {
            secondLon += latLongString[i];
            i++;
        }
        
        GeoCoord start (firstLat, firstLon);
        GeoCoord end (secondLat, secondLon);
        
        GeoSegment thisOne (start, end);
        
        finalOne.segment = thisOne;
        
        int n;
        infile >> n;
        infile.ignore(10000, '\n');
        
        for(int k = 0; k < n; k++)
        {
            Attraction heya;
            
            string attractionString;
            getline(infile, attractionString);
            string attractionName = "";
            
            int i = 0;
            
            while(attractionString[i] != '|')
            {
                attractionName += attractionString[i];
                i++;
            }
            
            i++;
            
            string attractionLat = "", attractionLon = "";
            
            while(attractionString[i] != ',')
            {
                attractionLat += attractionString[i];
                i++;
            }
            
            i++;
            i++;
            
            while(i < attractionString.size())
            {
                attractionLon += attractionString[i];
                i++;
            }
            
            GeoCoord coord(attractionLat, attractionLon);
            
            heya.name = attractionName;
            heya.geocoordinates = coord;
            
            finalOne.attractions.push_back(heya);
        }
        
        mainMap.associate(m_segmentNumber-1, finalOne);
    }
    
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_segmentNumber;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if(segNum >= getNumSegments()) return false;
    
    const StreetSegment* temp = mainMap.find(segNum);
    
    if(temp == nullptr)
        return false;
    
    seg = *temp;
    
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}




////////////TESTING


