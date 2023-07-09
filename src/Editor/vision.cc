struct Vision{
    bool showDemoWindow;

    void init(){
	showDemoWindow = false;
    };
    void render(){
	ImGui::Begin("Vision");
	if(ImGui::BeginTabBar("MyTabBar")){
	    if(ImGui::BeginTabItem("Engine")){
		if(ImGui::TreeNode("Layer Manager")){
		    ImGui::Text("layers: %p\ncount: %d", engine->lm.layers, engine->lm.layerCount);
		    ImGui::TreePop();
		};
		if(ImGui::TreeNode("Material System")){
		    MaterialSystem &ms = engine->ms;
		    ImGui::Text("materials: %p\ncount: %d\n", ms.materials.mem, ms.materials.count);
		    ImGui::TreePop();
		};
		ImGui::Text("windowX: %d\nwindowY: %d\n", engine->windowX, engine->windowY);
		ImGui::EndTabItem();
	    }
	    ImGui::EndTabBar();
	};
	ImGui::End();
	if(showDemoWindow){
	    ImGui::ShowDemoWindow(&showDemoWindow);
	};
    };
};
