#define PLAT_WINDOWS     true
#define DBG              true
#define RCONTEXT_GL      true
#define EDITOR           true

/*
  NOTE: We compile game code along with engine code. We can compile
  game code to dll and pass function pointers to the dll, but in cpp
  its too fucking annoying cuz I have to create header files.

  GAME_CODE is from Windows/
 */
#define GAME_CODE_PATH        "../../sandbox/src/include.hh"
