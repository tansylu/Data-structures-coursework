#ifndef _BST_H
#define _BST_H
#include "Contact.h"
#include<string>
using namespace std;



//tansylu akhmetova 29/04/2023

template <class itemType>
class BST {
public:
    itemType* head = nullptr;
    BST() {
        head = nullptr;
    }
    itemType* insert(itemType* node, Contact p);

    void search(string query, itemType* node, string & result, bool & found);

    itemType* delete_node(itemType* node, string query, bool & flag);

    int height(itemType* node);

    void clean(itemType* place);
    ~BST();
};

#include "bst_impl.cpp"  
#endif
