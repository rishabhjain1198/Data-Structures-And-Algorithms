#include "provided.h"
#include <string>
#include <vector>
#include "MyMap.h"
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    AttractionMapper attrac;
    SegmentMapper segMapper;
    MapLoader loader;
    
    string directionOfLine(const GeoSegment& gs) const
    {
        double angle = angleOfLine(gs);
        
        if(angle >= 0 && angle <= 22.5)
            return "east";
        
        if(angle >= 22.5 && angle <= 67.5)
            return "northeast";
        
        if(angle >= 67.5 && angle <= 112.5)
            return "north";
        
        if(angle >= 112.5 && angle <= 157.5)
            return "northwest";
        
        if(angle >= 157.5 && angle <= 202.5)
            return "west";
        
        if(angle >= 202.5 && angle <= 247.5)
            return "southwest";
        
        if(angle >= 247.5 && angle <= 292.5)
            return "south";
        
        if(angle >= 292.5 && angle <= 337.5)
            return "southeast";
        
        if(angle >= 337.5 && angle <= 360)
            return "east";
        
        return "problem";
    }
    
    string flippedDirectionOfLine(const GeoSegment& gs) const
    {
        double angle = angleOfLine(gs);
        
        if(angle >= 180)
            angle -= 180;
        else
            angle+=180;
        
        if(angle >= 0 && angle <= 22.5)
            return "east";
        
        if(angle >= 22.5 && angle <= 67.5)
            return "northeast";
        
        if(angle >= 67.5 && angle <= 112.5)
            return "north";
        
        if(angle >= 112.5 && angle <= 157.5)
            return "northwest";
        
        if(angle >= 157.5 && angle <= 202.5)
            return "west";
        
        if(angle >= 202.5 && angle <= 247.5)
            return "southwest";
        
        if(angle >= 247.5 && angle <= 292.5)
            return "south";
        
        if(angle >= 292.5 && angle <= 337.5)
            return "southeast";
        
        if(angle >= 337.5 && angle <= 360)
            return "east";
        
        return "problem";
    }
    
    class modGeoCoord
    {
    public:
        modGeoCoord(std::string lat, std::string lon)
        : latitudeText(lat), longitudeText(lon), latitude(stod(lat)), longitude(stod(lon))
        {}
        
        modGeoCoord()
        : latitudeText("0"), longitudeText("0"), latitude(0), longitude(0)
        {}
        
        modGeoCoord(GeoCoord toCopy)
        {
            latitudeText = toCopy.latitudeText;
            longitudeText = toCopy.longitudeText;
            latitude = toCopy.latitude;
            longitude = toCopy.longitude;
        }
        
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

    modGeoCoord modIt(GeoCoord copyit) const
    {
        modGeoCoord toReturn(copyit);
        return toReturn;
    }
    
    GeoCoord convertToGeo(modGeoCoord tobeconverted) const
    {
        GeoCoord thisOne(tobeconverted.latitudeText, tobeconverted.longitudeText);
        return thisOne;
    }
    
    struct forSorting
    {
        StreetSegment yehseg;
        double dist;
    };

    struct by_dist
    {
        bool operator()(forSorting const &a, forSorting const &b) {
            return a.dist < b.dist;
        }
    };
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if(!loader.load(mapFile))
        return false;
    
    attrac.init(loader);
    segMapper.init(loader);
	return true;  // This compiles, but may not be correct
}

