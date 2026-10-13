#include "scn/step/enemy/sun/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sun {

namespace {

const char* T_NODE_NAMES_SUN[] = {
    "TopL",
    "EffectL",
    "RotateL",
};

const char* T_NODE_NAMES_METEO[] = {
    "TopL",
    "ControlL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES_SUN[] = {
    { "Wait", 0 },
    { "Wait", 0 },
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES_METEO[] = {
    { "Main", 0 },
    { "MainGigant", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<96, 0>("step/chara/enemy/Sun", "Sun", 3, T_NODE_NAMES_SUN, 2, T_ANIM_ENTRIES_SUN, 8, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateMeteo() {
    return ModelDescUtil::CreateTmpl<98, 0>("step/chara/enemy/Meteo", "Meteo", 3, T_NODE_NAMES_METEO, 2, T_ANIM_ENTRIES_METEO, 8, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::sun
