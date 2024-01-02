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

    template<typename T, typename Function>
    void drawComponent(char *name, Entity e, Scene *s, ComponentID id,  Function func){
	auto *t = (T*)getComponent(e, (u32)id);
	if(t == nullptr){return;};
	const ImGuiTreeNodeFlags f = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
	ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	if(ImGui::TreeNodeEx(name, f)){
	    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
	    if(ImGui::Button("-", ImVec2{ lineHeight, lineHeight })){
	        removeComponent(e, (u32)id);
		ImGui::TreePop();
		return;
	    };

	    func(t, s, e);

	    ImGui::TreePop();
	};
    };
    void renderEntities(){
	if(ImGui::Begin("Entities")){
	    Scene *s = getEngine()->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    const u32 MAX_NAME = 50;
	    char entityName[MAX_NAME] = {0};
	    if(ImGui::InputText("New Entity", entityName, MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue)){
		if(entityName[0] == 0){
		    print("[error] Entity name not provided");
		}else{
		    Entity e = sceneNewEntity(entityName);
		};
	    };
	    u32 x = 0;
	    const char *key;
	    map_iter_t iter = map_iter(&s->entityNameToID);
	    while(key = map_next(&s->entityNameToID, &iter)){
		if(ImGui::Selectable(key, selectedEntity == x)){
		    selectedEntity = x;
		    e = *map_get(&s->entityNameToID, key);
		};
		x += 1;
	    };
	    ImGui::End();
	};
    };
    void renderComponents(){
	if(ImGui::Begin("Components")){
	    Scene *s = getEngine()->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    if(selectedEntity == -1){
		ImGui::End();
		return;
	    };
	    if(ImGui::Button("Add component")){ImGui::OpenPopup("Add component");};
	    if(ImGui::BeginPopup("Add component")){
		if(ImGui::MenuItem("Transform")){
		    addComponent<Component::Transform>(e, ComponentID::TRANSFORM);
		    ImGui::CloseCurrentPopup();
		};
		if(ImGui::MenuItem("PCamera")){
		    addComponent<Component::PCamera>(e, ComponentID::PCAMERA);
		    ImGui::CloseCurrentPopup();
		};
		if(ImGui::MenuItem("RigidBody")){
		    addComponent<Component::RigidBody>(e, ComponentID::RIGIDBODY);
		    ImGui::CloseCurrentPopup();
		};
		if(ImGui::MenuItem("Box Collider")){
		    addComponent<Component::BoxCollider>(e, ComponentID::BOXCOLLIDER);
		    ImGui::CloseCurrentPopup();
		};
		ImGui::EndPopup();
	    };
	    drawComponent<Component::Transform>("Transform", e, s, ComponentID::TRANSFORM, [](auto *c, Scene *s, Entity e){
		DrawVec3Control("Position", c->position);
		DrawVec3Control("Rotation", c->rotation);
		DrawVec3Control("Scale", c->scale);
	    });
	    drawComponent<Component::PCamera>("PCamera", e, s, ComponentID::PCAMERA, [](auto *c, Scene *s, Entity e){
		DrawVec3Control("Position", c->pos);
		ImGui::DragFloat("Zoom Level", &c->zoomLevel);
		ImGui::DragFloat("Aspect Ratio", &c->aspectRatio);
		ImGui::DragFloat("Field Of View", &c->fieldOfView);
		if(ImGui::Button("Set Active")){
		    s->activeCam = e;
		};
	    });
	    drawComponent<Component::RigidBody>("RigidBody", e, s, ComponentID::RIGIDBODY, [](auto *c, Scene *s, Entity e){
		ImGui::Checkbox("Fixed Rotation", &c->fixedRotation);
	    });
	    drawComponent<Component::BoxCollider>("Box Collider", e, s, ComponentID::BOXCOLLIDER, [](auto *c, Scene *s, Entity e){
		ImGui::DragFloat("Friction", &c->friction);
		ImGui::DragFloat("Density", &c->density);
	    });
	    ImGui::End();
	};
    };

    s32 selectedEntity;
    Entity e;
};
