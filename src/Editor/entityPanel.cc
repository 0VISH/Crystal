struct EntityPanel{
    void init(){
	selectedEntity = -1;
    };

    void drawTransformComponent(Component::Transform *t){
	ImGui::Text("TRANSFORM");
	ImGui::DragFloat3("Position", glm::value_ptr(t->mat[3]), 0.25);
    };
    void renderEntities(){
	if(ImGui::Begin("Entities")){
	    Scene *s = engine->curScene;
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
