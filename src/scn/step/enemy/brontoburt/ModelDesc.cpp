#include "scn/step/enemy/brontoburt/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "WaitLoop", 0 },
    { "Fly", 0 },
    { "WaitEnd", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "DamageEtc", 0 },
    { "DamageHard", 0 },
    { "FlyStart", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { "BrontoBurt.AnimScript.Fly.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "BrontoBurt.AnimScript.WhispyAppear.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<1, 0>("step/chara/enemy/Bront", "Brontoburt", 1, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& HalcandleCreate() {
    return ModelDescUtil::CreateTmpl<85, 0>("step/chara/enemy/HalcantBurt", "HalcantBurt", 1, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
