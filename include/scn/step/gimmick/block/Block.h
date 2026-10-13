#ifndef SCN_STEP_GIMMICK_BLOCK_BLOCK_H
#define SCN_STEP_GIMMICK_BLOCK_BLOCK_H

#include "g3d/ModelContext.h"
#include "g3d/ResFileAccessor.h"
#include "g3d/StdModel.h"
#include "scn/step/GridPos.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/block/BlockEffRequestInfo.h"
#include "scn/step/map/BinGmkBlockKind.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"
#include "util/SIntAABBox.h"

namespace effect {
class Requestor;
}

namespace g3d {
class Root;
}

namespace mcoll {
class LandManager;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {

class Component;

namespace gimmick {

class Effect;

namespace block {

class BlockInfo;
class BlockResFiles;

struct Param {
    u32 _0;
    u32 _4;
    u32 _8;
};

class Block {
public:
    Block(Component& component, mem::IAllocator& allocator, mcoll::LandManager& landManager, BlockResFiles& resFiles,
          map::BinGmkBlockKind kind, const GridPos& pos, Effect& effect, ParamAccessor<Param>& param);

    s32 width() const;
    s32 height() const;
    util::SIntAABBox aabb() const;
    bool isExistBlock(s32 x, s32 y) const;
    bool canVacuum(bool) const;
    bool canHit() const;
    bool canBreak(bool, bool, bool, bool, bool, bool) const;
    bool onVacuum();
    bool onHit(u64 attackId, u64 ownerId);
    void onBroken();
    void onActEnd();
    void registerToRoot(g3d::Root& root);
    void startWaitAnim();
    bool isLandBlock() const;
    bool isHeavyBlock() const;
    bool isChainBlock() const;
    bool canChainBreak() const;
    void startChainBreak();
    void startChainBreak(u32 frame);
    bool isEndChainBreak() const;
    void onChainBreak();
    bool isRemove() const;
    void setMapColl(u32 x, u32 y, bool isExist);
    void requestBreakEffect(const BlockEffRequestInfo::Info& info, const BlockInfo& blockInfo, ::effect::Requestor& requestor);
    u32 getBreakSE() const;
    void startCrumble();
    bool isRemainBroken(bool) const;
    map::BinGmkBlockKind kind() const;
    const GridPos& getGridPos() const;

private:
    bool mfIsAnimBlock() const;
    bool mfIsDefaultBufferOption() const;

    Component& mComponent;
    mcoll::LandManager& mLandManager;
    map::BinGmkBlockKind mKind;
    GridPos mPos;
    BlockResFiles& mResFiles;
    g3d::ResFileAccessor mResFile;
    g3d::StdModel mModel;
    Effect& mEffect;
    snd::SERequestor mSE;
    u64 mHitIds[4];
    bool _260;
    bool _261;
    bool _262;
    bool _263;
    bool _264;
    s32 mState;
    util::FrameCounter _26C;
    util::FrameCounter _274;
    util::FrameCounter _27C;
    util::FrameCounter _284;
    ParamAccessor<Param>& mParam;
};

}}}}  // namespace scn::step::gimmick::block

#endif
