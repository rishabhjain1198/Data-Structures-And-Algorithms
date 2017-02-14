class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = 'v';
    
    bool t;
    
    //NORTH
    if(maze[sr-1][sc] == '.')
    {
        t = pathExists(maze, nRows, nCols, sr-1, sc, er, ec);
        if(t)
            return true;
    }
    
    //SOUTH
    if(maze[sr+1][sc] == '.')
    {
        t= pathExists(maze, nRows, nCols, sr+1, sc, er, ec);
        if(t)
            return true;
    }
    
    //EAST
    if(maze[sr][sc+1] == '.')
    {
        t = pathExists(maze, nRows, nCols, sr, sc+1, er, ec);
        if(t)
            return true;
    }
    
    //WEST
    if(maze[sr][sc-1] == '.')
    {
        t = pathExists(maze, nRows, nCols, sr, sc-1, er, ec);
        if(t)
            return true;
    }
    
    
    return false;
}
