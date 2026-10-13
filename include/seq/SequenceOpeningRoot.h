#ifndef SEQ_SEQUENCEOPENINGROOT_H
#define SEQ_SEQUENCEOPENINGROOT_H

#include "seq/EntryInfo.h"
#include "seq/ISequence.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace seq {

class SequenceOpeningRoot : public ISequence {
public:
    struct Result {
        int _0;
        EntryInfo mEntryInfo;
    };

    SequenceOpeningRoot(storage::StoryMode mode, const EntryInfo& entryInfo);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceOpeningRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    u32 _4[0x8];
};

}  // namespace seq

#endif
