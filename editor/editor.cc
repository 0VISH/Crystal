#include <stdio.h>
#include <windows.h>
#include <Commdlg.h>
#include <ShObjIdl.h>
#include <ShlObj.h>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include "game.hh"
#include "console.cc"
#include "entityPanel.cc"

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
	    }else if(memcmp("scene", charMem+start, x-start-1) == 0){
		curScenePath = getName(charMem, x);
		setScene(curScenePath);
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
    bool showDemo;
    u32 *drawCalls;
    Console console;
    Renderer *r;
    u32 *gameTexture;
    char *levelName = nullptr;

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
	gameTexture = nullptr;
	auto *engine = getEngine();
	r = &engine->r;
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
	console.init();
	print = addLog;
	showDemo = false;
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
    EXPORT bool update(Event e, f64 dt){
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
	    if(ImGui::BeginMenu("File")){
		if(ImGui::MenuItem("Open Cry File")){
		    openCryFile();
		};
		if(ImGui::MenuItem("Save")){
		    Scene *s = getEngine()->curScene;
		    if(s == nullptr){
			print("[error] No scene to save");
		    }else{
			saveLevel();
		    };
		};
		ImGui::EndMenu();
	    };
	    if(ImGui::BeginMenu("Engine")){
		if(ImGui::MenuItem("New Scene")){
		    Scene *s = getEngine()->curScene;
		    if(s != nullptr){
			uninitAndFreeCurrentScene();
		    };
		    allocAndSetCurrentScene();
		    initCurrentScene(5);
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
	    ImGui::Text("Frame rate: %f\t\t\t\t\tDraw calls: %d", ImGui::GetIO().Framerate, r->drawCalls);
		
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
	console.Draw("Console");
	if(showDemo){ImGui::ShowDemoWindow(&showDemo);};

        ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };
    EXPORT void uninit(){
	console.uninit();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
	if(gameCodePath != nullptr){mem::free(gameCodePath);};
	if(materialSystemPath != nullptr){mem::free(materialSystemPath);};
	if(curScenePath != nullptr){mem::free(curScenePath);};
    };
};

#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
