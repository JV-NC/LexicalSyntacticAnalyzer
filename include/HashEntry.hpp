#ifndef HASHENTRY_HPP
#define HASHENTRY_HPP

#include <string>

using namespace std;

struct HashEntry{
	string word;
	int frequency;

	HashEntry(const string &w) : word(w), frequency(1) {}
};

#endif