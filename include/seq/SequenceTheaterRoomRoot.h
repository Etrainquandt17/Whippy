#ifndef SEQ_SEQUENCETHEATERROOMROOT_H
#define SEQ_SEQUENCETHEATERROOMROOT_H

#include "scn/theaterroom/SceneTheaterRoom.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceTheaterRoomRoot : public ISequence {
public:
    SequenceTheaterRoomRoot();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceTheaterRoomRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    int _4;
    bool _8;
    scn::theaterroom::SceneTheaterRoom::Recipe mRecipe;
    scn::theaterroom::SceneTheaterRoom::Result mResult;
};

}

#endif
