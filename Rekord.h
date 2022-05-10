#pragma once

// Create a structure to fill the vector with it
struct Rekord {
	int key;
	char ID[5];
};

// Overload operators for structures
bool operator ==(const Rekord& lk, const Rekord& rk);
bool operator >(const Rekord& lk, const Rekord& rk);
bool operator <(const Rekord& lk, const Rekord& rk);
bool operator !=(const Rekord& lk, const Rekord& rk);
bool operator <=(const Rekord& lk, const Rekord& rk);
bool operator >=(const Rekord& lk, const Rekord& rk);
