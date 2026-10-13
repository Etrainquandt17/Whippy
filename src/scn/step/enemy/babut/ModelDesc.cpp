#include "scn/step/enemy/babut/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "WaitCeil", 0 },
    { "MoveStart", 0 },
    { "Move", 0 },
    { "AttackWait", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 2, 0, 0 },
    { "Babut.AnimScript.Move.Exec", 0, 0, 0, 0 },
    { "Babut.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { "Babut.AnimScript.Wait.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<35, 0>("step/chara/enemy/Babut", "Babut", 2, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::babut
