#include<string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;


//tansylu akhmetova 29/04/2023

template <class itemType>
int AVL<itemType>::height(itemType* place) {
    if (place == nullptr) {
        return -1;
    }

    return place->height;
}

template <class itemType>
void AVL<itemType>::search(string query, itemType* place, bool& found, string & result) {
    if (place == nullptr) {
        return;
    }
    else if (place->person.contains(query)) {
        result = place->person.full + " " + place->person.phone + " " + place->person.city;
        found = true;
        if (query.find(" ") != std::string::npos) {
            return;
        }
        else {
            search(query, place->right, found, result);
            search(query, place->left, found, result);
        }
    }
    else if (place->person < query) {
        search(query, place->right, found, result);
    }
    else if (place->person > query) {
        search(query, place->left, found, result);
    }
}

template<class itemType>
itemType* AVL<itemType>::delete_node(itemType* place, string query, bool& flag) {
    if (place == nullptr) {
        return place;
    }

    if (place->person == query) {
        flag = true;

        if (place->left == nullptr && place->right == nullptr) {
            delete place;
            place = nullptr;
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

    if (place != nullptr) {
        place->height = max(
            height(place->left),
            height(place->right)
        ) + 1;

        int balance = height(place->left) - height(place->right);

        if (balance > 1) {
            if (height(place->left->left) >= height(place->left->right)) {
                place = right_r(place);
            }
            else {
                place->left = left_r(place->left);
                place = right_r(place);
            }
        }
        else if (balance < -1) {
            if (height(place->right->left) <= height(place->right->right)) {
                place = left_r(place);
            }
            else {
                place->right = right_r(place->right);
                place = left_r(place);
            }
        }
    }

    return place;
}


template <class itemType>
itemType* AVL<itemType>::insert(itemType* place, Contact person, bool & flag) {
    if (place == nullptr) {
        return new itemType(person);
    }

    if (person == place->person) {
        flag = true;
        //cout << "The given contact full name already exists in the database" <<endl;
        return place;
    }

    if (person < place->person) {
        place->left = insert(place->left, person, flag);
    }
    else {
        place->right = insert(place->right, person, flag);
    }

    int left_height = height(place->left);
    int right_height = height(place->right);

    place->height = max(left_height, right_height) + 1;

    int balance = left_height - right_height;

    if (balance > 1) {
        if (height(place->left->left) - height(place->left->right) >= 0) {
            place = right_r(place);
        }
        else {
            place = left_right(place);
        }
    }
    else if (balance < -1) {
        if (height(place->right->left) - height(place->right->right) <= 0) {
            place = left_r(place);
        }
        else {
            place = right_left(place);
        }
    }

    return place;
}

template <class itemType>
itemType* AVL<itemType>::right_r(itemType* place) {
    itemType* left = place->left;
    place->left = left->right;
    left->right = place;

    place->height = max(height(place->left), height(place->right)) + 1;
    left->height = max(height(left->left), height(left->right)) + 1;

    return left;
}

template <class itemType>
itemType* AVL<itemType>::left_r(itemType* place) {
    itemType* right = place->right;
    place->right = right->left;
    right->left = place;

    place->height = max(height(place->left), height(place->right)) + 1;
    right->height = max(height(right->left), height(right->right)) + 1;

    return right;
}


template <class itemType>
itemType* AVL<itemType>::left_right(itemType* place) {
    place->left = left_r(place->left);

    return right_r(place);
}

template <class itemType>
itemType* AVL<itemType>::right_left(itemType* place) {

    place->right = right_r(place->right);
    return left_r(place);

}


template <class itemType>
AVL<itemType>::~AVL() {
    clean(head);
}

template <class itemType>
void AVL<itemType>::clean(itemType* place) {
    /*if (place != nullptr) {
        clean(place->left);
        clean(place->right);
        delete place;
    }*/
}


//tansylu akhmetova 29/04/2023