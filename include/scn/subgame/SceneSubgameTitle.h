#ifndef SCN_SUBGAME_SCENESUBGAMETITLE_H
#define SCN_SUBGAME_SCENESUBGAMETITLE_H

#include "hel/common/NonCopyable.h"
#include "hel/common/ScopedPtr.h"
#include "scn/IScene.h"
#include "scn/subgame/Context.h"
#include "scn/subgame/IResultHolder.h"
#include "scn/subgame/Result.h"
#include "scn/subgame/common/util/DpdManager.h"
#include "scn/subgame/title/Main.h"
#include "types.h"

// TODO: hel/common/ScopedPtr.h does not derive from NonCopyable and defines no destructor, which this
// unit holds a copy of. Until it does, it is specialized here.
namespace hel {
namespace common {

template <>
class ScopedPtr<scn::subgame::title::Main> : private NonCopyable {
public:
    explicit ScopedPtr(scn::subgame::title::Main* ptr = 0);
    ~ScopedPtr();

    scn::subgame::title::Main* operator->() const;

    void swap(ScopedPtr& other) {
        scn::subgame::title::Main* ptr = other.mPtr;
        other.mPtr = mPtr;
        mPtr = ptr;
    }
    void reset(scn::subgame::title::Main* ptr = 0) { ScopedPtr(ptr).swap(*this); }

private:
    scn::subgame::title::Main* mPtr;
};

}
}

namespace scn {
namespace subgame {

class SceneSubgameTitle : public IScene, public IResultHolder {
public:
    class Recipe {
    public:
        static Recipe Create(const Context& context, Result::Seq seq);

        Context mContext;
        Result::Seq mSeq;
    };

    SceneSubgameTitle(const Recipe& recipe);

    virtual ~SceneSubgameTitle();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;
    virtual Result result() const;

private:
    Context mContext;
    common::util::DpdManager mDpdManager;
    hel::common::ScopedPtr<title::Main> mMain;
};

}
}

#endif
