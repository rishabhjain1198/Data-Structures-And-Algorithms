void listAll(const MenuItem* m, string path) // two-parameter overload
{
    //You will write this code.
    if(m->name() != "")
    {
        path += m -> name();
        cout<<path<<endl;
        path+="/";
    }
    
    if(m->menuItems() != NULL)
    {
        vector<MenuItem*>::const_iterator it = m->menuItems()->begin();
        while(it != m->menuItems()->end())
        {
            listAll(*it, path);
            it++;
        }
    }
}
