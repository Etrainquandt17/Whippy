#ifndef SEQ_SEQUENCESIMPLESCENE_H
#define SEQ_SEQUENCESIMPLESCENE_H

#include "hel/common/RuntimeTypeInfo.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

template <class Scene>
class SequenceSimpleScene : public ISequence {
public:
    SequenceSimpleScene() : mNextAction(2) {}

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

private:
    int mNextAction;
};

template <class Scene>
const hel::common::RuntimeTypeInfo& SequenceSimpleScene<Scene>::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceSimpleScene<Scene> >();
}

template <class Scene>
int SequenceSimpleScene<Scene>::nextAction() const {
    return mNextAction;
}

template <class Scene>
std::auto_ptr<ISequence> SequenceSimpleScene<Scene>::createChildSequence() const {
    return std::auto_ptr<ISequence>();
}

template <class Scene>
void SequenceSimpleScene<Scene>::onChildSequenceEnd(ISequence&) {
}

template <class Scene>
std::auto_ptr<scn::IScene> SequenceSimpleScene<Scene>::createScene() const {
    return std::auto_ptr<scn::IScene>(new Scene());
}

template <class Scene>
void SequenceSimpleScene<Scene>::onSceneEnd(scn::IScene&) {
    mNextAction = 0;
}

}  // namespace seq

#endif
