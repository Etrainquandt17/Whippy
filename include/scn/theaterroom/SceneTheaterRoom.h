#ifndef SCN_THEATERROOM_SCENETHEATERROOM_H
#define SCN_THEATERROOM_SCENETHEATERROOM_H

#include "scn/IScene.h"
#include "types.h"

namespace scn {
namespace theaterroom {

class SceneTheaterRoom : public IScene {
public:
    struct Result {
        bool _0;
        int _4;
        int _8;
    };

    struct Recipe {
        int _0;
    };

    SceneTheaterRoom(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneTheaterRoom();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4[0xBAF];
};

}
}

#endif
