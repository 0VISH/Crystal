//TODO: This is a copy of engine's mem.cc. We would like engine to hand over
//the game some memory and this files decides how to allocate from that pool.

namespace mem {
    s32 calls = 0;
    u64 notFreed = 0;
    
    //TODO: write an allocator
    void *alloc(u64 size) {
	return malloc(size);
    };
    void *calloc(u64 size){
	return ::calloc(1, size);
    };
    void free(void *mem) {
	::free(mem);
    };
};
