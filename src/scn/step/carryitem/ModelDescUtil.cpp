#include "scn/step/carryitem/ModelDescUtil.h"

#include "hel/common/FixedString.h"

namespace scn {
namespace step {
namespace carryitem {

namespace {

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

const char** ModelDescUtil::NODE_NAMES = T_NODE_NAMES;
const gobj::ScriptDesc::Entry* ModelDescUtil::SCRIPT_ENTRIES = T_SCRIPT_ENTRIES;

// TODO: the casts stand for members that chara::ModelDesc, gobj::ModelDesc and gobj::ScriptDesc keep as words:
// the path at 0, the name (a FixedString<24>) at 0x18, two bools at 0x64 and 0x65, the node names at 0x68 and
// 0x6C, the animation and script descriptions at 0x70 and 0x74.
void ModelDescUtil::Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path,
                        const char* name, u32 nodeNameCount, const char** nodeNames, u32 animEntryCount,
                        const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount,
                        const gobj::ScriptDesc::Entry* scriptEntries) {
    desc._0 = reinterpret_cast<u32>(path);
    *reinterpret_cast<hel::common::FixedString<24>*>(&desc.mModel._0[0]) = hel::common::FixedString<24>(name);
    reinterpret_cast<bool*>(&desc.mModel._44[2])[0] = false;
    desc.mModel._44[0] = 0x100;
    reinterpret_cast<bool*>(&desc.mModel._44[2])[1] = true;
    desc.mModel._44[3] = nodeNameCount;
    desc.mModel._44[4] = reinterpret_cast<u32>(nodeNames);
    animDesc._0 = 1;
    animDesc._4 = animEntryCount;
    animDesc._8 = animEntries;
    desc._70[0] = reinterpret_cast<u32>(&animDesc);
    scriptDesc._0[0] = reinterpret_cast<u32>("Scn.Step.CarryItem");
    scriptDesc._0[1] = scriptEntryCount;
    scriptDesc._0[2] = reinterpret_cast<u32>(scriptEntries);
    desc._70[1] = reinterpret_cast<u32>(&scriptDesc);
    desc._c = hel::math::Vector3(0.0f, 0.5f, 0.0f);
}

}}}  // namespace scn::step::carryitem
