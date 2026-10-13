#include "scn/step/enemy/grandlowperbullet/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ShotM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<116, 0>("step/weapon/grantlowper/Shot", "GrandLowperBullet", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<116, 0>("step/weapon/grantlowperex/Shot", "GrandLowperBullet", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::grandlowperbullet
