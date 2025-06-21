#include <ui.h>
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GRID/GRID_widget.h>
#include <GLFW/glfw3.h>
#include <window.h>
#include <implot.h>
#include <string>
#include <settings.h>

UI ui;

UI::UI() {
}

UI::~UI() {
}

void UI::destroy() {
    for (GRID_Widget* widget : m_widgets) {
        delete widget;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void UI::init(GLFWwindow* window, int ogl_version_major, int ogl_version_minor) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    static std::string iniPath = settings.getRelativePath() + "/" + settings.getSetting<std::string>("guiConfig");
	io.IniFilename = iniPath.c_str();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    std::string versionString = "#version " + std::to_string(ogl_version_major) + std::to_string(ogl_version_minor) + "0";
    ImGui_ImplOpenGL3_Init(versionString.c_str());
}

void UI::addWidget(GRID_Widget* widget) {
    m_widgets.push_back(widget);
}

void preRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void postRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void renderDockingSpace() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("dockingSpace", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImGui::DockSpace(ImGui::GetID("DockSpace"), ImVec2(0.0f, 0.0f));
	ImGui::End();

    ImGui::PopStyleVar(3);
}

void UI::render() {
    preRender();
    renderDockingSpace();
    for (GRID_Widget* widget : m_widgets) {
        widget->render();
    }
    postRender();
}