#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include "Contact.h"
#include "quicksort.cpp"
#include "mergesort.cpp"
#include "insertsort.cpp"
#include "heapsort.cpp"
using namespace std;

bool containsSpace(const string& str) {
	for (char c : str) {
		if (isspace(c)) {
			return true;
		}
	}
	return false;
}

template <class objectType>
bool binary_searcher( vector<objectType>& sorted_v, string item,int & res, int low, int high) {
	//int high = sorted_v.size() - 1
	//int low = 0;
	if (low > high) {//not found
		res = -1;
		return false;
	}
	int mid = low + (high - low) / 2;
	if (sorted_v[mid] == item) {
		res = mid;
		return true;
	}
	else if(sorted_v[mid] < item) {//item is in bigger half
		return binary_searcher(sorted_v, item, res, mid + 1, high);
	}
	else{//item is in smaller half
		return binary_searcher(sorted_v, item, res, low, mid - 1);
	}
}

template <class objectType>
bool partial_binary_searcher(vector<objectType>& sorted_v, string item, vector<int> & res, int low, int high) {
	//int high = sorted_v.size() - 1
	//int low = 0;
	if (low > high) {//not found
		if (res.size() > 0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	int mid = low + (high - low) / 2;
	if (sorted_v[mid].contains(item)) {
		res.push_back(mid);
	}
	else if (sorted_v[mid] < item) {//item is in bigger half
		return partial_binary_searcher(sorted_v, item, res, mid + 1, high);
	}
	else {//item is in smaller half
		return partial_binary_searcher(sorted_v, item, res, low, mid - 1);
	}
}

template <class objectType>
bool just_search( vector<objectType>& sorted_v, string item, int& res) {
	for (int i = 0; i < sorted_v.size(); i++) {
		if (sorted_v[i] == item) {
			res = i;
			return true;
		}
	}
	return false;
}


template <class objectType>
bool just_partial_search(vector<objectType>& sorted_v, string item, vector<int>& res) {
	for (int i = 0; i < sorted_v.size(); i++) {
		if (sorted_v[i].contains(item) ){
			res.push_back(i);
			
		}
	}
	if (res.size() != 0) {
		return true;
	}
	return false;
}



vector<Contact> loadFromFile(string file) {
	ifstream myfile;
	string line, name, lname, phone, city;
	myfile.open(file);
	vector<Contact> v;
	if (!myfile.is_open()) {
		cout << "Wrong file!" << endl;
		return v;
	}
	while (getline(myfile, line))
	{
		stringstream s(line);
		getline(s, name, ' ');
		getline(s, lname, ' ');
		getline(s, phone, ' ');
		getline(s, city, ' ');

		Contact p(name + " " + lname, phone, city);
		v.push_back(p);

	}
	return v;
}



int main() {
	string file, s;
	cout << "Please enter the contact file name :";
	cin >> file;
	vector<Contact> quick_v = loadFromFile(file);
	vector<Contact> merge_v = quick_v;
	vector<Contact> insert_v = quick_v;
	vector<Contact> heap_v = quick_v;
	cout << "Please enter the word to be queried :";
	cin.clear();
	cin.ignore();
	getline(cin, s);
	bool full = containsSpace(s);
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl<<endl;


	QuickSort<Contact> q;
	MergeSort<Contact> m;
	InsertionSort<Contact> ins;
	HeapSort<Contact> h;

	auto start = chrono::high_resolution_clock::now();
	q.partition(quick_v, 0, quick_v.size()-1);
	auto end = chrono::high_resolution_clock::now();
	auto quickSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	cout << "Quick Sort Time: " << quickSortTime.count() << " Nanoseconds" << endl;

	std::ofstream output_file("quick_sort_res.txt");
	for (Contact e : quick_v) {
		output_file << e << endl;
	}
	

	start = chrono::high_resolution_clock::now();
	m.split(merge_v);
	end = chrono::high_resolution_clock::now();
	auto mergeSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	cout << "Merge Sort Time: " << mergeSortTime.count() << " Nanoseconds" << endl;

	std::ofstream output_file2("merge_sort_res.txt");
	for (Contact e : merge_v) {
		output_file2 << e << endl;
	}

	start = chrono::high_resolution_clock::now();
	ins.sort(insert_v);
	end = chrono::high_resolution_clock::now();
	auto insertionSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	cout << "Insertion Sort Time: " << insertionSortTime.count() << " Nanoseconds" << endl;

	std::ofstream output_file3("insertion_sort_res.txt");
	for (Contact e : insert_v) {
		output_file3 << e << endl;
	}


	start = chrono::high_resolution_clock::now();
	h.placement(heap_v);
	end = chrono::high_resolution_clock::now();
	auto heapSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	cout << "Heap Sort Time: " << heapSortTime.count() << " Nanoseconds" << endl;

	std::ofstream output_file4("heap_sort_res.txt");
	for (Contact e : heap_v) {
		output_file4 << e << endl;
	}



	
	cout << "======================================" << endl<<endl;
	cout << "Searching for "<<s << endl;
	cout << "======================================" << endl<<endl;

	int res = -1;
	vector<int> results = {};
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	bool isItemFound = false;

	start = chrono::high_resolution_clock::now();
	if (full) {
		isItemFound = binary_searcher(quick_v, s, res, 0, quick_v.size() - 1);}
	else {
		isItemFound = partial_binary_searcher(quick_v, s, results, 0, quick_v.size() - 1);

	}
	end = chrono::high_resolution_clock::now();
	auto binarySearchTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	if (!isItemFound) {
		cout << s<<" does NOT exist in the dataset" << endl;
	}
	else {
		if (!full) {
			for (int i = 0; i < results.size(); i++) {
				cout << quick_v[results[i]]<<endl;
			}
		}
		else {
			cout << quick_v[res] << endl;
		}
	}

	cout << "Binary Search Time: " << binarySearchTime.count() << " Nanoseconds" << endl<<endl;





	// Search results for Sequential Search
	results = {};
	start = chrono::high_resolution_clock::now();
	if (full) {
		isItemFound = just_search(quick_v, s, res);
	}
	else {
		isItemFound = just_partial_search(quick_v, s, results);
	}
	end = chrono::high_resolution_clock::now();
	auto seqSearchTime = chrono::duration_cast<chrono::nanoseconds>(end - start);

	cout << "Search results for Sequential Search:" << endl;

	if (!isItemFound) {
		cout << s << " does NOT exist in the dataset" << endl;
	}
	else {
		if (!full) {
			for (int i = 0; i < results.size(); i++) {
				cout << quick_v[results[i]]<<endl;
			}
		}
		else {
			cout << quick_v[res] << endl;
		}
	}

	cout << "Sequential Search Time: " << seqSearchTime.count() << " Nanoseconds" << endl<<endl;

	// SpeedUp between Search Algorithms
	cout << "======================================" << endl;
	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl<<endl;

	double sequentialBinarySpeedUp = seqSearchTime.count()/ static_cast<double>(binarySearchTime.count());
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << sequentialBinarySpeedUp << endl;

	cout << "======================================" << endl<<endl;
	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl<<endl;

	double insertionQuickSpeedUp = insertionSortTime.count()/ static_cast<double>(quickSortTime.count());
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << insertionQuickSpeedUp << endl;

	double mergeQuickSpeedUp = mergeSortTime.count()/ static_cast<double>(quickSortTime.count());
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << mergeQuickSpeedUp << endl;

	double heapQuickSpeedUp = heapSortTime.count() / static_cast<double>(quickSortTime.count());
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << heapQuickSpeedUp << endl;

	return 0;
}
