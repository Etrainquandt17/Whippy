#define DYNAMICS_DESC_MEMBERS

#include "scn/step/enemy/poppybrojr/ModelDesc.h"

#include "dynamics/Desc.h"
#include "hel/common/Array.h"
#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

using hel::common::Array;

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BomM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait2", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
};

// TODO: the name is a guess; chara::ModelDesc holds a pointer to it at 0x7C.
struct ModelDynamicsDesc {
    u32 mNum;
    Array<dynamics::Desc, 1>* mDescs;
};

void t_dynamics(chara::ModelDesc& desc) {
    static Array<dynamics::Desc, 1> dynaDesc;
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
    dynaDesc[0].mNodeNum = 3;
    dynaDesc[0].mName = "CA6Hat1DJ";
    modelDynaDesc.mNum = 1;
    modelDynaDesc.mDescs = &dynaDesc;
    desc._70[3] = reinterpret_cast<u32>(&modelDynaDesc);
}

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<30, 0>("step/chara/enemy/PoppyJr", "Poppybrojr", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    t_dynamics(desc);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::poppybrojr
