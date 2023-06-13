#include "../include.hh"

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../../vendor/imgui/backends/imgui_impl_win32.h"

s32 main(){
    EventDispatcher eventDispatcher;
    window::Window window = window::create("crytal test", &eventDispatcher);
    if(window == NULL){
	log("Could not open a window");
	return EXIT_SUCCESS;
    };
    RenderContext::init(window);
    crystal::init();

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
    bool show_demo_window = true;
    
    while(window::shouldClose == false){
	window::pollEvents();
	crystal::update();
	dumpEvent(eventDispatcher.event);
	
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
	ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::Render();

	glClear(GL_COLOR_BUFFER_BIT);
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	
	RenderContext::swapBuffers();
    };

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    
    crystal::uninit();
    RenderContext::uninit(window);
    window::destroy(window);
    dlog("\nDONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
