#include "scn/step/enemy/bulby/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA1HipJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Wait2Start", 0 },
    { "Wait2", 0 },
    { "Wait2End", 0 },
    { "Wait3", 0 },
    { "Fall", 0 },
    { "Lnding1", 0 },
    { "Lnding2", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Move", 0 },
    { "JumpStart", 0 },
    { "JumpLoop", 0 },
    { "Jump", 0 },
    { "Attack1", 0 },
    { "Attack2", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Bulby.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 4, 0, 0 },
    { "Bulby.AnimScript.BuriedWait.Exec", 0, 0, 0, 0 },
    { "Bulby.AnimScript.HalfBuriedWait.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 12, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 14, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 15, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<27, 0>("step/chara/enemy/Bulby", "Bulby", 2, T_NODE_NAMES, 16, T_ANIM_ENTRIES, 13, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
