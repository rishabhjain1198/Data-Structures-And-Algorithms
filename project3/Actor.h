#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "Compiler.h"
#include <sstream>

// Students:  Add code to this file, Actor.cpp, StudentWzorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int const id1, StudentWorld* const world, int const x, int const y, Direction const d, int const depth);
    virtual void doSomething() = 0;
    int health();
    bool isDead();
    void setDead();
    void setHealth(int newHealth);
    int sleeping(int changer);
    int biting(int canBite);
    void canBeBitten(bool canbebitten);
    virtual void isBitten(int bitingPower, int x, int y);
    int id();
    void changeId(int newId);
    StudentWorld* world();
    void dirResolver(int &x, int &y, Direction dir);
    void notDeadAnymore();
    bool poolSleeping();
    bool poolSleeping(bool changer);
    Direction randDir();

private:
    int m_health;
    StudentWorld* m_myWorld;
    Direction m_dir;
    int m_depth;
    bool m_dead;
    int m_sleeping;
    int m_canBite;
    bool m_canBeBitten;
    int m_id;
    bool m_poolSleep;
};


class Pebble : public Actor
{
public:
    Pebble(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
};

class Grasshopper : public Actor
{
public:
    Grasshopper(int const id1, Direction const dir, StudentWorld* const world, int const x, int const y);
    virtual void doSomething() = 0;
    int dist();
    void changeDist(int newDist);

private:
    int m_dist;
};

class BabyGrasshopper: public Grasshopper
{
public:
    BabyGrasshopper(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
    virtual void isBitten(int bitingPower, int x, int y);
};


class AdultGrasshopper : public Grasshopper
{
public:
    AdultGrasshopper(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
    virtual void isBitten(int bitingPower, int x, int y);
    void findSpot(int &x, int &y, int r);
};

class Food : public Actor
{
public:
    Food(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
};


class PoolOfWater : public Actor
{
public:
    PoolOfWater(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
};

class Poison : public Actor
{
public:
    Poison(StudentWorld* const world, int const x, int const y);
    virtual void doSomething();
};

class Pheromone : public Actor
{
public:
    Pheromone(int const idd, StudentWorld* const world, int const x, int const y, int const colony);
    virtual void doSomething();
};

class Anthill : public Actor
{
public:
    Anthill(StudentWorld* const world, int const x, int const y, int const colony, Compiler* const tempo);
    virtual void doSomething();
private:
    int m_colony;
    Compiler* m_compiler;
};

class Ant : public Actor
{
public:
    Ant(int const idd, StudentWorld* const world, int const x, int const y, int const colony, Compiler* const tempo);
    virtual void doSomething();
    bool interpreter(Compiler::Command cmd, int &gotoif, bool &mustReturn, int &tickCount);
    void tryToMove();
    virtual void isBitten(int bitingPower, int x, int y);
private:
    int m_colonyOwner;
    Compiler* m_compilerOwner;
    int m_foodHeld;
    int m_rowNumber;
    bool wasBitten;
    bool wasBlocked;
    int randNum;
    int gotoif;
    bool mustReturn;
};

#endif // ACTOR_H_

