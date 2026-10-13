#ifndef SCN_STEP_ARENA_MANAGER_H
#define SCN_STEP_ARENA_MANAGER_H

#include "scn/arena/ArenaData.h"
#include "types.h"

namespace scn {
namespace step {
namespace arena {

// TODO: the other members; belongs in a header of its own.
class EntryManager {
public:
    class EntryId {
    public:
        EntryId();

        // TODO: the name is a guess; only seen inlined.
        bool isValid() const { return mId != 0; }

    private:
        u32 mId;
    };
};

// TODO: members and the other functions.
class Manager {
public:
    void timeStopEntry(EntryManager::EntryId& id);
    void timeStopRelease(EntryManager::EntryId& id);
    void timeHide();
    bool isArena() const;
    void setBoxState(scn::arena::ArenaData::BoxState state);
};

}
}
}

#endif
