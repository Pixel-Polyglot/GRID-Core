#include <GRID/GRID_window.h>
#include <window.h>

void GRID_Window::enableVsync(bool enable) {
    window.enableVsync(enable);
}

double GRID_Window::getDeltaTime() {
    return window.getDeltaTime();
}