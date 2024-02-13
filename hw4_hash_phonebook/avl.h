#ifndef _AVL_H
#define _AVL_H
#include "Contact.h"
#include<string>
using namespace std;


//tansylu akhmetova 29/04/2023

template <class itemType>
class AVL {
    public:
        itemType* head = nullptr;
        AVL() {
            head = nullptr;
        }
        itemType* insert(itemType* node, Contact p, bool & already_exists);

        void search(string query, itemType* node, bool & found, string & result);

        itemType* delete_node(itemType* node, string query, bool  & flag);
        ~AVL();

    private:
        void clean(itemType* place);

        int height(itemType* node);

        itemType* right_r(itemType* node);

        itemType* left_r(itemType* node);

        itemType* left_right(itemType* node);

        itemType* right_left(itemType* node);

      
};

#include "avl_impl.cpp"  
#endif
