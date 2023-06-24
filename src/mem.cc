#include <stdlib.h>

namespace mem {
    //TODO: write an allocator
    void *alloc(u64 size) {
#if(DBG)
	if(size == 0){
	    dlog("[ERROR]: trying to allocate memory of size 0\n");
	    return nullptr;
	};
#endif
	return malloc(size);
    };
    void *calloc(u64 size){
#if(DBG)
	if(size == 0){
	    dlog("[ERROR]: trying to callocate memory of size 0\n");
	    return nullptr;
	};
#endif
	return ::calloc(size, 1);	
    };
    void free(void *mem) {
#if(DBG)
	if (mem == nullptr) {
	    dlog("[ERROR]: trying to free a nullptr\n");
	};
#endif
	::free(mem);
    };
};
