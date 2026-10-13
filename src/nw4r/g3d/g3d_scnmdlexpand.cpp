#include "nw4r/g3d.h" // IWYU pragma: export

#include "nw4r/g3d/g3d_scnmdlexpand.h"

#include <ss/algorithm>

namespace nw4r {
namespace g3d {

NW4R_G3D_RTTI_DEF(ScnMdlExpand);

namespace {

u32 INVALID_NODE_ID = 0xFFFFFFFF;

} // namespace

// TODO: the versions of GetNodeID, SelectBaseNode, PushBack and Insert that take a node name were
// dropped by the link and are not written.

ScnMdlExpand *ScnMdlExpand::Construct(MEMAllocator *pAllocator, u32 *pSize, u32 maxChildren, ScnMdlSimple *pScnMdl) {
    ScnMdlExpand *pExpand = NULL;

    u32 childrenSize = maxChildren * sizeof(ScnObj *);
    u32 nodeIDSize = maxChildren * sizeof(u32);

    u32 nodeIDOfs = ut::RoundUp(sizeof(ScnMdlExpand) + childrenSize, 4);
    u32 size = ut::RoundUp(nodeIDOfs + nodeIDSize, 4);

    if (pSize != NULL) {
        *pSize = size;
    }

    if (pAllocator != NULL) {
        u8 *pBuffer = reinterpret_cast<u8 *>(Alloc(pAllocator, size));
        if (pBuffer == NULL) {
            return NULL;
        }

        pExpand = new (pBuffer) ScnMdlExpand(
            pAllocator, reinterpret_cast<ScnObj **>(pBuffer + sizeof(ScnMdlExpand)), maxChildren, pScnMdl,
            reinterpret_cast<u32 *>(pBuffer + nodeIDOfs)
        );
    }

    return pExpand;
}

ScnMdlExpand::ScnMdlExpand(
    MEMAllocator *pAllocator, ScnObj **ppObj, u32 capacity, ScnMdlSimple *pScnMdl, u32 *pNodeIDArray
)
    : ScnGroup(pAllocator, ppObj, capacity), mpScnMdlSimple(pScnMdl), mpNodeIDArray(pNodeIDArray) {
    for (u32 i = 0; i < capacity; i++) {
        mpNodeIDArray[i] = INVALID_NODE_ID;
    }

    pScnMdl->G3dProc(G3DPROC_ATTACH_PARENT, 0, this);
}

bool ScnMdlExpand::SelectBaseNode(u32 idx, u32 nodeID) {
    ResMdl mdl = mpScnMdlSimple->GetResMdl();

    if (nodeID < mdl.GetResNodeNumEntries() && idx < Size()) {
        mpNodeIDArray[idx] = nodeID;
        return true;
    }

    return false;
}

bool ScnMdlExpand::PushBack(ScnObj *pObj, u32 nodeID) {
    if (!Insert(Size(), pObj)) {
        return false;
    }

    if (!SelectBaseNode(Size() - 1, nodeID)) {
        PopBack();
        return false;
    }

    return true;
}

bool ScnMdlExpand::Insert(u32 idx, ScnObj *pObj, u32 nodeID) {
    bool success = ScnGroup::Insert(idx, pObj);

    if (success) {
        u32 numChildren = Size();

        for (u32 i = numChildren - 1; i > idx; i--) {
            mpNodeIDArray[i] = mpNodeIDArray[i - 1];
        }

        mpNodeIDArray[idx] = nodeID;
    }

    return success;
}

bool ScnMdlExpand::Insert(u32 idx, ScnObj *pObj) {
    return Insert(idx, pObj, INVALID_NODE_ID);
}

ScnObj *ScnMdlExpand::Remove(u32 idx) {
    ScnObj *pObj = ScnGroup::Remove(idx);

    if (pObj != NULL) {
        u32 numChildren = Size();

        for (u32 i = idx; i < numChildren; i++) {
            mpNodeIDArray[i] = mpNodeIDArray[i + 1];
        }
    }

    return pObj;
}

bool ScnMdlExpand::Remove(ScnObj *pObj) {
    ScnObj **ppObj = std::find(Begin(), End(), pObj);

    if (ppObj == End()) {
        return false;
    }

    return Remove(std::distance(Begin(), ppObj)) != NULL;
}

void ScnMdlExpand::G3dProc(u32 task, u32 param, void *pInfo) {
    if (IsG3dProcDisabled(task)) {
        return;
    }

    switch (task) {
        case G3DPROC_CALC_WORLD: {
            CheckCallback_CALC_WORLD(CALLBACK_TIMING_A, param, pInfo);

            CalcWorldMtx(static_cast<math::MTX34 *>(pInfo), &param);

            CheckCallback_CALC_WORLD(CALLBACK_TIMING_B, param, pInfo);

            if (mpScnMdlSimple != NULL) {
                mpScnMdlSimple->G3dProc(task, param, const_cast<math::MTX34 *>(GetMtxPtr(MTX_WORLD)));
            }

            u32 numChildren = Size();

            for (u32 i = 0; i < numChildren; i++) {
                u32 nodeID = mpNodeIDArray[i];
                u32 childParam = param;

                if (nodeID != INVALID_NODE_ID) {
                    ScnObj *pChild = (*this)[i];
                    math::MTX34 mtx;

                    if (mpScnMdlSimple != NULL) {
                        if (!mpScnMdlSimple->GetScnMtxPos(&mtx, MTX_WORLD, nodeID)) {
                            childParam |= 1;
                        }
                    } else {
                        childParam |= 1;
                    }

                    pChild->G3dProc(task, childParam, &mtx);
                }
            }

            CheckCallback_CALC_WORLD(CALLBACK_TIMING_C, param, pInfo);
            break;
        }

        case G3DPROC_ATTACH_PARENT:
        case G3DPROC_DETACH_PARENT: {
            DefG3dProcScnGroup(task, param, pInfo);
            break;
        }

        case G3DPROC_CHILD_DETACHED: {
            if (pInfo == mpScnMdlSimple) {
                mpScnMdlSimple->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
                mpScnMdlSimple = NULL;
            } else {
                DefG3dProcScnGroup(task, param, pInfo);
            }
            break;
        }

        default: {
            if (mpScnMdlSimple != NULL) {
                mpScnMdlSimple->G3dProc(task, param, pInfo);
            }

            DefG3dProcScnGroup(task, param, pInfo);
            break;
        }
    }
}

ScnMdlExpand::~ScnMdlExpand() {
    if (mpScnMdlSimple != NULL) {
        mpScnMdlSimple->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
    }
}

} // namespace g3d
} // namespace nw4r
