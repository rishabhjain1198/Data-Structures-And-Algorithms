#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//--------------------AUX-FUNCTIONS-------------------
Actor::Direction Insect::randDir()
{
    int i = randInt(1,4);       //create a random integer, and resolve it into a direction
    switch(i)
    {
        case 1:
            return right;
            break;
        case 2:
            return left;
            break;
        case 3:
            return up;
            break;
        case 4:
            return down;
            break;
    }
    return none;
}

void Insect::dirResolver(int &x, int &y, Direction dir)
{
    switch(dir)     //move a step in that direction
    {
        case right:
            x++;
            break;
        case left:
            x--;
            break;
        case up:
            y++;
            break;
        case down:
            y--;
            break;
        case none:
            break;
    }
}

//---------------------ACTOR---------------------------

Actor::Actor(int const id1, StudentWorld* const world, int const x, int const y, Direction const d, int const depth) : GraphObject(id1, x, y, d, depth), m_myWorld(world), m_dir(d), m_depth(depth), m_id(id1)
{
    m_dead = false;             //actor isn't dead
}

void Actor::isBitten(int bitingPower, int x, int y) {}      //dummy functions created to make use of later, virtually
bool Actor::poolSleeping() { return false;}
bool Actor::poolSleeping(bool changer){return false;}
int Actor::sleeping(int changer) { return 1;}

int Actor::health()
{
    return m_health;            //simply returns the health of the actor
}

bool Actor::isDead()
{
    return m_dead;              //returns if actor is dead or not
}

void Actor::setDead()
{
    m_dead = true;              //makes an actor dead
    setVisible(false);
}

void Actor::setHealth(int newHealth)
{
    m_health = newHealth;           //sets health to new value
}

int Insect::sleeping(int changer)
{
    m_sleeping += changer;          //increments the sleeping counter by changer value
    return m_sleeping;                 //and returns the new value
}


int Insect::biting(int canBite)
{
    m_canBite += canBite;       //increments the biting power by canBite value and returns
    return m_canBite;          //the new value
}

void Insect::canBeBitten(bool canbebitten)
{
    m_canBeBitten = canbebitten;            //changes whether actor can be bitten or not
}

int Actor::id()
{
    return m_id;                            //a way to uniquely identify some actor
}

StudentWorld* Actor::world()
{
    return m_myWorld;                       //keeps track of the actor's world
}

void Insect::isBitten(int bitingPower, int x, int y)
{
    //do nothing, this is implemented in derived classes
}

void Actor::notDeadAnymore()
{
    m_dead = false;
    setVisible(true);       //in case some identical object replaces something in the same tick
}                           //like food getting eaten fully and being created at the same tick

void Actor::changeId(int newId)
{
    m_id = newId;                       //changes the id of the actor
}

bool Insect::poolSleeping(bool changer)      //changes whether actor is stunned by pool or not
{
    m_poolSleep = changer;
    return m_poolSleep;
}

bool Insect::poolSleeping()
{
    return m_poolSleep;                 //returns whether actor is stunned by pool or not
}

//----------------------INSECT---------------------------

Insect::Insect(int const idd, int const depth, Direction const dir, StudentWorld* const world, int const x, int const y) : Actor(idd, world, x, y, dir, depth)
{
        m_poolSleep = false;;       //this keeps track of whether stunned by pool or not
        m_sleeping = 0;             //sets sleeping to false so it can move
}

//----------------------PEBBLE---------------------------

Pebble::Pebble(StudentWorld* const world, int const x, int const y) : Actor(IID_ROCK, world, x, y, right, 1)
{
}

void Pebble::doSomething()
{
    //It's a pebble. It doesn't do anything.
}


//-----------------------BABY-GRASSHOPPER-----------------

BabyGrasshopper::BabyGrasshopper(StudentWorld* const world, int const x, int const y) : Grasshopper(IID_BABY_GRASSHOPPER, randDir(), world, x, y)
{
    setHealth(500);             //starting health is 500
    biting(0);                  //bby grasshopper can't be bitten
}



