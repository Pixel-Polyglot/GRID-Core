#include <GRID/GRID_ui.h>
#include <ui.h>
#include <imgui.h>

void GRID_UI::addWidget(GRID_Widget* widget) {
    ui.addWidget(widget);
}

bool GRID_UI::isWindowHovered() {
    return ImGui::IsWindowHovered();
}

void GRID_UI::begin(std::string name, bool padding) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    m_styles = 2;
    if (!padding) {
    	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        m_styles += 1;
    }

    ImGui::Begin(name.c_str(), nullptr);
}

void GRID_UI::end() {
    ImGui::End();

    ImGui::PopStyleVar(m_styles);
}

void GRID_UI::text(std::string text) {
    ImGui::Text(text.c_str());
}

bool GRID_UI::checkbox(std::string label, bool* v) {
    return ImGui::Checkbox(label.c_str(), v);
}

bool GRID_UI::inputText(std::string label, char* buf, size_t buf_size) {
    return ImGui::InputText(label.c_str(), buf, buf_size);
}

bool GRID_UI::button(std::string label) {
    return ImGui::Button(label.c_str());
}

void GRID_UI::image(void* user_texture_id, const GRID_Vec2f& image_size, const GRID_Vec2f& uv0, const GRID_Vec2f& uv1) {
    ImGui::Image(user_texture_id, ImVec2(image_size.x, image_size.y), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y));
}

GRID_Vec2f GRID_UI::getContentRegionAvail() {
    ImVec2 avail = ImGui::GetContentRegionAvail();
    return GRID_Vec2f(avail.x, avail.y);
}