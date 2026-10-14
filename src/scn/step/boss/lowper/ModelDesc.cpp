#define DYNAMICS_DESC_MEMBERS

#include "scn/step/boss/lowper/ModelDesc.h"

#include "dynamics/Desc.h"
#include "gobj/AnimScript.h"
#include "hel/common/Array.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/ModelDesc.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/lowper/Param.h"
#include "std/min.h"

using hel::common::Array;
using hel::common::ArrayUtil;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace {

const char* DynamicsTargetNode_0[] = { "Tail21DJ", "Tail31DJ" };
const char* DynamicsTargetNode_1[] = { "Tail11DJ", "Tail41DJ", "Tail51DJ" };
const char* DynamicsTargetNode_2[] = { "Tail21DJ", "Tail31DJ", "Tail41DJ", "Tail51DJ" };
const char* DynamicsTargetNode_3[] = { "Tail11DJ", "Tail21DJ", "Tail31DJ", "Tail41DJ", "Tail51DJ" };

struct DynamicsTargetData {
    u32 mNum;
    const char** mNames;
};

const DynamicsTargetData DYNAMICS_TARGET_DATA[] = {
    { 2, DynamicsTargetNode_0 },
    { 3, DynamicsTargetNode_1 },
    { 4, DynamicsTargetNode_2 },
    { 5, DynamicsTargetNode_3 },
};

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyM",
    "ItemConstL",
    "ControlL",
    "Tail1M",
    "Tail2M",
    "Tail3M",
    "Tail4M",
    "Tail5M",
    "LWing1J",
    "LWing2J",
    "RWing1J",
    "RWing2J",
    "HairJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "SphereWait", 0 },
    { "Appear", 0 },
    { "Loop", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "PreGlide", 0 },
    { "PreGlideLoop", 0 },
    { "GlideStart", 0 },
    { "Glide", 0 },
    { "ShotStart", 0 },
    { "Shot", 0 },
    { "ShotDropStart", 0 },
    { "ShotDrop", 0 },
    { "ScrewGlide", 0 },
    { "SprinklerShotStart", 0 },
    { "SprinklerShot", 0 },
    { "Laugh", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Lowper.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "Lowper.AnimScript.ShotBulletStart.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.ShotBullet.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.ShotBulletFast.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.GlidePre.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.GlidePreLoop.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Glide.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.GlideFar.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.GlideFarRolling.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SphereWait.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.BombOutOutIn.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.BombOutInOut.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.BombFar.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Sprinkler.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.RainBombStart.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.RainBomb.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.RainBombGlide.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SummonBarrier.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Laugh.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.WarpIn.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.WarpOut.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FireTackleStart.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FireTackle.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SparkAttackStart.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SparkAttack.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SparkAttackRolling.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FreezeAttackStart.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FreezeAttackHold.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FreezeAttack.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FreezeAttack.ExecSmallOne", 0, 0, 0, 0 },
    { "Lowper.AnimScript.FreezeAttack.ExecIceSpine", 0, 0, 0, 0 },
    { "Lowper.AnimScript.Vortex.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.SparkShot.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.BarrierAttack.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.ReflectHomingShot.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.ReqBlackHole.Exec", 0, 0, 0, 0 },
    { "Lowper.AnimScript.ReverseDimension.Exec", 0, 0, 0, 0 },
};

// TODO: the name is a guess; chara::ModelDesc holds a pointer to it at 0x7C.
struct ModelDynamicsDesc {
    u32 mNum;
    Array<dynamics::Desc, 5>* mDescs;
};

// TODO: the original is dynamics::Desc::setDescNode expanded, with the nodes in a hel::common::Array.
inline void t_setDescNode(dynamics::Desc& desc, u32 index, const Param::DynamicsNode& node) {
    ArrayUtil::RangeCheck(index, 5);
    dynamics::DescNode& dst = desc.mNodes[index];
    dst._0[0] = node._0;
    dst._0[1] = node._4;
    dst._0[2] = node._8;
    dst._0[3] = node._C;
    dst._0[4] = node._10;
    dst._0[5] = node._14;
    dst._0[6] = node._18;
    dst._0[7] = node._1C;
    dst._0[8] = node._20;
}

