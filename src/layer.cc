#include "layer.hh"

void LayerManager::init(u8 len){
    layerCount = 0;
    layers = (Layer*)mem::alloc(sizeof(Layer) * len);
};
void LayerManager::uninit(){
    mem::free(layers);
};
Layer *LayerManager::newLayer(){
    Layer *layer = layers + layerCount;
    layer->layerID = layerCount;
    layerCount += 1;
    return layer;
};
void LayerManager::popLayer(){
    layerCount -= 1;
    Layer *layer = layers + layerCount;
    if(layer->onUninit != nullptr){layer->onUninit();};
};
void LayerManager::popLayerWithoutUninit(){
    layerCount -= 1;
};
void LayerManager::uninitLayers(){
    for(u8 x=layerCount; x>0;){
	x -= 1;
	if(layers[x].onUninit != nullptr){layers[x].onUninit();};
    };
};
void LayerManager::updateLayers(Event event, f64 dt){
    for(u8 x=0; x<layerCount; x+=1){
	Layer& layer = layers[x];
	if(layer.onUpdate && layer.shouldCallFuncs){
	    if(layer.onUpdate(event, dt)){
		event.type = EventType::NONE;
	    };
	};
    };
};
void LayerManager::renderLayers(){
    for(u8 x=layerCount; x>0;){
	x -= 1;
	Layer& layer = layers[x];
	if(layer.onRender && layer.shouldCallFuncs){
	    layer.onRender();
	};
    };
};
#if(DBG)
void LayerManager::dumpLayersStat(){
    for(u8 x=0; x<layerCount; x+=1){
	Layer *layer = layers + x;
	print("id: %d\nonUpdate: %p\nonRender: %p\nonUninit: %p\n", layer->layerID, layer->onUpdate, layer->onRender, layer->onUninit);
    };
};
#endif
