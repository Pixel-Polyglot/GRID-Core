#pragma once
#include <iostream>

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();
    void destroy();
    void init(std::string name, int width, int height, int ogl_version_major, int ogl_version_minor);
    GLFWwindow* getWindow();
    void enableVsync(bool enable);
    double getDeltaTime();

    GLFWwindow* window;
};

extern Window window;