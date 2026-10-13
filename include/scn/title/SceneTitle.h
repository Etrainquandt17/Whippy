#ifndef SCN_TITLE_SCENETITLE_H
#define SCN_TITLE_SCENETITLE_H

#include "hel/common/NonCopyable.h"
#include "hel/common/ScopedPtr.h"
#include "scn/IScene.h"
#include "scn/title/Main.h"
#include "types.h"

namespace scn {
namespace title {

class SceneTitle : public IScene {
public:
    class Recipe {
    public:
        bool _0;
    };

    SceneTitle(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneTitle();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

    int result() const;

private:
    int mState;
    hel::common::ScopedPtr<Main> mMain;
};

}}  // namespace scn::title

#endif
