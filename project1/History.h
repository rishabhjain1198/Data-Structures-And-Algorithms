//
//  history.h
//  project1
//
//  Created by Rishabh Jain on 1/12/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#ifndef history_h
#define history_h

#include "globals.h"

/////HISTORY DECLARATION//////

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_history_grid[MAXROWS][MAXCOLS];
    int m_history_rows;
    int m_history_cols;
};



#endif /* history_h */
