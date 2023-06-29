struct Vision{
    bool showDemoWindow;
    bool showConsole;
    Console console;

    void init(){
	showDemoWindow = false;
	showConsole = true;
#if(RCONTEXT_GL)
	char *backend = "OpenGL";
#endif
	console.AddLog("[RENDER CONTEXT]: %s %s", backend, engine->r.getRenderContextInfoString());
    };
    void render(){
	ImGui::Begin("Vision");
	ImGui::Text("Frame rate: %f", ImGui::GetIO().Framerate);
	if(ImGui::BeginTabBar("MyTabBar")){
	    if(ImGui::BeginTabItem("Engine")){
		if(ImGui::TreeNode("Layer Manager")){
		    ImGui::Text("layers: %p\ncount: %d", engine->lm.layers, engine->lm.layerCount);
		    ImGui::TreePop();
		};
		if(ImGui::TreeNode("Renderer")){
		    Renderer &r = engine->r;
		    ImGui::Text("shaderProgram: %d\nqvao: %d\nqvbo: %d\nqibo: %d\n", r.shaderProgram, r.qvao, r.qvbo, r.qibo);
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
	    if(ImGui::BeginTabItem("Windows")){
		if(ImGui::SmallButton("Demo Window")){
		    showDemoWindow = true;
		};
		if(ImGui::SmallButton("Console")){
		    showConsole = true;
		};
		ImGui::EndTabItem();
	    };
	    ImGui::EndTabBar();
	};
	ImGui::End();
	if(showDemoWindow){
	    ImGui::ShowDemoWindow(&showDemoWindow);
	};
	if(showConsole){
	    console.Draw("Console", &showConsole);
	};
    };
};