void BabyGrasshopper::doSomething()
{
    //loses 1 hit point because of hunger
    setHealth(health() - 1);
    
    //check to see if dead
    if(isDead())
        return ;
    
    if(health() <= 0)
    {
        //baby grasshopper is dead
        world()->addFood(getX(), getY(), 100, world());
        setDead();
        return ;
    }

    if(sleeping(0) > 0)        //check to see if it is stunned or sleeping
    {
        sleeping(-1);           //decrement sleeping tick by 1
        return ;
    }

    else
    {
        //check to see if it can evolve into Adult Grasshopper
        poolSleeping(false);
        if(health() >= 1600)
        {
            //time to kill this, and create an adult
            world()->createAdultGrasshopper(getX(), getY(), world());
            world()->addFood(getX(), getY(), 100, world());
            setDead();
            return ;
        }
        
        //try eating food
        if(world() -> isFood(getX(), getY()))
        {
            //EAT THE FOOOOOOOOD
            int eatingAttempt = world() -> eatFood(getX(), getY(), 200);
            setHealth(health()+eatingAttempt);

            //try to sleep
            if(randInt(1,2) == 1)
            {
                sleeping(2);
                return ;
            }
        }
        
        //moving the baby
        //if it has finished it's task to walk, give it another
        if(dist() <= 0)
        {
            setDirection(randDir());
            changeDist(randInt(2,10));
        }
        
        //time to move
        int newX = getX(), newY = getY();
        dirResolver(newX, newY, getDirection());
        
        //check if there is a pebble in the direction to be moved in
        if(world()->isPebble(newX, newY))
        {
            changeDist(0);
        }
        else
        {
            //time to actually move
            moveTo(newX, newY);
            int currentDist = dist();
            changeDist(currentDist-1);
        }
        
        sleeping(2);            //increments sleeping counter by 2
        
    }
}

void BabyGrasshopper::isBitten(int bitingPower, int x, int y)
{
    setHealth(health()-bitingPower);            //reduce health
    if(health() <= 0)               //if health is below 0, bby is dead
        setDead();
}

//-----------------------GRASSHOPPERS-CLASS---------------

Grasshopper::Grasshopper(int const id1, Direction const dir, StudentWorld* const world, int const x, int const y) : Insect(id1, 0, dir, world, x, y)
{
    canBeBitten(true);                      //grasshoppers can be bitten
    
    //time to pick random distance
    changeDist(randInt(2,10));
}

int Grasshopper::dist()
{
    return m_dist;                     //distance to be travelled by grasshopper
}

void Grasshopper::changeDist(int newDist)
{
    m_dist = newDist;                   //function to change distance to be travelled
}

//-----------------------ADULT-GRASSHOPPER----------------


AdultGrasshopper::AdultGrasshopper(StudentWorld* const world, int const x, int const y) : Grasshopper(IID_ADULT_GRASSHOPPER, randDir(), world, x, y)
{
    setHealth(1600);                //adult grasshoppers start with 1600hp
    biting(50);                     //they have a biting power of 50
}

void AdultGrasshopper::doSomething()
{
    //loses 1 health due to hunger
    setHealth(health() - 1);
    
    //check to see if dead
    if(isDead())
        return;
    
    if(health() <= 0)
    {
        //adult grasshopper is dead
        world()->addFood(getX(), getY(), 100, world());
        setDead();
        return ;
    }
    
    if(sleeping(0) > 0)        //check to see if it is stunned or sleeping
    {
        sleeping(-1);           //decrement sleeping tick by 1
        return ;
    }
    
    
    else
    {
        poolSleeping(false);
        //try and bite
        if(randInt(1,3) == 1 && world() -> isAlive(getX(), getY()))
        {
            //TIME TO BITE
            if(world() -> biteSomething(getX(), getY(), biting(0), this))
            {
                sleeping(2);
                return ;
            }
        }
        
        //no biting this time
        
        if(randInt(1,10) == 1)
        {
            //try to jump
            //check if there is an empty spot within a circle of radius 10
            int newwX = getX(), newwY = getY();
            findSpot(newwX, newwY, 10);
            if(newwX != getX() || newwY != getY())
            {
                moveTo(newwX, newwY);
            }
            return ;
        }
        
        //try to eat food
        if(world() -> isFood(getX(), getY()))
        {
            int foodEaten = world() -> eatFood(getX(), getY(), 200);
            setHealth(health()+foodEaten);
            
            //50% chance it wants to rest
            if(randInt(1,2) == 1)
            {
                sleeping(2);
                return ;
            }
        }
        
        //check if dist is 0, set dir and dist and attempt to mvoe
        if(dist() == 0)
        {
            setDirection(randDir());
            changeDist(randInt(2,10));
        }
        
        int newX = getX(), newY = getY();
        dirResolver(newX, newY, getDirection());
        
        if(world() -> isPebble(newX, newY))
        {
            changeDist(0);
            sleeping(2);
            return ;
        }
        
        //we should be able to move to newX, newY
        moveTo(newX, newY);
        changeDist(dist()-1);
        sleeping(2);
        return ;
    }
    
}

