#pragma once

#if(ENGINE)
#define ALLOC mem::alloc
#define FREE  mem::free
#elif(GAME)
#define ALLOC game::alloc
#define FREE  game::free
#endif

namespace ds{
    template<typename T>
    struct DynamicArray {
	T *mem;
	u32 count;
	u32 len;

	void realloc(u32 newCap) {
	    void *newMem = ALLOC(sizeof(T) * newCap);
	    memcpy(newMem, mem, sizeof(T) * len);
	    FREE(mem);
	    mem = (T*)newMem;
	    len = newCap;
	};
	T &getElement(u32 index) {
#if(DBG)
	    if (index >= len) {
		print("\n[ERROR]: abc(dynamic_array) failed");
	    };
#endif
	    return mem[index];
	};
	T &operator[](u32 index) { return getElement(index); };
	void init(u32 startCount = 5) {
	    count = 0;
	    len = startCount;
	    mem = (T*)ALLOC(sizeof(T) * startCount);
	};
	void uninit() { FREE(mem); };
	void push(const T &t) {
	    if (count == len) { realloc(len + len / 2 + 1); };
	    mem[count] = t;
	    count += 1;
	};
	T pop(){
	    count -= 1;
	    return mem[count];
	};
	T& newElem(){
	    if (count == len) { realloc(len + len / 2 + 1); };
	    count += 1;
	    return mem[count-1];
	};
	void reserve(u32 rCount){
	    if(count+rCount >= len){
		realloc(count+rCount);
	    }
	}
#if(DBG)
	void dumpStat() {
	    print("\n[DYNAMIC_ARRAY] mem: %p; count: %d; len: %d\n", mem, count, len);
	};
#endif
    };
};
