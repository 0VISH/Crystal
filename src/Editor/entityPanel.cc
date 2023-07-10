#include "imgui_internal.h"
//THANK YOU CHERNO!!
void DrawVec3Control(char *label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f){
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label);

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label);
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
	values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
	values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
	values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}

struct EntityPanel{
    void init(){
	selectedEntity = -1;
    };

    void drawTransformComponent(Component::Transform *t){
	ImGui::Text("TRANSFORM");
	DrawVec3Control("position", t->position);
	DrawVec3Control("rotation", t->rotation);
	DrawVec3Control("scale", t->scale);
    };
    void renderEntities(){
	if(ImGui::Begin("Entities")){
	    Scene *s = engine->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    u32 x = 0;
	    for(auto const &pair: s->entityNameToEntity){
		if(ImGui::Selectable(pair.first.c_str(), selectedEntity == x)){
		    selectedEntity = x;
		    e = pair.second;
		};
		x += 1;
	    };
	    ImGui::End();
	};
    };
    void renderComponents(){
	if(ImGui::Begin("Components")){
	    Scene *s = engine->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    if(selectedEntity == -1){
		ImGui::End();
		return;
	    };

	    Component::Transform *T = s->getComponent<Component::Transform>(e);
	    if(T != nullptr){drawTransformComponent(T);};
	    
	    ImGui::End();
	};
    };

    s32 selectedEntity;
    Entity e;
};
