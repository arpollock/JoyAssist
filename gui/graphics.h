#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// HAHA it's not a circle
string circle = R"(
  X    Y    Z    A    B    C    D    E


W                                      F


V                                      G

                   _
U                                      H


T                                      I


S                                      J
  R    Q    P    O    N    M    L    K
)";

string circle_symbols = R"(
  1  2  3  4  5    U    6  7  8  9  0

'                                     .


"                                     ,


L                                     R


=                                     ?


-                                     !

+                                     )
   #    /    &    D    $    @    (
)";

const char* RESET = "\033[0m";
const char* BOLD = "\033[4m";
const char* RED = "\033[31m";
const char* RED_BG = "\033[41m";
const char* GREEN = "\033[32m";
const char* BLUE = "\033[34m";
const char* YELLOW = "\033[33m";

char last_letter_visual = ' ';

void select_ascii(char c, int shift_level) {
    string orig_circle = circle;
    if (shift_level > 1) {
        orig_circle = circle_symbols;
    }

    string new_circle;

    for (char find : orig_circle) {
        if (find == toupper(c) && c != ' ') {
            new_circle += RED;
            //new_circle += BOLD;
            if (shift_level == 0) {
                new_circle += tolower(find);
            }
            else {
                new_circle += find;
            }
            new_circle += RESET;
            last_letter_visual = find;
        }
        else if (find == '_') {
            if (c == ' ')
                new_circle += last_letter_visual;
            else
                new_circle += toupper(c);
        }
        else {
            if (shift_level == 0) {
                new_circle += tolower(find);
            }
            else {
                new_circle += find;
            }
        }
    }

    cout << new_circle << endl;
}

#endif
