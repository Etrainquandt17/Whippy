#ifndef UTIL_OBJREFHANDLEINLINE_H
#define UTIL_OBJREFHANDLEINLINE_H

#include "nw4r/ut/LinkList.h"
#include "util/ObjList.h"
#include "util/ObjRefHandle.h"

// TODO: inline in util/ObjRefHandle.h in the original: a unit that assigns once expands it, a unit that assigns
// twice calls it. That header only declares it for the units written before the body was known, so the
// body is given here.

namespace util {

template <typename T>
inline ObjRefHandle<T>& ObjRefHandle<T>::operator=(const ObjRefHandle& other) {
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
#ifdef UTIL_OBJREFHANDLE_ASSIGNMENT_END_ITERATOR
        // TODO: what the original has, most likely through nw4r::ut::LinkList::PushBack: a unit that expands the
        // assignment and also emits another instance of it calls GetEndIter (scn/step/gimmick/popflower/PopFlower.cpp).
        nw4r::ut::detail::LinkListImpl::Iterator end = list->GetEndIter();
        list->Insert(end, nw4r::ut::LinkList<ObjListNode<T, ObjListDummyType>, 0>::GetNodeFromPointer(this));
#else
        list->Insert(
            nw4r::ut::detail::LinkListImpl::Iterator(
                reinterpret_cast<nw4r::ut::LinkListNode*>(reinterpret_cast<char*>(list) + 4)),
            nw4r::ut::LinkList<ObjListNode<T, ObjListDummyType>, 0>::GetNodeFromPointer(this));
#endif
    }
    return *this;
}

}  // namespace util

#endif