void t_dynamics(chara::ModelDesc& desc, const Param::Dynamics& param, u32 level) {
    static Array<dynamics::Desc, 5> dynaDesc;
    static ModelDynamicsDesc modelDynaDesc;

    dynaDesc[0]._0 = param._0;
    dynaDesc[0].mNodeNum = 3;
    for (u32 i = 0; i < dynaDesc[0].mNodeNum; i++) {
        Param::DynamicsNode node = param.mNodes[i];
        node._8 = 0.017453292f * node._8;
        node._10 = 0.017453292f * node._10;
        node._14 = 0.017453292f * node._14;
        node._18 = 0.017453292f * node._18;
        node._1C = 0.017453292f * node._1C;
        t_setDescNode(dynaDesc[0], i, node);
    }
    u32 num = DYNAMICS_TARGET_DATA[level].mNum;
    for (u32 i = 0; i < num; i++) {
        dynaDesc[i] = dynaDesc[0];
    }
    for (u32 i = 0; i < num; i++) {
        dynaDesc[i].mName = DYNAMICS_TARGET_DATA[level].mNames[i];
    }
    modelDynaDesc.mNum = num;
    modelDynaDesc.mDescs = &dynaDesc;
    desc._70[3] = reinterpret_cast<u32>(&modelDynaDesc);
}

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    const char* models[] = {
        "step/chara/enemy/lowper/ModelLv1",
        "step/chara/enemy/lowper/ModelLv2",
        "step/chara/enemy/lowper/ModelLv3",
        "step/chara/enemy/lowper/ModelLv4",
    };
    const char* modelsEx[] = {
        "step/chara/enemy/lowper/ModelLv1Ex",
        "step/chara/enemy/lowper/ModelLv2Ex",
        "step/chara/enemy/lowper/ModelLv3Ex",
        "step/chara/enemy/lowper/ModelLv4Ex",
    };
    const char** modelPaths = isExtra ? modelsEx : models;
    u32 maxLevel = 3;
    u32 lv = std::min<u32>(maxLevel, level);
    const char* motionPath = "step/chara/enemy/lowper/Motion";
    chara::ModelDesc* desc;
    switch (lv) {
    case 0:
        desc = &boss::ModelDesc::CreateTmpl<0, 0, 0>(modelPaths[lv], motionPath, "Lowper", 14, T_NODE_NAMES, 18, T_ANIM_ENTRIES, 42,
                                                     T_SCRIPT_ENTRIES);
        break;
    case 1:
        desc = &boss::ModelDesc::CreateTmpl<0, 1, 0>(modelPaths[lv], motionPath, "Lowper", 14, T_NODE_NAMES, 18, T_ANIM_ENTRIES, 42,
                                                     T_SCRIPT_ENTRIES);
        break;
    case 2:
        desc = &boss::ModelDesc::CreateTmpl<0, 2, 0>(modelPaths[lv], motionPath, "Lowper", 14, T_NODE_NAMES, 18, T_ANIM_ENTRIES, 42,
                                                     T_SCRIPT_ENTRIES);
        break;
    default:
        desc = &boss::ModelDesc::CreateTmpl<0, 3, 0>(modelPaths[lv], motionPath, "Lowper", 14, T_NODE_NAMES, 18, T_ANIM_ENTRIES, 42,
                                                     T_SCRIPT_ENTRIES);
        break;
    }
    desc->_c = Vector3(0.0f, 0.5f, 0.0f);
    t_dynamics(*desc, boss::Param().lowper()._138, lv);
    return *desc;
}

}

}}}}  // namespace scn::step::boss::lowper
