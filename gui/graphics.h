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

string circle_3 = R"(
 CUT     COPY      U      PASTE     TAB



PREV                                NEXT




L                                      R




CMD-A                               FIND



  Z-IN    Z-OUT    D  RESET-ZOOM   ENTER
)";

const char* RESET = "\033[0m";
const char* BOLD = "\033[4m";
const char* RED = "\033[31m";
const char* RED_BG = "\033[41m";
const char* GREEN = "\033[32m";
const char* BLUE = "\033[34m";
const char* YELLOW = "\033[33m";

char last_letter_visual = ' ';

string to_upper(string str) {
    string new_str = "";
    for (char c : str) {
        new_str += toupper(c);
    }
    return new_str;
}

string to_lower(string str) {
    string new_str = "";
    for (char c : str) {
        new_str += tolower(c);
    }
    return new_str;
}

void select_ascii(string select_str, int shift_level) {
    string orig_circle = circle;

    if (shift_level == 2) {
        orig_circle = circle_symbols;
    }
    if (shift_level == 3) {
        orig_circle = circle_3;
    }

    string new_circle = "";
    string find_str = "";

    for (char find : orig_circle) {
        find_str += find;

        if (find_str == select_str) {
            new_circle += RED;
            //new_circle += BOLD;
            if (shift_level == 0) {
                new_circle += to_lower(find_str);
            }
            else {
                new_circle += find_str;
            }
            new_circle += RESET;
            find_str = "";
            //last_letter_visual = find;
        }
        else if (find == ' ' || find == '\n') {
            if (shift_level == 0)
                new_circle += to_lower(find_str);
            else
                new_circle += to_upper(find_str);

            find_str = "";
        }
        else if (find == '_') {
            if (select_str == "")
                new_circle += last_letter_visual;
            //else
                //new_circle += toupper(c);

            find_str = "";
        }
    }

    cout << new_circle << endl;
}

#endif
