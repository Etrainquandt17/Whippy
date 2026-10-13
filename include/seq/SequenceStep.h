#ifndef SEQ_SEQUENCESTEP_H
#define SEQ_SEQUENCESTEP_H

#include "file/FileClearDisableScope.h"
#include "scn/step/Context.h"
#include "scn/step/SceneStep.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceStep : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(const scn::step::Context& context);

        scn::step::Context mContext;
    };

    SequenceStep(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceStep();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

    scn::step::SceneStep::Result result() const;

private:
    file::FileClearDisableScope mFileClearDisableScope;
    scn::step::Context mContext;
    scn::step::SceneStep::Result mResult;
    bool _FC8;
};

}  // namespace seq

#endif
