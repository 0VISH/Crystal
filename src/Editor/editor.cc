#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../../vendor/imgui/backends/imgui_impl_win32.h"

namespace Editor{
    Component::Camera cam;
    void init(window::Window window){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_InitForOpenGL(window);
	ImGui_ImplOpenGL3_Init();
	io.Fonts->AddFontFromFileTTF("resources/Roboto-Regular.ttf", 17.0f);

	cam.init();
	cam.initPerspective(45, 1280/720, glm::vec3(0.0f, 0.0f, 3.0f));
	cam.calculateViewMat();
	engine->r.setMat4Uniform(cam.projection * cam.view, "uProjectionView");
    };
    bool onUpdate(Event e, f64 dt){
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if(isMouseButtonEvent(e)){
	    io.AddMouseButtonEvent((s32)e.buttonCode, e.type == EventType::MOUSE_BUTTON_DOWN);
	}else if(e.type == EventType::MOUSE_SCROLL){
	    io.AddMouseWheelEvent(0.0f, e.scroll / 120);
	}else if(isKeyboardButtonEvent(e)){
	    //TODO: why is this so complicated?
	};
        bool show_demo_window = true;
	ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
	ImGui::ShowDemoWindow(&show_demo_window);

	if(isKeyboardButtonEvent(e) && isKeyDown(ButtonCode::Key_LeftShift)){
	    const float cameraSpeed = 5;
	    if(e.type == EventType::KEY_DOWN){
		switch(e.buttonCode){
		case ButtonCode::Key_W:cam.pos.y -= cameraSpeed * dt;break;
		case ButtonCode::Key_S:cam.pos.y += cameraSpeed * dt;break;
		case ButtonCode::Key_D:cam.pos.x -= cameraSpeed * dt;break;
		case ButtonCode::Key_A:cam.pos.x += cameraSpeed * dt;break;
		};
	    };
	}else if(e.type == EventType::MOUSE_SCROLL){
	    cam.updateZoomLevel(e.scroll/100);
	};
	cam.calculateViewMat();
	engine->r.setMat4Uniform(cam.projection * cam.view, "uProjectionView");
	
	return io.WantCaptureMouse || io.WantCaptureKeyboard;
    };
    void onRender(){
        ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };
    void onUninit(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
    };
};
