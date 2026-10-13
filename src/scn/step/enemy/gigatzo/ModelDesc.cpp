#include "scn/step/enemy/gigatzo/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

namespace {

const char* T_NODE_NAMES_GIGA[] = {
    "TopL",
    "BodyJ",
    "TopJ",
    "TransL",
    "BodyJ",
    "BodyJ",
    "BodyJ",
    "BaseM01",
    "BaseM02",
};

const char* T_NODE_NAMES_VOLT[] = {
    "TopL",
    "BodyJ",
    "TopJ",
    "TransL",
    "Effect1L",
    "Body2J",
    "Body3J",
    "BaseM01",
    "BaseM02",
};

const char* T_NODE_NAMES_COLD[] = {
    "TopL",
    "BodyJ",
    "TopJ",
    "TransL",
    "BodyJ",
    "BodyJ",
    "Body3J",
    "BaseM",
    "BaseM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<34, 0>("step/chara/enemy/Gigatzo", "Gigatzo", 9, T_NODE_NAMES_GIGA, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateVolt() {
    return ModelDescUtil::CreateTmpl<57, 0>("step/chara/enemy/Volttzo", "Volttzo", 9, T_NODE_NAMES_VOLT, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateCold() {
    return ModelDescUtil::CreateTmpl<73, 0>("step/chara/enemy/Coldtzo", "Coldtzo", 9, T_NODE_NAMES_COLD, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
