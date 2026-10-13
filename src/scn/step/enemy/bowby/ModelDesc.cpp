#include "scn/step/enemy/bowby/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "FaceJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack", 0 },
    { "AttackStart", 0 },
    { "AttackWait", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { "Bowby.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<46, 0>("step/chara/enemy/Bowby", "Bowby", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& HalcandleCreate() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<95, 0>("step/chara/enemy/HalcanBowby", "HalcanBowby", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc.mModel._44[0] = 0x1800;
    return desc;
}

}

}}}}  // namespace scn::step::enemy::bowby
