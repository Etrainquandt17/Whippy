#ifndef SEQ_SEQUENCEARENAROOT_H
#define SEQ_SEQUENCEARENAROOT_H

#include "seq/EntryInfo.h"
#include "scn/arena/ArenaData.h"
#include "seq/ISequence.h"
#include "storage/ArenaGameKind.h"
#include "types.h"

namespace seq {

class SequenceArenaRoot : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(storage::ArenaGameKind kind, EntryInfo entryInfo);

    private:
        storage::ArenaGameKind mKind;
        EntryInfo mEntryInfo;
    };

    // TODO: 0x254 bytes with a player at 0xB0; most likely scn::arena::ArenaData itself.
    struct Result {
        u32 _0[0x2C];
        scn::arena::ArenaData::Player mPlayer;
        u32 _E4[0x5C];
    };

    SequenceArenaRoot(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceArenaRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    u32 _4[0x32A];
};

}

#endif
