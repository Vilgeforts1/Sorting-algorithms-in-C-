#include <iostream>
#include <time.h>
#include "Functions.h"
#include "Rekord.h"
#include <iomanip>



using namespace std;



int main() {
	srand(time(NULL));

	vector<Rekord> vec;
	readfile(vec, "wczyt_danych_10.txt");
	cout << "Vector przed posortowaniem:\n";
	Print(vec);


	clock_t start_time = clock();
	cout << "\nVector po posortowaniu fukcja Sort():\n";
	
	vector<Rekord> v_sort = { vec.begin(), vec.end() };		// VECTOR DO POSORTOWANIA DLA FUNKCJI SORT()
	Sort(v_sort);
	Print(v_sort);
	clock_t end_time = clock(); 
	double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;


	clock_t start_time1 = clock();
	cout << "\nVector po posortowaniu fukcja StableSort():\n";  // VECTOR DO POSORTOWANIA DLA FUNKCJI StableSort()
	
	vector<Rekord> v1 = { vec.begin(), vec.end() };
	auto right = v1.size() - 1;
	int left = 0;
	StableSort(v1, left, right);
	Print(v1);
	clock_t end_time1 = clock();
	double search_time1 = (double)(end_time1 - start_time1) / CLOCKS_PER_SEC;

	Printvec(v1, "wczyt_danych_10_output.txt", search_time, search_time1);
	
	return 0;
}