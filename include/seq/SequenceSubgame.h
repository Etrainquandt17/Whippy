#ifndef SEQ_SEQUENCESUBGAME_H
#define SEQ_SEQUENCESUBGAME_H

#include "scn/subgame/Context.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceSubgame : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(const scn::subgame::Context& context);

    private:
        scn::subgame::Context mContext;
    };

    SequenceSubgame(const Recipe& recipe);

    scn::subgame::Context result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceSubgame();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    u32 _4[0x14];
};

}

#endif
