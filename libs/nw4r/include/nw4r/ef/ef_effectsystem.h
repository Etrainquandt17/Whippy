#ifndef NW4R_EF_EFFECT_SYSTEM_H
#define NW4R_EF_EFFECT_SYSTEM_H
#include <kdc/nw4r/types_nw4r.h>

#include <nw4r/ef/ef_creationqueue.h>
#include <nw4r/ef/ef_random.h>

#include <kdc/nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class MemoryManagerBase;
class DrawOrderBase;
class DrawStrategyBuilder;
class EmitFormBuilder;
class ActivityList;



class EffectSystem {
private:
    MemoryManagerBase* mMemoryManager; // at 0x0

public:
    DrawOrderBase* mDrawOrderFunc;             // at 0x4
    DrawStrategyBuilder* mDrawStrategyBuilder; // at 0x8
    EmitFormBuilder* mEmitFormBuilder;         // at 0xC
    CreationQueue mCreationQueue;              // at 0x10
    u32 mMaxGroupID;                           // at 0xC014
    ActivityList* mActivityList;               // at 0xC018
    Random mRandom;                            // at 0xC01C
    math::VEC3 mProcessCameraPos;              // at 0xC020
    math::MTX34 mProcessCameraMtx;             // at 0xC02C
    f32 mProcessCameraFar;                     // at 0xC05C
    f32 mProcessCameraNear;                    // at 0xC060
    bool mXFFlushSafe;                         // at 0xC064
    Emitter* mTmpEmitter;                      // at 0xC068

    static s32 mDisplayVersion;
    static EffectSystem instance;
    static DrawInfo mSortEffectOperatorZDrawInfo;
public:
    static EffectSystem* GetInstance();

    bool Initialize(u32 maxGroupID);
    bool Closing(Effect* pEffect);

    Effect* CreateEffect(const char* pName, u32 groupID, u16 calcRemain);
    Effect* CreateEffect(EmitterResource* pResource, u32 groupID,
                         u16 calcRemain);
    u32 RetireEffect(Effect* pEffect);

    u32 RetireEffectAll(u32 groupID);
    u32 RetireEmitterAll(u32 groupID);
    u32 RetireParticleAll(u32 groupID);

    void Calc(u32 groupID, CalcOption option);
    void Draw(const DrawInfo& rInfo, u32 groupID);

    void SetProcessCamera(const math::VEC3& rPos, const math::MTX34& rMtx, f32 near, f32 far);

    MemoryManagerBase* GetMemoryManager() const {
        return mMemoryManager;
    }
    void SetMemoryManager(MemoryManagerBase* pManager, u32 maxGroupID) {
        mMemoryManager = pManager;

        if (mMemoryManager != NULL) {
            Initialize(maxGroupID);
        } else {
            maxGroupID = 0;
            mActivityList = NULL;
        }
    }

    void SetXFFlushSafe(bool safe) {
        mXFFlushSafe = safe;
    }

private:
    EffectSystem();
    ~EffectSystem();
};

} // namespace ef
} // namespace nw4r

#endif
