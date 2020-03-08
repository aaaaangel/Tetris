#include <iostream>

#include "Controller.h"

using namespace cv;
using namespace std;


int main() {
    Controller controller(500);
    controller.run();

    return 0;
}
