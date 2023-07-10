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
		    ImGui::Text("materials: %p\ncount: %d", ms.materials.mem, ms.materials.count);
		    ImGui::TreePop();
		};
		if(ImGui::TreeNode("Shader System")){
		    ShaderSystem &ss = engine->ss;
		    ImGui::Text("shader programs: %p\nshader count: %d", ss.shaderPrograms.mem, ss.shaderPrograms.count);
		    ImGui::TreePop();
		};
		if(ImGui::TreeNode("Frame Buffer")){
		    FrameBuffer &fbo = engine->fb;
		    ImGui::Text("fbo: %d\nrbo: %d\n texture: %d", fbo.fbo, fbo.rbo, fbo.texture);
		    ImGui::TreePop();
		};
		ImGui::Text("windowX: %d\nwindowY: %d\ncurrent scene: %p", engine->windowX, engine->windowY, engine->curScene);
		if(engine->curScene != nullptr){
		    ImGui::Text("current scene ID: %d", engine->curScene->id);
		};
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
