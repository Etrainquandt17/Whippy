#include "scn/step/enemy/scarfy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ScarfyBody1M",
    "ScarfyBody2M",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Change", 0 },
    { "Change2", 0 },
    { "ChangeWait", 0 },
    { "BeforeBurst", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
};

const u32 T_MESHFLIP_NODE_TABLE[] = { 1, 2 };

// TODO: the name is a guess; chara::ModelDesc holds a pointer to it at 0x78.
struct MeshFlipDesc {
    u32 _0;
    u32 mNodeNum;
    const u32* mNodes;
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    static MeshFlipDesc desc;
    chara::ModelDesc& result = ModelDescUtil::CreateTmpl<21, 0>("step/chara/enemy/Scarfy", "Scarfy", 3, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
    desc._0 = 0;
    desc.mNodeNum = 2;
    desc.mNodes = T_MESHFLIP_NODE_TABLE;
    result._70[2] = reinterpret_cast<u32>(&desc);
    return result;
}

chara::ModelDesc& CreateChaseKey() {
    static MeshFlipDesc desc;
    chara::ModelDesc& result = ModelDescUtil::CreateTmpl<89, 0>("step/chara/enemy/ChaseKeyScarfy", "ChaseKeyScarfy", 3, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
    desc._0 = 0;
    desc.mNodeNum = 2;
    desc.mNodes = T_MESHFLIP_NODE_TABLE;
    result._70[2] = reinterpret_cast<u32>(&desc);
    return result;
}

}

}}}}  // namespace scn::step::enemy::scarfy
