//
//  Sequence.cpp
//  Project2
//
//  Created by Rishabh Jain on 1/27/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#include "Sequence.h"
#include<iostream>

Sequence::Sequence()
{
    first = nullptr;
    seqSize = 0;
}

Sequence::~Sequence()
{
    Node *temp = first;
    
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
        ItemType val;
        src.get(i, val);
        insert(i, val);
    }
}

Sequence & Sequence::operator = (const Sequence &src)
{
    while(size() != 0)
    {
        erase(0);
    }
    
    for(int i = 0; i < src.size(); i++)
    {
        ItemType val;
        src.get(i, val);
        insert(i, val);
    }
    
    return *this;
}

bool Sequence::empty() const
{
    if(seqSize == 0)
        return true;
    
    return false;
}

int Sequence::size() const
{
    return seqSize;
}

bool Sequence::insert(int pos, const ItemType &value)
{
    if(pos < 0 || pos > seqSize)
        return false;
    
    if(first == nullptr)
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
        int i = 0;
        while(i != pos)
        {
            peeche = temp;
            temp = temp -> next;
            i++;
        }
        
        //The new node is to be inserted between temp and peeche
        if(temp == nullptr)
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
    
    return true;
}

int Sequence::insert(const ItemType &value)
{
    int i = 0;
 
    if(first == nullptr)
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
        
        while(true)
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
        
        if(temp == nullptr)
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
    if(pos < 0 || pos >= seqSize)
        return false;
    
    int i = 0;
    
    Node *temp = first;
    Node *peeche = nullptr;
    
    while(i != pos)
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
    
    seqSize--;
    return true;
}

int Sequence::remove(const ItemType &value)
{
    if(first == nullptr)
        return 0;
    int counter = 0;
    Node *temp = first;
    Node *peeche = nullptr;
    
    while(temp != nullptr)
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
            
            counter++;
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
    
    while(i!=pos)
    {
        temp = temp -> next;
        i++;
    }
    
    value = temp->value;
        
    
    return true;
}

bool Sequence::set(int pos, const ItemType &value)
{
    if(pos < 0 || pos >= seqSize)
        return false;
    
    int i = 0;
    Node * temp = first;
    while(i!=pos)
    {
        temp = temp -> next;
        i++;
    }
    
    temp -> value = value;
    
    return true;
}

int Sequence::find(const ItemType &value) const
{
    int p = -1;
    int i = 0;
    
    Node *temp = first;
    
    while(temp != nullptr)
    {
        if(temp -> value == value)
        {
            p = i;
            break;
        }
        i++;
        temp = temp -> next;
    }
    
    return p;
}

void Sequence::swap(Sequence &other)
{
    Node *temp = first;
    first = other.first;
    other.first = temp;
    int tempSize = seqSize;
    seqSize = other.seqSize;
    other.seqSize = tempSize;
}

void Sequence::dump() const
{
    Node *temp = first;
    while(temp != nullptr)
    {
        std::cerr<<temp -> value<<std::endl;
        temp = temp-> next;
    }
    std::cerr<<std::endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.size() == 0)
        return -1;
    
    for(int i = 0; i < seq1.size(); i++)
    {
        for(int j = 0; j < seq2.size(); j++)
        {
            if(i+j < seq1.size())
            {
                ItemType temp1;
                ItemType temp2;
                seq1.get(i+j, temp1);
                seq2.get(j, temp2);
                if(temp1 == temp2)
                {
                    if(j == seq2.size() - 1)
                    {
                        return i;
                    }
                }
                else
                    break;
            }
            else
                break;
        }
    }
    
    return -1;
    
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp;
    int i = 0;
    int j = 0;
    while(i < seq1.size() && i < seq2.size())
    {
        ItemType val1;
        ItemType val2;
        seq1.get(i, val1);
        seq2.get(i, val2);
        
        temp.insert(j, val1);
        j++;
        temp.insert(j, val2);
        j++;
        
        i++;
    }
    
    while(i < seq1.size())
    {
        ItemType val1;
        seq1.get(i, val1);
        
        temp.insert(j, val1);
        j++;
        i++;
    }
    
    while(i < seq2.size())
    {
        ItemType val2;
        seq2.get(i, val2);
        
        temp.insert(j, val2);
        j++;
        i++;
    }
    
    result = temp;
}

int main()
{
    Sequence s;
    Sequence q;
    s.insert("hello");
    s.insert("yolo");
    s.insert(2, "potaf");
    s.remove("hello");
    q.insert("this");
    q.insert("haiehq");
   
    s.swap(q);
    s.dump();

    q.dump();
    
    Sequence fina;
    
    interleave(s, q, fina);
    
    Sequence test;
    test.insert(0, "this");
    test.insert(1, "potaf");
    
    std::cerr<<subsequence(fina, test)<<std::endl;
  
    fina.dump();
}
