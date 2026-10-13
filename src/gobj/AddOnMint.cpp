#include "gobj/AddOnMint.h"

#include "g3d/MintWrapNative.h"
#include "gobj/MintAnim.h"
#include "gobj/MintFootState.h"
#include "gobj/MintGearAnim.h"
#include "gobj/MintLocation.h"
#include "gobj/MintMeshFlip.h"
#include "gobj/MintModel.h"
#include "gobj/MintMove.h"
#include "gobj/MintScript.h"
#include "gobj/MintTarget.h"

namespace gobj {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void Start(int)", Start, static_cast<void (*)(u32)>(&MintAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void Start(int,bool)", Start, static_cast<void (*)(u32, bool)>(&MintAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void Start(int,bool,float)", Start, static_cast<void (*)(u32, bool, f32)>(&MintAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "float Frame()", Frame, &MintAnim::Frame);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "int TotalFrame()", TotalFrame, &MintAnim::TotalFrame);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void SetFrame(float)", SetFrame, &MintAnim::SetFrame);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void SetFrameToHead()", SetFrameToHead, &MintAnim::SetFrameToHead);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void SetFrameToTail()", SetFrameToTail, &MintAnim::SetFrameToTail);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "bool IsAnimEnd()", IsAnimEnd, &MintAnim::IsAnimEnd);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "bool IsLooped()", IsLooped, &MintAnim::IsLooped);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "float FrameRate()", FrameRate, &MintAnim::FrameRate);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void SetFrameRate(float)", SetFrameRate, &MintAnim::SetFrameRate);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "int CurrentG3DAnimIndex()", CurrentG3DAnimIndex, &MintAnim::CurrentG3DAnimIndex);
    MINT_NATIVE_FUNCTION(core, "GObj.Anim", "void CheckIsReachableFrame(int)", CheckIsReachableFrame, &MintAnim::CheckIsReachableFrame);

    MINT_NATIVE_FUNCTION(core, "GObj.FootState", "bool IsGround()", IsGround, &MintFootState::IsGround);
    MINT_NATIVE_FUNCTION(core, "GObj.FootState", "bool IsAir()", IsAir, &MintFootState::IsAir);

    core.addNativePod("GObj.GearAnim", sizeof(MintGearAnim));
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "void start(int)const", start, static_cast<void (MintGearAnim::*)(u32) const>(&MintGearAnim::start));
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "void start(int,bool)const", start,
                           static_cast<void (MintGearAnim::*)(u32, bool) const>(&MintGearAnim::start));
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "void start(int,bool,uint)const", start,
                           static_cast<void (MintGearAnim::*)(u32, bool, u32) const>(&MintGearAnim::start));
    // BUG: frame and totalFrame are bound as methods that return nothing, so their wrapper stores no
    // return value for the script. setFrame is bound as a const method, which only shares a wrapper.
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "float frame()const", frame, (void (MintGearAnim::*)() const) & MintGearAnim::frame);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "float totalFrame()const", totalFrame, (void (MintGearAnim::*)() const) & MintGearAnim::totalFrame);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "void setFrame(float)", setFrame, (void (MintGearAnim::*)(f32) const) & MintGearAnim::setFrame);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "bool isAnimEnd()const", isAnimEnd, &MintGearAnim::isAnimEnd);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "bool isLooped()const", isLooped, &MintGearAnim::isLooped);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "float frameRate()const", frameRate, &MintGearAnim::frameRate);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "void setFrameRate(float)const", setFrameRate, &MintGearAnim::setFrameRate);
    MINT_NATIVE_POD_METHOD(core, "GObj.GearAnim", "int currentG3DAnimIndex()const", currentG3DAnimIndex, &MintGearAnim::currentG3DAnimIndex);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "GObj.GearAnim Obj()", Obj, &MintGearAnim::Obj);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "void Start(int)", Start, static_cast<void (*)(u32)>(&MintGearAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "void Start(int,bool)", Start, static_cast<void (*)(u32, bool)>(&MintGearAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "void Start(int,bool,int)", Start, static_cast<void (*)(u32, bool, u32)>(&MintGearAnim::Start));
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "float Frame()", Frame, &MintGearAnim::Frame);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "int TotalFrame()", TotalFrame, &MintGearAnim::TotalFrame);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "void SetFrame(float)", SetFrame, &MintGearAnim::SetFrame);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "bool IsAnimEnd()", IsAnimEnd, &MintGearAnim::IsAnimEnd);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "bool IsLooped()", IsLooped, &MintGearAnim::IsLooped);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "float FrameRate()", FrameRate, &MintGearAnim::FrameRate);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "void SetFrameRate(float)", SetFrameRate, &MintGearAnim::SetFrameRate);
    MINT_NATIVE_FUNCTION(core, "GObj.GearAnim", "int CurrentG3DAnimIndex()", CurrentG3DAnimIndex, &MintGearAnim::CurrentG3DAnimIndex);

    MINT_NATIVE_FUNCTION(core, "GObj.Location", "void LoadPos()", LoadPos, &MintLocation::LoadPos);
    MINT_NATIVE_FUNCTION(core, "GObj.Location", "void LoadPrevPos()", LoadPrevPos, &MintLocation::LoadPrevPos);
    MINT_NATIVE_FUNCTION(core, "GObj.Location", "const HEL.Math.Vector3 Pos()", Pos, &MintLocation::Pos);
    MINT_NATIVE_FUNCTION(core, "GObj.Location", "const HEL.Math.Vector3 PrevPos()", PrevPos, &MintLocation::PrevPos);

    MINT_NATIVE_FUNCTION(core, "GObj.MeshFlip", "void Flip(int)", Flip, &MintMeshFlip::Flip);

    MINT_NATIVE_FUNCTION(core, "GObj.Model", "void LoadNode(int)", LoadNode, &MintModel::LoadNode);
    MINT_NATIVE_FUNCTION(core, "GObj.Model", "void SetScale(float,float,float)", SetScale, &MintModel::SetScale);

    MINT_NATIVE_FUNCTION(core, "GObj.Move", "float GetSpeedH()", GetSpeedH, &MintMove::GetSpeedH);
    MINT_NATIVE_FUNCTION(core, "GObj.Move", "float GetSpeedV()", GetSpeedV, &MintMove::GetSpeedV);
    MINT_NATIVE_FUNCTION(core, "GObj.Move", "float GetSpeedD()", GetSpeedD, &MintMove::GetSpeedD);
    MINT_NATIVE_FUNCTION(core, "GObj.Move", "void SetSpeedH(float)", SetSpeedH, &MintMove::SetSpeedH);
    MINT_NATIVE_FUNCTION(core, "GObj.Move", "void SetSpeedV(float)", SetSpeedV, &MintMove::SetSpeedV);
    MINT_NATIVE_FUNCTION(core, "GObj.Move", "void SetSpeedD(float)", SetSpeedD, &MintMove::SetSpeedD);

    MINT_NATIVE_FUNCTION(core, "GObj.Script", "int PrevScriptIndex()", PrevScriptIndex, &MintScript::PrevScriptIndex);

    MINT_NATIVE_FUNCTION(core, "GObj.Target", "bool IsRightDir()", IsRightDir, &MintTarget::IsRightDir);
    MINT_NATIVE_FUNCTION(core, "GObj.Target", "void SetIsRightDir(bool)", SetIsRightDir, &MintTarget::SetIsRightDir);
    MINT_NATIVE_FUNCTION(core, "GObj.Target", "float GetSign()", GetSign, &MintTarget::GetSign);
    MINT_NATIVE_FUNCTION(core, "GObj.Target", "void Invert()", Invert, &MintTarget::Invert);
    MINT_NATIVE_FUNCTION(core, "GObj.Target", "void LoadDirection3()", LoadDirection3, &MintTarget::LoadDirection3);
}

}}  // namespace gobj::AddOnMint
