//
//  player.h
//  project1
//
//  Created by Rishabh Jain on 1/12/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#ifndef player_h
#define player_h


class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    std::string dropPoisonPellet();
    std::string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* player_h */
