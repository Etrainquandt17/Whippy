#include "scn/step/enemy/bouncy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA2UpBodyJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "JumpStart", 0 },
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 6, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { "Bouncy.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "Bouncy.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<17, 0>("step/chara/enemy/Bouncy", "Bouncy", 2, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& HalcandleCreate() {
    return ModelDescUtil::CreateTmpl<94, 0>("step/chara/enemy/HalcanBouncy", "HalcanBouncy", 2, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::bouncy
