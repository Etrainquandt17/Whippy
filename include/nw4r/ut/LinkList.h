#ifndef NW4R_UT_LINKLIST_H
#define NW4R_UT_LINKLIST_H

namespace nw4r {

namespace db {

void Panic(const char* file, int line, const char* message, ...);

}

namespace ut {

class LinkListNode;

namespace detail {

class LinkListImpl {
public:
    // TODO: returns an iterator.
    LinkListNode* Erase(LinkListNode* node);

    class Iterator {
    public:
        explicit Iterator(LinkListNode* node) : mNode(node) {}

        LinkListNode* mNode;
    };

    Iterator Insert(Iterator it, LinkListNode* node);
    // TODO: &mNode, once the class has its members.
    Iterator GetEndIter() { return Iterator(reinterpret_cast<LinkListNode*>(reinterpret_cast<char*>(this) + 4)); }
};

}

template <typename T, int Offset>
class LinkList : public detail::LinkListImpl {
public:
    void Erase(T* p) { detail::LinkListImpl::Erase(GetNodeFromPointer(p)); }

    // TODO: a unit that expands util::ObjRefHandle's assignment and has neither this body nor its strings calls it
    // (scn/step/enemy/buraburadee/Custom.cpp). How the original keeps the body out of such a unit is not known,
    // so that unit defines NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE ahead of its includes.
#ifdef NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
    static LinkListNode* GetNodeFromPointer(T* p);
#else
    static LinkListNode* GetNodeFromPointer(T* p) {
        if (p == 0) {
            db::Panic("LinkList.h", 563, "NW4R:Pointer must not be NULL (p)");
        }
        return reinterpret_cast<LinkListNode*>(reinterpret_cast<char*>(p) + Offset);
    }
#endif
};

}
}

#endif
