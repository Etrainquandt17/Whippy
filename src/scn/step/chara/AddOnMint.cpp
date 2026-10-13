#include "scn/step/chara/AddOnMint.h"

#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/MintModel.h"
#include "scn/step/chara/MintModelRotCtrl.h"
#include "scn/step/chara/MintObjColl.h"
#include "scn/step/chara/MintScriptTrigger.h"
#include "scn/step/chara/MintShake.h"

namespace scn {
namespace step {
namespace chara {

// TODO: this is scn/step/chara/MintEffect.h as the original has it, a class that scripts hold by value. That
// header declares the static functions as a namespace, which cannot have the methods bound below; the
// two are to be merged there.
class MintEffect {
public:
    static void RequestP(u32 kind);
    static void RequestPS(u32 kind, f32 scale);
    static void RequestPD(u32 kind);
    static void RequestPDS(u32 kind, f32 scale);
    static void RequestN(u32 kind, u32 node);
    static void RequestNS(u32 kind, u32 node, f32 scale);
    static void RequestNO(u32 kind, u32 node);
    static void RequestNOS(u32 kind, u32 node, f32 scale);
    static void RequestND(u32 kind, u32 node);
    static void RequestNDS(u32 kind, u32 node, f32 scale);
    static void RequestNDO(u32 kind, u32 node);
    static void RequestNDOS(u32 kind, u32 node, f32 scale);
    static void Release();
    static void ReleaseAndVanish();
    static void RequestP(u32 kind, const hel::math::Vector3& pos);
    static void RequestP(u32 kind, const hel::math::Vector3& pos, f32 scale);
    static void RequestPD(u32 kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir);
    static void RequestPD(u32 kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale);
    static void RequestN(u32 kind, u32 node, f32 scale);
    static void RequestN(u32 kind, u32 node, const hel::math::Vector3& offset);
    static void RequestN(u32 kind, u32 node, const hel::math::Vector3& offset, f32 scale);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, f32 scale);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale);

    void requestP(effect::Kind kind, const hel::math::Vector3& pos) const {
        mEffect->requestP(kind, pos);
    }
    void requestP(effect::Kind kind, const hel::math::Vector3& pos, f32 scale) const {
        mEffect->requestP(kind, pos, scale);
    }
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir) const {
        mEffect->requestPD(kind, pos, dir);
    }
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale) const {
        mEffect->requestPD(kind, pos, dir, scale);
    }
    void requestN(effect::Kind kind, u32 node) const {
        mEffect->requestN(kind, node);
    }
    void requestN(effect::Kind kind, u32 node, f32 scale) const {
        mEffect->requestN(kind, node, scale);
    }
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset) const {
        mEffect->requestN(kind, node, offset);
    }
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset, f32 scale) const {
        mEffect->requestN(kind, node, offset, scale);
    }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir) const {
        mEffect->requestND(kind, node, dir);
    }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, f32 scale) const {
        mEffect->requestND(kind, node, dir, scale);
    }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset) const {
        mEffect->requestND(kind, node, dir, offset);
    }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale) const {
        mEffect->requestND(kind, node, dir, offset, scale);
    }
    void release() const {
        mEffect->release();
    }
    void releaseAndVanish() const {
        mEffect->releaseAndVanish();
    }

