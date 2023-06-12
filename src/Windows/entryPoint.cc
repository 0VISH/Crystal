#include "../include.hh"

s32 main(){
    window::Window window = window::create("crytal test");
    if(window == NULL){
	return EXIT_SUCCESS;
    };
    crystal::init();
    while(window::shouldClose == false){
	window::pollEvents();
	crystal::update();
    };
    window::destroy(window);
    crystal::uninit();
    printf("\nDONE :)\n");
    return EXIT_SUCCESS;
}

#pragma comment(lib, "User32.lib")
