#include <libserialport.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <math.h>
#include "graphics.h"

using namespace std;

struct sp_port *port_ptr;

int D_WIDTH = 0;
int D_HEIGHT = 0;

const int X_REST = 496;
const int Y_REST = 515;

int MPOS_X = 0;
int MPOS_Y = 0;

vector<int> new_params;

void MoveMouse(int x, int y) {
    int newX = MPOS_X - x;
    int newY = MPOS_Y - y;

    if (newX < 0 || newX > D_WIDTH) {
        newX = MPOS_X;
    }
    if (newY < 0 || newY > D_HEIGHT) {
        newY = MPOS_Y;
    }

    MPOS_X = newX;
    MPOS_Y = newY;
}

void init_serial(sp_event_set *ev){
    CGDirectDisplayID d_id = CGMainDisplayID();
    D_WIDTH = CGDisplayPixelsWide(d_id);
    D_HEIGHT = CGDisplayPixelsHigh(d_id);
    MPOS_X = D_WIDTH/2;
    MPOS_Y = D_HEIGHT/2;

    sp_get_port_by_name("/dev/cu.usbserial-DA01R1FM", &port_ptr);
    sp_set_baudrate(port_ptr, 9600);

    sp_open(port_ptr, SP_MODE_READ);
    sp_new_event_set(&ev);
    sp_add_port_events(ev, port_ptr, SP_EVENT_RX_READY);
}

vector<int> parse_cmd(string cmd) {
    vector<int> params;
    string new_num;

    for (char c : cmd) {
        if (c != ',' && c != '\r' && c != '\n') {
            new_num += c;
        }
        else if (c == ',' || c == '\r') {
            params.push_back(atoi(new_num.c_str()));
            new_num = "";

            if (c == '\r')
                return params;
        }
    }

    params.clear();
    return params;
}

vector<int> get_params() {
    return new_params;
}

bool last_clicked = false;
int click_count = 0;

int last_x = 0;
int last_y = 0;
bool mouse_mode = false;

void mouse_mode_exec(vector<int> params) {
    int SCALE = 7;

    int x =  (((double)params.at(0) - X_REST) / 1023.0) * SCALE;
    int y =  (((double)params.at(1) - Y_REST) / 1023.0) * SCALE;

    MoveMouse(x*SCALE, y*SCALE);

    bool clicked = (params.at(2) == 0) && last_clicked;

    CGEventRef move = CGEventCreateMouseEvent(
            NULL, kCGEventMouseMoved,
            CGPointMake(MPOS_X, MPOS_Y),
            kCGMouseButtonLeft // ignored
            );
    CGEventPost(kCGHIDEventTap, move);

    if (!last_clicked && params.at(2) == 0) {
        if (abs(last_x - MPOS_X) < 15 || abs(last_y - MPOS_Y) < 15) {
            click_count++;
        }

        if (click_count == 2) {
            mouse_mode = !mouse_mode;
            click_count = 0;
        }
    }

    if (clicked) {
        // press left mouse button
        CGEventRef click_down = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseDown,
                CGPointMake(MPOS_X, MPOS_Y),
                kCGMouseButtonLeft
                );

        CGEventPost(kCGHIDEventTap, click_down);
        CFRelease(click_down);

    } else if (last_clicked) {
        // release left mouse button
        CGEventRef click_up = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseUp,
                CGPointMake(MPOS_X, MPOS_Y),
                kCGMouseButtonLeft
                );

        CGEventPost(kCGHIDEventTap, click_up);
        CFRelease(click_up);
    }

    last_clicked = (params.at(2) == 0);

    last_x = MPOS_X;
    last_y = MPOS_Y;

    CFRelease(move);
}

void clear_display() {
    cout << "\033[2J";
}

