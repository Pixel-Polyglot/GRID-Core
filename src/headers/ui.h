#pragma once
#include <GRID/GRID_widget.h>
#include <vector>

struct GLFWwindow;

class UI {
public:
    UI();
    ~UI();
    void init(GLFWwindow* window, int ogl_version_major, int ogl_version_minor);
    void render();
    void addWidget(GRID_Widget* widget);
    void destroy();

private:
    std::vector<GRID_Widget*> m_widgets;
};

extern UI ui;