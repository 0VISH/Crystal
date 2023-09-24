struct MaterialPanel{
    u32 selectedID;

    void init(){selectedID = -1;};
    
    void showMatNames(){
	if(ImGui::Begin("Materials")){
	    Scene *s = engine->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    const u32 MAX_NAME = 50;
	    char matName[MAX_NAME] = "TODO: RMEMOVE ME";
	    char shaderName[MAX_NAME] = {0};
	    shaderName[0] = 1;    //TODO: remove
	    ImGui::InputText("Material Name", matName, MAX_NAME);
	    ImGui::InputText("Shader Name", shaderName, MAX_NAME);
	    if(ImGui::Button("New Material")){
		if(matName[0] == 0){
		    print("[error] Material name not provided");
		}else if(shaderName[0] == 0){
		    print("[error] Shader name not provided");
		}else{
		    //TODO: get shader id from name
		    newMaterial(matName, 1);
		};
	    };

	    MaterialSystem *ms = engine->ms;
	    for(u32 x=0; x<ms->materials.count; x+=1){
		Material &mat = ms->materials[x];
		if(ImGui::Selectable(mat.name, selectedID == x)){
		    selectedID = x;
		};
	    };
	
	    ImGui::End();
	};
    };
    void showSelectedMatInfo(){
	if(ImGui::Begin("Material Info")){
	    if(selectedID == -1){
		ImGui::End();
		return;
	    };
	    Material &mat = engine->ms->materials[selectedID];
	    ImGui::Text("%s: %d", mat.name, mat.id);
	    ImGui::ColorEdit4("Colour", (float*)&mat.col, ImGuiColorEditFlags_AlphaPreview);
	    ImGui::Text("Shader ID: %d", mat.shader);

	    if(ImGui::TreeNodeEx("Show Entities")){
		for(u32 x=0; x<mat.registeredEntities.count; x+=1){
		    ImGui::Text("%d", mat.registeredEntities[x]);
		};
		ImGui::TreePop();
	    };
	    const u32 MAX_NAME = 50;
	    char entityName[MAX_NAME] = "TODO: REMOVE ME";
	    ImGui::InputText("Register Entity", entityName, MAX_NAME);
	    
	    if(ImGui::Button("Add Entity")){
		Entity e = getEntity(entityName);
		if(e != -1){
		    materialRegisterEntity(mat, e);
		}else{print("[error] Invalid entity name");};
	    };
	    ImGui::End();
	};
    };
};
