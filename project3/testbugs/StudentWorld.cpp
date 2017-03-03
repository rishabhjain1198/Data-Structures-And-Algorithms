#include "StudentWorld.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir)
{
    for(int i = 0; i < VIEW_WIDTH; i++)     //go through every cell of the data structure and empty it
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {
            for(int k = 0; k < NUM_OBJECTS; k++)
            {
                field[i][j][k].clear();
            }
        }
    }
    
    for(int i = 0; i < 4; i++)          //initialize the ant produced array to 0
        antProduced[i] = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();              //simply let the cleanUp function do the destructor's work
}

int StudentWorld::init()
{
    tickCounter = 2000;         //start the tick counter from 2000
    string fieldFileName;
    Field f;
    
    std::string fieldFile = getFieldFilename();
    
    if(f.loadField(fieldFile) != Field::LoadResult::load_success)
        return false;    //failed to load field
    
    //loading field was successful
    //time to get the contents of the field and start putting pebbles and grasshoppers
    
    Compiler *compilerForEntrant0, *compilerForEntrant1,
    *compilerForEntrant2, *compilerForEntrant3;
    
    compiledCorrectly[0] = false;       //this array keeps track of how many anthills should be created
    compiledCorrectly[1] = false;
    compiledCorrectly[2] = false;
    compiledCorrectly[3] = false;
    
    //Actor *ah0, *ah1, *ah2, *ah3;
    
    // get the names of all of the ant program source files
    // we provide the getFilenamesOfAntPrograms() function for
    // you in our GameWorld class.
    
    fileNames = getFilenamesOfAntPrograms();        //this keeps the names of the filenames
    
    // compile the source file... If the compile function returns // false, there was a syntax error during compilation!
    int i = 0;

    if(fileNames.size() > i){

        compilerForEntrant0 = new Compiler;
        std::string error0;
    if ( ! compilerForEntrant0 -> compile(fileNames[0], error0) )
    {
       // cout<<fileNames[0]<<endl;
         //       cout<<"hello "<<error0<<endl;
        // entrant 0’s source code had a syntax error!
        // send this error to our framework to warn the user. // do it JUST like this!
        setError(fileNames[0] + " " + error0);
        // return an error to tell our simulation framework
        // that something went wrong, and it’ll inform the user return GWSTATUS_LEVEL_ERROR;
    }
    else
        compiledCorrectly[0] = true;
        
        i++;
    }
    
    if(fileNames.size() > i) {
    
    compilerForEntrant1 = new Compiler;
    std::string error1;
    
    if ( ! compilerForEntrant1->compile(fileNames[1], error1) )
    {
        // entrant 0’s source code had a syntax error!
        // send this error to our framework to warn the user. // do it JUST like this!
        setError(fileNames[1] + " " + error1);
        // return an error to tell our simulation framework
        // that something went wrong, and it’ll inform the user return GWSTATUS_LEVEL_ERROR;
    }
    else
        compiledCorrectly[1] = true;
        
        i++;
    }
    
    if(fileNames.size() > i) {
    
    compilerForEntrant2 = new Compiler;
    std::string error2;
    
    if ( ! compilerForEntrant2->compile(fileNames[2], error2) )
    {
        // entrant 0’s source code had a syntax error!
        // send this error to our framework to warn the user. // do it JUST like this!
        setError(fileNames[2] + " " + error2);
        // return an error to tell our simulation framework
        // that something went wrong, and it’ll inform the user return GWSTATUS_LEVEL_ERROR;
    }
    else
        compiledCorrectly[2] = true;
        i++;
    
    }
    
    if(fileNames.size() > i) {
    compilerForEntrant3 = new Compiler;
    std::string error3;
    
    if ( ! compilerForEntrant3->compile(fileNames[3], error3) )
    {
        // entrant 0’s source code had a syntax error!
        // send this error to our framework to warn the user. // do it JUST like this!
        setError(fileNames[3] + " " + error3);
        // return an error to tell our simulation framework
        // that something went wrong, and it’ll inform the user return GWSTATUS_LEVEL_ERROR;
    }
    else
        compiledCorrectly[3] = true;
        
        i++;
    }
    
    for(int i = 0; i < fileNames.size(); i++)   //store filenames in new vector
    {
        string colonyName ="";
        switch(i)
        {
            case 0:
                colonyName = compilerForEntrant0 -> getColonyName();
                break;
            case 1:
                colonyName = compilerForEntrant1 -> getColonyName();
                break;
            case 2:
                colonyName = compilerForEntrant2 -> getColonyName();
                break;
            case 3:
                colonyName = compilerForEntrant3 -> getColonyName();
                break;
        }
        newFileNames.push_back(colonyName);
    }
    // otherwise, the entrant’s file compiled correctly!
    // now allocate our first anthill object and make sure it has
    // a pointer to the Compiler object for ant type #0,
    // so it can determine what set of instructions to use to control // ants in colony #0.
    // You have to figure out what to put for ... in the line below. ah0 = new AntHill(..., compilerForEntrant0);
    // now add our new anthill object to our simulation data
    // structure so it can be tracked and asked to do something by // our virtual world during each tick of the simulation addObjectToSimulation(ah0);
    // now do the same thing for anthills 1, 2 and 3, assuming there // is more than one competitor ant. The user may just want to // test out her one ant without any competitors, in which case // there would just be one ant (or two, or three).
    
    for(int i = 0; i < VIEW_WIDTH; i++)
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {

            field[i][j][ANTHILL_INDEX].clear();
            Field::FieldItem item = f.getContentsOf(i, j);
            if(item == Field::FieldItem::rock)
            {
                //pebble found.
                Actor* temp = new Pebble(this, i, j);
                field[i][j][PEBBLE_INDEX].push_back(temp);
            }
            else if(item == Field::FieldItem::grasshopper)
            {
                //baby grasshopper found.
                Actor* temp = new BabyGrasshopper(this, i, j);
                field[i][j][BBYGRASS_INDEX].push_back(temp);
            }
            else if(item == Field::FieldItem::food)
            {
                //food item found
                Actor* temp = new Food(this, i, j);
                field[i][j][FOOD_INDEX].push_back(temp);
            }
            else if(item == Field::FieldItem::poison)
            {
                //poison item found
                Actor* temp = new Poison(this, i, j);
                field[i][j][POISON_INDEX].push_back(temp);
            }
            else if(item == Field::FieldItem::water)
            {
                //pool of water item found
                Actor* temp = new PoolOfWater(this, i, j);
                field[i][j][POOL_OF_WATER_INDEX].push_back(temp);
            }
            else if(item == Field::FieldItem::anthill0 && fileNames.size() > 0 && compiledCorrectly[0] == true)
            {
                //anthill found
                //cout<<" FOUND 0"<<endl;
                Actor* ah0 = new Anthill(this, i, j, 0, compilerForEntrant0);
                field[i][j][ANTHILL_INDEX].push_back(ah0);
            }
            else if(item == Field::FieldItem::anthill1 && fileNames.size() > 1 && compiledCorrectly[1] == true)
            {
                //anthill found
                //cout<<" FOUND 1"<<endl;
                Actor* ah1 = new Anthill(this, i, j, 1, compilerForEntrant1);
                field[i][j][ANTHILL_INDEX].push_back(ah1);
            }
            else if(item == Field::FieldItem::anthill2 && fileNames.size() > 2 && compiledCorrectly[2] == true)
            {
                //anthill found
                //cout<<" FOUND 2"<<endl;
               Actor* ah2 = new Anthill(this, i, j, 2, compilerForEntrant2);
                field[i][j][ANTHILL_INDEX].push_back(ah2);
            }
            else if(item == Field::FieldItem::anthill3 && fileNames.size() > 3 && compiledCorrectly[3] == true)
            {
                //anthill found
                //cout<<" FOUND 3"<<endl;
                Actor* ah3 = new Anthill(this, i, j, 3, compilerForEntrant3);
                field[i][j][ANTHILL_INDEX].push_back(ah3);
            }
        }
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter.
		  // Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.
    
    tickCounter--;      // a tick has passed
    
    if(tickCounter <= 0)
    {
        //END GAME
        if(newFileNames.size() == 0)        //if no ants were playing, there was no winner
            return GWSTATUS_NO_WINNER;
        setWinner(newFileNames[winningAnt]);    //check who the winner was
        return GWSTATUS_PLAYER_WON;
    }
    
    for(int i = 0; i < 4; i++)
        if(antProduced[winningAnt] < antProduced[i])        //update winning ant
            winningAnt = i;
    
    updateDisplayText();            //update game text
    
    //DOING SOMETHING FOR EVERY SINGLE OBJECT IN THE FIELD
    
    for(int i = 0; i < VIEW_WIDTH; i++)
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {
            for(int k = 0; k <= NUM_OBJECTS; k++)
            {
                for(int z = 0; z < field[i][j][k].size(); z++)
                {
                    field[i][j][k][z] -> doSomething();
                    
                    
                    
                 
                    
                    
                }
            }
        }
    }
    
    
    //CHECK IF STUFF MOVED
    
    for(int i = 0; i < VIEW_WIDTH; i++)
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {
            for(int k = 1; k <= LAST_ALIVE_INDEX; k++)
            {
                for(int z = 0; z < field[i][j][k].size(); z++)
                {
                    int newX = field[i][j][k][z] -> getX();
                    int newY = field[i][j][k][z] -> getY();
                    if(newX != i || newY != j)
                    {
                        //stuff has moved
                        Actor* temp = field[i][j][k][z];
                        field[i][j][k].erase(field[i][j][k].begin()+z);
                        field[newX][newY][k].push_back(temp);
                    }
                    
                }
            }
        }
    }
    
    //check if stuff died
    for(int i = 0; i < VIEW_WIDTH; i++)
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {
            for(int k = 1; k <= NUM_OBJECTS; k++)
            {
                for(int z = 0; z < field[i][j][k].size(); z++)
                {
                    if(field[i][j][k][z] -> isDead() ){
                        Actor* temp = field[i][j][k][z];
                        delete temp;
                        field[i][j][k].erase(field[i][j][k].begin() + z);
                        
                    }
                    
                }
            }
        }
    }
    
    
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::updateDisplayText()
{
    int i = 0;
    string s = "Ticks: ";
    s += to_string(tickCounter);
    s += " - ";
    
   // std::cout<<fileNames.size()<<std::endl;
    
    //for every ant, add something to the string to be made the game text at top
    
    if(newFileNames.size() > i){
    s += newFileNames[0];
    if(winningAnt == 0) s += "*";
    s += ": ";
    if(antProduced[0] <= 9) s+= "0";
    s += to_string(antProduced[0]);
    s += " ants ";
        i++;
    }
    
    if(newFileNames.size() > i)
    {
    s += newFileNames[1];
    if(winningAnt == 1) s += "*";
    s += ": ";
        if(antProduced[1] <= 9) s+= "0";
    s += to_string(antProduced[1]);
    s += " ants ";
            i++;
    }
    
    if(newFileNames.size() > i)
    {
    s += newFileNames[2];
    if(winningAnt == 2) s += "*";
    s += ": ";
        if(antProduced[2] <= 9) s+= "0";
    s += to_string(antProduced[2]);
    s += " ants ";
        i++;
    }
    
    if(newFileNames.size() > i)
    {
    s += newFileNames[3];
    if(winningAnt == 3) s += "*";
    s += ": ";
        if(antProduced[3] <= 9) s+= "0";
    s += to_string(antProduced[3]);
    s += " ants ";
        i++;
    }
    
    setGameStatText(s);
}

