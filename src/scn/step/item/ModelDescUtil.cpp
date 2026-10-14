#include "scn/step/item/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace item {

namespace {

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

}

const gobj::ScriptDesc::Entry* ModelDescUtil::SCRIPT_ENTRIES = T_SCRIPT_ENTRIES;

// TODO: the casts stand for members that chara::ModelDesc, gobj::ModelDesc and gobj::ScriptDesc keep as words:
// the path at 0, the name (a FixedString<24>) at 0x18, two bools at 0x64 and 0x65, the node names at 0x68 and
// 0x6C, the animation and script descriptions at 0x70 and 0x74.
void ModelDescUtil::Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path,
                        const char* name, const char* topNodeName, u32 animEntryCount,
                        const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount,
                        const gobj::ScriptDesc::Entry* scriptEntries) {
    static const char* NODE_NAMES[] = { "TopL" };
    desc._0 = reinterpret_cast<u32>(path);
    *reinterpret_cast<FixedString<24>*>(&desc.mModel._0[0]) = FixedString<24>(name);
    desc.mModel._18 = FixedString<40>(topNodeName);
    reinterpret_cast<bool*>(&desc.mModel._44[2])[0] = false;
    desc.mModel._44[0] = 0x100;
    reinterpret_cast<bool*>(&desc.mModel._44[2])[1] = false;
    desc.mModel._44[3] = 1;
    desc.mModel._44[4] = reinterpret_cast<u32>(NODE_NAMES);
    animDesc._0 = 1;
    animDesc._4 = animEntryCount;
    animDesc._8 = animEntries;
    desc._70[0] = reinterpret_cast<u32>(&animDesc);
    scriptDesc._0[0] = reinterpret_cast<u32>("Scn.Step.Item");
    scriptDesc._0[1] = scriptEntryCount;
    scriptDesc._0[2] = reinterpret_cast<u32>(scriptEntries);
    desc._70[1] = reinterpret_cast<u32>(&scriptDesc);
}

}}}  // namespace scn::step::item
