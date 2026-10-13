#ifndef NW4R_G3D_RES_RESMDL_H
#define NW4R_G3D_RES_RESMDL_H

#include "nw4r/g3d/res/g3d_rescommon.h"
#include "nw4r/g3d/res/g3d_resnode.h"
#include "types.h"

namespace nw4r {
namespace g3d {

struct ResMdlData;

class ResMdl : public ResCommon<ResMdlData> {
public:
    explicit ResMdl(void* pData = 0) : ResCommon<ResMdlData>(pData) {
        void* p = ptr();
        NW4R_ASSERT_AT("g3d_resmdl_ac.h", 120, !((u32)p & 0x1f));
    }

    ResNode GetResNode(const char* pName) const;
    ResNode GetResNode(int idx) const;
    ResNode GetResNode(u32 idx) const;
    u32 GetResNodeNumEntries() const;
};

}}  // namespace nw4r::g3d

#endif
