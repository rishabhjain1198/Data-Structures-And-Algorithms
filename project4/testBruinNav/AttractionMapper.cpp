#include "provided.h"
#include <string>
#include <cctype>
#include "MyMap.h"
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> mainMap;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    for(size_t i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment seg;
        if(!ml.getSegment(i, seg))
            return;
        
        for(int j = 0; j < seg.attractions.size(); j++)
        {
            //taking care of case
            for(int k = 0; k < seg.attractions[j].name.size(); k++)
                seg.attractions[j].name[k] = tolower(seg.attractions[j].name[k]);
            
            mainMap.associate(seg.attractions[j].name, seg.attractions[j].geocoordinates);
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    //taking care of case
    for(int i = 0; i < attraction.size(); i++)
        attraction[i] = tolower(attraction[i]);
    
    
    const GeoCoord* temp = mainMap.find(attraction);

    if(temp == nullptr) return false;
    
    gc = *(temp);
    
    return true;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
