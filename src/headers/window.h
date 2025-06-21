#pragma once
#include <iostream>
#include <glm/glm.hpp>

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();
    void destroy();
    void init(const char* name, glm::ivec2 size, int ogl_version_major, int ogl_version_minor);
    GLFWwindow* getWindow();
    void enableVsync(bool enable);
    double getDeltaTime();
    void setDeltaTime();

    GLFWwindow* window;
    
private:
    double m_lastTime;
    double m_deltaTime;
};

extern Window window;