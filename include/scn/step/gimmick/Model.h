#ifndef SCN_STEP_GIMMICK_MODEL_H
#define SCN_STEP_GIMMICK_MODEL_H

#include "types.h"

namespace g3d {
class ModelAccessor;
class Root;
class StdModel;
}

namespace hel {
namespace math {
class Matrix34;
class Vector3;
}
}

namespace scn {
namespace step {

class Component;

namespace gimmick {

class Model {
public:
    Model(Component& component, const char*, const char*, bool, bool);
    // TODO: implicit in the original: the class is a Component&, a word and a g3d::StdModel, and
    // g3d/StdModel.h declares no destructor yet.
    ~Model();

    void registerToRoot(g3d::Root& root);
    g3d::ModelAccessor model();
    g3d::StdModel& stdModel();
    void setAnimByName(const char* name);
    void setTrans(const hel::math::Vector3& trans);
    void setMtx(const hel::math::Matrix34& mtx);
    void setScale(const hel::math::Vector3& scale);
    f32 frame() const;
    bool isAnimEnd() const;
    void setIsAutoUpdateWorldMtx(bool isAutoUpdate);
    void setFrame(f32 frame);
    void setFrameToTail();
    void setFrameRate(f32 rate);
    void setVisibility(bool visible);
    void start(bool);
    void stop();
    f32 totalFrame() const;
    void updateWorldMtx();
    void updateFrame();

private:
    u8 _0[0x1B4];
};

}
}
}

#endif
