#include <GRID/window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window window = Window();

Window::Window() {
}

Window::~Window() {
}

void Window::destroy() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::init(std::string name, int width, int height, int ogl_version_major, int ogl_version_minor) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ogl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ogl_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RED_BITS, 32);
    glfwWindowHint(GLFW_GREEN_BITS, 32);
    glfwWindowHint(GLFW_BLUE_BITS, 32);

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    for(int i = 0; i < count; i++) {
        std::cout << glfwGetMonitorName(monitors[i]) << std::endl;
    }

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    // window = glfwCreateWindow(2560, 1440, name.c_str(), monitors[1], NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::enableVsync(bool enable) {
    glfwSwapInterval(enable);
}