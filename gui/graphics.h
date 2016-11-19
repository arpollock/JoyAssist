#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// HAHA it's not a circle
string circle = R"(
--X----Y----Z----A----B----C----D----E--
|                                      |
|                                      |
W                                      F
|                                      |
|                                      |
V                                      G
|                                      |
|                                      |
U                                      H
|                                      |
|                                      |
T                                      I
|                                      |
|                                      |
S                                      J
--R----Q----P----O----N----M----L----K--
)";

const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";
const char* BLUE = "\033[34m";
const char* YELLOW = "\033[33m";

void select_letter(char c) {
    string new_circle;
    for (char find : circle) {
        if (find == toupper(c)) {
            new_circle += RED;
            new_circle += find;
            new_circle += RESET;
        }
        else {
            new_circle += find;
        }
    }

    cout << new_circle << endl;
    cout << "Selected Letter: " << (char)toupper(c) << endl;
}

#endif