void AdultGrasshopper::isBitten(int bitingPower, int x, int y)
{
    setHealth(health()-bitingPower);            //bitten, so must reduce health
    if(health() <= 0)
        setDead();
    
    //50% chance to bite back
    
    if(randInt(1,2) == 1)
        world() -> biteSomething(x, y, 50, this);
}

void AdultGrasshopper::findSpot(int &x, int &y, int r)
{
    for(int i = 0; i < VIEW_WIDTH; i++)     //go through every spot on the grid
    {
        for(int j = 0; j < VIEW_HEIGHT; j++) {
    
    if(sqrt(((i-x)*(i-x)) - ((j - y) * (j - y))) <= r)       //if not too far away
    {
    
    if(!(world() -> isPebble(i, j)) && (i != x || j != y))  //if not far away and no pebble
    {
        x = i;                  //jump to it
        y = j;
        return;
    }
    } }}
}

//----------------------------FOOD-----------------------------------

Food::Food(StudentWorld* const world, int const x, int const y) : Actor(IID_FOOD, world, x, y, right, 2)
{
    setHealth(6000);            //food starts out with 6000hp
}

void Food::doSomething()
{
    //It is food. It does nothing.
}


//----------------------------POOL-OF-WATER---------------------------

PoolOfWater::PoolOfWater(StudentWorld* const world, int const x, int const y) : Actor(IID_WATER_POOL, world, x, y, right, 2)
{ }

void PoolOfWater::doSomething()
{
    //ask world() to stun them
    world() -> stunThem(getX(), getY(), 2);         //stun everything on those coordinates for 2
}

//---------------------------POISON---------------------------------

Poison::Poison(StudentWorld* const world, int const x, int const y) : Actor(IID_POISON, world, x, y, right, 2) { }

void Poison::doSomething()
{
    //ask world() to poison them
    world() -> poisonThem(getX(), getY(), 150);
}

//----------------------------PHEROMONE------------------------------

Pheromone::Pheromone(int idd, StudentWorld* const world, int const x, int const y, int const colony) : Actor(idd, world, x, y, right, 2)
{
    setHealth(256);                     //starts out with 256 hp
    changeId(colony);                   //save colony number in ID
}

void Pheromone::doSomething()
{
    setHealth(health() - 1);            //losing health every tick
    if(health() <= 0)
        setDead();
}

//--------------------------ANTHILL-----------------------------------

Anthill::Anthill(StudentWorld* const world, int const x, int const y, int const colony, Compiler* const tempo) : Actor(IID_ANT_HILL, world, x, y, right, 2), m_colony(colony), m_compiler(tempo)
{
    setHealth(8999);            //starts out with 8999 hp
    changeId(colony);           //store id in colony number
    m_compiler = tempo;         //store compiler pointer in private variable
}

