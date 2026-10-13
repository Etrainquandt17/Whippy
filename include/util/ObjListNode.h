#ifndef UTIL_OBJLISTNODE_H
#define UTIL_OBJLISTNODE_H

#include "nw4r/ut/list.h"

namespace util {

struct ObjListDummyType;

template <typename T, typename Tag>
class ObjListNode {
public:
    // TODO: where a unit expands the constructor, the original builds the empty link before it takes the
    // member's address, which the reference gives (scn/step/gimmick/popflower/PopFlower.cpp). Opt-in until
    // the linked units have been checked against it.
#ifdef UTIL_OBJLISTNODE_CONSTRUCTOR_LINK_REFERENCE
    ObjListNode() : mList(0), mObj(0) {
        const nw4r::ut::Link& link = nw4r::ut::Link();
        mLink = link;
    }
#else
    ObjListNode() : mList(0), mObj(0) {
        mLink = nw4r::ut::Link();
    }
#endif

    // Defined in util/ObjList.h, which only some units include.
    ~ObjListNode();

    bool isLink() const;
    void unlink();

protected:
    nw4r::ut::Link mLink;
    void* mList;
    T* mObj;
};

}

#endif
