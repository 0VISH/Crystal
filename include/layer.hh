#pragma once

typedef bool (*LayerUpdateFunc)(Event e, f64 dt);   //returns true if event handled

struct Layer{
    u8 layerID;
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
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
