#ifndef SCN_OPTION_SCENEOPTION_H
#define SCN_OPTION_SCENEOPTION_H

#include "scn/IScene.h"
#include "types.h"

namespace scn {
namespace option {

class SceneOption : public IScene {
public:
    SceneOption();

    bool result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneOption();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4[0xA1B];
};

}
}

#endif
