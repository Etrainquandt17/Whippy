#ifndef SCN_STEP_WEAPON_MODELDESCUTIL_H
#define SCN_STEP_WEAPON_MODELDESCUTIL_H

#include "gobj/AnimDesc.h"
#include "gobj/ScriptDesc.h"
#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ModelDescUtil {

void Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* path, const char* name,
         u32 nodeNameCount, const char** nodeNames, u32 animEntryCount, const gobj::G3DAnimDataReposDesc::Entry* animEntries,
         u32 scriptEntryCount, const gobj::ScriptDesc::Entry* scriptEntries);

// One set of descriptions per template argument, the weapon's kind.
template <int Kind>
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

}
}
}
}

#endif