/*

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    directions.clear();

    
    GeoCoord startingCoord;
    if(!attrac.getGeoCoord(start, startingCoord))
        return NAV_BAD_SOURCE;
    
    GeoCoord endingCoord;
    if(!attrac.getGeoCoord(end, endingCoord))
        return NAV_BAD_DESTINATION;
    
    modGeoCoord modStartingCoord(startingCoord);
    modGeoCoord modEndingCoord(endingCoord);
    
    MyMap<modGeoCoord, bool> closedSet;
    vector<modGeoCoord> openSet;
    MyMap<modGeoCoord, modGeoCoord> cameFrom;
    openSet.push_back(modStartingCoord);
    MyMap<modGeoCoord, double> gScore;
    gScore.associate(modStartingCoord, 0);
    MyMap<modGeoCoord, double> fScore;
    fScore.associate(modStartingCoord, distanceEarthMiles(startingCoord, endingCoord));
    
    //check for the trivial case that start and end are on the same segment
    vector<StreetSegment> first = segMapper.getSegments(startingCoord);
    vector<StreetSegment> second = segMapper.getSegments(endingCoord);
    
    for(int i = 0; i < first.size(); i++)
    {
        for(int j = 0; j < second.size(); j++)
        {
            if(first[i].streetName == second[j].streetName)
            {
                //THIS IS TRIVIAL CASE
                double dist = distanceEarthMiles(startingCoord, endingCoord);
                string dir = dirResolver(angleOfLine(first[i].segment));
                NavSegment onlyOne(dir, first[i].streetName, dist, first[i].segment);
                directions.push_back(onlyOne);
                return NAV_SUCCESS;
            }
        }
    }
    
    //time to find route from startingCoord to endingCoord

    while(!openSet.empty())
    {
        //select the node in openSet with least fscore
        modGeoCoord currentNode = openSet[0];
        int currLocator = 0;
        double fvalueCurrent = *(fScore.find(currentNode));
        for(int i = 1; i < openSet.size(); i++)
        {
           double fvalueNew = *(fScore.find(openSet[i]));
           if(fvalueCurrent > fvalueNew)
           {
               currLocator = i;
               fvalueCurrent = fvalueNew;
               currentNode = openSet[i];
           }
        }
        
        //currentNode is now the node in openSet with least fscore
        
        if(currentNode.latitude == endingCoord.latitude && currentNode.longitude == endingCoord.longitude)
        {
            //RECONSTRUCT PATH HERE....TO BE IMPLEMENTED....
            
            vector<GeoCoord> path;
            
            while(!(currentNode.latitude == startingCoord.latitude && currentNode.longitude == startingCoord.longitude))
            {
                path.push_back(convertToGeo(currentNode));
                currentNode = *cameFrom.find(currentNode);
                
            }
            
            //time to output NavSegments
            StreetSegment puranaSeg;
            
            for(int i = path.size()-1; i > 0; i--)
            {
                StreetSegment myseg = segMapper.getSegments(path[i])[0];
                
                if(i == path.size()-1)
                    puranaSeg = myseg;
                else
                {
                    if(puranaSeg.streetName != myseg.streetName)
                    {
                        if(angleBetween2Lines(puranaSeg.segment, myseg.segment) < 180)
                        {
                            //add turn left navseg
                            NavSegment turnNav("left", myseg.streetName);
                            directions.push_back(turnNav);
                        }
                        else
                        {
                            //add turn right navseg
                            NavSegment turnNav("right", myseg.streetName);
                            directions.push_back(turnNav);
                        }
                    }
                    puranaSeg = myseg;
                }
                
                string dir = dirResolver(angleOfLine(myseg.segment));
                double dist = distanceEarthMiles(path[i], path[i-1]);
                NavSegment myNav(dir, myseg.streetName, dist, myseg.segment);
                directions.push_back(myNav);
                
            }
           
            return NAV_SUCCESS;
            
        }
        
        openSet.erase(openSet.begin() + currLocator);
        closedSet.associate(currentNode, true);
        
        vector<GeoCoord> neighbours;
        vector<StreetSegment> currentSegment = segMapper.getSegments(convertToGeo(currentNode));
        
        for(int i = 0; i < currentSegment.size(); i++)
        {
            if(closedSet.find(currentSegment[i].segment.end) == nullptr)
            {
                //this does not exist in closed set
                double tentativeScore = *(gScore.find(currentNode)) + distanceEarthMiles(convertToGeo(currentNode), currentSegment[i].segment.end);
                
                bool found = false;
                
                //trying to tell if node exists in open set
                for(int j = 0; j < openSet.size(); j++)
                    if(openSet[j].latitude == currentSegment[i].segment.end.latitude && openSet[j].longitude == currentSegment[i].segment.end.longitude)
                        found = true;
                
                if(!found)
                    openSet.push_back(currentSegment[i].segment.end);
                else if (tentativeScore >= *(gScore.find(currentSegment[i].segment.end)))
                    continue;
                
                cameFrom.associate(currentSegment[i].segment.end, currentNode);
                gScore.associate(currentSegment[i].segment.end, tentativeScore);
                fScore.associate(currentSegment[i].segment.end, *(gScore.find(currentSegment[i].segment.end)) + distanceEarthMiles(currentSegment[i].segment.end, endingCoord));
            }
        }
    }
    
	return NAV_NO_ROUTE;  // This compiles, but may not be correct
}
*/

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    directions.clear();
    
    //taking care of case of end
    for(int i = 0;  i < end.size(); i++)
        end[i] = tolower(end[i]);
    
    GeoCoord startingCoord;
    if(!attrac.getGeoCoord(start, startingCoord))
        return NAV_BAD_SOURCE;
    
    GeoCoord endingCoord;
    if(!attrac.getGeoCoord(end, endingCoord))
        return NAV_BAD_DESTINATION;
    
    vector<StreetSegment> startingSeg = segMapper.getSegments(startingCoord);
    vector<StreetSegment> endingSeg = segMapper.getSegments(endingCoord);
    
    //checking if they lie on the same segment
    
    for(int i = 0; i < startingSeg.size(); i++)
    {
        for(int j = 0; j < endingSeg.size(); j++)
        {
            if(startingSeg[i].streetName == endingSeg[j].streetName)
            {
                //they lie on same segment. put one navsegment in directions and return
                NavSegment thisOne(directionOfLine(startingSeg[i].segment), startingSeg[i].streetName, distanceEarthMiles(startingCoord, endingCoord), startingSeg[i].segment);
                directions.push_back(thisOne);
                return NAV_SUCCESS;
            }
        }
    }
    
    //time to find route from startingCoord to endingCoord using maze finding algo
    
    queue<GeoCoord> toBeProcessed;
    //MyMap<modGeoCoord, bool> beenHere;
    MyMap<modGeoCoord, modGeoCoord> cameFrom;
    MyMap<modGeoCoord, StreetSegment> streetFrom;
    MyMap<modGeoCoord, bool> endCoordHai;
    
    toBeProcessed.push(startingCoord);
    //beenHere.associate(modIt(startingCoord), true);
    
    //int goes = 0;
    
    while(!toBeProcessed.empty())
    {

        GeoCoord thisNow = toBeProcessed.front();
        toBeProcessed.pop();
        
        //get all segments related to this geocoord
        vector<StreetSegment> theseSegs = segMapper.getSegments(thisNow);
        
        
        //check if the attraction lies on one of these segments
        for(int i = 0; i < theseSegs.size(); i++)
        {
            for(int j = 0; j < theseSegs[i].attractions.size(); j++)
            {
                string thisAttrac = "";
                //taking care of case
                for(int k = 0; k < theseSegs[i].attractions[j].name.size(); k++)
                    thisAttrac += tolower(theseSegs[i].attractions[j].name[k]);
                
                if(thisAttrac == end)
                {
                    //TIME TO END IT
                    //WE HAVE FOUND IT
                    //CONSTRUCT THE PATH... TO BE IMPLEMENTED.... TO BE IMPLEMENTED
                    
                    //first form the optimal path in another vector using cameFrom map
                    vector<GeoCoord> path;
                    GeoCoord currentCoord = thisNow;
                    
                    path.push_back(endingCoord);
                    streetFrom.associate(modIt(endingCoord), theseSegs[i]);
                    
                    while(!(currentCoord.latitude == startingCoord.latitude && currentCoord.longitude == startingCoord.longitude))
                    {
                        //end this loop when currentCoord is the startingCoord
                        path.push_back(currentCoord);
                        currentCoord = convertToGeo(*(cameFrom.find(modIt(currentCoord))));
                    }
                    //path.push_back(currentCoord);
                    
                    //Entire path has now been constructed in path, but in reverse order
                    
                    //time to construct the nav segments using this path
                    
                    for(int i = path.size() - 1; i > 0; i--)
                    {
                        GeoCoord starts = path[i];
                        GeoCoord ends = path[i-1];
                        
                        StreetSegment toTravel = *(streetFrom.find(path[i]));
                        string dir = directionOfLine(toTravel.segment);
                        if(!(*endCoordHai.find(modIt(starts))))
                            dir = flippedDirectionOfLine(toTravel.segment);
                        
                        
                        double dist = distanceEarthMiles(starts, ends);
                        
                        NavSegment toBeAdded(dir, toTravel.streetName, dist, toTravel.segment);
                        directions.push_back(toBeAdded);
                        
                        //check if turn based NavSegment is needed
                        
                            StreetSegment nextSeg = *(streetFrom.find(path[i-1]));
                            if(toTravel.streetName != nextSeg.streetName)
                            {
                                //we need to put a turn
                                if(angleBetween2Lines(toTravel.segment, nextSeg.segment) < 180)
                                {
                                    //turn left
                                    NavSegment turnkaro("left", nextSeg.streetName);
                                    directions.push_back(turnkaro);
                                }
                                else
                                {
                                    //turn right
                                    NavSegment turnkaro("right", nextSeg.streetName);
                                    directions.push_back(turnkaro);
                                }
                            }
                        
                    }
                    
                    return NAV_SUCCESS;
                }
            }
        }
      
        
        //Sort theseSegs according to their distances
        vector<forSorting> tempSegs;
        
        for(int i = 0; i < theseSegs.size(); i++)
        {
            forSorting temp;
            temp.yehseg = theseSegs[i];
            temp.dist = distanceEarthMiles(thisNow, theseSegs[i].segment.end);
            tempSegs.push_back(temp);
        }
        
        sort(tempSegs.begin(), tempSegs.end(), by_dist());
        
        //SORTING COMPLETED
        
       // for(int i = 0; i < tempSegs.size(); i++)
       // {
          //  cout<<tempSegs[i].yehseg.streetName<<endl;
      //  }
        
        for(int i = 0; i < tempSegs.size(); i++)
        {
            GeoCoord toGoTo = tempSegs[i].yehseg.segment.end;
            
            //cout<<tempSegs[i].yehseg.streetName<<endl;
            
            //before adding to queue, need to make sure we haven't been here before
            if(cameFrom.find(modIt(toGoTo)) == nullptr)
            {
               // cout<<tempSegs[i].yehseg.streetName<<endl;
                //NEW GEOCOORD!
                cameFrom.associate(modIt(toGoTo), modIt(thisNow));
                streetFrom.associate(modIt(toGoTo), tempSegs[i].yehseg);
                toBeProcessed.push(toGoTo);
                endCoordHai.associate(modIt(toGoTo), true);
            }
            
            
            toGoTo = tempSegs[i].yehseg.segment.start;
            
            //cout<<tempSegs[i].yehseg.streetName<<endl;
            
            //before adding to queue, need to make sure we haven't been here before
            if(cameFrom.find(modIt(toGoTo)) == nullptr)
            {
                // cout<<tempSegs[i].yehseg.streetName<<endl;
                //NEW GEOCOORD!
                cameFrom.associate(modIt(toGoTo), modIt(thisNow));
                streetFrom.associate(modIt(toGoTo), tempSegs[i].yehseg);
                toBeProcessed.push(toGoTo);
                endCoordHai.associate(modIt(toGoTo), false);
            }
        }
        

    }
    
 
    return NAV_NO_ROUTE;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}

//TESTING
/*
int main()
{
    MapLoader map;
    
    map.load("/Users/rishabhjain/Documents/VIM_C++/cs32/project4/project4/mapdata.txt");
    
    map.getNumSegments();
    
    SegmentMapper segmap;
    
    segmap.init(map);
    
    AttractionMapper attrmap;
    
    attrmap.init(map);
    
    GeoCoord texte("34.0630614", "-118.4468781");       //coordinates of diddy riese
    
    vector<StreetSegment> tester = segmap.getSegments(texte);
    
    
    for(int i = 0; i < tester.size(); i ++)
        for(int j = 0; j < tester[i].attractions.size(); j++)
            cout<<tester[i].attractions[j].name<<endl;
    
    
    return 0;
}
*/
