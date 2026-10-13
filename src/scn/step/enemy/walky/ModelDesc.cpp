#include "scn/step/enemy/walky/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA2HeadJ",
    "CA3MouthDwnJ",
    "CB3MouthUpJ",
    "MouthE",
    "PtclL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Jamp", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { "Walky.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<64, 0>("step/chara/enemy/Walky", "Walky", 6, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::enemy::walky
