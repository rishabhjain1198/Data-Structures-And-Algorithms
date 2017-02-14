//
//  Sequence.h
//  Project2
//
//  Created by Rishabh Jain on 1/27/17.
//  Copyright © 2017 Rishabh Jain. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include "OurType.h"

typedef OurType ItemType;

struct Node
{
    ItemType value;
    Node *next;
    Node *prev;
};

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence &src);
    Sequence & operator = (const Sequence &src);
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    Node *first;
    int seqSize;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, const Sequence& result);

#endif /* Sequence_h */