int key_code_from_str(string c) {
    if (c == "a") { return 0; }
    if (c == "s") { return 1; }
    if (c == "d") { return 2; }
    if (c == "f") { return 3; }
    if (c == "h") { return 4; }
    if (c == "g") { return 5; }
    if (c == "z") { return 6; }
    if (c == "x") { return 7; }
    if (c == "c") { return 8; }
    if (c == "v") { return 9; }
    // what is 10?
    if (c == "b") { return 11; }
    if (c == "q") { return 12; }
    if (c == "w") { return 13; }
    if (c == "e") { return 14; }
    if (c == "r") { return 15; }
    if (c == "y") { return 16; }
    if (c == "t") { return 17; }
    if (c == "1") { return 18; }
    if (c == "2") { return 19; }
    if (c == "3") { return 20; }
    if (c == "4") { return 21; }
    if (c == "6") { return 22; }
    if (c == "5") { return 23; }
    if (c == "=") { return 24; }
    if (c == "9") { return 25; }
    if (c == "7") { return 26; }
    if (c == "-") { return 27; }
    if (c == "8") { return 28; }
    if (c == "0") { return 29; }
    if (c == "") { return 30; }
    if (c == "o") { return 31; }
    if (c == "u") { return 32; }
    if (c == "[") { return 33; }
    if (c == "i") { return 34; }
    if (c == "p") { return 35; }
    if (c == "RETURN") { return 36; }
    if (c == "l") { return 37; }
    if (c == "j") { return 38; }
    if (c == "'") { return 39; }
    if (c == "k") { return 40; }
    if (c == ";") { return 41; }
    if (c == "\\") { return 42; }
    if (c == ",") { return 43; }
    if (c == "/") { return 44; }
    if (c == "n") { return 45; }
    if (c == "m") { return 46; }
    if (c == ".") { return 47; }
    if (c == "TAB") { return 48; }
    if (c == "SPACE") { return 49; }
    if (c == "`") { return 50; }
    if (c == "DELETE") { return 51; }
    if (c == "ENTER") { return 52; }
    //if (c == "ESCAPE") { return 53; }

    // some more missing codes abound, reserved I presume, but it would
    // have been helpful for Apple to have a document with them all listed

    //if (c == ".") { return 65; }
    //if (c == "*") { return 67; }
    //if (c == "+") { return 69; }
    //if (c == "CLEAR") { return 71; }
    //if (c == "/") { return 75; }
    //if (c == "ENTER") { return 76;  // numberpad on full kbd }
    //if (c == "=") { return 78; }
    //if (c == "=") { return 81; }
    //if (c == "0") { return 82; }
    //if (c == "1") { return 83; }
    //if (c == "2") { return 84; }
    //if (c == "3") { return 85; }
    //if (c == "4") { return 86; }
    //if (c == "5") { return 87; }
    //if (c == "6") { return 88; }
    //if (c == "7") { return 89; }
    //if (c == "8") { return 91; }
    //if (c == "9") { return 92; }
    //if (c == "F5") { return 96; }
    //if (c == "F6") { return 97; }
    //if (c == "F7") { return 98; }
    //if (c == "F3") { return 99; }
    //if (c == "F8") { return 100; }
    //if (c == "F9") { return 101; }
    //if (c == "F11") { return 103; }
    //if (c == "F13") { return 105; }
    //if (c == "F14") { return 107; }
    //if (c == "F10") { return 109; }
    //if (c == "F12") { return 111; }
    //if (c == "F15") { return 113; }
    //if (c == "HELP") { return 114; }
    //if (c == "HOME") { return 115; }
    //if (c == "PGUP") { return 116; }
    //if (c == "DELETE") { return 117; }
    //if (c == "F4") { return 118; }
    //if (c == "END") { return 119; }
    //if (c == "F2") { return 120; }
    //if (c == "PGDN") { return 121; }
    //if (c == "F1") { return 122; }
    //if (c == "LEFT") { return 123; }
    //if (c == "RIGHT") { return 124; }
    //if (c == "DOWN") { return 125; }
    //if (c == "UP") { return 126; }

    return 0;
}

void press_key(string s) {
    CGEventRef press = CGEventCreateKeyboardEvent( NULL, (CGKeyCode)key_code_from_str(s),
            true);
    CGEventPost(kCGHIDEventTap, press);

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    CGEventRef depress = CGEventCreateKeyboardEvent( NULL, (CGKeyCode)key_code_from_str(s),
            false);
    CGEventPost(kCGHIDEventTap, depress);

    CFRelease(press);
    CFRelease(depress);
}


