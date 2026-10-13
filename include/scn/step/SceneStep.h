#ifndef SCN_STEP_SCENESTEP_H
#define SCN_STEP_SCENESTEP_H

#include "scn/IScene.h"
#include "scn/step/Context.h"
#include "types.h"

namespace scn {
namespace step {

class SceneStep : public IScene {
public:
    class Recipe {
    public:
        static Recipe Create(const Context& context);

    private:
        u32 _0[0x1F7];
    };

    struct Result {
        int _0;
        Context mContext;
        int _7E0;
    };

    SceneStep(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneStep();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4;
};

}}  // namespace scn::step

#endif
