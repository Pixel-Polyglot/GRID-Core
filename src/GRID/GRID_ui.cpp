#include <GRID/GRID_ui.h>
#include <ui.h>
#include <imgui.h>

void GRID_UI::addWidget(GRID_Widget* widget) {
    ui.addWidget(widget);
}

bool GRID_UI::isWindowHovered() {
    return ImGui::IsWindowHovered();
}

void GRID_UI::begin(const char* name, bool padding) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    styles = 2;
    if (!padding) {
    	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        styles += 1;
    }

    ImGui::Begin(name, nullptr);
}

void GRID_UI::end() {
    ImGui::End();

    ImGui::PopStyleVar(styles);
}

void GRID_UI::text(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
}

bool GRID_UI::checkbox(const char* label, bool* v) {
    return ImGui::Checkbox(label, v);
}

bool GRID_UI::inputText(const char* label, char* buf, size_t buf_size) {
    return ImGui::InputText(label, buf, buf_size);
}

bool GRID_UI::button(const char* label) {
    return ImGui::Button(label);
}

void GRID_UI::image(void* user_texture_id, const GRID_Vec2f& image_size, const GRID_Vec2f& uv0, const GRID_Vec2f& uv1) {
    ImGui::Image(user_texture_id, ImVec2(image_size.x, image_size.y), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y));
}

GRID_Vec2f GRID_UI::getContentRegionAvail() {
    ImVec2 avail = ImGui::GetContentRegionAvail();
    return GRID_Vec2f(avail.x, avail.y);
}