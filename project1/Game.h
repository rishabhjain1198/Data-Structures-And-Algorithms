//
//  game.h
//  project1
//
//  Created by Rishabh Jain on 1/12/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#ifndef game_h
#define game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};

#endif /* game_h */
