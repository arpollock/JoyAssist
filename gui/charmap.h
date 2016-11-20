#ifndef CHARMAP_H
#define CHARMAP_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

string loadSeed(string);
void gen_char_occ(string);
map<char, char> load_char_occ();

#endif
