#ifndef UTIL_OBJLIST_H
#define UTIL_OBJLIST_H

#include "nw4r/ut/LinkList.h"
#include "util/ObjListNode.h"

namespace util {

template <typename T, typename Tag>
inline bool ObjListNode<T, Tag>::isLink() const {
    return mList != 0;
}

template <typename T, typename Tag>
inline void ObjListNode<T, Tag>::unlink() {
    if (isLink()) {
        static_cast<nw4r::ut::LinkList<ObjListNode, 0>*>(mList)->Erase(this);
        mList = 0;
    }
}

template <typename T, typename Tag>
ObjListNode<T, Tag>::~ObjListNode() {
    unlink();
}

}  // namespace util

#endif
