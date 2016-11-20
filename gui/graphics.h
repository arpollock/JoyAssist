#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

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
 #   1  2  3  4  5  6  7  8  9   0   $

'                                     %


"                                     *


@                                     ,


+                                     ?


-                                     !


=                                     /
  <    >     &    .    ;     :  (   )
)";

string circle_3 = R"(
 CUT     COPY      U      PASTE     TAB



B-                                    B+




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

char recommended_char = ' ';

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

void select_ascii(string select_str, int shift_level, map<char, char> occurence_map, char last_letter) {
    string orig_circle = circle;
    char lll = last_letter;

    if (shift_level == 2) {
        orig_circle = circle_symbols;
    }
    if (shift_level == 3) {
        orig_circle = circle_3;
    }

    string new_circle = "";
    string find_str = "";

    for (char find : orig_circle) {

        last_letter = tolower(last_letter);
        if (last_letter >= 'a' && last_letter <= 'z')
            recommended_char = occurence_map.at(last_letter);
        else
            recommended_char = ' ';

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

        }
        else if (find == ' ' || find == '\n') {
            if (shift_level == 0)
                new_circle += to_lower(find_str);
            else
                new_circle += to_upper(find_str);

            find_str = "";
        }

        if (find == '_') {
            new_circle += recommended_char;
            find_str = "";
        }
    }

    cout << new_circle << endl;
    cout << lll << endl;
}

#endif
