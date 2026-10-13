#ifndef SCN_STEP_ITEM_MODELDESCUTIL_H
#define SCN_STEP_ITEM_MODELDESCUTIL_H

#include "gobj/AnimDesc.h"
#include "gobj/ScriptDesc.h"
#include "hel/common/FixedString.h"
#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

namespace ModelDescUtil {

extern const gobj::ScriptDesc::Entry* SCRIPT_ENTRIES;

void Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path, const char* name,
         const char* topNodeName, u32 animEntryCount, const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount,
         const gobj::ScriptDesc::Entry* scriptEntries);

// One set of descriptions per pair of template arguments: the item's kind and a number per model.
template <int Kind, int Variation>
inline chara::ModelDesc& CreateTmpl(const char* path, const char* name, const char* topNodeName, u32 animEntryCount,
                                    const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount,
                                    const gobj::ScriptDesc::Entry* scriptEntries) {
    static chara::ModelDesc desc;
    static gobj::AnimDesc animDesc;
    static gobj::ScriptDesc scriptDesc;
    Set(desc, animDesc, scriptDesc, path, name, topNodeName, animEntryCount, animEntries, scriptEntryCount, scriptEntries);
    return desc;
}

template <int Kind, int Variation>
inline chara::ModelDesc& CreateGeneral(const char* name, const char* path, const char* topNodeName) {
    chara::ModelDesc& desc = CreateTmpl<Kind, Variation>(path, name, "Model", 0, 0, 2, SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>(topNodeName);
    return desc;
}

}

}}}  // namespace scn::step::item

#endif
