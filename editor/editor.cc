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

bool isKeyDown(ButtonCode code);
Console console;

void openGameFolder(){
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    IFileOpenDialog* pFileOpen;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOpen));

    if (SUCCEEDED(hr)) {
        DWORD dwOptions;
        pFileOpen->GetOptions(&dwOptions);
        pFileOpen->SetOptions(dwOptions | FOS_PICKFOLDERS); // Set the folder selection option

        if (pFileOpen->Show(NULL) == S_OK) {
            IShellItem* pItem;
            if (pFileOpen->GetResult(&pItem) == S_OK) {
                PWSTR folderPath;
                pItem->GetDisplayName(SIGDN_FILESYSPATH, &folderPath);

                // Convert the folderPath from wide character to multi-byte character
                int bufferSize = WideCharToMultiByte(CP_UTF8, 0, folderPath, -1, NULL, 0, NULL, NULL);
                char* folderPathUtf8 = (char*)mem::alloc(bufferSize);
                WideCharToMultiByte(CP_UTF8, 0, folderPath, -1, folderPathUtf8, bufferSize, NULL, NULL);

                setGameFolder(folderPathUtf8);

		mem::free(folderPathUtf8);
                CoTaskMemFree(folderPath);
                pItem->Release();
            }
        }
        pFileOpen->Release();
    }

    CoUninitialize();
};

namespace Editor{ 
    EntityPanel ep;
    bool showDemo;
    u32 *drawCalls;
    
    EXPORT void init(HWND window, u32 *batchDrawCall){
	drawCalls = batchDrawCall;
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
	showDemo = false;
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
		if (ImGui::MenuItem("Open")){
		    openGameFolder();
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
	    ImGui::Text("Frame rate: %f\t\t\t\t\tDraw calls: %d", ImGui::GetIO().Framerate, *drawCalls);
	    if(ImGui::IsWindowHovered()){
		
	    };
		
	    float width = ImGui::GetContentRegionAvail().x;
	    float height = ImGui::GetContentRegionAvail().y;

	    /*
	    if(engine->curScene != nullptr){
#pragma warning(disable: 4312)
	    ImGui::Image(
			 (ImTextureID)engine->fb.texture, 
			 ImGui::GetContentRegionAvail(), 
			 ImVec2(0, 1), 
			 ImVec2(1, 0)
			 );
#pragma warning(default: 4312)
	    };
	    */
	    ImGui::End();
	}

	
	
	//DOCKING
	ImGui::End();
	
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
    };
};

#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
