void serializeString(char *mem, FILE *f){
    u32 len = strlen(mem);
    fwrite(&len, sizeof(len), 1, f);
    fwrite(mem, len, 1, f);
};
void serializeHashmapStr(HashmapStr &map, FILE *f){
    fwrite(&map.count, sizeof(map.count), 1, f);
    for(u32 x=0; x<map.len; x+=1){
	if(map.status[x]){
	    serializeString(map.keys[x].mem, f);
	    fwrite(&map.values[x], sizeof(u32), 1, f);
	};
    };
};
void serializeDynamicArrayString(DynamicArray<char*>& arr, FILE *f){
    fwrite(&arr.count, sizeof(arr.count), 1, f);
    for(u32 x=0; x<arr.count; x+=1){
	serializeString(arr[x], f);
    };
};
template<typename T>
void serializeDynamicArray(DynamicArray<T> &arr, FILE *f){
    fwrite(&arr.count, sizeof(arr.count), 1, f);
    fwrite(arr.mem, sizeof(T)*arr.count, 1, f);
};

template<typename T>
inline T deserialize(char *mem, u32 &x){
    T val = *(T*)(&mem[x]);
    x += sizeof(T);
    return val;
};
char* deserializeString(u32 &length, char *mem, u32 &x){
    u32 len = deserialize<u32>(mem, x);
    char *str = (char*)mem::alloc(len+1);
    memcpy(str, &mem[x], len);
    str[len] = '\0';
    x += len;
    length = len;
    return str;
};
void deserializeDynamicArrayString(DynamicArray<char*> &arr, char *mem, u32 &x){
    u32 count = deserialize<u32>(mem, x);
    arr.init(count+1);
    for(u32 j=0; j<count; j+=1){
	u32 len;
	arr.push(deserializeString(len, mem, x));
    };
};
void deserializeHashmapStr(HashmapStr &map, char *mem, u32 &x){
    u32 count = deserialize<u32>(mem, x);
    map.init(count);
    for(u32 j=0; j<count; j+=1){
	u32 len;
	char *str = deserializeString(len, mem, x);
	u32 value = deserialize<u32>(mem, x);
	map.insertValue({str, len}, value);
    };
};
template<typename T>
void deserializeDynamicArray(DynamicArray<T> &arr, char *mem, u32 &x){
    u32 count = deserialize<u32>(mem, x);
    arr.init(count);
    for(u32 j=0; j<count; j+=1){
	T *t = (T*)(&mem[x]);
	arr.push(*t);
	x += sizeof(T);
    };
};
