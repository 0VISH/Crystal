#pragma once

typedef bool (*LayerUpdateFunc)(Event e, f64 dt);   //returns true if event handled

enum class LayerFlag{
    RENDER = 1,
    UPDATE = 2,
};

struct Layer{
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
    u8 flags;  //if flags == 0, then onUpdate and onRender will be called.
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
