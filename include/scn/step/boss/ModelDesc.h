#ifndef SCN_STEP_BOSS_MODELDESC_H
#define SCN_STEP_BOSS_MODELDESC_H

#include "gobj/AnimDesc.h"
#include "gobj/ScriptDesc.h"
#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace ModelDesc {

void Set(chara::ModelDesc& desc, gobj::AnimDesc& animDesc, gobj::ScriptDesc& scriptDesc, const char* modelPath, const char* motionPath,
         const char* name, u32 nodeNameCount, const char** nodeNames, u32 animEntryCount,
         const gobj::G3DAnimDataReposDesc::Entry* animEntries, u32 scriptEntryCount, const gobj::ScriptDesc::Entry* scriptEntries);

// One set of descriptions per triple of template arguments: the boss's number, an index and the variation.
template <int Kind, int Index, int Variation>
inline chara::ModelDesc& CreateTmpl(const char* modelPath, const char* motionPath, const char* name, u32 nodeNameCount,
                                    const char** nodeNames, u32 animEntryCount, const gobj::G3DAnimDataReposDesc::Entry* animEntries,
                                    u32 scriptEntryCount, const gobj::ScriptDesc::Entry* scriptEntries) {
    static chara::ModelDesc desc;
    static gobj::AnimDesc animDesc;
    static gobj::ScriptDesc scriptDesc;
    Set(desc, animDesc, scriptDesc, modelPath, motionPath, name, nodeNameCount, nodeNames, animEntryCount, animEntries, scriptEntryCount,
        scriptEntries);
    return desc;
}

}
}
}
}

#endif
