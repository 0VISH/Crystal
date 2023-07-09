namespace Editor{ 
    Component::Camera cam;
    Vision vs;
    Console console;
    EntityPanel ep;
    bool showDemo;
    
    void init(window::Window window){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_InitForOpenGL(window);
	ImGui_ImplOpenGL3_Init();
	io.Fonts->AddFontFromFileTTF("resources/Roboto-Regular.ttf", 17.0f);

	vs.init();
	ep.init();
	console.init();
	showDemo = false;

	cam.init();
	cam.initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
    };
    bool onUpdate(Event e, f64 dt){
	//FEEDING IMGUI EVENTS
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if(isMouseButtonEvent(e)){
	    io.AddMouseButtonEvent((s32)e.buttonCode, e.type == EventType::MOUSE_BUTTON_DOWN);
	}else if(e.type == EventType::MOUSE_SCROLL){
	    io.AddMouseWheelEvent(0.0f, e.scroll / 120);
	}else if(isKeyboardButtonEvent(e)){
	    //TODO: WTFFFFFFFFFF WHY NO WORK???????
	};

	//NEW FRAME
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

	//DOCKSPACE
	bool dockspaceOpen = true;
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode){window_flags |= ImGuiWindowFlags_NoBackground;};
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
	    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	style.WindowMinSize.x = minWinSizeX;

	if(ImGui::BeginMenuBar()){
	    if(ImGui::BeginMenu("Windows")){
		if (ImGui::MenuItem("ImGui Demo")){
		    showDemo = !showDemo;
		};
		ImGui::EndMenu();
	    };
	    ImGui::EndMenuBar();
	};
	
	if(ImGui::Begin("Scene")){
	    ImGui::Text("Frame rate: %f\t\t\t\t\tDraw calls: %d", ImGui::GetIO().Framerate, engine->br.drawCalls);
	    if(ImGui::IsWindowHovered()){
		if(isKeyboardButtonEvent(e) && isKeyDown(ButtonCode::Key_LeftShift)){
		    const float cameraSpeed = 5;
		    if(e.type == EventType::KEY_DOWN){
			switch(e.buttonCode){
			case ButtonCode::Key_W:cam.pos.y += cameraSpeed * dt;break;
			case ButtonCode::Key_S:cam.pos.y -= cameraSpeed * dt;break;
			case ButtonCode::Key_D:cam.pos.x += cameraSpeed * dt;break;
			case ButtonCode::Key_A:cam.pos.x -= cameraSpeed * dt;break;
			};
		    };
		}else if(e.type == EventType::MOUSE_SCROLL){
		    cam.updateZoomLevel(e.scroll/100);
		};
	    };
		
	    float width = ImGui::GetContentRegionAvail().x;
	    float height = ImGui::GetContentRegionAvail().y;
		
	    ImGui::Image(
			 (ImTextureID)engine->fb.texture, 
			 ImGui::GetContentRegionAvail(), 
			 ImVec2(0, 1), 
			 ImVec2(1, 0)
			 );
	    ImGui::End();
	}

	
	
	//DOCKING
	ImGui::End();

	//UPDATE EDITOR CAMERA
	cam.calculateViewMat();
	engine->ss.setCameraProjectionViewMatrix(cam.projection * cam.view);
	
	return io.WantCaptureMouse || io.WantCaptureKeyboard;
    };
    void onRender(){
	ep.renderEntities();
	ep.renderComponents();
       	vs.render();
	console.Draw("Console");
	if(showDemo){ImGui::ShowDemoWindow(&showDemo);};

        ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };
    void onUninit(){
	console.uninit();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
    };
};


#if(DBG)
#define LOG(fmt, ...) Editor::console.AddLog(fmt, __VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif
