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
|                  _                   |
U                                      H
|                                      |
|                                      |
T                                      I
|                                      |
|                                      |
S                                      J
--R----Q----P----O----N----M----L----K--
)";

string circle_symbols = R"(
#   %  $   .   ,   !   ?

&                      :

$                      ;

/                      "

*                      '

@                      -
+ [  ]  {   }   (   )  =
)";

const char* RESET = "\033[0m";
const char* BOLD = "\033[4m";
const char* RED = "\033[31m";
const char* RED_BG = "\033[41m";
const char* GREEN = "\033[32m";
const char* BLUE = "\033[34m";
const char* YELLOW = "\033[33m";

char last_letter_visual = ' ';
void select_letter(char c) {
    string new_circle;
    for (char find : circle) {
        if (find == toupper(c) && c != ' ') {
            new_circle += RED;
            //new_circle += BOLD;
            new_circle += find;
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
            new_circle += find;
        }

    }

    cout << new_circle << endl;
    //cout << "Selected Letter: " << (char)toupper(c) << endl;
}

#endif
