//
//  main.cpp
//  hw3
//
//  Created by Rishabh Jain on 2/13/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

class File
{
private:
    string m_name;
    bool isVid;
    bool isTxt;

    
public:
    File(std::string name) : m_name(name)
    {}
    virtual ~File()
    {
    }
    virtual string name() const
    {
        return m_name;
    }
    
    virtual void open() const = 0;
    
    virtual void redisplay() const = 0;
};



class TextMsg : public File
{
public:
    TextMsg(string namez) : File(namez){}
    virtual ~TextMsg()
    {
        cout<<"Destroying "<<name()<<", a text message"<<endl;
    }
    virtual void open() const
    {
        cout<<"open text message";
    }
    virtual void redisplay() const
    {
        cout<<"refresh the screen";
    }
};



class Video : public File
{
public:
    Video(string namez, int timez) : File(namez), m_time(timez)
    {
        
    }
    int time() const
    {
        return m_time;
    }
    virtual ~Video()
    {
        cout<<"Destroying "<<name()<<", a video"<<endl;
    }
    virtual void open() const
    {
        cout<<"play "<<time()<<" second video";
    }
    virtual void redisplay() const
    {
        cout<<"replay video";
    }
private:
    int m_time;
    
};



class Picture : public File
{
public:
    
    Picture(string namez) : File(namez){}
    
    virtual ~Picture()
    {
        cout<<"Destroying the pitcure "<<name()<<endl;
    }
    virtual void open() const
    {
        cout<<"show picture";
    }
    virtual void redisplay() const
    {
        cout<<"refresh the screen";
    }
    
};

