#include "../include.hh"

s32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, s32 nCmdShow){
    if(crystal::init() == false){
	//TODO: debug log
	crystal::uninit();
	return EXIT_FAILURE;
    };
    crystal::uninit();
    return EXIT_SUCCESS;
}
