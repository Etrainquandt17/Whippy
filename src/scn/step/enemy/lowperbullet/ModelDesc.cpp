#include "scn/step/enemy/lowperbullet/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
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

chara::ModelDesc& CreateLv1() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<102, 0>("step/weapon/lowper/LowperShot", "LowperBullet", 1, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& CreateLv2() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<103, 0>("step/weapon/lowperlv2/LowperShotLv2", "LowperBullet", 1, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc._8 = "step/weapon/lowper/LowperShot";
    return desc;
}

chara::ModelDesc& CreateLv3() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<104, 0>("step/weapon/lowperlv2a/LowperShotLv2A", "LowperBullet", 1, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc._8 = "step/weapon/lowper/LowperShot";
    return desc;
}

chara::ModelDesc& CreateLv4() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<105, 0>("step/weapon/lowperlv3/LowperShotLv3", "LowperBullet", 1, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc._8 = "step/weapon/lowper/LowperShot";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::lowperbullet
