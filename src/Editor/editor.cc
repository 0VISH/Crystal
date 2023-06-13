#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../../vendor/imgui/backends/imgui_impl_win32.h"

namespace Editor{
    void init(window::Window window){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_InitForOpenGL(window);
	ImGui_ImplOpenGL3_Init();
    };
    bool onUpdate(Event e){
	log("updating\n");
	return false;
    };
    void onRender(){
	log("rendering\n");
    };
    void onUninit(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
    };
};
