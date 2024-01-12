struct MaterialPanel{
    u32 selectedID;

    void init(){
	selectedID = -1;
    };
    
    void showMatNames(){
	if(ImGui::Begin("Materials")){
	    Scene *s = engine->curScene;
	    if(s == nullptr){
		ImGui::End();
		return;
	    };
	    const u32 MAX_NAME = 50;
	    char matName[MAX_NAME] = {0};
	    char shaderName[MAX_NAME] = "default";
	    if(ImGui::InputText("New Material", matName, MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue)){
		if(matName[0] != 0){
		    if(shaderName[0] != 0){
			if(shaderName[0] != 0){
			    newMaterial(matName, shaderName);
			};
		    }else{
			print("[error] Shader name not provided");
		    }
		}else{
		    print("[error] Material name not provided");
		};
	    };
	    ImGui::InputText("Shader Name", shaderName, MAX_NAME);
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
	    ImGui::Text("Texture ID: %d", mat.textureId);

	    const u32 MAX_NAME = 50;
	    char textureName[MAX_NAME] = {0};
	    if(ImGui::InputText("Add Texture", textureName, MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue)){
		if(textureName[0] == 0){
		    print("[error] Texture name not provided");
		}else{
		    MaterialSystem *ms = engine->ms;
		    u32 id;
		    if(engine->textures.getValue({textureName, (u32)strlen(textureName)}, &id)){
			mat.textureId = id;
		    }else{
			s32 id = loadTexture(textureName, mat.shader);
			if(id == -1){
			    print("[error] invalid path provided for texture: %s", textureName);
			}else{
			    mat.textureId = id;
			};
		    };
		};
	    };
	    if(ImGui::TreeNodeEx("Show Entities")){
		for(u32 x=0; x<mat.registeredEntities.count; x+=1){
		    ImGui::Text("%d", mat.registeredEntities[x]);
		};
		ImGui::TreePop();
	    };
	    char entityName[MAX_NAME] = {0};
	    if(ImGui::InputText("Register Entity", entityName, MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue)){
		if(entityName[0] == 0){
		    print("[error] Entity name not provided");
		}else{
		    Entity e = getEntity(entityName);
		    if(e != -1){
			materialRegisterEntity(mat, e);
		    };
		};
	    };
	    ImGui::End();
	};
    };
};
