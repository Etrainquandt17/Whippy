#include "scn/step/enemy/fattybufferjr/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "FallOut", 0 },
    { "WaitJump", 0 },
    { "WaitFall", 0 },
    { "WaitLanding", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { "FattyBufferJr.AnimScript.AppearFall.Exec", 0, 0, 0, 0 },
    { "FattyBufferJr.AnimScript.Jump.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<126, 0>("step/chara/enemy/fattybufferjr/Model", "FattyBufferJr", 1, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/fattybufferjr/Motion";
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<126, 0>("step/chara/enemy/fattybufferjr/ModelEx", "FattyBufferJr", 1, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/fattybufferjr/Motion";
    return desc;
}

}

}
}
}
}
