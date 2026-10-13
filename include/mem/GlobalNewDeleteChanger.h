#ifndef MEM_GLOBALNEWDELETECHANGER_H
#define MEM_GLOBALNEWDELETECHANGER_H

namespace mem {

class IAllocator;

class GlobalNewDeleteChanger {
public:
    GlobalNewDeleteChanger(IAllocator& allocator);
    ~GlobalNewDeleteChanger();

private:
    IAllocator& mAllocator;
};

}

#endif
