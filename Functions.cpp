#include "Functions.h"
#include <stdlib.h>
#include <fstream>



// ID generation function
char* generator() {
    static char array[5];
    char pass[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };

    for (int i = 0; i < 4; i++) {
        array[i] = pass[rand() % 36];
    }
    array[4] = '\0';
    return array;
}


// The function creates a text document with data to read  
void writefile(int quantity, std::string filename) {
    std::ofstream fon;
    fon.open(filename);

    for (int i = 0; i < quantity; i++) {
        char* ptr = generator();
        fon << (rand() % 100) * pow(-1, rand() % 2) << '\t' << ptr << '\n';
    }
    fon.close();
}

// The function reads data from the document and saves them to a vector
void readfile(std::vector<Rekord>& vec, std::string filename) {
    vec.clear();
    std::ifstream fin;
    fin.open(filename);
    std::string key_str, ID_str;
    while (!fin.eof()) {

        fin >> key_str;
        fin >> ID_str;

        int key = stoi(key_str);
        char ID[5];
        strcpy_s(ID, ID_str.c_str());

        Rekord rekord;
        rekord.key = key;
        strcpy_s(rekord.ID, ID);

        vec.push_back(rekord);
    }
    vec.pop_back();
    fin.close();
}

// Sorting function SORT (ShellShort)
void Sort(std::vector<Rekord>& v) {
    int n = v.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {

            Rekord temp;
            temp.key = v[i].key;
            strcpy_s(temp.ID, v[i].ID);


            int j;
            for (j = i; j >= gap && v[j - gap].key > temp.key; j -= gap)
                Swap(v[j], v[j - gap]);

            Swap(v[j], temp);
        }
    }
}

// Sorting function StableSort (MergeSort)
void Merge(std::vector<Rekord>& v, int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto* leftArray = new Rekord[subArrayOne],
        * rightArray = new Rekord[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = v[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = v[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            v[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            v[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        v[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        v[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

}


void StableSort(std::vector<Rekord>& v, int const begin, int const end) {
    if (begin >= end)
        return; 

    auto mid = begin + (end - begin) / 2;
    StableSort(v, begin, mid);
    StableSort(v, mid + 1, end);
    Merge(v, begin, mid, end);
}



// Swap rekordow
void Swap(Rekord& rekord1, Rekord& rekord2) {
    Rekord temp;
    temp.key = rekord1.key;
    strcpy_s(temp.ID, rekord1.ID);

    rekord1.key = rekord2.key;
    strcpy_s(rekord1.ID, rekord2.ID);

    rekord2.key = temp.key;
    strcpy_s(rekord2.ID, temp.ID);
}

//  The function outputs the content of the vector to the console
void Print(const std::vector<Rekord>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << "KEY:" << std::setw(3) << v[i].key << "\t ID:" << v[i].ID << std::endl;
    }
}

// The function saves the sorted vector with Sort() and StableSort() in a text document also 
// shows the algorithm's execution time with these functions for comparison
void Printvec(const std::vector<Rekord>& v, std::string filename, double x1, double x2) {
    std::ofstream fon;
    fon.open(filename);
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Wynik sortowania pliku: \t" << filename << std::endl;
    fon << "Ilosc rekordow: \t\t" << v.size() << std::endl;
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Sort: \t\t ShellSort" << std::endl << "StableSort: \t MergeSort" << std::endl;
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Czas dla algorytmu Sort: \t " << x1 << "ms" << std::endl;
    fon << "Czas dla algorytmu StableSort: \t " << x2 << "ms" << std::endl;
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Wynik sortowania za pomoca Sort:" << std::endl;
    for (int i = 0; i < v.size(); i++) {
        fon << "{ KEY:" << std::setw(4) << v[i].key << "\t ID: " << v[i].ID << " } ";
        if (i % 6 == 0 && i != 0) fon << std::endl;
    }
    fon << std::endl;
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Wynik sortowania za pomoca StableSort:" << std::endl;
    for (int i = 0; i < v.size(); i++) {
        fon << "{ KEY:" << std::setw(4) << v[i].key << "\t ID: " << v[i].ID << " } ";
        if (i % 6 == 0 && i != 0) fon << std::endl;
    }
    fon << std::endl;
    fon << "-------------------------------------------------------------" << std::endl;
    fon << "Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz 2.59 GHz,  DDR4 16.0GB ";

    fon.close();
}

// Overload operators 

bool operator ==(const Rekord& lk, const Rekord& rk) {
    return lk.key == rk.key;
}

bool operator !=(const Rekord& lk, const Rekord& rk) {
    return !(lk.key == rk.key);
}

bool operator >(const Rekord& lk, const Rekord& rk) {
    return lk.key > rk.key;
}

bool operator <(const Rekord& lk, const Rekord& rk) {
    return lk.key < rk.key;
}

bool operator <=(const Rekord& lk, const Rekord& rk) {
    return !(lk.key > rk.key);
}

bool operator >=(const Rekord& lk, const Rekord& rk) {
    return !(lk.key < rk.key);
}