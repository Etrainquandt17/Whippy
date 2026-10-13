#ifndef MEM_ALLOCATORHANDLE_H
#define MEM_ALLOCATORHANDLE_H

namespace mem {

class IAllocator;

class AllocatorHandle {
public:
    AllocatorHandle();
    AllocatorHandle(IAllocator& allocator);

    bool isValid() const;
    IAllocator* obj() const;

private:
    IAllocator* mAllocator;
};

}

#endif
