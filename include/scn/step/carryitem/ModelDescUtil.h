#ifndef SCN_STEP_CARRYITEM_MODELDESCUTIL_H
#define SCN_STEP_CARRYITEM_MODELDESCUTIL_H

#include "gobj/AnimDesc.h"
#include "gobj/ScriptDesc.h"
#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

namespace ModelDescUtil {

extern const char** NODE_NAMES;
extern const gobj::ScriptDesc::Entry* SCRIPT_ENTRIES;

void Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path, const char* name,
         u32 nodeNameCount, const char** nodeNames, u32 animEntryCount, const gobj::G3DAnimDataReposDesc::Entry* animEntries,
         u32 scriptEntryCount, const gobj::ScriptDesc::Entry* scriptEntries);

// TODO: gobj::ModelDesc has a bool at 0x4C, which its header keeps inside the words of _44.
inline void Set_4C(chara::ModelDesc& desc, bool value) {
    *reinterpret_cast<bool*>(&desc.mModel._44[2]) = value;
}

// One set of descriptions per pair of template arguments: the carry item's kind and its sub kind.
template <int Kind, int SubKind>
inline chara::ModelDesc& CreateTmpl(const char* path, const char* name, u32 nodeNameCount, const char** nodeNames,
                                    u32 animEntryCount, const gobj::G3DAnimDataReposDesc::Entry* animEntries,
                                    u32 scriptEntryCount, const gobj::ScriptDesc::Entry* scriptEntries) {
    static chara::ModelDesc desc;
    static gobj::AnimDesc animDesc;
    static gobj::ScriptDesc scriptDesc;
    Set(desc, animDesc, scriptDesc, path, name, nodeNameCount, nodeNames, animEntryCount, animEntries, scriptEntryCount,
        scriptEntries);
    return desc;
}

// TODO: only seen expanded here; the name is that of item::ModelDescUtil's, which has the same arguments.
template <int Kind, int SubKind>
inline chara::ModelDesc& CreateGeneral(const char* name, const char* path, const char* topNodeName) {
    const gobj::ScriptDesc::Entry* scriptEntries = SCRIPT_ENTRIES;
    const char** nodeNames = NODE_NAMES;
    chara::ModelDesc& desc = CreateTmpl<Kind, SubKind>(path, name, 1, nodeNames, 0, 0, 2, scriptEntries);
    desc.mModel._18 = hel::common::FixedString<40>(topNodeName);
    return desc;
}

}

}}}  // namespace scn::step::carryitem

#endif
