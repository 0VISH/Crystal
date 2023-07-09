struct MaterialPanel{
    void init(){
	selectedMat = -1;
	mat = nullptr;
    };
    void renderMaterialInfo(){
	if(mat == nullptr){return;};
	if(ImGui::Begin("Material Info")){
	    ImGui::End();
	};
    };
    void render(){
	MaterialSystem &ms = engine->ms;
	if(ImGui::Begin("Material Panel")){
	    u32 x = 0;
	    /*
	      for(auto const &pair: ms.matNameToOff){
	      if(ImGui::Selectable(pair.first.c_str(), selectedMat == x)){
	      selectedMat = x;
	      mat = &ms.materials[pair.second];
	      };
	      };
	    */
	    ImGui::End();
	};
    };
    s32 selectedMat;
    Material *mat;
};
