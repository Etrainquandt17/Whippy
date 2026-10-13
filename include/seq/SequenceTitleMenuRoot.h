#ifndef SEQ_SEQUENCETITLEMENUROOT_H
#define SEQ_SEQUENCETITLEMENUROOT_H

#include "scn/titlemenunew/SceneTitleMenu.h"
#include "seq/EntryInfo.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceTitleMenuRoot : public ISequence {
public:
    // Named after the sequence createChildSequence makes for each.
    enum Child {
        CHILD_OPENING_0,
        CHILD_OPENING_1,
        CHILD_SUBGAME_0,
        CHILD_SUBGAME_1,
        CHILD_ARENA_0,
        CHILD_ARENA_1,
        CHILD_SOUND_ROOM,
        CHILD_THEATER_ROOM,
        CHILD_OPTION,
    };

    SequenceTitleMenuRoot();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceTitleMenuRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    int _4;
    bool _8;
    scn::titlemenunew::SceneTitleMenu::Recipe mRecipe;
    int _28;
};

}  // namespace seq

#endif
