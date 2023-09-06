#include "widget/SApplication.h"
#include <cstdlib>

int main() {
    if (!SApplication::getIntance()->init()) {
        return 1;
    }

    SApplication::getIntance()->run();
    SApplication::getIntance()->quit(); 
}
