#ifndef SCN_STEP_GIMMICK_MANAGER_H
#define SCN_STEP_GIMMICK_MANAGER_H

#include "hel/math/Vector3.h"
#include "mem/ExplicitScopedPtr.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {

namespace warpstar {
class Manager;
}

namespace shipevent {
class Manager;
}

namespace airflow {
class Manager;
}

namespace aquarock {
class Manager;
}

namespace areaevent {
class Manager;
}

namespace arease {
class Manager;
}

namespace arrowboard {
class Manager;
}

namespace bitestatue {
class Manager;
}

namespace block {
class BlockManager;
}

namespace bombmachine {
class Manager;
}

namespace cameralock {
class Manager;
}

namespace cannon {
class Manager;
}

namespace cannonblow {
class Manager;
}

namespace carrydeegenerator {
class Manager;
}

namespace chainstarter {
class Manager;
}

namespace challengedoor {
class Manager;
}

namespace circuitblock {
class Manager;
}

namespace consecutivebattle {
class Manager;
}

namespace crushwallbellsuper {
class Manager;
}

namespace crushwallsuper {
class Manager;
}

namespace crystalwall {
class Manager;
}

namespace cutropestep {
class Manager;
}

namespace darkwall {
class Manager;
}

namespace door {
class Manager;
}

namespace fallpole {
class Manager;
}

namespace finalpopstar {
class Manager;
}

namespace fuse {
class Manager;
}

namespace guideboard {
class Manager;
}

namespace guideplate {
class Manager;
}

namespace hangswitch {
class Manager;
}

namespace icepin {
class Manager;
}

namespace icicle {
class Manager;
}

namespace injection {
class SEManager;
}

namespace injectionbox {
class Manager;
}

namespace lavageyser {
class Manager;
}

namespace lightblock {
class Manager;
}

namespace lockshutter {
class Manager;
}

namespace lvmapdoor {
class Manager;
}

namespace mahoroa {
class Manager;
}

namespace monitor {
class Manager;
}

namespace movegroupctrl {
class Manager;
}

namespace movelandattack {
class Manager;
}

namespace octpusship {
class Manager;
}

namespace pinata {
class Manager;
}

namespace popflower {
class Manager;
}

namespace powersource {
class Manager;
}

namespace pressmachine {
class Manager;
}

namespace rollball {
class Manager;
}

namespace ropeflat {
class Manager;
}

namespace salamanderarm {
class Manager;
}

namespace salamanderbody {
class Manager;
}

namespace sandcastlesuper {
class Manager;
}

namespace screwsuper {
class Manager;
}

namespace scutobj {
class Manager;
}

namespace ship {
class Manager;
}

namespace shipdoor {
class Manager;
}

namespace shooting {
class Manager;
}

namespace shutter {
class Manager;
}

namespace sicevolcano {
class Manager;
}

namespace snowmanbody {
class Manager;
}

namespace spikebar {
class Manager;
}

namespace stake {
class Manager;
}

namespace stakemedium {
class Manager;
}

namespace stakesuper {
class Manager;
}

namespace statue {
class Manager;
}

namespace strikebox {
class Manager;
}

namespace sun {
class Manager;
}

namespace superbeamcenter {
class Manager;
}

namespace superbeamswitch {
class Manager;
}

namespace superbeamswitchtarget {
class Manager;
}

namespace switch_n {
class Manager;
}

namespace totempole {
class Manager;
}

namespace volcano {
class Manager;
}

namespace warplowper {
class Manager;
}

namespace warpstarcontinue {
class Manager;
}

namespace waterflow {
class Manager;
}

namespace zoneswitch {
class Manager;
}

class SwitchReceiverManager;
class TalkManager;

class Manager {
public:
    void onEat(const hel::math::Vector3& pos);
    warpstar::Manager& warpStarManager();
    // TODO: inline in the original. The units written with the call define nothing; a unit that expands it defines
    // SCN_STEP_GIMMICK_MANAGER_SWITCHRECEIVERMANAGER_IN_CLASS ahead of its includes.
#ifdef SCN_STEP_GIMMICK_MANAGER_SWITCHRECEIVERMANAGER_IN_CLASS
    SwitchReceiverManager& switchReceiverManager() { return mSwitchReceiverManager.ref(); }
#else
    SwitchReceiverManager& switchReceiverManager();
#endif
    void onVomit(const hel::math::Vector3& pos);
    void onThroughLand(const hel::math::Vector3& pos);
    void onRun(const hel::math::Vector3& pos);
    void onDrink(const hel::math::Vector3& pos);
    void onHover(const hel::math::Vector3& pos);

