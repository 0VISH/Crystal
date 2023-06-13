typedef void (*LayerFunc)();
typedef bool (*LayerUpdateFunc)(Event e);   //returns true if event handled

struct Layer{
    u8 layerID;
    LayerFunc onUninit;
    LayerFunc onRender;
    LayerUpdateFunc onUpdate;
};

struct LayerManager{
    Layer *layers;
    u8 layerLen;
    u8 layerCount;

    void init(u8 len){
	layerCount = 0;
	layerLen = len;
	layers = (Layer*)mem::alloc(sizeof(Layer*) * len);
    };
    void uninit(){
	mem::free(layers);
    };
    Layer *newLayer(){
#if(DBG)
	if(layerCount >= layerLen){
	    dlog("[ERROR]: layerCount >= layerLen\n");
	    return nullptr;
	};
#endif
	Layer *layer = &layers[layerCount];
	layer->layerID = layerCount;
	layerCount += 1;
	return layer;
    };
    void popLayer(){
	layerCount -= 1;
	Layer *layer = &layers[layerCount];
	if(layer->onUninit != nullptr){layer->onUninit();};
    };
    void uninitLayers(){
	for(u8 x=layerCount; x>0;){
	    x -= 1;
	    layers[x].onUninit();
	};
    };
    void updateLayers(Event event){
	for(u8 x=layerCount; x>0;){
	    x -= 1;
	    Layer& layer = layers[x];
	    bool res = layer.onUpdate(event);
	    if(res){
	        event.type = EventType::NONE;
	    };
	};
    };
    void renderLayers(){
	for(u8 x=0; x<layerCount; x+=1){
	    layers[x].onRender();
	};
    };
#if(DBG)
    void dumpLayersStat(){
	for(u8 x=0; x<layerCount; x+=1){
	    Layer *layer = layers + x;
	    log("id: %d\nonUpdate: %p\nonRender: %p\nonUninit: %p\n", layer->layerID, layer->onUpdate, layer->onRender, layer->onUninit);
	};
    };
#endif
};