#include "scn/step/boss/roah/AddOnMint.h"

#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/StateBoomerang.h"
#include "scn/step/boss/roah/StateBullet.h"
#include "scn/step/boss/roah/StateComeInBackward.h"
#include "scn/step/boss/roah/StateMahoroaMotionStarWait.h"
#include "scn/step/boss/roah/StateMove.h"
#include "scn/step/boss/roah/StateMoveCircle.h"
#include "scn/step/boss/roah/StateOar.h"
#include "scn/step/boss/roah/StateOarEnd.h"
#include "scn/step/boss/roah/StatePursuit.h"
#include "scn/step/boss/roah/StateStar.h"
#include "scn/step/boss/roah/StateStorm.h"
#include "scn/step/boss/roah/StateTackle.h"
#include "scn/step/boss/roah/StateTackleEnd.h"
#include "scn/step/boss/roah/StateTacklePursuit.h"
#include "scn/step/boss/roah/StateWaveStar.h"
#include "scn/step/boss/roah/StateZPassThrough.h"
#include "scn/step/boss/roah/StateZStar.h"
#include "scn/step/boss/roah/WeaponCtrl.h"

using hel::common::DynamicCastToRef;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace roah {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Move(f32 x, f32 y, int kind, bool flag) {
    StateMove::Config config;
    config._0 = kind;
    config._4.x = x;
    config._4.y = y;
    config._C = flag;
    MintBoss::Obj().stateChanger().setNextState<StateMove, Boss*, StateMove::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Star(int kind) {
    StateStar::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateStar, Boss*, StateStar::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_WaveStar(int kind) {
    StateWaveStar::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateWaveStar, Boss*, StateWaveStar::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_MahoroaMotionStarWait() {
    MintBoss::Obj().stateChanger().setNextState<StateMahoroaMotionStarWait, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Boomerang(int kind) {
    StateBoomerang::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateBoomerang, Boss*, StateBoomerang::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Storm(int time, f32 speed, StormKind kind) {
    StateStorm::Config config;
    config._0 = time;
    config._4 = speed;
    config._8 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateStorm, Boss*, StateStorm::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_StormUpDown(int time, f32 speed) {
    t_SetNextState_Storm(time, speed, StormKind_UpDown);
}

void t_SetNextState_StormCircle(int time) {
    t_SetNextState_Storm(time, 0.0f, StormKind_Circle);
}

void t_SetNextState_Oar() {
    MintBoss::Obj().stateChanger().setNextState<StateOar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_OarEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateOarEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MoveCircle(int time, f32 _1, f32 _2, f32 _3) {
    StateMoveCircle::Config config;
    config._0 = time;
    config._4 = _1;
    config._8 = _2;
    config._C = _3;
    MintBoss::Obj().stateChanger().setNextState<StateMoveCircle, Boss*, StateMoveCircle::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Pursuit(int time, f32 _1, f32 _2, f32 _3) {
    StatePursuit::Config config;
    config._0 = time;
    config._4 = gobj::MoveParamAccel::Create(_1, _2, _3);
    MintBoss::Obj().stateChanger().setNextState<StatePursuit, Boss*, StatePursuit::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Bullet(int _0, int _1) {
    StateBullet::Config config;
    config._0 = _0;
    config._4 = _1;
    MintBoss::Obj().stateChanger().setNextState<StateBullet, Boss*, StateBullet::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Tackle(int time, f32 _1, f32 _2, f32 _3, int _4, f32 _5, f32 _6) {
    StateTacklePursuit::Config pursuitConfig;
    pursuitConfig._0 = time;
    pursuitConfig._4 = gobj::MoveParamAccel::Create(_1, _2, _3);
    StateTackle::Config tackleConfig;
    tackleConfig._0 = _4;
    tackleConfig._4 = _5;
    tackleConfig._8 = _6;
    MintBoss::Obj().stateChanger().setNextState<StateTacklePursuit, Boss*, StateTacklePursuit::Config, StateTackle::Config>(&MintBoss::Obj(), pursuitConfig,
                                                                                                                            tackleConfig);
}

void t_SetNextState_TackleEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ComeInBackward(f32 x, f32 y, int kind) {
    StateComeInBackward::Config config;
    config._0 = kind;
    config._4.x = x;
    config._4.y = y;
    MintBoss::Obj().stateChanger().setNextState<StateComeInBackward, Boss*, StateComeInBackward::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_ZStar(int _0, f32 _1, f32 _2, int _3, bool _4) {
    StateZStar::Config config;
    config._0 = _0;
    config._4 = _1;
    config._8 = _2;
    config._C = _3;
    config._10 = _4;
    MintBoss::Obj().stateChanger().setNextState<StateZStar, Boss*, StateZStar::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_ZPassThrough() {
    MintBoss::Obj().stateChanger().setNextState<StateZPassThrough, Boss*>(&MintBoss::Obj());
}

void t_WeaponCtrl_AddReqData(int _0, f32 _1, f32 _2, int _3) {
    WeaponCtrl::ReqData data;
    data._0 = _0;
    data._4 = _1;
    data._8 = _2;
    data._C = _3;
    t_custom().weaponCtrl().addReqData(data);
}

void t_WeaponCtrl_Request() {
    t_custom().weaponCtrl().request();
}

void t_WeaponCtrl_ClearReqBuff() {
    t_custom().weaponCtrl().clearReqBuff();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Move(float,float,int,bool)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Star(int)", Star, t_SetNextState_Star);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void WaveStar(int)", WaveStar, t_SetNextState_WaveStar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void MahoroaMotionStarWait()", MahoroaMotionStarWait,
                         t_SetNextState_MahoroaMotionStarWait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Boomerang(int)", Boomerang, t_SetNextState_Boomerang);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void StormUpDown(int,float)", StormUpDown, t_SetNextState_StormUpDown);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void StormCircle(int)", StormCircle, t_SetNextState_StormCircle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Oar()", Oar, t_SetNextState_Oar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void OarEnd()", OarEnd, t_SetNextState_OarEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void MoveCircle(int,float,float,float)", MoveCircle, t_SetNextState_MoveCircle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Pursuit(int,float,float,float)", Pursuit, t_SetNextState_Pursuit);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Bullet(int,int)", Bullet, t_SetNextState_Bullet);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void Tackle(int,float,float,float,int,float,float)", Tackle, t_SetNextState_Tackle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void TackleEnd()", TackleEnd, t_SetNextState_TackleEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void ComeInBackward(float,float,int)", ComeInBackward, t_SetNextState_ComeInBackward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void ZStar(int,float,float,int,bool)", ZStar, t_SetNextState_ZStar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.SetNextState", "void ZPassThrough()", ZPassThrough, t_SetNextState_ZPassThrough);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.WeaponCtrl", "void AddReqData(int,float,float,int)", AddReqData, t_WeaponCtrl_AddReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.WeaponCtrl", "void Request()", Request, t_WeaponCtrl_Request);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Roah.WeaponCtrl", "void ClearReqBuff()", ClearReqBuff, t_WeaponCtrl_ClearReqBuff);
}

}

}}}}  // namespace scn::step::boss::roah
