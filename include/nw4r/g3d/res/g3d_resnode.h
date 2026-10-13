#ifndef NW4R_G3D_RES_RESNODE_H
#define NW4R_G3D_RES_RESNODE_H

#include "nw4r/g3d/res/g3d_rescommon.h"
#include "nw4r/math/math_types.h"
#include "types.h"

namespace nw4r {
namespace g3d {

struct ResNodeData {
    u32 size;
    s32 toResMdlData;
    s32 name;
    u32 id;
    u32 mtxID;
    u32 flags;
    u32 bbmode;
    u32 bbref_nodeid;
    math::_VEC3 scale;
    math::_VEC3 rot;
    math::_VEC3 translate;
    math::_VEC3 volume_min;
    math::_VEC3 volume_max;
    s32 toParentNode;
    s32 toChildNode;
    s32 toNextSibling;
    s32 toPrevSibling;
    s32 toResUserData;
    math::_MTX34 modelMtx;
    math::_MTX34 invModelMtx;
};

class ResNode : public ResCommon<ResNodeData> {
public:
    explicit ResNode(void* pData = 0) : ResCommon<ResNodeData>(pData) {
        void* p = ptr();
        NW4R_ASSERT_AT("g3d_resnode_ac.h", 44, !((u32)p & 0x3));
    }

    static const char* GetClassName() { return "ResNode"; }

    const ResNodeData& ref() const {
        NW4R_ASSERTMSG_AT("g3d_resnode_ac.h", 44, ptr() != 0, "%s::%s: Object not valid.", GetClassName(), __FUNCTION__);
        const ResNodeData& ret = *ptr();
        return ret;
    }

    u32 GetID() const {
        NW4R_ASSERT_AT("g3d_resnode_ac.h", 56, IsValid());
        return IsValid() ? ptr()->id : 0;
    }

    u32 GetMtxID() const {
        NW4R_ASSERT_AT("g3d_resnode_ac.h", 83, IsValid());
        return IsValid() ? ptr()->mtxID : 0;
    }

    const math::VEC3& GetScale() const { return *(const math::VEC3*)&ref().scale; }
    const math::VEC3& GetRotate() const { return *(const math::VEC3*)&ref().rot; }
    const math::VEC3& GetTranslate() const { return *(const math::VEC3*)&ref().translate; }

    ResNode GetParentNode() { return ofs_to_obj<ResNode>(ref().toParentNode); }
    ResNode GetChildNode() { return ofs_to_obj<ResNode>(ref().toChildNode); }
    ResNode GetNextSibling() { return ofs_to_obj<ResNode>(ref().toNextSibling); }
    ResNode GetPrevSibling() { return ofs_to_obj<ResNode>(ref().toPrevSibling); }
};

}
}

#endif
