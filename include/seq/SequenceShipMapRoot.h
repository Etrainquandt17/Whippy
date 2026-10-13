#ifndef SEQ_SEQUENCESHIPMAPROOT_H
#define SEQ_SEQUENCESHIPMAPROOT_H

#include "seq/ContextStory.h"
#include "seq/ISequence.h"
#include "types.h"

namespace scn {
namespace step {
class ContextMode;
}}  // namespace scn::step

namespace seq {

class SequenceShipMapRoot : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(const ContextStory& context, const scn::step::ContextMode& mode, bool flag1, bool flag2);

    private:
        u32 _0[0x126];
    };

    struct Result {
        ContextStory mContext;
        int _480;
    };

    SequenceShipMapRoot(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceShipMapRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

    Result result() const;

private:
    u8 _4[0xA00];
};

}  // namespace seq

#endif