    // A unit that uses this defines MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE ahead of its includes.
    shipevent::Manager& shipeventManager() { return mShipeventManager.ref(); }
    TalkManager& talkManager() { return mTalkManager.ref(); }
    airflow::Manager& airFlowManager() { return mAirFlowManager.ref(); }
    aquarock::Manager& aquaRockManager() { return mAquaRockManager.ref(); }
    areaevent::Manager& areaEventManager() { return mAreaEventManager.ref(); }
    arease::Manager& areaSEManager() { return mAreaSEManager.ref(); }
    arrowboard::Manager& arrowBoardManager() { return mArrowBoardManager.ref(); }
    bitestatue::Manager& biteStatueManager() { return mBiteStatueManager.ref(); }
    block::BlockManager& blockManager() { return mBlockManager.ref(); }
    bombmachine::Manager& bombMachineManager() { return mBombMachineManager.ref(); }
    cameralock::Manager& cameraLockManager() { return mCameraLockManager.ref(); }
    cannon::Manager& cannonManager() { return mCannonManager.ref(); }
    cannonblow::Manager& cannonBlowManager() { return mCannonBlowManager.ref(); }
    carrydeegenerator::Manager& carryDeeGeneratorManager() { return mCarryDeeGeneratorManager.ref(); }
    chainstarter::Manager& chainStarterManager() { return mChainStarterManager.ref(); }
    challengedoor::Manager& challengeDoorManager() { return mChallengeDoorManager.ref(); }
    circuitblock::Manager& circuitBlockManager() { return mCircuitBlockManager.ref(); }
    consecutivebattle::Manager& consecutiveBattleManager() { return mConsecutiveBattleManager.ref(); }
    crushwallsuper::Manager& crushWallSuperManager() { return mCrushWallSuperManager.ref(); }
    crushwallbellsuper::Manager& crushWallBellSuperManager() { return mCrushWallBellSuperManager.ref(); }
    crystalwall::Manager& crystalWallManager() { return mCrystalWallManager.ref(); }
    cutropestep::Manager& cutRopeStepManager() { return mCutRopeStepManager.ref(); }
    darkwall::Manager& darkWallManager() { return mDarkWallManager.ref(); }
    door::Manager& doorManager() { return mDoorManager.ref(); }
    fallpole::Manager& fallPoleManager() { return mFallPoleManager.ref(); }
    finalpopstar::Manager& finalPopstarManager() { return mFinalPopstarManager.ref(); }
    fuse::Manager& fuseManager() { return mFuseManager.ref(); }
    guideboard::Manager& guideBoardManager() { return mGuideBoardManager.ref(); }
    guideplate::Manager& guidePlateManager() { return mGuidePlateManager.ref(); }
    hangswitch::Manager& hangSwitchManager() { return mHangSwitchManager.ref(); }
    icepin::Manager& icePinManager() { return mIcePinManager.ref(); }
    icicle::Manager& icicleManager() { return mIcicleManager.ref(); }
    injectionbox::Manager& injectionBoxManager() { return mInjectionBoxManager.ref(); }
    lavageyser::Manager& lavaGeyserManager() { return mLavaGeyserManager.ref(); }
    lightblock::Manager& lightBlockManager() { return mLightBlockManager.ref(); }
    lockshutter::Manager& lockShutterManager() { return mLockShutterManager.ref(); }
    lvmapdoor::Manager& lvMapDoorManager() { return mLvMapDoorManager.ref(); }
    mahoroa::Manager& mahoroaManager() { return mMahoroaManager.ref(); }
    movegroupctrl::Manager& movegroupctrlManager() { return mMovegroupctrlManager.ref(); }
    movelandattack::Manager& moveLandAttackManager() { return mMoveLandAttackManager.ref(); }
    octpusship::Manager& octpusShipManager() { return mOctpusShipManager.ref(); }
    pinata::Manager& pinataManager() { return mPinataManager.ref(); }
    popflower::Manager& popFlowerManager() { return mPopFlowerManager.ref(); }
    powersource::Manager& powerSourceManager() { return mPowerSourceManager.ref(); }
    pressmachine::Manager& pressMachineManager() { return mPressMachineManager.ref(); }
    rollball::Manager& rollballManager() { return mRollballManager.ref(); }
    ropeflat::Manager& ropeFlatManager() { return mRopeFlatManager.ref(); }
    salamanderarm::Manager& salamanderArmManager() { return mSalamanderArmManager.ref(); }
    salamanderbody::Manager& salamanderBodyManager() { return mSalamanderBodyManager.ref(); }
    sandcastlesuper::Manager& sandCastleSuperManager() { return mSandCastleSuperManager.ref(); }
    screwsuper::Manager& screwSuperManager() { return mScrewSuperManager.ref(); }
    scutobj::Manager& scutobjManager() { return mScutobjManager.ref(); }
    ship::Manager& shipManager() { return mShipManager.ref(); }
    shipdoor::Manager& shipdoorManager() { return mShipdoorManager.ref(); }
    shooting::Manager& shootingManager() { return mShootingManager.ref(); }
    shutter::Manager& shutterManager() { return mShutterManager.ref(); }
    sicevolcano::Manager& sIceVolcanoManager() { return mSIceVolcanoManager.ref(); }
    snowmanbody::Manager& snowmanBodyManager() { return mSnowmanBodyManager.ref(); }
    spikebar::Manager& spikeBarManager() { return mSpikeBarManager.ref(); }
    stake::Manager& stakeManager() { return mStakeManager.ref(); }
    stakemedium::Manager& stakeMediumManager() { return mStakeMediumManager.ref(); }
    stakesuper::Manager& stakeSuperManager() { return mStakeSuperManager.ref(); }
    statue::Manager& statueManager() { return mStatueManager.ref(); }
    strikebox::Manager& strikeBoxManager() { return mStrikeBoxManager.ref(); }
    sun::Manager& sunManager() { return mSunManager.ref(); }
    superbeamcenter::Manager& superBeamCenterManager() { return mSuperBeamCenterManager.ref(); }
    superbeamswitch::Manager& superBeamSwitchManager() { return mSuperBeamSwitchManager.ref(); }
    superbeamswitchtarget::Manager& superBeamSwitchTargetManager() { return mSuperBeamSwitchTargetManager.ref(); }
    switch_n::Manager& switchManager() { return mSwitchManager.ref(); }
    totempole::Manager& totemPoleManager() { return mTotemPoleManager.ref(); }
    volcano::Manager& volcanoManager() { return mVolcanoManager.ref(); }
    warplowper::Manager& warpLowperManager() { return mWarpLowperManager.ref(); }
    warpstarcontinue::Manager& warpStarContinueManager() { return mWarpStarContinueManager.ref(); }
    waterflow::Manager& waterFlowManager() { return mWaterFlowManager.ref(); }
    zoneswitch::Manager& zoneSwitchManager() { return mZoneSwitchManager.ref(); }
    monitor::Manager& monitorManager() { return mMonitorManager.ref(); }
    injection::SEManager& injectionSEManager() { return mInjectionSEManager.ref(); }

private:
    // TODO: what this is.
    u32 _0;
    mem::ExplicitScopedPtr<SwitchReceiverManager> mSwitchReceiverManager;
    mem::ExplicitScopedPtr<TalkManager> mTalkManager;
    mem::ExplicitScopedPtr<airflow::Manager> mAirFlowManager;
    mem::ExplicitScopedPtr<aquarock::Manager> mAquaRockManager;
    mem::ExplicitScopedPtr<areaevent::Manager> mAreaEventManager;
    mem::ExplicitScopedPtr<arease::Manager> mAreaSEManager;
    mem::ExplicitScopedPtr<arrowboard::Manager> mArrowBoardManager;
    mem::ExplicitScopedPtr<bitestatue::Manager> mBiteStatueManager;
    mem::ExplicitScopedPtr<block::BlockManager> mBlockManager;
    mem::ExplicitScopedPtr<bombmachine::Manager> mBombMachineManager;
    mem::ExplicitScopedPtr<cameralock::Manager> mCameraLockManager;
    mem::ExplicitScopedPtr<cannon::Manager> mCannonManager;
    mem::ExplicitScopedPtr<cannonblow::Manager> mCannonBlowManager;
    mem::ExplicitScopedPtr<carrydeegenerator::Manager> mCarryDeeGeneratorManager;
    mem::ExplicitScopedPtr<chainstarter::Manager> mChainStarterManager;
    mem::ExplicitScopedPtr<challengedoor::Manager> mChallengeDoorManager;
    mem::ExplicitScopedPtr<circuitblock::Manager> mCircuitBlockManager;
    mem::ExplicitScopedPtr<consecutivebattle::Manager> mConsecutiveBattleManager;
    mem::ExplicitScopedPtr<crushwallsuper::Manager> mCrushWallSuperManager;
    mem::ExplicitScopedPtr<crushwallbellsuper::Manager> mCrushWallBellSuperManager;
    mem::ExplicitScopedPtr<crystalwall::Manager> mCrystalWallManager;
    mem::ExplicitScopedPtr<cutropestep::Manager> mCutRopeStepManager;
    mem::ExplicitScopedPtr<darkwall::Manager> mDarkWallManager;
    mem::ExplicitScopedPtr<door::Manager> mDoorManager;
    mem::ExplicitScopedPtr<fallpole::Manager> mFallPoleManager;
    mem::ExplicitScopedPtr<finalpopstar::Manager> mFinalPopstarManager;
    mem::ExplicitScopedPtr<fuse::Manager> mFuseManager;
    mem::ExplicitScopedPtr<guideboard::Manager> mGuideBoardManager;
    mem::ExplicitScopedPtr<guideplate::Manager> mGuidePlateManager;
    mem::ExplicitScopedPtr<hangswitch::Manager> mHangSwitchManager;
    mem::ExplicitScopedPtr<icepin::Manager> mIcePinManager;
    mem::ExplicitScopedPtr<icicle::Manager> mIcicleManager;
    mem::ExplicitScopedPtr<injectionbox::Manager> mInjectionBoxManager;
    mem::ExplicitScopedPtr<lavageyser::Manager> mLavaGeyserManager;
    mem::ExplicitScopedPtr<lightblock::Manager> mLightBlockManager;
    mem::ExplicitScopedPtr<lockshutter::Manager> mLockShutterManager;
    mem::ExplicitScopedPtr<lvmapdoor::Manager> mLvMapDoorManager;
    mem::ExplicitScopedPtr<mahoroa::Manager> mMahoroaManager;
    mem::ExplicitScopedPtr<movegroupctrl::Manager> mMovegroupctrlManager;
    mem::ExplicitScopedPtr<movelandattack::Manager> mMoveLandAttackManager;
    mem::ExplicitScopedPtr<octpusship::Manager> mOctpusShipManager;
    mem::ExplicitScopedPtr<pinata::Manager> mPinataManager;
    mem::ExplicitScopedPtr<popflower::Manager> mPopFlowerManager;
    mem::ExplicitScopedPtr<powersource::Manager> mPowerSourceManager;
    mem::ExplicitScopedPtr<pressmachine::Manager> mPressMachineManager;
    mem::ExplicitScopedPtr<rollball::Manager> mRollballManager;
    mem::ExplicitScopedPtr<ropeflat::Manager> mRopeFlatManager;
    mem::ExplicitScopedPtr<salamanderarm::Manager> mSalamanderArmManager;
    mem::ExplicitScopedPtr<salamanderbody::Manager> mSalamanderBodyManager;
    mem::ExplicitScopedPtr<sandcastlesuper::Manager> mSandCastleSuperManager;
    mem::ExplicitScopedPtr<screwsuper::Manager> mScrewSuperManager;
    mem::ExplicitScopedPtr<scutobj::Manager> mScutobjManager;
    mem::ExplicitScopedPtr<ship::Manager> mShipManager;
    mem::ExplicitScopedPtr<shipdoor::Manager> mShipdoorManager;
    mem::ExplicitScopedPtr<shipevent::Manager> mShipeventManager;
    mem::ExplicitScopedPtr<shooting::Manager> mShootingManager;
    mem::ExplicitScopedPtr<shutter::Manager> mShutterManager;
    mem::ExplicitScopedPtr<sicevolcano::Manager> mSIceVolcanoManager;
    mem::ExplicitScopedPtr<snowmanbody::Manager> mSnowmanBodyManager;
    mem::ExplicitScopedPtr<spikebar::Manager> mSpikeBarManager;
    mem::ExplicitScopedPtr<stake::Manager> mStakeManager;
    mem::ExplicitScopedPtr<stakemedium::Manager> mStakeMediumManager;
    mem::ExplicitScopedPtr<stakesuper::Manager> mStakeSuperManager;
    mem::ExplicitScopedPtr<statue::Manager> mStatueManager;
    mem::ExplicitScopedPtr<strikebox::Manager> mStrikeBoxManager;
    mem::ExplicitScopedPtr<sun::Manager> mSunManager;
    mem::ExplicitScopedPtr<superbeamcenter::Manager> mSuperBeamCenterManager;
    mem::ExplicitScopedPtr<superbeamswitch::Manager> mSuperBeamSwitchManager;
    mem::ExplicitScopedPtr<superbeamswitchtarget::Manager> mSuperBeamSwitchTargetManager;
    mem::ExplicitScopedPtr<switch_n::Manager> mSwitchManager;
    mem::ExplicitScopedPtr<totempole::Manager> mTotemPoleManager;
    mem::ExplicitScopedPtr<volcano::Manager> mVolcanoManager;
    mem::ExplicitScopedPtr<warplowper::Manager> mWarpLowperManager;
    mem::ExplicitScopedPtr<warpstar::Manager> mWarpStarManager;
    mem::ExplicitScopedPtr<warpstarcontinue::Manager> mWarpStarContinueManager;
    mem::ExplicitScopedPtr<waterflow::Manager> mWaterFlowManager;
    mem::ExplicitScopedPtr<zoneswitch::Manager> mZoneSwitchManager;
    mem::ExplicitScopedPtr<monitor::Manager> mMonitorManager;
    mem::ExplicitScopedPtr<injection::SEManager> mInjectionSEManager;
};

}}}  // namespace scn::step::gimmick

#endif
