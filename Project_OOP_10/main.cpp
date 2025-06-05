#include "System.h"

int main() {
    System& system = System::getInstance();
    system.run();
    return 0;
}
