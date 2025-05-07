#pragma once
#include <GRID/widget.h>
#include <vector>

class GLFWwindow;

class UI {
public:
    UI();
    ~UI();
    void init(GLFWwindow* window, int ogl_version_major, int ogl_version_minor);
    void render();
    void addWidget(Widget* widget);
    void destroy();

private:
    std::vector<Widget*> widgets;
};

extern UI ui;