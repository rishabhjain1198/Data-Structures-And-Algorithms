//
//  Sequence.cpp
//  Project2
//
//  Created by Rishabh Jain on 1/27/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#include "Sequence.h"
#include<iostream>
#include<cassert>

using namespace std;

Sequence::Sequence()
{
    first = nullptr;	//setting list as empty
    seqSize = 0;
}

Sequence::~Sequence()
{
    Node *temp = first;	//temporary pointer towards head of list made, which is then moved forward and each node is deleted one by one
    
    while(temp != nullptr)
    {
        Node *temp2 = temp;
        temp = temp -> next;
        delete temp2;
    }
}

Sequence::Sequence(const Sequence &src)
{
    for(int i = 0; i < src.size(); i++)
    {
        ItemType val;		//looping through every value in source list, and inserting each value one by one into destination list
        src.get(i, val);
        insert(i, val);
    }
}

Sequence & Sequence::operator = (const Sequence &src)
{
    while(size() != 0)
    {
        erase(0);		//first we have to remove pre-existing contents of the destination list
    }
    
    for(int i = 0; i < src.size(); i++)
    {
        ItemType val;       //now we do exactly what we did for assignment operator
        src.get(i, val);
        insert(i, val);
    }
    
    return *this;
}

bool Sequence::empty() const
{
    if(seqSize == 0)        //if size of list is 0, it is empty
        return true;
    
    return false;
}

int Sequence::size() const
{
    return seqSize;         //returns size of list
}

bool Sequence::insert(int pos, const ItemType &value)
{
    if(pos < 0 || pos > seqSize)
        return false;       //stop function if pos is invalid
    
    if(first == nullptr)
    {
        first = new Node;           //if the first node is being inserted, we need to take special care
        first -> prev = nullptr;
        first -> next = nullptr;
        first -> value = value;
    }
    else
    {
        Node *temp = first;         //now we loop through the list until we get to the desired pos. Every time we go a step forward, we remember the node we leave behind
        Node *peeche = nullptr;
        int i = 0;
        while(i != pos)
        {
            peeche = temp;
            temp = temp -> next;
            i++;
        }
        
        //The new node is to be inserted between temp and peeche
        if(temp == nullptr)     //special case of node being at the end of the list
        {
            temp = new Node;
            temp -> prev = peeche;
            temp -> next = nullptr;
            temp -> value = value;
            
            if(peeche != nullptr)
                peeche -> next = temp;
        }
        
        else {      //if node is to be inserted anywhere else in the list
            Node *newvalue = new Node;
            newvalue->next = temp;
            newvalue -> prev = peeche;
            newvalue -> value = value;
            
            if(temp == first)
                first = newvalue;
        
            if(peeche != nullptr)
                peeche -> next = newvalue;
        
            if(temp != nullptr)
                temp -> prev = newvalue;
        }
    }
    
    seqSize++;          //increase size of list by 1
    
    return true;
}

int Sequence::insert(const ItemType &value)
{
    int i = 0;
 
    if(first == nullptr)        //if first node is being inserted, special care has to be taken
    {
        first = new Node;
        first -> prev = nullptr;
        first -> next = nullptr;
        first -> value = value;
    }
    else
    {
        Node *temp = first;
        Node *peeche = nullptr;
        
        while(true)         //now we loop through the list until we get to the desired value. We make sure to remember the node when we leave it behind (in peeche)
        {
            if(temp == nullptr)
                break;
            
            if(value <= temp -> value)
                break;
            
            peeche = temp;
            temp = temp -> next;
            
            i++;
        }
        
        //The new node is to be inserted between temp and peeche
        
        if(temp == nullptr)     //the rest of the implementation is exactly like that of the Boolean insert function
        {
            temp = new Node;
            temp -> prev = peeche;
            temp -> next = nullptr;
            temp -> value = value;
            
            if(peeche != nullptr)
                peeche -> next = temp;
        }
        
        else {
            Node *newvalue = new Node;
            newvalue->next = temp;
            newvalue -> prev = peeche;
            newvalue -> value = value;
            
            if(temp == first)
                first = newvalue;
            
            if(peeche != nullptr)
                peeche -> next = newvalue;
            
            if(temp != nullptr)
                temp -> prev = newvalue;
        }
        
    }
    
    
    
    
    seqSize++;
    return i;
}

bool Sequence::erase(int pos)
{
    if(pos < 0 || pos >= seqSize)       //if pos is invalid, function is immediately stopped
        return false;
    
    int i = 0;
    
    Node *temp = first;
    Node *peeche = nullptr;
    
    while(i != pos)     //we loop through the list to find the desired pos
    {
        peeche = temp;
        temp = temp -> next;
        i++;
    }
    
    Node *aage = temp -> next;
    
    //temp is now the node to be deleted, peeche is node before it, and aage is the node right after it
    
    if(temp == first)
    {
        delete first;
        first = aage;
    }
    
    else
    {
        delete temp;
    
        if(peeche != nullptr)
            peeche -> next = aage;
    
        if(aage != nullptr)
            aage -> prev = peeche;
    }
    
    seqSize--;          //reduce size by 1
    return true;
}

