#include "BST.h"
#include<string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;



//tansylu akhmetova 16/05/2023

template <class itemType>
int BST<itemType>::height(itemType* place) {
   
        if (place == NULL)
            return 0;
        else {
          
            int l = height(place->left);
            int r = height(place->right);

            if (l > r)
                return (l + 1);
            else
                return (r + 1);
        }
    
}


template <class itemType>
void BST<itemType>::search(string query, itemType* root, string& result, bool& found) {
    std::stack<itemType*> nodeStack;
    itemType* current = root;

    while (current != nullptr || !nodeStack.empty()) {
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();

        if (current->person.contains(query)) {
            found = true;
            result = current->person.full + " " + current->person.phone + " " + current->person.city;
            if (query.find(" ") != std::string::npos) {
                return;
            }
        }

        current = current->right;
    }
}



template<class itemType>
itemType* BST<itemType>::delete_node(itemType* place, string query, bool& flag) {
    if (place == nullptr) {
        return place;
    }

    if (place->person.full == query) {

        flag = true;

        if (place->left == nullptr && place->right == nullptr) {
            delete place->left;
            delete place->right;
            delete place;
            place = nullptr;
            return nullptr;
        }
        else if (place->left == nullptr && place->right != nullptr) {
            itemType* rightChild = place->right;
            delete place;
            place = rightChild;
        }
        else if (place->left != nullptr && place->right == nullptr) {
            itemType* leftChild = place->left;
            delete place;
            place = leftChild;
        }
        else {
            itemType* temp = place->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            place->person = temp->person;
            place->right = delete_node(place->right, query, flag);
        }
    }
    else if (place->person > query) {
        place->left = delete_node(place->left, query, flag);
    }
    else {
        place->right = delete_node(place->right, query, flag);
    }

    return nullptr;
}



template <class itemType>
itemType* BST<itemType>::insert(itemType* place, Contact person) {
    if (place == nullptr) {
        return new itemType(person);
    }

    itemType* current_place = place;
    itemType* parent = nullptr;
    while (current_place != nullptr) {
        if (person == current_place->person) {
            //cout << "The given contact full name already exists in the database" << endl;
            return place;
        }
        parent = current_place;
        if (person < current_place->person) {
            current_place = current_place->left;
        }
        else {
            current_place = current_place->right;
        }
    }

    if (person < parent->person) {
        parent->left = new itemType(person);
    }
    else {
        parent->right = new itemType(person);
    }

    return place;
}


template <class itemType>
BST<itemType>::~ BST() {
    clean(head);
}

template <class itemType>
void BST<itemType>::clean(itemType* place) {
    if (place != nullptr) {
        clean(place->left);
        clean(place->right);
        delete place;
    }
}
