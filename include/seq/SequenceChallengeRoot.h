#ifndef SEQ_SEQUENCECHALLENGEROOT_H
#define SEQ_SEQUENCECHALLENGEROOT_H

#include "file/FileClearDisableScope.h"
#include "scn/step/ChallengeKind.h"
#include "scn/step/ContextChallenge.h"
#include "scn/step/ContextMode.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceChallengeRoot : public ISequence {
public:
    class Recipe {
    public:
        static Recipe Create(scn::step::ChallengeKind kind, scn::step::ContextMode mode);

        scn::step::ChallengeKind mKind;
        u32 _4[0x120];
        scn::step::ContextMode mMode;
        u32 _498;
    };

    SequenceChallengeRoot(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceChallengeRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

    scn::step::ContextChallenge result() const;
    void onChildSequenceEndForStep(ISequence& child);
    void branchHint(bool flag);
    void keepHighScore();

private:
    scn::step::ContextChallenge mResult;
    scn::step::ContextMode mContextMode;
    scn::step::ContextChallenge mContextChallenge;
    int _130;
    file::FileClearDisableScope mFileClearDisableScope;
};

}  // namespace seq

#endif
