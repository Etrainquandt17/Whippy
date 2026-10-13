#ifndef NW4R_G3D_RES_RESFILE_H
#define NW4R_G3D_RES_RESFILE_H

#include "nw4r/g3d/res/g3d_rescommon.h"
#include "nw4r/g3d/res/g3d_resmdl.h"
#include "types.h"

namespace nw4r {
namespace g3d {

struct ResFileData;

class ResFile : public ResCommon<ResFileData> {
public:
    // TODO: inline in the library, with this assertion. A partly written unit that builds one ResFile would expand
    // it where the original calls it, so until those are whole the body is for units that define
    // NW4R_G3D_RESFILE_CONSTRUCTOR_INLINE ahead of their includes (g3d/ResFile.cpp holds the program's copy).
#ifdef NW4R_G3D_RESFILE_CONSTRUCTOR_INLINE
    explicit ResFile(void* pData = 0) : ResCommon<ResFileData>(pData) {
        void* p = ptr();
        NW4R_ASSERT_AT("g3d_resfile_ac.h", 60, !((u32)p & 0x1f));
    }
#else
    explicit ResFile(void* pData);
#endif

    void Init();
    void Terminate();
    bool CheckRevision() const;

    bool Bind(const ResFile file);
    void Release();

    bool Bind() { return Bind(*this); }

    ResMdl GetResMdl(const char* pName) const;
    ResMdl GetResMdl(int idx) const;
    ResMdl GetResMdl(u32 idx) const;

    void* GetExternalData(const char* pName) const;

    u32 GetResMdlNumEntries() const;
};

}}  // namespace nw4r::g3d

#endif
