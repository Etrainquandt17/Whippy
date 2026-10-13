#define DYNAMICS_DESC_MEMBERS

#include "scn/step/enemy/bladeknight/ModelDesc.h"

#include "dynamics/Desc.h"
#include "gobj/AnimScript.h"
#include "hel/common/Array.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA4FaceJ",
    "TransL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },       { "Fall", 0 },         { "Landing", 0 }, { "Walk", 0 },    { "Damage", 0 },
    { "DamageEtc", 0 },   { "AttackStart", 0 },  { "DoubleAttack", 0 }, { "Attack", 0 }, { "Retreat", 0 },
    { "Walk2", 0 },       { "JumpStart", 0 },    { "Jump", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "BladeKnight.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { "BladeKnight.AnimScript.DoubleAttack.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 10, 4, 0, 0 },
    { "BladeKnight.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "BladeKnight.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
    { "BladeKnight.AnimScript.SuperAppear.Exec", 0, 0, 0, 0 },
};

// TODO: the name is a guess; chara::ModelDesc holds a pointer to it at 0x7C.
struct ModelDynamicsDesc {
    u32 mNum;
    hel::common::Array<dynamics::Desc, 1>* mDescs;
};

void t_dynamics(chara::ModelDesc& desc) {
    static hel::common::Array<dynamics::Desc, 1> dynaDesc;
    static ModelDynamicsDesc modelDynaDesc;

    dynaDesc[0]._0 = 0.02f;
    dynamics::DescNode node0;
    node0.init(1.0f, 0.0f, 0.0f, 0.4f, 0.0034906585f, 0.034906585f, 0.12217305f, 0.7853982f, 1.0f);
    dynaDesc[0].setDescNode(0, node0);
    dynamics::DescNode node1;
    node1.init(1.0f, 0.0f, 0.0f, 0.3f, 0.0034906585f, 0.034906585f, 0.12217305f, 0.7853982f, 1.0f);
    dynaDesc[0].setDescNode(1, node1);
    dynamics::DescNode node2;
    node2.init(1.0f, 0.0f, 0.0f, 0.2f, 0.0034906585f, 0.034906585f, 0.12217305f, 0.7853982f, 1.0f);
    dynaDesc[0].setDescNode(2, node2);
    dynamics::DescNode node3;
    node3.init(1.0f, 0.0f, 0.0f, 0.1f, 0.0034906585f, 0.034906585f, 0.12217305f, 0.7853982f, 1.0f);
    dynaDesc[0].setDescNode(3, node3);
    dynaDesc[0].mNodeNum = 4;
    dynaDesc[0].mName = "CA5Hair1DJ";
    modelDynaDesc.mNum = 1;
    modelDynaDesc.mDescs = &dynaDesc;
    desc._70[3] = reinterpret_cast<u32>(&modelDynaDesc);
}

}

namespace ModelDesc {

chara::ModelDesc& CreateNormal() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<3, 0>("step/chara/enemy/Blade", "Bladeknight", 3, T_NODE_NAMES, 13,
                                                             T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
    t_dynamics(desc);
    return desc;
}

chara::ModelDesc& CreateSuper() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<3, 1>("step/chara/enemy/Blade", "Bladeknight", 3, T_NODE_NAMES, 13,
                                                             T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
    desc._4 = "step/chara/enemy/SpBlade";
    t_dynamics(desc);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::bladeknight
