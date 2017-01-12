//
//  history.cpp
//  project1
//
//  Created by Rishabh Jain on 1/12/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#include <iostream>
#include "History.h"



////HISTORY IMPLEMENTATION////

History::History(int nRows, int nCols)
{
    m_history_rows = nRows;
    m_history_cols = nCols;
    
    for (int r = 1; r <= m_history_rows; r++)
        for (int c = 1; c <= m_history_cols; c++)
            m_history_grid[r-1][c-1] = 0;
    
}

bool History::record(int r, int c)
{
    if(r<1 || c<1 || r>m_history_rows || c>m_history_cols)
        return false;
    
    m_history_grid[r-1][c-1]++;
    
    return true;
}

void History::display() const
{
    clearScreen();
    
    for(int r = 0; r <m_history_rows; r++)
    {
        for(int c = 0; c < m_history_cols; c++)
        {
            if(m_history_grid[r][c] == 0)
                std::cout<<".";
            else
                std::cout<<char(m_history_grid[r][c]+64);
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

