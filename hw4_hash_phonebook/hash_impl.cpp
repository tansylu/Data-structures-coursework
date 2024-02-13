#include "hash.h"
#include <vector>
#include "hash.h"
#include <stack>
#include <iostream>

template<class itemType>
long Hash<itemType>::calc_position(char* name, int s) {
	long hashed = 0;
	while (*name != '\0') {
		hashed = (hashed << 4) + *(name++);
		hashed ^= (hashed & 0xF0000000L) >> 24;
		hashed &= 0x0FFFFFFF;
	}
	return hashed % s;
}


template<class itemType>
void Hash<itemType>::insert(Contact person)
{
	string s = person.full;
	char* char_array = new char[s.length() + 1];
	strcpy_s(char_array, s.length() + 1, s.c_str());

	int index = calc_position(char_array, size);
	bool already_exists = false;
	person.full = s;
	my_table[index].head = my_table[index].insert(my_table[index].head, person, already_exists);

	if (!already_exists) {
		count++;
	}

	load_factor = count / size;
	if (load_factor > 0.75) {
		rehash();
	}
}




template<class itemType>
void Hash<itemType>::search(string full, string & result, bool & found)
{
	
	int length = full.length();
	char* char_array = new char[length + 1];
	strcpy_s(char_array, length + 1, full.c_str());

	int index = calc_position(char_array, size);
	
	if (my_table[index].head == nullptr) {
		found = false;
		return;
	}
	
	my_table[index].search(full, my_table[index].head, found, result);

}

template<class itemType>
void inorder(itemType* head, ofstream& out) {
	if (head == nullptr) {
		return;
	}
	inorder(head->left, out);
	out << head->person << endl;
	inorder(head->right, out);

}

template<class itemType>
void Hash<itemType>::save(string file)
{
	ofstream out;
	out.open(file);
	for (AVL<itemType> e : my_table) {
		if (e.head != nullptr) {
			inorder(e.head, out);
		}
	}
}

template<class itemType>
void Hash<itemType>::rehash()
{
	cout << "rehashed..." << endl;
	int doubled_size = size * 2;
	vector<AVL<itemType>> temp(doubled_size);

	for (AVL<itemType> e : my_table) {
		if (e.head != nullptr) {
			rehash_helper(e.head, temp);
		}
	}
	int old_size = my_table.size();
	my_table = temp;
	size = doubled_size;
	load_factor = count / size;
	cout << "previous table size: " << old_size << ", new table size: " << size << ", current unique word count " << count << ", current load factor: " << load_factor <<endl;
	//cout << "old size: " << old_size << "new size: " << size << "count: " << count << endl;
}

template<class itemType>
void Hash<itemType>::rehash_helper(itemType* place, vector<AVL<itemType>>& temp)
{
	if (place == nullptr) {
		return;
	}

	rehash_helper(place->left, temp);
	string s = place->person.full;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	char* char_array = new char[s.length() + 1];
	strcpy_s(char_array, s.length() + 1, s.c_str());

	int index = calc_position(char_array, temp.size());
	bool alreadyExists = false;
	temp[index].head = temp[index].insert(temp[index].head, place->person, alreadyExists);

	rehash_helper(place->right, temp);
}

template<class itemType>
bool Hash<itemType>::delete_person(string & full)
{

	int length = full.length();
	char* char_array = new char[length + 1];
	strcpy_s(char_array, length + 1, full.c_str());

	int index = calc_position(char_array, size);
	bool success_delete = false;
	if (my_table[index].head != nullptr) {
		
		my_table[index].delete_node(my_table[index].head, full, success_delete);
	}
	my_table[index].head = nullptr;
	return success_delete;
}