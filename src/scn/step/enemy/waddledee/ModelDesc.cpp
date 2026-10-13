#include "scn/step/enemy/waddledee/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL", "CA4FaceJ", "RA3HandJ", "RA1ShoulderJ", "RHaveL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },         { "Fall", 0 },       { "Landing", 0 },            { "Walk", 0 },        { "Damage", 0 },
    { "DamageEtc", 0 },    { "DamageEnd", 0 },  { "SleepFall", 0 },          { "Cheer1", 0 },      { "Cheer2", 0 },
    { "ParasolDee", 0 },   { "ParasolDeeLanding", 0 }, { "ParasolDeeOut", 0 }, { "HaveParasol", 0 }, { "JumpStart", 0 },
    { "Jump", 0 },         { "ConnectionHavePose", 0 }, { "SwingFront", 0 }, { "SwingBack", 0 },   { "TurnFront", 0 },
    { "TurnBack", 0 },     { "RideWait", 0 },   { "LRide2", 0 },             { "RRide2", 0 },      { "Pursuit", 0 },
    { "Wait2", 0 },        { "Wait3", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 10, 36, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 12, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 13, 4, 0, 0 },
    { "WaddleDee.AnimScript.WhispyAppear.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.WhispyFall.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.WhispyLanding.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.GrandLowperAppear.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.GrandLowperLanding.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "WaddleDee.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 16, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 17, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 18, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 19, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 20, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 21, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 22, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 23, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 24, 4, 0, 0 },
    { "WaddleDee.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 25, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 26, 8, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc =
        ModelDescUtil::CreateTmpl<2, 0>("step/chara/enemy/Dee", "Waddledee", 5, T_NODE_NAMES, 27, T_ANIM_ENTRIES, 33, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

chara::ModelDesc& HalcandledeeCreate() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<72, 0>("step/chara/enemy/Halcandledee", "Halcandledee", 5, T_NODE_NAMES, 27,
                                                              T_ANIM_ENTRIES, 33, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}
}
}
}
