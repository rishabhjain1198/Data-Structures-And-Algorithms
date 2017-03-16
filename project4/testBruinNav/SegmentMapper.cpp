#include "provided.h"
#include <vector>
#include "MyMap.h"
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    class modGeoCoord
    {
    public:
        modGeoCoord(std::string lat, std::string lon)
        : latitudeText(lat), longitudeText(lon), latitude(stod(lat)), longitude(stod(lon))
        {}
        
        modGeoCoord()
        : latitudeText("0"), longitudeText("0"), latitude(0), longitude(0)
        {}
        
        bool operator==(modGeoCoord& rhs)const
        {
            if(rhs.latitude == latitude && rhs.longitude == longitude)
                return true;
            
            return false;
        }
        
        bool operator>(modGeoCoord& rhs) const
        {
            if(latitude > rhs.latitude)
                return true;
            
            return false;
        }
        
        std::string latitudeText;
        std::string longitudeText;
        double      latitude;
        double      longitude;
    };

    MyMap<modGeoCoord, vector<StreetSegment> > mainMap;
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for(int i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment seg;
        if(!ml.getSegment(i, seg))
            return;
        
        modGeoCoord tempStart(seg.segment.start.latitudeText, seg.segment.start.longitudeText);
        
        vector<StreetSegment>* temp1 = mainMap.find(tempStart);
        
        if(temp1 != nullptr)
            temp1 -> push_back(seg);
        else
        {
            vector<StreetSegment> nayaWala;
            nayaWala.push_back(seg);
            mainMap.associate(tempStart, nayaWala);
        }
        
        modGeoCoord tempEnd(seg.segment.end.latitudeText, seg.segment.end.longitudeText);
        
        vector<StreetSegment>* temp2 = mainMap.find(tempEnd);
        if(temp2 != nullptr)
            temp2 -> push_back(seg);
        else
        {
            vector<StreetSegment> nayaWala;
            nayaWala.push_back(seg);
            mainMap.associate(tempEnd, nayaWala);
        }
        
      //  for(int j = 0; j < seg.attractions.size(); j++)
        //{
          //  cout<<seg.attractions[j].name<<endl;
        //}
        
        for(int j = 0; j < seg.attractions.size(); j++)
        {
            modGeoCoord tempAtt(seg.attractions[j].geocoordinates.latitudeText, seg.attractions[j].geocoordinates.longitudeText);
            
            vector<StreetSegment>* temp3 = mainMap.find(tempAtt);
            if(temp3 != nullptr)
                temp3 -> push_back(seg);
            else
            {
                vector<StreetSegment> nayaWala;
                nayaWala.push_back(seg);
                mainMap.associate(tempAtt, nayaWala);
            }
        }
    } 
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    modGeoCoord temp(gc.latitudeText, gc.longitudeText);
    const vector<StreetSegment>* segments = mainMap.find(temp);
	
    if(segments == nullptr)
    {
        vector<StreetSegment> empti;
        empti.clear();
        return empti;
    }
    
    cout<<segments -> size()<<endl;
    return *segments;
}



// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}


