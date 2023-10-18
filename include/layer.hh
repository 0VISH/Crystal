#pragma once

typedef void (*LayerFunc)();
//returns true if event handled
typedef bool (*LayerUpdateFunc)(Event e, f64 dt);

struct Layer{
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
    u8 layerID;
};

struct LayerManager{
    Layer *layers;
    u8 layerCount;

    void init(u8 len);
    void uninit();
    Layer *newLayer();
    void popLayer();
    void popLayerWithoutUninit();
    void uninitLayers();
    void updateLayers(Event event, f64 dt);
    void renderLayers();
#if(DBG)
    void dumpLayersStat();
#endif
};
