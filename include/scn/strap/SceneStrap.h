#ifndef SCN_STRAP_SCENESTRAP_H
#define SCN_STRAP_SCENESTRAP_H

#include "gfx/FullScreenPlate.h"
#include "lyt/Layout.h"
#include "scn/IScene.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace strap {

class SceneStrap : public IScene {
public:
    SceneStrap();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneStrap();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    bool isButtonReceived() const;

    gfx::FullScreenPlate _4;
    lyt::Layout _C;
    lyt::Layout _19C;
    gfx::FullScreenPlate _32C;
    int _334;
    util::FrameCounter _338;
    bool _340;
};

}}  // namespace scn::strap

#endif
