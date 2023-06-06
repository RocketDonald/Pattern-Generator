#include <iostream>
#include "Canvas.h"

using namespace std;
using namespace wfc;

int main() {
    Canvas c = Canvas();
    c.read("test_1.png");
    
    c.draw("test_2.png");

    c.read("test_2.png");

    c.draw("test_3.png");
    return 0;
}