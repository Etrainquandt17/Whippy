#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#include "scn/step/gimmick/lvmapdoor/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/Component.h"
#include "scn/step/gimmick/lvmapdoor/DoorUnlockStar.h"
#include "scn/step/gimmick/lvmapdoor/LvMapDoor.h"
#include "scn/step/gimmick/lvmapdoor/Manager.h"
#include "scn/step/gimmick/lvmapdoor/MintLvMapDoor.h"
#include "snd/MintSERequestor.h"

// TODO: these belong in the headers of their units, which do not exist yet.
namespace scn {
namespace step {

namespace info {

class Manager {
public:
    void start();
};

}

namespace StepReleaseUtil {

void StepRelease(Component& component);

}}}  // namespace scn::step::StepReleaseUtil

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

namespace {

void t_SoundSE_BindNormal() {
    snd::MintSERequestor::RegisterForce(MintLvMapDoor::Obj().soundSE());
}

void t_UnlockAnim() {
    MintLvMapDoor::Obj().unlockAnim();
}

void t_ReqUnlockEffect1_WoodBreak() {
    MintLvMapDoor::Obj().reqUnlockEffect1_WoodBreak();
}

void t_ReqUnlockEffect1() {
    MintLvMapDoor::Obj().reqUnlockEffect1();
}

void t_ReqUnlockEffect2() {
    MintLvMapDoor::Obj().reqUnlockEffect2();
}

void t_ReqUnlockEffect3_GrowSmoke() {
    MintLvMapDoor::Obj().reqUnlockEffect3_GrowSmoke();
}

void t_ReqUnlockEffect3_MagmaHit(u32 index) {
    MintLvMapDoor::Obj().reqUnlockEffect3_MagmaHit(index);
}

void t_ReqUnlockEffect3_Aurora() {
    MintLvMapDoor::Obj().reqUnlockEffect3_Aurora();
}

void t_ReqUnlockEffect3_Magma() {
    MintLvMapDoor::Obj().reqUnlockEffect3_Magma();
}

void t_StopUnlockEffect2() {
    MintLvMapDoor::Obj().stopUnlockEffect2();
}

void t_StopUnlockEffect3() {
    MintLvMapDoor::Obj().stopUnlockEffect3();
}

void t_reqCommonEffect() {
    MintLvMapDoor::Obj().reqCommonEffect();
}

bool t_isDoorAnimEnd() {
    return MintLvMapDoor::Obj().isDoorAnimEnd();
}

void t_disableDoorUnlockFlag() {
    MintLvMapDoor::Obj().manager().disableDoorUnlockFlag();
}

void t_onVisibleStageBoard() {
    MintLvMapDoor::Obj().onVisibleStageBoard();
}

void t_InfoAnimIn() {
    MintLvMapDoor::Obj().infoAnimIn();
}

void t_SetZoom(f32 a, f32 b) {
    MintLvMapDoor::Obj().setZoom(a, b);
}

u32 t_SetZoom(f32 a, f32 b, f32 c, f32 d) {
    return MintLvMapDoor::Obj().setZoom(a, b, c, d);
}

void t_SetDistance(f32 distance) {
    MintLvMapDoor::Obj().setDistance(distance);
}

void t_SetTargetDistance(f32 distance) {
    MintLvMapDoor::Obj().setTargetDistance(distance);
}

void t_SetTargetFrame(int frame) {
    MintLvMapDoor::Obj().setTargetFrame(frame);
}

void t_SetCameraTargetDoor() {
    MintLvMapDoor::Obj().setCameraTargetDoor();
}

void t_UnsetCameraTargetDoor() {
    MintLvMapDoor::Obj().unsetCameraTargetDoor();
}

void t_ReqQuakeSS() {
    MintLvMapDoor::Obj().reqQuake(static_cast<camera::QuakeKind>(1));
}

void t_ReqQuakeL() {
    MintLvMapDoor::Obj().reqQuake(static_cast<camera::QuakeKind>(7));
}

void t_UnsetZoom(u32 id) {
    MintLvMapDoor::Obj().unsetZoom(id);
}

void t_SetCamRotDegX(f32 a, f32 b) {
    MintLvMapDoor::Obj().setCamRotDegX(a, b);
}

void t_UnsetCamRotDegX(u32 id) {
    MintLvMapDoor::Obj().unsetCamRotDegX(id);
}

void t_SetRotRateBGX(f32 rate) {
    MintLvMapDoor::Obj().setRotRateBGX(rate);
}

bool t_IsInDoor() {
    return MintLvMapDoor::Obj().isInDoor();
}

void t_StarStart(bool isBoss) {
    LvMapDoor& obj = MintLvMapDoor::Obj();
    if (isBoss) {
        obj.manager().doorUnlockStar().start_Boss();
    } else {
        obj.manager().doorUnlockStar().start();
    }
}

void t_StarSetZoom(bool a, f32 b) {
    MintLvMapDoor::Obj().manager().doorUnlockStar().setZoom(a, b);
}

void t_StarSetKeepCloseDoorIn(bool isValid) {
    MintLvMapDoor::Obj().manager().doorUnlockStar().setVisibleDoorPosValid(isValid);
}

void t_StarUnsetZoom() {
    MintLvMapDoor::Obj().manager().doorUnlockStar().unsetZoom();
}

bool t_StarIsFlyEnd() {
    return MintLvMapDoor::Obj().manager().doorUnlockStar().isFlyEnd();
}

bool t_StarPosSet() {
    return MintLvMapDoor::Obj().manager().starPosSet();
}

void t_DisableDoorInfo() {
    MintLvMapDoor::Obj().manager().disableInfoForDemo();
}

void t_EnableDoorInfo() {
    MintLvMapDoor::Obj().manager().enableInfoForDemo();
}

void t_DisableInputs() {
    MintLvMapDoor::Obj().manager().disableInputs();
}

void t_EnableInputs() {
    MintLvMapDoor::Obj().manager().enableInputs();
}

void t_FlagStart() {
    MintLvMapDoor::Obj().flagStart();
}

bool t_IsUnlock() {
    return MintLvMapDoor::Obj().manager().showDoorUnlockStarDemo();
}

void t_InfoStart() {
    LvMapDoor& obj = MintLvMapDoor::Obj();
    obj.comp().infoManager().start();
    StepReleaseUtil::StepRelease(obj.comp());
}

bool t_IsBossUnlock() {
    LvMapDoor& obj = MintLvMapDoor::Obj();
    return obj.manager().showDoorUnlockStarDemo() && obj.isBossUnlock();
}

int t_GetLevel() {
    return MintLvMapDoor::Obj().getLevel();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.SoundSE", "void BindNormal()", BindNormal, &t_SoundSE_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void UnlockAnim()", UnlockAnim, &t_UnlockAnim);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect1_WoodBreak()", ReqUnlockEffect1_WoodBreak,
                         &t_ReqUnlockEffect1_WoodBreak);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect1()", ReqUnlockEffect1, &t_ReqUnlockEffect1);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect2()", ReqUnlockEffect2, &t_ReqUnlockEffect2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect3_MagmaHit(int)", ReqUnlockEffect3_MagmaHit,
                         &t_ReqUnlockEffect3_MagmaHit);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect3_GrowSmoke()", ReqUnlockEffect3_GrowSmoke,
                         &t_ReqUnlockEffect3_GrowSmoke);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect3_Aurora()", ReqUnlockEffect3_Aurora,
                         &t_ReqUnlockEffect3_Aurora);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqUnlockEffect3_Magma()", ReqUnlockEffect3_Magma,
                         &t_ReqUnlockEffect3_Magma);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StopUnlockEffect2()", StopUnlockEffect2, &t_StopUnlockEffect2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StopUnlockEffect3()", StopUnlockEffect3, &t_StopUnlockEffect3);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqCommonEffect()", ReqCommonEffect, &t_reqCommonEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool IsDoorAnimEnd()", IsDoorAnimEnd, &t_isDoorAnimEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void DisableDoorUnlockFlag()", DisableDoorUnlockFlag,
                         &t_disableDoorUnlockFlag);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void OnVisibleStageBoard()", OnVisibleStageBoard, &t_onVisibleStageBoard);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "int SetZoom(float,float)", SetZoom,
                         reinterpret_cast<u32 (*)(f32, f32)>(static_cast<void (*)(f32, f32)>(t_SetZoom)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "int SetZoom(float,float,float,float)", SetZoom,
                         static_cast<u32 (*)(f32, f32, f32, f32)>(t_SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void SetDistance(float)", SetDistance, &t_SetDistance);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void SetTargetDistance(float)", SetTargetDistance, &t_SetTargetDistance);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void SetTargetFrame(int)", SetTargetFrame,
                         reinterpret_cast<void (*)(u32)>(t_SetTargetFrame));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void UnsetZoom(int)", UnsetZoom, &t_UnsetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void SetCameraTargetDoor()", SetCameraTargetDoor, &t_SetCameraTargetDoor);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void UnsetCameraTargetDoor()", UnsetCameraTargetDoor,
                         &t_UnsetCameraTargetDoor);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqQuakeSS()", ReqQuakeSS, &t_ReqQuakeSS);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void ReqQuakeL()", ReqQuakeL, &t_ReqQuakeL);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void InfoAnimIn()", InfoAnimIn, &t_InfoAnimIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "int SetCamRotDegX(float,float)", SetCamRotDegX,
                         reinterpret_cast<u32 (*)(f32, f32)>(t_SetCamRotDegX));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void UnsetCamRotDegX(int)", UnsetCamRotDegX, &t_UnsetCamRotDegX);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void SetRotRateBGX(float)", SetRotRateBGX, &t_SetRotRateBGX);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool IsInDoor()", IsInDoor, &t_IsInDoor);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StarStart(bool)", StarStart, &t_StarStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StarSetZoom(bool,float)", StarSetZoom, &t_StarSetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StarSetKeepCloseDoorIn(bool)", StarSetKeepCloseDoorIn,
                         &t_StarSetKeepCloseDoorIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void StarUnsetZoom()", StarUnsetZoom, &t_StarUnsetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool StarIsFlyEnd()", StarIsFlyEnd, &t_StarIsFlyEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool StarPosSet()", StarPosSet, &t_StarPosSet);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void DisableDoorInfo()", DisableDoorInfo, &t_DisableDoorInfo);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void EnableDoorInfo()", EnableDoorInfo, &t_EnableDoorInfo);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void DisableInputs()", DisableInputs, &t_DisableInputs);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void EnableInputs()", EnableInputs, &t_EnableInputs);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void FlagStart()", FlagStart, &t_FlagStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool IsUnlock()", IsUnlock, &t_IsUnlock);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "void InfoStart()", InfoStart, &t_InfoStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "bool IsBossUnlock()", IsBossUnlock, &t_IsBossUnlock);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.LvMapDoor.Custom", "int GetLevel()", GetLevel, &t_GetLevel);
}

}}}}}  // namespace scn::step::gimmick::lvmapdoor::AddOnMint
