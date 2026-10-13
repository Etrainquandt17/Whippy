#ifndef NW4R_G3D_SCN_MDL_EXPAND_H
#define NW4R_G3D_SCN_MDL_EXPAND_H
#include <nw4r/types_nw4r.h>

#include "nw4r/g3d/g3d_scnmdlsmpl.h"
#include "nw4r/g3d/g3d_scnobj.h"

namespace nw4r {
namespace g3d {

class ScnMdlExpand : public ScnGroup {
public:
    static ScnMdlExpand *Construct(MEMAllocator *pAllocator, u32 *pSize, u32 maxChildren, ScnMdlSimple *pScnMdl);

    ScnMdlExpand(
        MEMAllocator *pAllocator, ScnObj **ppObj, u32 capacity, ScnMdlSimple *pScnMdl, u32 *pNodeIDArray
    );

    virtual void G3dProc(u32 task, u32 param, void *pInfo); // at 0xC
    virtual ~ScnMdlExpand();                                // at 0x10

    virtual bool Insert(u32 idx, ScnObj *pObj); // at 0x34
    virtual ScnObj *Remove(u32 idx);            // at 0x38
    virtual bool Remove(ScnObj *pObj);          // at 0x3C

    bool SelectBaseNode(u32 idx, u32 nodeID);
    bool PushBack(ScnObj *pObj, u32 nodeID);
    bool Insert(u32 idx, ScnObj *pObj, u32 nodeID);

private:
    ScnMdlSimple *mpScnMdlSimple; // at 0xE8
    u32 *mpNodeIDArray;           // at 0xEC

    NW4R_G3D_RTTI_DECL_DERIVED(ScnMdlExpand, ScnGroup);
};

} // namespace g3d
} // namespace nw4r

#endif
