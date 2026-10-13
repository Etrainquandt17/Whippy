#ifndef SEQ_SEQUENCECALLSCENE_H
#define SEQ_SEQUENCECALLSCENE_H

#include "hel/common/RuntimeTypeInfo.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

template <class Scene>
class SequenceCallScene : public ISequence {
public:
    SequenceCallScene() : mNextAction(2), mResult(false) {}

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

    bool result() const { return mResult; }

private:
    int mNextAction;
    bool mResult;
};

template <class Scene>
const hel::common::RuntimeTypeInfo& SequenceCallScene<Scene>::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceCallScene<Scene> >();
}

template <class Scene>
int SequenceCallScene<Scene>::nextAction() const {
    return mNextAction;
}

template <class Scene>
std::auto_ptr<ISequence> SequenceCallScene<Scene>::createChildSequence() const {
    return std::auto_ptr<ISequence>();
}

template <class Scene>
void SequenceCallScene<Scene>::onChildSequenceEnd(ISequence&) {
}

template <class Scene>
std::auto_ptr<scn::IScene> SequenceCallScene<Scene>::createScene() const {
    return std::auto_ptr<scn::IScene>(new Scene());
}

template <class Scene>
void SequenceCallScene<Scene>::onSceneEnd(scn::IScene& scene) {
    mNextAction = 0;
    mResult = static_cast<Scene&>(scene).result();
}

}

#endif
