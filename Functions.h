#pragma once

#include "Rekord.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


// ID generation function
char* generator();

// The function creates a text document with data to read  
void writefile(int quantity, std::string filename);

// The function reads data from the document and saves them to a vector
void readfile(std::vector<Rekord>& vec, std::string filename);

// Sorting function SORT (ShellShort)
void Sort(std::vector<Rekord>& v);

// Swap rekordow
void Swap(Rekord& rekord1, Rekord& rekord2);

// The function outputs the content of the vector to the console
void Print(const std::vector<Rekord>& v);

// Sorting function StableSort (MergeSort)
void Merge(std::vector<Rekord>& v, int const left, int const mid, int const right);
void StableSort(std::vector<Rekord>& v, int const begin, int const end);

// The function saves the sorted vector with Sort() and StableSort() in a text document also 
// shows the algorithm's execution time with these functions for comparison
void Printvec(const std::vector<Rekord>& v, std::string filename, double x1, double x2);