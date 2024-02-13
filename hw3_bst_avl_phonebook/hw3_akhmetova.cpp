#include "avl.h"
#include "bst.h"
#include "Contact.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector> 
#include <sstream>
#include <stack>


//tansylu akhmetova 29/04/2023
using namespace std;
using namespace std::chrono;

struct element {
public:
	element* left;
	element* right;
	Contact person;
	int height;

	element(Contact person, int h = 0, element* l = nullptr, element* r = nullptr):
		person(person), height(h), left(l), right(r) {

	}
};

void inorder(element* head, ofstream& out) {
	if (head == nullptr) {
		return;
	}
	inorder(head->left, out);
	out << head->person << endl;
	inorder(head->right, out);

}

void preorder(element* head, ofstream& out) {
	if (head == nullptr) {
		return;
	}
	out << head->person << endl;
	preorder(head->left, out);
	preorder(head->right, out);

};

void draw(element* head, ofstream& out, string dir) {
	if (head == nullptr) {
		return;
	}

	stack<element*> s;
	s.push(head);

	while (!s.empty()) {
		element* cur = s.top();
		s.pop();

		out << dir << "|__ " << cur->person.full << endl;

		if (cur->left != nullptr) {
			s.push(cur->left);
			out << dir << "|-- ";
		}

		if (cur->right != nullptr) {
			s.push(cur->right);
			out << dir << "|__ ";
		}

		dir += "   ";
	}
}


void exporter(element* avl_head, element* bst_head, int & bst1, int & bst2, int & avl1, int & avl2) {
	ofstream exportfile1;
	ofstream exportfile2;
	ofstream exportfile3;
	ofstream exportfile4;

	exportfile1.open("InOrderBST.txt");
	exportfile2.open("PreOrderBST.txt");
	exportfile3.open("InOrderAVL.txt");
	exportfile4.open("PreOrderAVL.txt");

	if (!(exportfile1.is_open() && exportfile2.is_open() && exportfile3.is_open() && exportfile4.is_open())) {
		cout << "file couldnt be opened" << endl;
		return;
	}

	auto start1 = chrono::high_resolution_clock::now();
	inorder(bst_head, exportfile1);//inorder bst
	auto end1 = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
	bst1 = duration1.count();

	auto start2 = chrono::high_resolution_clock::now();
	preorder(bst_head, exportfile2);//preorder bst
	auto end2 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2);
	bst2 = duration2.count();

	auto start3 = chrono::high_resolution_clock::now();
	inorder(avl_head, exportfile3);//inorder avl
	auto end3 = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration_cast<chrono::nanoseconds>(end3 - start3);
	avl1 = duration3.count();

	auto start4 = chrono::high_resolution_clock::now();
	preorder(avl_head, exportfile4);//preorder avl
	auto end4 = chrono::high_resolution_clock::now();
	auto duration4 = chrono::duration_cast<chrono::nanoseconds>(end4 - start4);
	avl2 = duration4.count();
}

void drawer(element* head_bst, element* head_avl, int& a, int& b) {
	ofstream exportfile1;
	ofstream exportfile2;
	exportfile1.open("phonebookTreeBST.txt");
	exportfile2.open("phonebookTreeAVL.txt");
	if (!(exportfile1.is_open() && exportfile2.is_open())) {
		cout << "file couldnt be opened" << endl;
		return;
	}
	auto start1 = chrono::high_resolution_clock::now();
	draw(head_bst, exportfile1, "");//draw bst
	auto end1 = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
	a =duration1.count();

	auto start2 = chrono::high_resolution_clock::now();
	draw(head_avl, exportfile2, "");//draw avl
	auto end2 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1);
	 b =duration2.count();
}


template<typename T>
bool load(T & book, string file_name) {
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

		Contact p(name, lname, phone, city);
		book.head = book.insert(book.head, p);
			
	}
	myfile.close();
	return true;
}

/*
1.Searchcontact
2. Addcontact
3. Deletecontact
4. InOrderPrintToFile
5. PreOrderPrintToFile
6. DrawTreeToFile
*/