int first_active = -1;
char last_letter = ' ';

bool depressed = false;
bool gesture_mode = false;

void kb_mode_exec(vector<int> params) {
    clear_display();

    bool clicked = (params.at(2) == 0);

    string row1 = "EDCBAZYX";
    string col1 = "JIHGF";
    string col2 = "STUVW";
    string row2 = "KLMNOPQR";

    double x = ((double)params.at(0)) / 1023.0;
    double y = ((double)params.at(1)) / 1023.0;

    x = round(x * 10.0 ) / 10.0;
    y = round(y * 10.0 ) / 10.0;

    if (x != 0.5 && y == 0.5) {
        first_active = 0;
    }
    else if (x == 0.5 && y != 0.5) {
        first_active = 1;
    }
    else if (x == 0.5 && y == 0.5) {
        first_active = -1;
        if (clicked) {
            gesture_mode = true;
            return;
        }
    }

    char selection = ' ';
    string use_me = "";
    double use_axis = 0;

    // use columns, x was moved first
    if (first_active == 0) {
        if (x > 0.5)
            use_me = col2;
        else if (x < 0.5)
            use_me = col1;

        use_axis = y;
        //cout << "Using Cols" << endl;
    }

    if (first_active == 1) {
        if (y > 0.5)
            use_me = row1;
        else if (y < 0.5)
            use_me = row2;

        use_axis = x;
        //cout << "Using Rows" << endl;
    }

    if (first_active != -1) {
        selection = use_me[round((use_me.length()-1) * use_axis)];
    }
    select_letter(selection);

    if (selection != ' ')
        last_letter = selection;

    string s(1, tolower(last_letter));
    cout << s << endl;
    if (clicked && !depressed) {
        press_key(s);
    }

    depressed = clicked;
}

void kb_gesture(vector<int> params) {
    double x = ((double)params.at(0)) / 1023.0;
    double y = ((double)params.at(1)) / 1023.0;

    x = round(x * 10.0 ) / 10.0;
    y = round(y * 10.0 ) / 10.0;

    if (x < 0.5) {
        press_key("SPACE");
        gesture_mode = false;
        depressed = true;
        click_count = 0;
    }
    else if (x > 0.5) {
        press_key("DELETE");
        gesture_mode = false;
        depressed = true;
        click_count = 0;
    }
    // TODO: shift
    else if (y > 0.5) { }
    //press_key("");
    else if (y < 0.5) {
        press_key("ENTER");
        gesture_mode = false;
        depressed = true;
        click_count = 0;
    }
    else {
        click_count++;
        if (click_count == 2) {
            mouse_mode = !mouse_mode;
            click_count = 0;
        }
    }

}

void exec_cmd(vector<int> params) {
    if (params.size() == 3) {

        int p0 = params.at(0);

        if (p0 == 0 || p0 == 6 || p0 == 96)
            return;

        new_params = params;

        //mouse_mode_exec(params);
        if (gesture_mode) {
            kb_gesture(params);
        }
        else {
            if (!mouse_mode)
                kb_mode_exec(params);
            else
                mouse_mode_exec(params);
        }
    }
}

int main() {
    struct sp_event_set *ev = nullptr;
    init_serial(ev);

    //int used = 0;
    string cmd = "";

    for (;;) {
        char buf[1] = {0};
        sp_wait(ev, 0);
        int res = sp_blocking_read_next(port_ptr, buf, 1, 50);

        //used += res;
        if (res > 0) {
            cmd += (char)buf[0];
        }

        if (buf[0] == '\r') {
            //std::this_thread::sleep_for(std::chrono::milliseconds(20));
            vector<int> params = parse_cmd(cmd);
            exec_cmd(params);
            //cout << cmd;
            cmd = "";
        }
        else {
            //cout << "ERROR, NUGGET: " << res << endl;
        }
    }

    sp_close(port_ptr);
    return 0;
}
