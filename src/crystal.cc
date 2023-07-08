struct Crystal{
    LayerManager      lm;
    Renderer          r;
    EventDispatcher   ed;
    MaterialSystem    ms;
    FrameBuffer       fb;
    u32               windowX;
    u32               windowY;
    bool              shouldClose;
    
    void init(){
	lm.init(3);
	ms.init();
	r.init();
	fb.init(windowX, windowY);
    };
    void uninit(){
	if(lm.layers != nullptr){
	    lm.uninitLayers();
	    lm.uninit();
	};
	ms.uninit();
	r.uninit();
	fb.uninit();
    };
};

//@ignore
static_assert(sizeof(u8) == 1, "u8 is not 1 byte");
static_assert(sizeof(u16) == 2, "u16 is not 2 byte");
static_assert(sizeof(u32) == 4, "u32 is not 4 byte");
static_assert(sizeof(u64) == 8, "u64 is not 8 byte");
static_assert(sizeof(s8) == 1, "s8 is not 1 byte");
static_assert(sizeof(s16) == 2, "s16 is not 2 byte");
static_assert(sizeof(s32) == 4, "s32 is not 4 byte");
static_assert(sizeof(s64) == 8, "s64 is not 8 byte");
static_assert(sizeof(b8) == 1, "b8 is not 1 byte");
static_assert(sizeof(b16) == 2, "b16 is not 2 byte");
static_assert(sizeof(b32) == 4, "b32 is not 4 byte");
static_assert(sizeof(b64) == 8, "b64 is not 8 byte");
static_assert(sizeof(f32) == 4, "f32 is not 4 byte");
static_assert(sizeof(f64) == 8, "f64 is not 8 byte");
