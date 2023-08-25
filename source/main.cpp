#include "widget/SApplication.h"

int main() {
    if (!SApplication::getIntance()->init()) {
        return 1;
    }

    SApplication::getIntance()->run();
    SApplication::getIntance()->quit();
}