void StudentWorld::cleanUp()
{
    //delete every single object
    for(int i = 0; i < VIEW_WIDTH; i++)
    {
        for(int j = 0; j < VIEW_HEIGHT; j++)
        {
            for(int k = 0; k < NUM_OBJECTS; k++)
            {
                for(int z = 0; z < field[i][j][k].size(); z++)
                {
                    delete field[i][j][k][z];
                }
                field[i][j][k].clear();
            }
        }
    }
}

void StudentWorld::addFood(int x, int y, int foodAmount, StudentWorld* myWorld)
{
    
    if(!field[x][y][FOOD_INDEX].empty())    //if there already was food
    {
        if(field[x][y][FOOD_INDEX][0] -> health() < 0)  //if that food was dead, make it alive
        {
            field[x][y][FOOD_INDEX][0] -> setHealth(0);
            field[x][y][FOOD_INDEX][0] -> notDeadAnymore();
        }
   
        field[x][y][FOOD_INDEX][0] -> setHealth(field[x][y][FOOD_INDEX][0]->health()+foodAmount);
        //sets the food amount of that food to new food amount
    }
    else            //new food must be created
    {
        Food* temp = new Food(myWorld, x, y);
        temp -> setHealth(foodAmount);
        field[x][y][FOOD_INDEX].push_back(temp);
    }
    
}

