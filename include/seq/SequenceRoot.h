#ifndef SEQ_SEQUENCEROOT_H
#define SEQ_SEQUENCEROOT_H

#include "seq/ISequence.h"

namespace seq {

class SequenceRoot : public ISequence {
public:
    SequenceRoot();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);
};

}

#endif
