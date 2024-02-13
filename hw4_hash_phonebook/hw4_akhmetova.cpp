#include <iostream>
#include <string>
#include <sstream>
#include "bst.h"
#include "hash.h"
#include "Contact.h"
#include <vector>
#include <chrono>
using namespace std;

struct element {
public:
	element* left = nullptr;
	element* right = nullptr;
	Contact person;
	int height;
	bool deleted;
	element(Contact person, bool deleted = false, int h = 0, element* l = nullptr, element* r = nullptr) :
		person(person), height(h), left(l), right(r), deleted(deleted) {

	}
};

template<typename T>
bool load_hash(T& hashtable, string file_name) {
	string line, name, lname, phone, city;
	ifstream myfile;
	myfile.open(file_name);
	vector<string> parsed(4);
	if (!myfile.is_open()) {
		cout << "Wrong file!" << endl;
		return false;
	}
	while (getline(myfile, line))
	{
		stringstream s(line);
		getline(s, name, ' ');
		getline(s, lname, ' ');
		getline(s, phone, ' ');
		getline(s, city, ' ');

		Contact p(name + " " + lname, phone, city);
		hashtable.insert(p);

	}
	myfile.close();
	return true;
}


template<typename T>
bool load_bst(T& book, string file_name) {
	string line, name, lname, phone, city;
	ifstream myfile;
	myfile.open(file_name);
	vector<string> parsed(4);
	if (!myfile.is_open()) {
		cout << "Wrong file!" << endl;
		return false;
	}
	while (getline(myfile, line))
	{
		stringstream s(line);
		getline(s, name, ' ');
		getline(s, lname, ' ');
		getline(s, phone, ' ');
		getline(s, city, ' ');

		Contact p(name + " " + lname, phone, city);
		book.head = book.insert(book.head, p);

	}
	myfile.close();
	return true;
}



int main() {
	cout << "Enter the file name: ";
	string filen;
	cin >> filen;

	Contact p;
	BST<element> bst_book;
	Hash<element> n;
	load_hash(n, filen);
	load_bst(bst_book, filen);
	cout << endl << "After preprocessing, the contact count is " << n.count << ". Current load ratio is " << n.load_factor << endl << endl;
	//n.save("res.txt");

	int k = 500;
	int choice = 0;
	string  full = "", search_res = "", phone = "", address = "";
	bool found = false;
	auto start = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	auto HTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
	auto BSTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
	do {
		cout << "Choose which action to perform from 1 to 4:\n";
		cout << "1 - Search a phonebook contact\n";
		cout << "2 - Add a phonebook contact\n";
		cout << "3 - Delete a phonebook contact\n";
		cout << "4 - Press 4 to exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			// Code for searching a phonebook contact
			cout << "Enter name to search for: ";
			cin.clear();
			cin.ignore();
			getline(cin, full);
			transform(full.begin(), full.end(), full.begin(), ::toupper);

			cout << endl << "Searching for an item in the phonebook (BST) . . .\n";
			cout << "Phonebook: Searching for : (" << full << ")\n";
			cout << "====================================" << endl;
			start = chrono::high_resolution_clock::now();
			found = false;
			for (int i = 0; i < k; i++)
			{
				bst_book.search(full, bst_book.head, search_res, found);

			}
			end = chrono::high_resolution_clock::now();

			BSTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
			if (found) {
				cout << endl << search_res << endl << endl;
			}
			else {
				cout << endl << "Name not found!" << endl << endl;
			}

			cout << "BST Search Time: " << BSTTime.count() / k << endl << endl;

			cout << "Searching for an item in the phonebook (HashTable) . . .\n";
			cout << "Phonebook: Searching for : (" << full << ")\n";
			cout << "====================================\n";

			found = false;
			start = chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				n.search(full, search_res, found);

			}
			end = chrono::high_resolution_clock::now();

			HTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
			if (found) {
				cout << endl << search_res << endl << endl;
			}
			else {
				cout << endl << "Name not found!" << endl << endl;
			}
			cout << "Hash Table Search Time: " << HTTime.count() / k << endl;

			cout << "Speed Up: " << (BSTTime.count() / k) / (HTTime.count() / k) << endl << endl;
			break;

		case 2:
			// Code for adding a phonebook contact
			cout << "Enter the information of the contact to be added:\n";
			cin.clear();
			cin.ignore();
			cout << "Name: ";
			getline(cin, full);
			cout << endl << "Tel: ";
			getline(cin, phone);
			cout << endl << "City: ";
			getline(cin, address);
			transform(full.begin(), full.end(), full.begin(), ::toupper);
			p = Contact(full, phone, address);
			start = chrono::high_resolution_clock::now();
			bst_book.head = bst_book.insert(bst_book.head, p);
			end = chrono::high_resolution_clock::now();
			BSTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

			start = chrono::high_resolution_clock::now();
			n.insert(p);
			end = chrono::high_resolution_clock::now();
			HTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

			cout << endl << "Adding an item to the phonebook BST . . .\n";
			cout << "====================================\n";
			cout << "Contact has been added successfully to the BST Tree\n" << endl;

			cout << "Adding an item to the phonebook (Hashtable) . . .\n";
			cout << "====================================\n";
			cout << "Contact has been added successfully to the Hashtable\n" << endl;

			cout << "Adding a contact to the Binary Tree took " << BSTTime.count() << " nanoseconds. . .\n";
			cout << "Adding a contact to the Hashtable took " << HTTime.count() << " nanoseconds. . .\n" << endl;

			break;
		case 3:
			// Code for deleting a phonebook contact
			cout << "Deleting an item from the phonebook..." << std::endl;
			cout << "Enter the full name of the contact to be deleted: ";
			cin.clear();
			cin.ignore();
			getline(cin, full);
			transform(full.begin(), full.end(), full.begin(), ::toupper);
			start = chrono::high_resolution_clock::now();

			bst_book.delete_node(bst_book.head, full, found);
			end = chrono::high_resolution_clock::now();
			BSTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

			start = chrono::high_resolution_clock::now();
			n.delete_person(full);
			end = chrono::high_resolution_clock::now();
			HTTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

			cout << "Deleted successfully." << std::endl;
			cout << "Deletion from the Binary Tree took " << BSTTime.count() << " nanoseconds." << std::endl;
			cout << "Deletion from the Hashtable took " << HTTime.count() << " nanoseconds." << std::endl;

			break;
		case 4:
			cout << "Exiting the program.\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			cin >> choice;
			break;
		}
	} while (choice != 4);



	return 0;
}