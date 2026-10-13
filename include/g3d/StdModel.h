#ifndef G3D_STDMODEL_H
#define G3D_STDMODEL_H

#include "g3d/ModelAccessor.h"
#include "types.h"

namespace hel {
namespace math {
class Matrix34;
class Vector3;
}
}

namespace g3d {

class ModelAnimAccessor;
class ResFileAccessor;
class StdModelContext;
class Root;

class StdModel {
public:
    StdModel(const StdModelContext& context);
    ~StdModel();

    ModelAccessor model();
    void setModelRTMtx(const hel::math::Matrix34& mtx);
    hel::math::Matrix34 modelRTMtx() const;
    void registerToRoot(Root& root);
    void setAnim(const ResFileAccessor& resFile, const char* name);
    bool tryToSetAnim(const ResFileAccessor& resFile, const char* name);
    bool wasSetAnim() const;
    ModelAnimAccessor anim();
    void start(bool doLoop);
    int totalFrame() const;
    void setFrame(f32 frame);
    void setFrameRate(f32 rate);
    void updateFrame();
    void updateFrameNoReflectToAnim();
    void reflectFrameToAnim();
    bool isAnimEnd() const;
    void updateWorldMtx();
    void setModelScale(const hel::math::Vector3& scale);
    void setIsAutoUpdateWorldMtx(bool isAutoUpdate);
    void stop();
    f32 frame() const;
    void setFrameToTail();

private:
    u8 _0[0x1AC];
};

}

#endif