private:
    Effect* mEffect;
};

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    // BUG: "Vector3const,float", "Direciont3" and the releaseAndVanish without const are the original's declarations.
    core.addNativePod("Scn.Step.Chara.Effect", sizeof(MintEffect));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestP(int,const ref HEL.Math.Vector3)const", requestP,
                           static_cast<void (MintEffect::*)(effect::Kind, const hel::math::Vector3&) const>(&MintEffect::requestP));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestP(int,const ref HEL.Math.Vector3,float)const", requestP,
                           static_cast<void (MintEffect::*)(effect::Kind, const hel::math::Vector3&, f32) const>(&MintEffect::requestP));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestPD(int,const ref HEL.Math.Vector3,HEL.Math.Direction3)const", requestPD,
                           static_cast<void (MintEffect::*)(effect::Kind, const hel::math::Vector3&, const hel::math::Direction3&) const>(&MintEffect::requestPD));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestPD(int,const ref HEL.Math.Vector3,HEL.Math.Direction3,float)const", requestPD,
                           static_cast<void (MintEffect::*)(effect::Kind, const hel::math::Vector3&, const hel::math::Direction3&, f32) const>(&MintEffect::requestPD));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestN(int,int)const", requestN,
                           static_cast<void (MintEffect::*)(effect::Kind, u32) const>(&MintEffect::requestN));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestN(int,int,float)const", requestN,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, f32) const>(&MintEffect::requestN));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestN(int,int,const ref HEL.Math.Vector3)const", requestN,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Vector3&) const>(&MintEffect::requestN));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestN(int,int,const ref HEL.Math.Vector3const,float)", requestN,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Vector3&, f32) const>(&MintEffect::requestN));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestND(int,int,const ref HEL.Math.Direction3)const", requestND,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Direction3&) const>(&MintEffect::requestND));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestND(int,int,const ref HEL.Math.Direction3,float)const", requestND,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Direction3&, f32) const>(&MintEffect::requestND));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestND(int,int,const ref HEL.Math.Direction3,const ref HEL.Math.Vector3)const", requestND,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Direction3&, const hel::math::Vector3&) const>(&MintEffect::requestND));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void requestND(int,int,const ref HEL.Math.Direction3,const ref HEL.Math.Vector3,float)const", requestND,
                           static_cast<void (MintEffect::*)(effect::Kind, u32, const hel::math::Direction3&, const hel::math::Vector3&, f32) const>(&MintEffect::requestND));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void release()const", release,
                           static_cast<void (MintEffect::*)() const>(&MintEffect::release));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Chara.Effect", "void releaseAndVanish()", releaseAndVanish,
                           static_cast<void (MintEffect::*)() const>(&MintEffect::releaseAndVanish));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestP(int)", RequestP, static_cast<void (*)(u32)>(&MintEffect::RequestP));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestPS(int,float)", RequestPS,
                         static_cast<void (*)(u32, f32)>(&MintEffect::RequestPS));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestPD(int)", RequestPD, static_cast<void (*)(u32)>(&MintEffect::RequestPD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestPDS(int,float)", RequestPDS,
                         static_cast<void (*)(u32, f32)>(&MintEffect::RequestPDS));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestN(int,int)", RequestN,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(u32, u32)>(&MintEffect::RequestN)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNS(int,int,float)", RequestNS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintEffect::RequestNS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNO(int,int)", RequestNO,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(u32, u32)>(&MintEffect::RequestNO)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNOS(int,int,float)", RequestNOS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintEffect::RequestNOS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestND(int,int)", RequestND,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(u32, u32)>(&MintEffect::RequestND)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNDS(int,int,float)", RequestNDS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintEffect::RequestNDS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNDO(int,int)", RequestNDO,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(u32, u32)>(&MintEffect::RequestNDO)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestNDOS(int,int,float)", RequestNDOS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintEffect::RequestNDOS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void Release()", Release, static_cast<void (*)()>(&MintEffect::Release));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void ReleaseAndVanish()", ReleaseAndVanish,
                         static_cast<void (*)()>(&MintEffect::ReleaseAndVanish));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestP(int,const ref HEL.Math.Vector3)", RequestP,
                         static_cast<void (*)(u32, const hel::math::Vector3&)>(&MintEffect::RequestP));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestP(int,const ref HEL.Math.Vector3,float)", RequestP,
                         static_cast<void (*)(u32, const hel::math::Vector3&, f32)>(&MintEffect::RequestP));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestPD(int,const ref HEL.Math.Vector3,const ref HEL.Math.Direciont3)", RequestPD,
                         static_cast<void (*)(u32, const hel::math::Vector3&, const hel::math::Direction3&)>(&MintEffect::RequestPD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestPD(int,const ref HEL.Math.Vector3,const ref HEL.Math.Direciont3,float)", RequestPD,
                         static_cast<void (*)(u32, const hel::math::Vector3&, const hel::math::Direction3&, f32)>(&MintEffect::RequestPD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestN(int,int,float)", RequestN,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintEffect::RequestN)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestN(int,int,const ref HEL.Math.Vector3)", RequestN,
                         static_cast<void (*)(u32, u32, const hel::math::Vector3&)>(&MintEffect::RequestN));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestN(int,int,const ref HEL.Math.Vector3,float)", RequestN,
                         static_cast<void (*)(u32, u32, const hel::math::Vector3&, f32)>(&MintEffect::RequestN));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestND(int,int,const ref HEL.Math.Direction3)", RequestND,
                         static_cast<void (*)(u32, u32, const hel::math::Direction3&)>(&MintEffect::RequestND));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestND(int,int,const ref HEL.Math.Direction3,float)", RequestND,
                         static_cast<void (*)(u32, u32, const hel::math::Direction3&, f32)>(&MintEffect::RequestND));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestND(int,int,const ref HEL.Math.Direction3,const ref HEL.Math.Vector3)", RequestND,
                         static_cast<void (*)(u32, u32, const hel::math::Direction3&, const hel::math::Vector3&)>(&MintEffect::RequestND));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Effect", "void RequestND(int,int,const ref HEL.Math.Direction3,const ref HEL.Math.Vector3,float)", RequestND,
                         static_cast<void (*)(u32, u32, const hel::math::Direction3&, const hel::math::Vector3&, f32)>(&MintEffect::RequestND));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddBodyColl(int,float)", AddBodyColl,
                         static_cast<void (*)(u32, f32)>(&MintObjColl::AddBodyColl));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddBodyColl(int,float,float,float)", AddBodyColl,
                         reinterpret_cast<void (*)(int, f32, f32, f32)>(static_cast<void (*)(u32, f32, f32, f32)>(&MintObjColl::AddBodyColl)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddBodyColl(int,float,float,float,float,float)", AddBodyColl,
                         static_cast<void (*)(u32, f32, f32, f32, f32, f32)>(&MintObjColl::AddBodyColl));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddBodyColl(int,float,const ref HEL.Math.Vector2)", AddBodyColl,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&)>(&MintObjColl::AddBodyColl));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddBodyColl(int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2)", AddBodyColl,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&, const hel::math::Vector2&)>(&MintObjColl::AddBodyColl));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void ClearBodyColl()", ClearBodyColl, static_cast<void (*)()>(&MintObjColl::ClearBodyColl));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float)", AddAttack,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintObjColl::AddAttack)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,float,float)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, f32, f32)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,float,float,float,float)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, f32, f32, f32, f32)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,float,float,float,float,bool)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, f32, f32, f32, f32, bool)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,const ref HEL.Math.Vector2)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, const hel::math::Vector2&)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, const hel::math::Vector2&, const hel::math::Vector2&)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddAttack(int,int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2,bool)", AddAttack,
                         static_cast<void (*)(u32, u32, f32, const hel::math::Vector2&, const hel::math::Vector2&, bool)>(&MintObjColl::AddAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void ClearAttack()", ClearAttack, static_cast<void (*)()>(&MintObjColl::ClearAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void ClearAttack(int)", ClearAttack, static_cast<void (*)(u32)>(&MintObjColl::ClearAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetAttackType(int,int)", SetAttackType,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(u32, u32)>(&MintObjColl::SetAttackType)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetAttackCenter(int,float,float)", SetAttackCenter,
                         static_cast<void (*)(u32, f32, f32)>(&MintObjColl::SetAttackCenter));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void RenewAttack()", RenewAttack, static_cast<void (*)()>(&MintObjColl::RenewAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float)", AddSearchHit,
                         static_cast<void (*)(u32, f32)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,float,float)", AddSearchHit,
                         reinterpret_cast<void (*)(int, f32, f32, f32)>(static_cast<void (*)(u32, f32, f32, f32)>(&MintObjColl::AddSearchHit)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,float,float,float,float)", AddSearchHit,
                         static_cast<void (*)(u32, f32, f32, f32, f32, f32)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,float,float,float,float,bool)", AddSearchHit,
                         static_cast<void (*)(u32, f32, f32, f32, f32, f32, bool)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,const ref HEL.Math.Vector2)", AddSearchHit,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2)", AddSearchHit,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&, const hel::math::Vector2&)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchHit(int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2,bool)", AddSearchHit,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&, const hel::math::Vector2&, bool)>(&MintObjColl::AddSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void ClearSearchHit()", ClearSearchHit,
                         static_cast<void (*)()>(&MintObjColl::ClearSearchHit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetSearchHitTeamXlu(int)", SetSearchHitTeamXlu,
                         static_cast<void (*)(u32)>(&MintObjColl::SetSearchHitTeamXlu));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float)", AddSearchAttack,
                         static_cast<void (*)(u32, f32)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,float,float)", AddSearchAttack,
                         reinterpret_cast<void (*)(int, f32, f32, f32)>(static_cast<void (*)(u32, f32, f32, f32)>(&MintObjColl::AddSearchAttack)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,float,float,float,float)", AddSearchAttack,
                         static_cast<void (*)(u32, f32, f32, f32, f32, f32)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,float,float,float,float,bool)", AddSearchAttack,
                         static_cast<void (*)(u32, f32, f32, f32, f32, f32, bool)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,const ref HEL.Math.Vector2)", AddSearchAttack,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2)", AddSearchAttack,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&, const hel::math::Vector2&)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void AddSearchAttack(int,float,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2,bool)", AddSearchAttack,
                         static_cast<void (*)(u32, f32, const hel::math::Vector2&, const hel::math::Vector2&, bool)>(&MintObjColl::AddSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void ClearSearchAttack()", ClearSearchAttack,
                         static_cast<void (*)()>(&MintObjColl::ClearSearchAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "bool IsSearchAttackCollide()", IsSearchAttackCollide,
                         static_cast<bool (*)()>(&MintObjColl::IsSearchAttackCollide));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetBodyCollStateNormal()", SetBodyCollStateNormal,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollStateNormal));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetBodyCollStateInvincible()", SetBodyCollStateInvincible,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollStateInvincible));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetBodyCollStateXlu()", SetBodyCollStateXlu,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollStateXlu));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetBodyCollStateHitOnly()", SetBodyCollStateHitOnly,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollStateHitOnly));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ObjColl", "void SetBodyCollStateCaptureOnly()", SetBodyCollStateCaptureOnly,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollStateCaptureOnly));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Model", "void SetScale3(float,float,float)", SetScale3,
                         static_cast<void (*)(f32, f32, f32)>(&MintModel::SetScale3));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetValid(bool)", SetValid,
                         static_cast<void (*)(bool)>(&MintModelRotCtrl::SetValid));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void ResetRotTarget()", ResetRotTarget,
                         static_cast<void (*)()>(&MintModelRotCtrl::ResetRotTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "float GetRotH()", GetRotH, static_cast<f32 (*)()>(&MintModelRotCtrl::GetRotH));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void InitRotH(float)", InitRotH,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::InitRotH));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotH(float)", SetRotH, static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotH));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotHTarget(float)", SetRotHTarget,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotHTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotHIntpRate(float)", SetRotHIntpRate,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotHIntpRate));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotHIntoTarget()", SetRotHIntoTarget,
                         static_cast<void (*)()>(&MintModelRotCtrl::SetRotHIntoTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "float GetRotV()", GetRotV, static_cast<f32 (*)()>(&MintModelRotCtrl::GetRotV));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void InitRotV(float)", InitRotV,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::InitRotV));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotV(float)", SetRotV, static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotV));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotVTarget(float)", SetRotVTarget,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotVTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotVIntpRate(float)", SetRotVIntpRate,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotVIntpRate));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotVIntoTarget()", SetRotVIntoTarget,
                         static_cast<void (*)()>(&MintModelRotCtrl::SetRotVIntoTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "float GetRotD()", GetRotD, static_cast<f32 (*)()>(&MintModelRotCtrl::GetRotD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void InitRotD(float)", InitRotD,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::InitRotD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotD(float)", SetRotD, static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotD));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotDTarget(float)", SetRotDTarget,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotDTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotDIntpRate(float)", SetRotDIntpRate,
                         static_cast<void (*)(f32)>(&MintModelRotCtrl::SetRotDIntpRate));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.ModelRotCtrl", "void SetRotDIntoTarget()", SetRotDIntoTarget,
                         static_cast<void (*)()>(&MintModelRotCtrl::SetRotDIntoTarget));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Trigger", "void Set(int)", Set, static_cast<void (*)(u32)>(&MintScriptTrigger::Set));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Chara.Shake", "void Request(int)", Request, static_cast<void (*)(int)>(&MintShake::Request));
}

}

}
}
}
