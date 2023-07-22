typedef void (*LayerFunc)();
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

    void init(u8 len){
	layerCount = 0;
	layers = (Layer*)mem::alloc(sizeof(Layer) * len);
    };
    void uninit(){
	mem::free(layers);
    };
    Layer *newLayer(){
	Layer *layer = layers + layerCount;
	layer->layerID = layerCount;
	layerCount += 1;
	return layer;
    };
    void popLayer(){
	layerCount -= 1;
	Layer *layer = layers + layerCount;
	if(layer->onUninit != nullptr){layer->onUninit();};
    };
    void popLayerWithoutUninit(){
	layerCount -= 1;
    };
    void uninitLayers(){
	for(u8 x=layerCount; x>0;){
	    x -= 1;
	    layers[x].onUninit();
	};
    };
    void updateLayers(Event event, f64 dt){
	for(u8 x=0; x<layerCount; x+=1){
	    Layer& layer = layers[x];
	    if(layer.onUpdate == nullptr){continue;};
	    if(layer.onUpdate(event, dt)){
		event.type = EventType::NONE;
	    };
	};
    };
    void renderLayers(){
	for(u8 x=layerCount; x>0;){
	    x -= 1;
	    Layer& layer = layers[x];
	    if(layer.onRender == nullptr){continue;};
	    layer.onRender();
	};
    };
#if(DBG)
    void dumpLayersStat(){
	for(u8 x=0; x<layerCount; x+=1){
	    Layer *layer = layers + x;
	    print("id: %d\nonUpdate: %p\nonRender: %p\nonUninit: %p\n", layer->layerID, layer->onUpdate, layer->onRender, layer->onUninit);
	};
    };
#endif
};