void Anthill::doSomething()
{
    setHealth(health() - 1);        //losing health because of tick
    
    if(health() <= 0)
    {
        //anthill is dead
        setDead();
        return ;
    }
    
    //try to eat food
    //std::cout<<"x :  "<<getX()<<"   y : "<<getY()<<std::endl;
    if(world() -> isFood(getX(), getY()))
    {
        //there's food. EAT IT
        int eatingAttempt = world() -> eatFood(getX(), getY(), 10000);
        setHealth(health() + eatingAttempt);
        //std::cout<<" FOOD EATEN !    "<<eatingAttempt<<std::endl;
        return ;
    }
    
    //try to produce an ant
    if(health() >= 2000)
    {
        //TIME TO MAKE AN ANT
        Actor* temp = nullptr;
        switch(m_colony)
        {
            case 0:
                temp = new Ant(IID_ANT_TYPE0, world(), getX(), getY(), m_colony, m_compiler);
                break;
            case 1:
                temp = new Ant(IID_ANT_TYPE1, world(), getX(), getY(), m_colony, m_compiler);
                break;
            case 2:
                temp = new Ant(IID_ANT_TYPE2, world(), getX(), getY(), m_colony, m_compiler);
                break;
            case 3:
                temp = new Ant(IID_ANT_TYPE3, world(), getX(), getY(), m_colony, m_compiler);
                break;
        }
        
        //ask world to put it in the data structure
        world() -> createAnt(getX(), getY(), temp, m_colony);
        
       //decrease health
  
        setHealth(health() - 1500);
    }
}

//--------------------------ANT-------------------------------------------

Ant::Ant(int const idd, StudentWorld* const world, int const x, int const y, int const colony, Compiler* const tempo) : Insect(idd, 1, randDir(), world, x, y)
{
    setHealth(1500);
    m_foodHeld = 0;
    m_rowNumber = 0;
    wasBitten = false;
    wasBlocked = false;
    biting(15);
    m_colonyOwner = colony;
    changeId(colony);
    m_compilerOwner = tempo;
}

