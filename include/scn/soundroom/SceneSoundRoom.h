#ifndef SCN_SOUNDROOM_SCENESOUNDROOM_H
#define SCN_SOUNDROOM_SCENESOUNDROOM_H

#include "scn/IScene.h"
#include "types.h"

namespace scn {
namespace soundroom {

class SceneSoundRoom : public IScene {
public:
    SceneSoundRoom();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneSoundRoom();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4[0x121D];
};

}}  // namespace scn::soundroom

#endif