int main() {
	int choice = 0;
	int s, t;
	string file_name;
	cout << "Please enter the contact file name:";
	cin >> file_name;
	AVL<element> avl_book;
	BST<element> bst_book;
	auto start = chrono::high_resolution_clock::now();
	bool flag = load(avl_book, file_name);
	auto end = chrono::high_resolution_clock::now();
	auto duration =chrono::duration_cast<chrono::milliseconds>(end - start);
	s = duration.count();
	int j, k;
	if (flag) {
		start = chrono::high_resolution_clock::now();
		flag = load(bst_book, file_name);
		end = chrono::high_resolution_clock::now();
		duration =chrono::duration_cast<chrono::milliseconds>(end - start);
		t = duration.count();
	}
	if (flag) {
		int l, r;
		l = bst_book.height(bst_book.head->left) ;
		r = bst_book.height(bst_book.head->right);

		cout << "Loading the phonebook into a BST." << endl;
		cout << "Phonebook creation in BST took "<<s<<" milliseconds. . ." << endl;
		if (l != r) {
			cout << "The tree is not balanced" << endl;
		}
		else {
			cout << "The tree is balanced" << endl;
		}
		cout << "The heights of BST are for left: " << l << " and right: "<<r<< endl;

		l = avl_book.head->left->height + 1;
		r = avl_book.head->right->height + 1;

		cout << "Loading the phonebook into an AVL" << endl;
		cout << "Phonebook creation in AVL took " << t << " milliseconds. . ." << endl;
		cout << "The tree is balanced " << endl;
		cout << "The heights of AVL are for left: " << l << " and " << "right: " << r << endl << endl<<endl;

		while (choice != 6) {
			cout << "Choose which action to perform from 1 to 6:" << endl <<
				"1 - Search a phonebook contact" << endl <<
				"2 - Adding a phonebook contact" << endl <<
				"3 - Deleting a phonebook contact" << endl <<
				"4 - Print the phonebook to a file(inorder)" << endl <<
				"Print the phonebook to a file(preorder)" << endl <<
				"5 - Draw the phonebook as a Tree to a file" << endl <<
				"6 - Press 6 to exit" <<  endl;
			cin >> choice;
			cout << endl;
			string q, f, name, lname, phone, city;
			int a, b;
			int bst1, bst2, avl1, avl2;
			string aaa;
			bool found_to_delete_bst = false;
			bool found_to_delete_avl = false;
			std::chrono::nanoseconds duration;
			switch (choice) {
			case 1:
				cout << "Search for a contact: ";
				cin.clear();
				cin.ignore();
				getline(cin, q);
				if (q != "") {
					transform(q.begin(), q.end(), q.begin(),::toupper);
					cout << endl;
					cout << "Searching an item in the phonebook (BST) . . ." << endl << endl;
					cout << "Phonebook: Searching for: (" << q << ")" << endl;
					cout << "====================================" << endl;

					start = chrono::high_resolution_clock::now();
					bst_book.search(q, bst_book.head);
					end = chrono::high_resolution_clock::now();
					duration =chrono::duration_cast<chrono::nanoseconds>(end - start);
					a = duration.count();

					cout << endl << "Searching an item in the phonebook (AVL) . . ." << endl << endl;
					cout << "Phonebook: Section: (" << q << ")" << endl;
					cout << "====================================" << endl;

					start = chrono::high_resolution_clock::now();
					avl_book.search(q, avl_book.head);
					end = chrono::high_resolution_clock::now();
					duration =chrono::duration_cast<chrono::nanoseconds>(end - start);
					b = duration.count();

					cout << endl << "The search in BST took " << a << " nanoseconds..." << endl;
					cout << "The search in AVL took " << b << " nanoseconds..." << endl << endl;
				}
				break;

			case 2:

				cout << "Enter the information of the contact to be added:" << endl;
				cout << "Name: ";
				cin >> name >> lname;
				cout << "Tel: ";
				cin >> phone;
				cout << "City: ";
				cin >> city;
				cout << endl<< "Adding an item to the phonebook BST . . ." << endl;
			
				start = chrono::high_resolution_clock::now();

				bst_book.insert(bst_book.head, Contact(name, lname, phone, city));

				 end = chrono::high_resolution_clock::now();
				  duration =chrono::duration_cast<chrono::nanoseconds>(end - start);
				a =duration.count();

				cout << "====================================" << endl;
				cout << "contact has been added successfully to the BST" << endl << endl;

				cout << "Adding an item to the phonebook(AVL) . . ." << endl;
				start = chrono::high_resolution_clock::now();

				avl_book.insert(avl_book.head, Contact(name, lname, phone, city));

				end = chrono::high_resolution_clock::now();
				duration =chrono::duration_cast<chrono::nanoseconds>(end - start);
				b =duration.count();

				cout << "====================================" << endl;
				cout << "contact has been added successfully to the AVL Tree" << endl << endl;

				cout << "Adding a contact to the Binary Tree took "<<a<<" nanoseconds. . ." << endl;
				cout << "Adding a contact to the AVL Tree took "<<b<<" nanoseconds. . ." << endl<<endl;

				break;
			case 3:

				cout << "Deleting an item from the phonebook . . ." << endl;
				cout << "Enter the fullname of the contact to be deleted: ";
				cin >> name >> lname;
				cout << endl;
				f = name + " " + lname;
				transform(f.begin(), f.end(), f.begin(),::toupper);

				start = chrono::high_resolution_clock::now();

				bst_book.delete_node(bst_book.head, f, found_to_delete_bst);

				end = chrono::high_resolution_clock::now();
				duration =chrono::duration_cast<chrono::nanoseconds>(end - start);
				a = duration.count();

				start = chrono::high_resolution_clock::now();

				avl_book.delete_node(avl_book.head, f, found_to_delete_avl);

				end = chrono::high_resolution_clock::now();
				duration =chrono::duration_cast<chrono::nanoseconds>(end - start);

				b =duration.count();

				

				if (found_to_delete_avl && found_to_delete_bst) {
					cout << "Deleted succcessfully. . ." << endl << endl;
					cout << "Deletion from the Binary Tree took " << a << " nanoseconds. . ." << endl;
					cout << "Deletion from AVL Tree took " << b << " nanoseconds. . ." << endl << endl;
				}
				else {
					cout << "Not found" << endl;
				}
				
				break;

			case 4:
				exporter(avl_book.head, bst_book.head, bst1, bst2, avl1, avl2);
				cout << "Printing in order to file from the Binary Tree took "<<bst1<<" nanoseconds. . ." << endl;
				cout << "Printing in order to file from AVL Tree took "<<avl1<<" nanoseconds. . ." << endl;
				cout << "Printing pre order to file from the Binary Tree took "<<bst2<<" nanoseconds. . ." << endl;
				cout << "Printing pre order to file from AVL Tree took "<<avl2<<" nanoseconds. . ." << endl<<endl;

				break;
			case 5:
				drawer(bst_book.head, avl_book.head, j, k);

				cout << "Drawing tree to file from the Binary Tree took " << j << " nanoseconds. . ." << endl;
				cout << "Drawing tree to file from AVL Tree took " << k << " nanoseconds. . ." << endl<<endl;
				break;
			case 6:
				return 0;

			default:
				break;
			}
		}
	}
	return 0;
}


//tansylu akhmetova 29/04/2023