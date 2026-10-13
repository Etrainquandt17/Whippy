#include "scn/step/enemy/waddledoo/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

namespace {

const char* T_NODE_NAMES_NORMAL[] = {
    "TopL", "CA4FaceJ", "BeamBaseJ", "Beam1J", "Beam2J", "Beam3J", "Beam4J", "RA3HandJ", "RA1ShoulderJ", "RHaveL", "CA4FaceJ",
};

const char* T_NODE_NAMES_SUPER[] = {
    "TopL", "CA4FaceJ", "BeamBaseJ", "Beam1J", "Beam2J", "Beam3J", "Beam4J", "RA3HandJ", "RA1ShoulderJ", "RHaveL", "KariL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Jump", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
    { "AttackStart", 0 },
    { "AttackReserve", 0 },
    { "ParasolDoo", 0 },
    { "ParasolDooLanding", 0 },
    { "ParasolDooOut", 0 },
    { "HaveParasol", 0 },
    { "ConnectionHavePose", 0 },
    { "SwingFront", 0 },
    { "SwingBack", 0 },
    { "TurnFront", 0 },
    { "TurnBack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 2, 0, 0 },
    { "WaddleDoo.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 12, 36, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 13, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 14, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 15, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 16, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 17, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 18, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 19, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 20, 2, 0, 0 },
    { "WaddleDoo.AnimScript.SuperAppear.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& CreateNormal() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<16, 0>("step/chara/enemy/Doo", "Waddledoo", 11, T_NODE_NAMES_NORMAL, 21,
                                                              T_ANIM_ENTRIES, 20, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

chara::ModelDesc& CreateSuper() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<16, 1>("step/chara/enemy/Doo", "Waddledoo", 11, T_NODE_NAMES_SUPER, 21,
                                                              T_ANIM_ENTRIES, 20, T_SCRIPT_ENTRIES);
    desc._4 = "step/chara/enemy/SpDoo";
    return desc;
}

}

}
}
}
}
