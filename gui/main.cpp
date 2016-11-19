#include <libserialport.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

struct sp_port *port_ptr;

int D_WIDTH = 0;
int D_HEIGHT = 0;

const int X_REST = 496;
const int Y_REST = 515;

int MPOS_X = 0;
int MPOS_Y = 0;

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
        else if (c == ',' || c == '\n') {
            params.push_back(atoi(new_num.c_str()));
            new_num = "";

            if (c == '\n') {
                if (params.size() != 3) {
                    //cout << cmd << endl;
                }
                return params;
            }
        }
    }

    params.clear();
    return params;
}

void exec_cmd(vector<int> params) {
    if (params.size() == 3) {

        int p0 = params.at(0);

        if (p0 == 0 || p0 == 6 || p0 == 96)
            return;

        int SCALE = 8;

        int x =  (((double)params.at(0) - X_REST) / 1023.0) * SCALE;
        int y =  (((double)params.at(1) - Y_REST) / 1023.0) * SCALE;

        MoveMouse(x*SCALE, y*SCALE);

        bool clicked = (params.at(2) == 0);

        CGEventRef move = CGEventCreateMouseEvent(
                NULL, kCGEventMouseMoved,
                CGPointMake(MPOS_X, MPOS_Y),
                kCGMouseButtonLeft // ignored
                );
        CGEventPost(kCGHIDEventTap, move);
        //cout << "(" << x << ", " << y << ")" << endl;
        CFRelease(move);

        if (clicked) {
            // press left mouse button
            CGEventRef click_down = CGEventCreateMouseEvent(
                    NULL, kCGEventLeftMouseDown,
                    CGPointMake(MPOS_X, MPOS_Y),
                    kCGMouseButtonLeft
                    );

            CGEventPost(kCGHIDEventTap, click_down);
            CFRelease(click_down);
        } else {
            // release left mouse button
            CGEventRef click_up = CGEventCreateMouseEvent(
                    NULL, kCGEventLeftMouseUp,
                    CGPointMake(MPOS_X, MPOS_Y),
                    kCGMouseButtonLeft
                    );

            CGEventPost(kCGHIDEventTap, click_up);
            CFRelease(click_up);
        }
    }
}

int main() {
    struct sp_event_set *ev = nullptr;
    init_serial(ev);

    for (;;) {
        char buf[256] = {0};
        sp_wait(ev, 0);
        int res = sp_blocking_read_next(port_ptr, buf, sizeof(buf), 50);

        if (res > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            string cmd = string(buf);
            vector<int> params = parse_cmd(cmd);
            exec_cmd(params);
        }
        else {
            cout << "ERROR, NUGGET: " << res << endl;
        }
    }

    sp_close(port_ptr);
    return 0;
}