void StudentWorld::createAdultGrasshopper(int x, int y, StudentWorld* myWorld)
{
    AdultGrasshopper* temp = new AdultGrasshopper(myWorld, x, y);
    field[x][y][ADUGRASS_INDEX].push_back(temp);
}

bool StudentWorld::isPebble(int x, int y)
{
    if(field[x][y][PEBBLE_INDEX].empty())       //no pebbles on this spot, return false
        return false;
    return true;                //pebble found, return true
}

bool StudentWorld::isAlive(int x, int y)
{
    for(int i = 1; i <= LAST_ALIVE_INDEX; i++)
    {
        if(!field[x][y][i].empty())     //if something alive was found, return true
            return true;
    }
    return false;
}

bool StudentWorld::biteSomething(int x, int y, int bitingPower, Actor* biter)
{
    
    //check if something biteable is there, if yes, try to bite it
    if(!field[x][y][1].empty() || !field[x][y][2].empty() || !field[x][y][3].empty())
    {
        //something is there. Bite it. Randomly.
        int i = randInt(1,LAST_ALIVE_INDEX-1);
        
        for(int j = 1; j <= LAST_ALIVE_INDEX; j++)
        {
            if(i!=0){
            if(!field[x][y][i].empty())
            {
                //BITE THIS
                if(field[x][y][i][0] != biter)
                {
                    field[x][y][i][0] -> isBitten(bitingPower, x, y);
                    return true;
                }
                else if(1 < field[x][y][i].size())
                {
                    field[x][y][i][1] -> isBitten(bitingPower, x, y);
                    return true;
                }
            }
            else
            {
                if(i == LAST_ALIVE_INDEX-1)     //this is here to switch i to values from 0 to LAST_ALIVE_INDEX
                    i = LAST_ALIVE_INDEX;
                else
                    i = (i+1)%LAST_ALIVE_INDEX;
            }
            }
            else
                i = 1;
        }
        
        return true;
    }
    
    return false;
    
}

