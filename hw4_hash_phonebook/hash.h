#ifndef _hash_H
#define _hash_H
#include "avl.h"
#include<string>
#include<vector>
using namespace std;



//tansylu akhmetova 09/05/2023

template <class itemType>
class Hash {
private:
    int size = 0;
   
    void rehash();
    void rehash_helper(itemType* place, vector<AVL<itemType>>& temp);
    vector<AVL<itemType>> my_table = {};
    long calc_position(char* name, int s);

public:
    Hash() {
        size = 53;
        my_table = vector<AVL<itemType>>(size);
    };
    double count = 0;
    double load_factor = 0;
    void save(string file);
    bool delete_person(string & full);
    void insert(Contact e);
    void search(string full, string & result, bool & found);
};

#include "hash_impl.cpp"  
#endif
#pragma once
