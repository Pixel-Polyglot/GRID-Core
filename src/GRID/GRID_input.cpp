#include <GRID/GRID_input.h>
#include <imgui.h>

GRID_Vec2f GRID_Input::getMousePos() {
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 mousePos = ImGui::GetMousePos();
    return GRID_Vec2f(mousePos.x, mousePos.y);
}

bool GRID_Input::isMouseButtonDown(MouseButton button) {
    ImGuiIO& io = ImGui::GetIO();
    return io.MouseDown[(int)button];
}

float GRID_Input::getMouseWheel() {
    ImGuiIO& io = ImGui::GetIO();
    return io.MouseWheel;
}