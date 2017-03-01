#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <stack>

#define NUM_OBJECTS 8
#define PEBBLE_INDEX 0
#define BBYGRASS_INDEX 1
#define ADUGRASS_INDEX 2
#define ANT_INDEX 3
#define FOOD_INDEX 4
#define POISON_INDEX 5
#define POOL_OF_WATER_INDEX 6
#define PHEROMONE_INDEX 7
#define ANTHILL_INDEX 8
#define LAST_ALIVE_INDEX 3

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    
    virtual int init();
    
    virtual int move();

    virtual void cleanUp();
    
    void addFood(int x, int y, int foodAmount, StudentWorld* myWorld);
    void createAdultGrasshopper(int x, int y, StudentWorld* myWorld);
    bool isPebble(int x, int y);
    bool isAlive(int x, int y);
    bool biteSomething(int x, int y, int bitingPower, Actor* biter);
    bool isFood(int x, int y);
    int eatFood(int x, int y, int eatingAttempt);
    void stunThem(int x, int y, int stunValue);
    void poisonThem(int x, int y, int poisonValue);
    void createAnt(int x, int y, Actor* temp, int colony);
    void createPheromone(int x, int y, int colony);
    bool checkCompilation(int idd);
    bool isEnemy(int x, int y, int colony);
    bool isMyAnthill(int x, int y, int colony);
    bool isPheromone(int x, int y);
    void updateDisplayText();
private:
    std::vector<Actor*> field [VIEW_WIDTH][VIEW_HEIGHT][NUM_OBJECTS];
    std::vector<std::string> fileNames;
    std::vector<std::string> newFileNames;
    //using a 3d array of vectors
    // 0 index represents pebbles, 1 index represents baby grasshoppers (for now)
    // 2 index represents adult grasshoppers, 3 index represents ants
    // 4 index represents food
    
    int antProduced [4];
    int tickCounter;
    bool compiledCorrectly[4];
    int winningAnt;
    
    /*
    struct ActorIdentifier
    {
        ActorIdentifier(int x1, int y1, Actor* myActor1, int idd1) : x(x1), y(y1), myActor(myActor1), idd(idd1)
        {}
        
        int x;
        int y;
        Actor* myActor;
        int idd;
    };
    
    std::stack<ActorIdentifier> deadStack;      //something to keep track of what has died
     */
};

#endif // STUDENTWORLD_H_
