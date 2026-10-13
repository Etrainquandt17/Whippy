#ifndef SCN_STAFFCREDIT_SCENESTAFFCREDIT_H
#define SCN_STAFFCREDIT_SCENESTAFFCREDIT_H

#include "scn/IScene.h"
#include "types.h"

namespace scn {
namespace staffcredit {

class SceneStaffCredit : public IScene {
public:
    struct Recipe {
        int _0;
        bool _4;
    };

    SceneStaffCredit(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneStaffCredit();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4[0x95E];
};

}
}

#endif
