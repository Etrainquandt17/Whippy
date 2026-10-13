#ifndef SEQ_SEQUENCELVMAPROOT_H
#define SEQ_SEQUENCELVMAPROOT_H

#include "scn/step/LevelKind.h"
#include "seq/ContextStory.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class ContextStory;

class SequenceLvMapRoot : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(scn::step::LevelKind level, const ContextStory& context);

    private:
        u32 _0[0x126];
    };

    struct Result {
        ContextStory mContext;
        int _480;
    };

    SequenceLvMapRoot(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceLvMapRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    u8 _4[0x944];
};

}  // namespace seq

#endif