int Sequence::remove(const ItemType &value)
{
    if(first == nullptr)
        return 0;
    int counter = 0;
    Node *temp = first;
    Node *peeche = nullptr;
    
    while(temp != nullptr)      //very similar implementation when compared to erase, the difference being the node removal code is executed every time a particular value is found, rather than on a particular position
    {
        if(temp -> value == value)
        {
            Node *temp2 = temp;
            temp = temp -> next;
            
            if(temp2 == first)
            {
                delete first;
                first = temp;
            }
            else
            {
                delete temp2;
                if(temp != nullptr)
                    temp -> prev = peeche;
                if(peeche != nullptr)
                    peeche -> next = temp;
            }
            
            counter++;          //to keep track of how many nodes have been removed
            seqSize--;
            
        }
        else
        {
            peeche = temp;
            temp = temp -> next;
        }
    }

    return counter;
}

bool Sequence::get(int pos, ItemType &value) const
{
    if(pos < 0 || pos >= seqSize)
        return false;
    
    int i = 0;
    Node *temp = first;
    
    while(i!=pos)       //loop through to the desired position
    {
        temp = temp -> next;
        i++;
    }
    
    value = temp->value;        //store desired value in the variable
        
    
    return true;
}

bool Sequence::set(int pos, const ItemType &value)
{
    if(pos < 0 || pos >= seqSize)
        return false;
    
    int i = 0;
    Node * temp = first;
    while(i!=pos)           //loop through to the desired position
    {
        temp = temp -> next;
        i++;
    }
    
    temp -> value = value;      //store desired value in the node
    
    return true;
}

int Sequence::find(const ItemType &value) const
{
    int p = -1;
    int i = 0;
    
    Node *temp = first;
    
    while(temp != nullptr)          //loop through until end of list or until you find the desired value
    {
        if(temp -> value == value)
        {
            p = i;      //if desired value is found, set p equal to the position of that node
            break;
        }
        i++;
        temp = temp -> next;
    }
    
    return p;
}

void Sequence::swap(Sequence &other)
{
    Node *temp = first;     //exchange the head nodes of the two sequences and their sizes
    first = other.first;
    other.first = temp;
    int tempSize = seqSize;
    seqSize = other.seqSize;
    other.seqSize = tempSize;
}

void Sequence::dump() const
{
    Node *temp = first;         //simply loop through the list and output every single value
    while(temp != nullptr)
    {
        cerr<<temp -> value<<endl;
        temp = temp-> next;
    }
    cerr<<endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.size() == 0)        //if seq2 is empty, stop function
        return -1;
    
    for(int i = 0; i < seq1.size(); i++)
    {
        for(int j = 0; j < seq2.size(); j++)    //for every node in seq1, loop through all nodes in seq2, as long as we find equal relative values
        {
            if(i+j < seq1.size())       //to make sure we dont go out of bounds
            {
                ItemType temp1;
                ItemType temp2;
                seq1.get(i+j, temp1);
                seq2.get(j, temp2);
                if(temp1 == temp2)
                {
                    if(j == seq2.size() - 1)
                    {
                        return i;       //last node of seq2 has found a match, return the position of the node of seq1
                    }
                }               //desired value not found, no point on continuing on this particular node of seq1
                else
                    break;
            }               //we will definitely go out of bounds if we would have continued, so top acting on this particular node of seq1
            else
                break;
        }
    }
    
    return -1;          //no match was found
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp;      //this is where the result of interleaving will be temporarily stored, to avoid problems in aliasing
    int i = 0;
    int j = 0;
    while(i < seq1.size() && i < seq2.size())       //loop through the sequences until either of them ends
    {
        ItemType val1;
        ItemType val2;
        seq1.get(i, val1);
        seq2.get(i, val2);
                                //get 1 value from each list, and insert them into the temporary list one by one
        temp.insert(j, val1);
        j++;
        temp.insert(j, val2);
        j++;
        
        i++;
    }
    
    while(i < seq1.size())      //in case seq2 ran out first, insert the rest of the elements of seq1 into temp
    {
        ItemType val1;
        seq1.get(i, val1);
        
        temp.insert(j, val1);
        j++;
        i++;
    }
    
    while(i < seq2.size())      //in case seq1 ran out first, insert the rest of the elements of seq2 into temp
    {
        ItemType val2;
        seq2.get(i, val2);
        
        temp.insert(j, val2);
        j++;
        i++;
    }
    
    result = temp;          //copy the sequence into the desired location
}

int main()
{
                            //abstract test cases
    Sequence t;
    Sequence q;
    t.insert("hello");
    t.insert("yolo");
    t.insert(2, "potaf");
    t.remove("hello");
    q.insert("this");
    q.insert("haiehq");
   
    t.swap(q);
    
    t.dump();

    q.dump();
    
    Sequence fina;
    
    interleave(t, q, fina);
    
    Sequence test;
    test.insert(0, "this");
    test.insert(1, "potaf");
    
    cerr<<subsequence(fina, test)<<endl;
    
    fina.dump();
  
}