bool StudentWorld::isFood(int x, int y)
{
    if(!field[x][y][FOOD_INDEX].empty()){       //if food of more than 0 health was found, return true
        if(field[x][y][FOOD_INDEX][0] -> health() > 0)
            return true;
        else
            field[x][y][FOOD_INDEX][0] -> setDead();
    }
    
    return false;
}

int StudentWorld::eatFood(int x, int y, int eatingAttempt)
{
    int foodAmount = field[x][y][FOOD_INDEX][0] -> health();
    field[x][y][FOOD_INDEX][0] -> setHealth(foodAmount - eatingAttempt);
    
    if(foodAmount <= eatingAttempt)
    {
        //food needs to die
        field[x][y][FOOD_INDEX][0] -> setDead();
        //std::cout<<" mar gaya "<<std::endl;
        return foodAmount;
    }
    
    return eatingAttempt;
}


void StudentWorld::stunThem(int x, int y, int stunValue)
{
    for(int i = 0; i < field[x][y][BBYGRASS_INDEX].size(); i++)     //check if actor had been stunned before by pool. Stun the actor by the passed stun value
    {
        if(field[x][y][BBYGRASS_INDEX][i] -> poolSleeping() ==  false){
            field[x][y][BBYGRASS_INDEX][i] -> sleeping(stunValue);
            field[x][y][BBYGRASS_INDEX][i] -> poolSleeping(true);
        }
    }
    
    for(int i = 0; i < field[x][y][ANT_INDEX].size(); i++)
    {
        if(field[x][y][ANT_INDEX][i] -> poolSleeping() ==  false){
            field[x][y][ANT_INDEX][i] -> sleeping(stunValue);
            field[x][y][ANT_INDEX][i] -> poolSleeping(true);
        }
    }
    
}