void Ant::interpreter(Compiler::Command cmd, int &gotoif, bool &mustReturn, int &tickCount)
{
       //gotoif keeps track of what command it was
                        // 0 means not go to or if
                        // 1 means go to
                        // 2 means if
    
    tickCount++;            //increase depth of interpreter

    switch(cmd.opcode)
    {
        case Compiler::moveForward:
            tryToMove();                //try to move and must return after this
            mustReturn = true;
            break;
        case Compiler::eatFood:
            if(m_foodHeld > 0)
            {
                //time to eat food
                if(m_foodHeld >= 100)
                {
                    m_foodHeld -= 100;
                    setHealth(health() + 100);
                }
                else
                {
                    setHealth(health() + m_foodHeld);
                    m_foodHeld = 0;
                }
                mustReturn = true;
            }
            break;
        case Compiler::dropFood:
            world() -> addFood(getX(), getY(), m_foodHeld, world());
            m_foodHeld = 0;
            mustReturn = true;
            
            
            //std::cout<<"FOOD DROPPED"<<std::endl; and must return
            
            
            break;
        case Compiler::bite:
            world() -> biteSomething(getX(), getY(), biting(15), this);
            mustReturn = true;          //try to bite something here
            break;
        case Compiler::pickupFood:
            if(world() -> isFood(getX(), getY()))
            {
                //time to pick up the food
                int pickingAttempt = 400;
                
                if(m_foodHeld >= 1400)
                    pickingAttempt = 1800 - m_foodHeld;
                
                int foodPickedUp = world() -> eatFood(getX(), getY(), pickingAttempt);
                m_foodHeld += foodPickedUp;
                mustReturn = true;
            }
            break;
        case Compiler::emitPheromone:
            //ask world to create Pheromone here
            world() -> createPheromone(getX(), getY(), m_colonyOwner);
            mustReturn = true;
            break;
        case Compiler::faceRandomDirection:
            setDirection(randDir());            //set a new direction
            mustReturn = true;
            break;
        case Compiler::generateRandomNumber:
        {
            //first we need to convert string operand1 into integer
            std::string text = cmd.operand1;
            int limit;
            std::stringstream convert (text);
            convert >> limit;
            //now we generate random integer and store in private member
            randNum = randInt(0, limit);
            break;
        }
        case Compiler::goto_command:
        {
            gotoif = 1;
            std::string textt = cmd.operand1;
            int lineNumber;
            std::stringstream convertt (textt);
            convertt >> lineNumber;
            //now we set line number correctly in the private variable
            m_rowNumber = lineNumber;
            break;
        }
        case Compiler::if_command:
            std::string commandNumber = cmd.operand1;
            std::string textt = cmd.operand2;
            int lineNumber = stoi(textt);;
            //std::stringstream convertt (textt);
            //convertt >> lineNumber;

            int newCommand = stoi(commandNumber);
           

            //now we do a switch to see what the if statement was
            if(newCommand == Compiler::last_random_number_was_zero)
            {
                if(randNum == 0)
                {
                    gotoif = 2;
                    //now we set line number correctly in the private variable
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_am_carrying_food)
            {
                if(m_foodHeld > 0)
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_am_hungry)
            {
                if(health() <= 25)
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_am_standing_with_an_enemy)
            {
                //ask world whether it is standing with an enemy
                if(world() -> isEnemy(getX(), getY(), m_colonyOwner))
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_am_standing_on_food)
            {
                //ask world to check for food
               //std::cout<<gotoif<<std::endl;
                if(world() -> isFood(getX(), getY()))
                {
                    gotoif = 2;
                    //std::cout<<"lololololo"<<std::endl;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_am_standing_on_my_anthill)
            {
                //ask world to check for position on Anthill
                if(world() -> isMyAnthill(getX(), getY(), m_colonyOwner))
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_smell_pheromone_in_front_of_me)
            {
                int newX = getX(), newY = getY();
                dirResolver(newX, newY, getDirection());
                //ask world if there is pheromone
                if(world() -> isPheromone(getX(), getY()))
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_smell_danger_in_front_of_me)
            {
                int newX = getX(), newY = getY();
                dirResolver(newX, newY, getDirection());
                //ask world if there is danger
                if(world() -> isEnemy(newX, newY, m_colonyOwner))
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_was_bit)
            {
                if(wasBitten)
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            else if(newCommand == Compiler::i_was_blocked_from_moving)
            {
                if(wasBlocked)
                {
                    gotoif = 2;
                    m_rowNumber = lineNumber;
                }
            }
            
            break;
    }
}



void Ant::isBitten(int bitingPower, int x, int y)
{
    //need to make sure that its bite is recorded
    setHealth(health()-bitingPower);
    if(health() <= 0){
        setDead();
    
        world() -> addFood(getX(), getY(), 100, world()); }
    
    wasBitten = true;
}

void Ant::tryToMove()
{
    int newX = getX(), newY = getY();
    dirResolver(newX, newY, getDirection());
    
    //newX and newY now have the required values
    
    if(world() -> isPebble(newX, newY))
    {
        wasBlocked = true;
        return ;
    }
    
    wasBlocked = false;
    moveTo(newX, newY);
}

void Ant::doSomething()
{
    //losing health because of hunger
    setHealth(health() - 1);
    
    if(isDead())
        return ;
    
    if(health() <= 0)
    {
        world() -> addFood(getX(), getY(), 100, world());       //ant died
        setDead();
        return ;
    }
    
    if(sleeping(0) > 0)     //if sleeping counter is not 0, reduce the counter and return
    {
        sleeping(-1);
        return ;
    }
 
    else
    {
        //ANT WILL DO SOMETHING NOW
        poolSleeping(false);        //set pool stun status to false
        if(world() -> checkCompilation(m_colonyOwner))      //check if compilation was successful
        {
            Compiler::Command cmd;
            
                // this would fill the cmd variable up with the 3rd entry
                // in the vector above: generateRandomNumber, "5", "", ...
                // Instructions were obtained successfully, time to interpret
                //std::cout<<cmd.text<<std::endl;
                int gotoif = 0;
                int tickCount = 0;
                while(true)     //continue going until returns
                {
                    if (m_compilerOwner -> getCommand(m_rowNumber,cmd))
                    {       //get command of that particular row number
                        std::cout<<cmd.text<<std::endl;
                    gotoif = 0; bool mustReturn = false;
                    interpreter(cmd, gotoif, mustReturn, tickCount);
                    wasBitten = false;
                    if(gotoif == 0)     //must go to next line of instruction
                        m_rowNumber++;
                
                    if(mustReturn)      //we must return immediately
                        return;
                        
                    if(tickCount >= 10) //depth of instructions exceeded
                        return ;
                    }
                    
                    else
                    {               //error in retrieving instruction, kill ant
                        setDead();
                        return ;
                    }
                }
            
            
            
        }

         
        
        
    }
}
