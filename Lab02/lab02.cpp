#include "window.h"

int main() {
    auto window = new Window();

    while(window->isOpen()) {
        window->render();
    }

    delete window;
}