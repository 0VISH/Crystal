namespace mem {
    s32 calls = 0;
    u64 notFreed = 0;
    
    //TODO: write an allocator
    void *alloc(u64 size) {
	void *mem;
#if(DBG)
	if(size == 0){
	    print("[ERROR]: trying to allocate memory of size 0\n");
	    return nullptr;
	};
	calls += 1;
	notFreed += size;
	mem = malloc(size + sizeof(u64));
	u64 *num = (u64*)mem;
	*num = size;
	mem = (char*)mem + sizeof(u64);
#endif
	return mem;
    };
    void *calloc(u64 size){
	void *mem;
#if(DBG)
	if(size == 0){
	    print("[ERROR]: trying to callocate memory of size 0\n");
	    return nullptr;
	};
	calls += 1;
	notFreed += size;
	mem = ::calloc(1, size + sizeof(u64));
	u64 *num = (u64*)mem;
	*num = size;
	mem = (char*)mem + sizeof(u64);
#endif
	return mem;	
    };
    void free(void *mem) {
#if(DBG)
	if (mem == nullptr) {
	    print("[ERROR]: trying to free a nullptr\n");
	    return;
	};
	calls -= 1;
	u64 *num = reinterpret_cast<u64*>((char*)mem - sizeof(u64));
	notFreed -= *num;
	mem = num;
#endif
	::free(mem);
    };
};
