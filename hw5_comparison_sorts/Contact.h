#ifndef _Contact_H
#define _Contact_H

#include <algorithm>
#include <string>
#include<iostream>
using namespace std;


//tansylu akhmetova 29/04/2023

class Contact {
   
public:
    string phone;
    string city;
    string full;
    Contact(string f="", string phone = "", string city = "") :phone(phone), city(city) {
        transform(f.begin(), f.end(), f.begin(), ::toupper);
        full = f;
    }
    Contact& operator=(const Contact& other) {
        if (this != &other) {
            this->phone = other.phone;
            this->city = other.city;
            this->full = other.full;
        }
        return *this;
    }

    bool operator > (Contact& rhs) {
        if (this->full > rhs.full) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator < (Contact& rhs) {
        if (this->full < rhs.full) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator == (Contact& rhs) {
        if (this->full == rhs.full) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator == (string rhs) {
        if (this->full == rhs) {
            return true;
        }
        else {
            return false;
        }
    }

    bool contains(string rhs) {
        int m = min(rhs.length(), full.length());
        if (this->full.substr(0, m) == rhs ) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator > (string rhs) {
        //int m = min(rhs.length(), full.length());

        if (this->full > rhs) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator < (string rhs) {
       // int m = min(rhs.length(), full.length());
        if (this->full < rhs) {
            return true;
        }
        else {
            return false;
        }
    }

    friend ostream& operator << (ostream& out, const Contact& c) {
        out << c.full << " " << c.phone << " " << c.city;
        return out;
    }

};
#endif
