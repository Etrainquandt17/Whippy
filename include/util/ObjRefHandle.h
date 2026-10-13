#ifndef UTIL_OBJREFHANDLE_H
#define UTIL_OBJREFHANDLE_H

#include "util/ObjListNode.h"

// The bodies of isLink and unlink are in util/ObjList.h, which a unit includes itself if the original expands them.
#ifdef UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "nw4r/ut/LinkList.h"
#endif

namespace util {

template <typename T>
class ObjRefHandle : public ObjListNode<T, ObjListDummyType> {
public:
    ObjRefHandle() {}
    ObjRefHandle(const ObjRefHandle& other) { *this = other; }

    // TODO: the assignment and isAlive have their bodies in the class in the original: a unit that assigns twice
    // emits the assignment where it is first needed, with isAlive expanded in it (scn/step/info/HeroStatus.cpp).
    // The units written before that was known only match with the declarations, so a unit that needs the
    // bodies defines UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS ahead of its includes.
#ifdef UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
    ObjRefHandle& operator=(const ObjRefHandle& other) {
        if (this->isLink()) {
            this->unlink();
        }
        this->mObj = 0;
        if (other.isAlive()) {
            this->mObj = other.mObj;
        }
        if (other.isLink()) {
            nw4r::ut::LinkList<ObjListNode<T, ObjListDummyType>, 0>* list =
                static_cast<nw4r::ut::LinkList<ObjListNode<T, ObjListDummyType>, 0>*>(other.mList);
            this->mList = list;
            list->Insert(
                nw4r::ut::detail::LinkListImpl::Iterator(
                    reinterpret_cast<nw4r::ut::LinkListNode*>(reinterpret_cast<char*>(list) + 4)),
                nw4r::ut::LinkList<ObjListNode<T, ObjListDummyType>, 0>::GetNodeFromPointer(this));
        }
        return *this;
    }
#else
    ObjRefHandle& operator=(const ObjRefHandle& other);
#endif
    T* operator->() const { return this->mObj; }
    T& ref() const;

    bool isNull() const { return !isAlive(); }
#ifdef UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
    bool isAlive() const { return this->mObj != 0; }
#else
    bool isAlive() const;
#endif
};

}

#endif