void StudentWorld::poisonThem(int x, int y, int poisonValue)
{
    for(int i = 0; i < field[x][y][BBYGRASS_INDEX].size(); i++)
    {
        field[x][y][BBYGRASS_INDEX][i] -> setHealth(field[x][y][BBYGRASS_INDEX][i] -> health() - poisonValue);      //reduce health by poison
    }
    
    for(int i = 0; i < field[x][y][ANT_INDEX].size(); i++)
    {
        field[x][y][ANT_INDEX][i] -> setHealth(field[x][y][ANT_INDEX][i] -> health() - poisonValue);        //reduce health by poison
    }
}

void StudentWorld::createAnt(int x, int y, Actor* temp, int colony)
{
    field[x][y][ANT_INDEX].push_back(temp);
    antProduced[colony]++;  //another ant made by a colony
}

void StudentWorld::createPheromone(int x, int y, int colony)
{
    int idd = IID_PHEROMONE_TYPE0;
    
    switch(colony)          //need to set id of pheromone according to colony
    {
        case 1: idd = IID_PHEROMONE_TYPE1; break;
        case 2: idd = IID_PHEROMONE_TYPE2; break;
        case 3: idd = IID_PHEROMONE_TYPE3; break;
    }
    
    bool alreadyExist = false;
    int j = 0;
    
    for(int i = 0; i < field[x][y][PHEROMONE_INDEX].size(); i++)       //check if pheromone
    {                               //of the same colony already exists
        if(field[x][y][PHEROMONE_INDEX][i] -> id() == colony)
        {
            alreadyExist = true;
            j = i;
            break;
        }
    }
    
    if(alreadyExist == false)   
    {
        Actor* temp = new Pheromone(idd, this, x, y, colony);
        field[x][y][PHEROMONE_INDEX].push_back(temp);
    }
    else
    {
        field[x][y][PHEROMONE_INDEX][j] -> setHealth(field[x][y][PHEROMONE_INDEX][j] -> health() + 256);
        if(field[x][y][PHEROMONE_INDEX][j] -> health() >= 768)  //if new health exceeds 768,
            field[x][y][PHEROMONE_INDEX][j] -> setHealth(768);  //set it to 768
    }
}

bool StudentWorld::checkCompilation(int idd)
{
    return compiledCorrectly[idd];          //tell if compilation of instructions was successful
}

bool StudentWorld::isEnemy(int x, int y, int colony)
{
    if(!field[x][y][BBYGRASS_INDEX].empty())       //if bby grasshopper is here, return true
        return true;
    
    if(!field[x][y][ADUGRASS_INDEX].empty())        //if adult grasshopper is here, return true
        return true;
    
    for(int i = 0; i < field[x][y][ANT_INDEX].size(); i++)
    {
        if(field[x][y][ANT_INDEX][i] -> id() != colony)
            return true;                    //if ant of different colony is here, return true
    }
    
    return false;
}

bool StudentWorld::isMyAnthill(int x, int y, int colony)
{
    if(!field[x][y][ANTHILL_INDEX].empty()){        //if ant is standing on your colony, return true
    if(field[x][y][ANTHILL_INDEX][0] -> id() == colony)
        return true;
    }
    return false;
}

bool StudentWorld::isPheromone(int x, int y)
{
    for(int i = 0; i < field[x][y][PHEROMONE_INDEX].size(); i++)
    {
        if(field[x][y][PHEROMONE_INDEX][i] -> health() > 0)     //if pheromone of more than 0 health is there, return true
            return true;
    }
    
    return false;
}
