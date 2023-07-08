#include <stdlib.h>

namespace mem {
    s32 calls = 0;
    //TODO: write an allocator
    void *alloc(u64 size) {
#if(DBG)
	if(size == 0){
	    dlog("[ERROR]: trying to allocate memory of size 0\n");
	    return nullptr;
	};
	calls += 1;
#endif
	return malloc(size);
    };
    void *calloc(u64 size){
#if(DBG)
	if(size == 0){
	    dlog("[ERROR]: trying to callocate memory of size 0\n");
	    return nullptr;
	};
	calls += 1;
#endif
	return ::calloc(size, 1);	
    };
    void free(void *mem) {
#if(DBG)
	if (mem == nullptr) {
	    dlog("[ERROR]: trying to free a nullptr\n");
	    return;
	};
	calls -= 1;
#endif
	::free(mem);
    };
};
