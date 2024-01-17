#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <windows.h>
#include <Commdlg.h>
#include <ShObjIdl.h>
#include <ShlObj.h>
#include "stb_image.hh"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imGuizmo.h"
#if(GL)
#include "backends/imgui_impl_opengl3.h"
#endif
#include "backends/imgui_impl_win32.h"
#include "game.hh"

Entity selectedEntity = -1;

#include "console.cc"
#include "entityPanel.cc"
#include "materialPanel.cc"

Crystal *engine;
char *gameCodePath = nullptr;
char *curScenePath = nullptr;
char *materialSystemPath = nullptr;

bool openFileDialog(char *filter, char *buffer){
    OPENFILENAME ofn;

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if(GetOpenFileName(&ofn)){return true;};
    return false;
};
void eatEmptySpaces(char *buff, u32 &x){
    u32 y = x;
    while(true){
	switch(buff[y]){
	case ' ':
	case '\t':
	case '\n':
	    y += 1;
	    break;
	default:
	    x = y;
	    return;
	};
    };
};
char *getName(char *charMem, u32 &x){
    eatEmptySpaces(charMem,x);
    u32 start = x;
    while(charMem[x] != '\n'){x+=1;};
    x += 1;
    u32 len = x - start - 1;
    char *str = (char*)mem::alloc(len);
    memcpy(str, charMem+start, len-1);
    str[len-1] = '\0';
    return str;
};
void openCryFile(){
    char path[MAX_PATH] = "";

    if(openFileDialog("Crystal Project File (*.cry)\0*.cry\0All Files (*.*)\0*.*\0", path)){
	FILE *f = fopen(path, "rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	void *mem = mem::calloc(size);
	fread(mem, size, 1, f);
	fclose(f);
	char *charMem = (char*)mem;

	u32 x = 0;
	while(true){
	    eatEmptySpaces(charMem, x);
	    u32 start = x;
	    while(charMem[x] != ':'){x += 1;};
	    x += 1;
	    if(memcmp("game code", charMem+start, x-start-1) == 0){
		gameCodePath = getName(charMem, x);
		setGameCode(gameCodePath);
	    }else if(memcmp("material system", charMem+start, x-start-1) == 0){
		materialSystemPath = getName(charMem, x);
		setMaterialSystem(materialSystemPath);
	    }else if(memcmp("scene", charMem+start, x-start-1) == 0){
		curScenePath = getName(charMem, x);
		setScene(curScenePath);
		if(engine->curScene){engine->curScene->state = SceneState::NONE;};
	    }else if(memcmp("END", charMem+start, x-start-1)){
		break;
	    }else{
		print("[error] Unkown %.*s", x-start-1, charMem+start);
	    };
	    eatEmptySpaces(charMem, x);
	};
	mem::free(mem);
    }else{
	print("[warning] Project file not selected");
    }
}; 

namespace Editor{ 
    EntityPanel ep;
    MaterialPanel mp;
    bool showDemo;
    u32 *drawCalls;
    Console console;
    Renderer *r;
    u32 *gameTexture;
    char *levelName = nullptr;
    Scene *curScene;

    EXPORT void setGameTextureAdd(u32 *tAdd){
	gameTexture = tAdd;
    };
    EXPORT void addLog(char *fmt, ...){
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf)-1] = 0;
	va_end(args);
	console.Items.push_back(Strdup(buf));
    };
   
    EXPORT void init(HWND window){
	mem::init();
	gameTexture = nullptr;
	engine = getEngine();
	r = &engine->r;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
#if(GL)
	ImGui_ImplWin32_InitForOpenGL(window);
	ImGui_ImplOpenGL3_Init();
#endif
	io.Fonts->AddFontFromFileTTF("editor/assets/Roboto-Regular.ttf", 17.0f);
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	ep.init();
	mp.init();
	console.init();
	print = addLog;
	showDemo = false;
    };
    void saveMS(){
	OPENFILENAME ofn;
	TCHAR szFile[260];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrDefExt = "scn";
	ofn.lpstrFilter = TEXT("Material System (*.ms)\0*.ms\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXTENSIONDIFFERENT;

	if (GetSaveFileName(&ofn) == TRUE) {
	    serializeMaterialSystem(szFile);
	} else {
	    print("[error] User canceled the dialog or an error occurred");
	}
    };
    void saveLevel(){
	if(levelName != nullptr){
	    serializeCurrentScene(levelName);
	    return;
	};
	OPENFILENAME ofn;
	TCHAR szFile[260];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrDefExt = "scn";
	ofn.lpstrFilter = TEXT("Scene File (*.scn)\0*.scn\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXTENSIONDIFFERENT;

	if (GetSaveFileName(&ofn) == TRUE) {
	    serializeCurrentScene(szFile);
	} else {
	    print("[error] User canceled the dialog or an error occurred");
	}
    };
    Scene *deepCopyAndSetCurScene(){
	Scene *cpy = (Scene*)mem::alloc(sizeof(Scene));
	Scene *cur = engine->curScene;
	engine->curScene = cpy;
	cpy->onInit   = cur->onInit;
	cpy->onUpdate = cur->onUpdate;
	cpy->onRender = cur->onRender;
	cpy->onUninit = cur->onUninit;
	cpy->activeCam = cur->activeCam;
	cpy->entityCount = cur->entityCount;
	cpy->id = cur->id;
	cpy->components.init(cur->components.count);
	for(u32 x=0; x<cur->components.count; x+=1){
	    ComponentPool &curcp = cur->components[x];
	    ComponentPool  cpycp;
	    cpycp.componentSize = curcp.componentSize;
	    cpycp.count = curcp.count;
	    cpycp.len = curcp.count;
	    cpycp.entityWatermark = curcp.entityWatermark;
	    u64 memLen = curcp.componentSize * curcp.count;
	    u32 entLen = sizeof(Entity) * curcp.entityWatermark;
	    char *cpyMem = (char*)mem::alloc(memLen);
	    Entity *cpyEntity = (Entity*)mem::alloc(entLen);
	    memcpy(cpyMem, curcp.mem, memLen);
	    memcpy(cpyEntity, curcp.entityToComponentOff, entLen);
	    cpycp.mem = cpyMem;
	    cpycp.entityToComponentOff = cpyEntity;
	    cpy->components.push(cpycp);
	};
	cpy->entityComponentMask.init(cur->entityComponentMask.count);
	for(u32 x=0; x<cur->entityComponentMask.count; x+=1){
	    cpy->entityComponentMask.push(cur->entityComponentMask[x]);
	};
	cpy->entityNameToID.init();
	HashmapStr &map = cur->entityNameToID;
	for(u32 j=0; j<map.len; j+=1){
	    if(map.status[j]){
		String str = map.keys[j];
		u32 e;
		map.getValue(str, &e);
		cpy->entityNameToID.insertValue(str, e);
	    };
	};
	cpy->physicsWorld = new b2World({0.0, -9.8});
	if(cpy->components.count <= (u32)ComponentID::RIGIDBODY){return cpy;};
	ComponentPool &rbp = cpy->components[(u32)ComponentID::RIGIDBODY];
	for(u32 x=0; x<rbp.entityWatermark; x+=1){
	    if(rbp.entityToComponentOff[x] == -1){continue;};
	    auto *rb = (Component::RigidBody*)getComponent(x, ComponentID::RIGIDBODY);
	    rb->initMore(cpy, x);
	};
	if(cpy->components.count <= (u32)ComponentID::BOXCOLLIDER){return cpy;};
	ComponentPool &bcp = cpy->components[(u32)ComponentID::BOXCOLLIDER];
	for(u32 x=0; x<bcp.entityWatermark; x+=1){
	    if(bcp.entityToComponentOff[x] == -1){continue;};
	    auto *bc = (Component::BoxCollider*)getComponent(x, ComponentID::BOXCOLLIDER);
	    bc->initMore(cpy, x);
	};
	return cpy;
    };
    void uninitAndDeepFreeCurrentScene(){
	Scene *s = engine->curScene;
	if(s->onUninit){s->onUninit();};
	s->entityComponentMask.uninit();
	for(u32 x=0; x<s->components.count; x+=1){
	    ComponentPool &cp = s->components[x];
	    //componentPoolUninit(cp);
	    mem::free(cp.mem);
	    mem::free(cp.entityToComponentOff);
	};
	s->components.uninit();
	s->entityNameToID.uninit();
	delete s->physicsWorld;
	mem::free(s);
    };
    EXPORT bool update(Event e, f64 dt){
	//NEW FRAME
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
	ImGuizmo::BeginFrame();
	
	//FEEDING IMGUI EVENTS
	ImGuiIO& io = ImGui::GetIO();
	if(isMouseButtonEvent(e)){
	    io.AddMouseButtonEvent((s32)e.buttonCode, e.type == EventType::MOUSE_BUTTON_DOWN);
	}else if(e.type == EventType::MOUSE_SCROLL){
	    io.AddMouseWheelEvent(0.0f, e.scroll / 120);
	}else if(isKeyboardButtonEvent(e)){
	    ImGuiKey key = ImGuiKey_None;
	    if(e.type == EventType::KEY_DOWN){
		switch(e.buttonCode){
		case ButtonCode::Key_Period:
		    key = (ImGuiKey)'.';
		    break;
		case ButtonCode::Key_Slash:
		    key = (ImGuiKey)'/';
		    break;
		};
		if(e.buttonCode >= ButtonCode::Key_A && e.buttonCode <= ButtonCode::Key_Z){
		    key = (ImGuiKey)((u32)e.buttonCode + ((u32)'a' - (u32)ButtonCode::Key_A));
		};
		io.AddInputCharacter(key);
	    };
	    key = ImGuiKey_None;
	    switch(e.buttonCode){
	    case ButtonCode::Key_Enter:
		key = ImGuiKey_Enter;
		break;
	    case ButtonCode::Key_LeftShift:
		key = ImGuiKey_LeftShift;
		break;
	    case ButtonCode::Key_RightShift:
		key = ImGuiKey_RightShift;
		break;
	    case ButtonCode::Key_Backspace:
		key = ImGuiKey_Backspace;
		break;
	    case ButtonCode::Key_LeftArrow:
		key = ImGuiKey_LeftArrow;
		break;
	    case ButtonCode::Key_RightArrow:
		key = ImGuiKey_RightArrow;
		break;
	    };
	    io.AddKeyEvent(key, e.type == EventType::KEY_DOWN);
	};

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
	    if(ImGui::BeginMenu("File")){
		if(ImGui::MenuItem("Open Cry File")){
		    openCryFile();
		};
		if(ImGui::MenuItem("Save Scene")){
		    Scene *s = engine->curScene;
		    if(s == nullptr){
			print("[error] No scene to save");
		    }else{
			saveLevel();
		    };
		};
		if(ImGui::MenuItem("Save Material System")){
		    saveMS();
		};
		ImGui::EndMenu();
	    };
	    if(ImGui::BeginMenu("Engine")){
		if(ImGui::MenuItem("New Scene")){
		    Scene *s = engine->curScene;
		    if(s != nullptr){
			uninitAndFreeCurrentScene();
		    };
		    allocAndSetCurrentScene();
		    initCurrentScene(5);
		    engine->curScene->state = SceneState::NONE;
		};
		ImGui::EndMenu();
	    };
	    if(ImGui::BeginMenu("Windows")){
		if (ImGui::MenuItem("ImGui Demo")){
		    showDemo = !showDemo;
		};
		ImGui::EndMenu();
	    };
	    ImGui::EndMenuBar();
	};
	
	if(ImGui::Begin("Scene")){
	    engine->windowX = ImGui::GetWindowWidth();
	    engine->windowY = ImGui::GetWindowHeight();
	    ImGui::Text("Frame rate: %f\t\t\t\t\tDraw calls: %d", ImGui::GetIO().Framerate, r->drawCalls);
	    if(engine->curScene != nullptr){
		ImGui::Text("-");
		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x * 0.5);

		SceneState sceneState = engine->curScene->state;
		if(sceneState == SceneState::NONE){
		    if(ImGui::Button("PLAY")){
			curScene = engine->curScene;
			deepCopyAndSetCurScene();
			engine->curScene->state = SceneState::PLAYING;
			if(engine->curScene->onInit){
			    engine->curScene->onInit();
			};
		    };
		}else if(sceneState == SceneState::PLAYING){
		    if(ImGui::Button("PAUSE")){
			engine->curScene->state = SceneState::PAUSED;
			Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
		    };
		    ImGui::SameLine();
		    if(ImGui::Button("STOP")){
			Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
			uninitAndDeepFreeCurrentScene();
			engine->curScene = curScene;
			curScene = nullptr;
		    };
		}else if(sceneState == SceneState::PAUSED){
		    if(ImGui::Button("PLAY")){
			engine->curScene->state = SceneState::PLAYING;
			Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
		    };
		    ImGui::SameLine();
		    if(ImGui::Button("STOP")){
			Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
			uninitAndDeepFreeCurrentScene();
			engine->curScene = curScene;
			curScene = nullptr;
		    };
		};
	    };
	    float width = ImGui::GetContentRegionAvail().x;
	    float height = ImGui::GetContentRegionAvail().y;

	    if(gameTexture != nullptr){
#pragma warning(disable: 4312)
	    ImGui::Image(
			 (ImTextureID)(*gameTexture), 
			 ImGui::GetContentRegionAvail(), 
			 ImVec2(0, 1), 
			 ImVec2(1, 0)
			 );
#pragma warning(default: 4312)
	    };

	    Scene *s = engine->curScene;
	    if(selectedEntity != -1 && s->activeCam != -1){
		auto *pcam = (Component::PCamera*)getComponent(s->activeCam, ComponentID::PCAMERA);
		auto *trans = (Component::Transform*)getComponent(selectedEntity, ComponentID::TRANSFORM);
		if(trans != nullptr){
		    ImGuizmo::SetOrthographic(true);
		    ImGuizmo::SetDrawlist();
		    auto pos = ImGui::GetWindowPos();
		    ImGuizmo::SetRect(pos.x, pos.y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		    glm::mat4 view = pcam->calculateViewMat();
		    glm::mat4 &projection = pcam->projection;
		    glm::mat4 transform = trans->genMatrix();
		    ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));
		    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), (float*)&trans->translation, (float*)&trans->rotation, (float*)&trans->scale);
		};
	    };
	    ImGui::End();
	}

	//DOCKING
	ImGui::End();

	if(isKeyboardButtonEvent(e)){
	    if(e.buttonCode == ButtonCode::Key_R && isKeyDown(ButtonCode::Key_LeftShift)){
		editorSignal();
	    };
	};
	return io.WantCaptureMouse || io.WantCaptureKeyboard;
    };
    EXPORT void render(){
	ep.renderEntities();
	ep.renderComponents();
	mp.showMatNames();
	mp.showSelectedMatInfo();
	console.Draw("Console");
	if(showDemo){ImGui::ShowDemoWindow(&showDemo);};

        ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };
    EXPORT void uninit(){
	if(curScene != nullptr){
	    uninitAndDeepFreeCurrentScene();
	    engine->curScene = curScene;
	};
	console.uninit();

#if(GL)
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif
	ImGui::DestroyContext();
	
	if(gameCodePath != nullptr){mem::free(gameCodePath);};
	if(materialSystemPath != nullptr){mem::free(materialSystemPath);};
	if(curScenePath != nullptr){mem::free(curScenePath);};
	mem::uninit();
    };
};

#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
