#ifndef SCN_STEP_CHARA_MODEL_H
#define SCN_STEP_CHARA_MODEL_H

#include "gobj/Model.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/ModelDesc.h"
#include "scn/step/core/DrawLayerKind.h"

namespace gobj {
class Anim;
class GearModel;
class IScriptCallback;
class MeshFlip;
class Script;
}

namespace hel {
namespace math {
class Matrix34;
}
}

namespace scn {
namespace step {
namespace chara {

class ModelRotCtrl;
class Shake;

// TODO: the members are unknown.
class Model {
public:
    void setScale(const hel::math::Vector3& scale);
    void setBaseScale(const hel::math::Vector3& scale);
    hel::math::Vector3 getTotalScale() const;
    void reqScript(u32 script);
    void setViewOffset(const hel::math::Vector3& offset);
    gobj::Model& model();
    void updateMtx();
    bool isAllEnd() const;
    void setFrameRate(f32 rate);
    void setVisibility(bool isVisible);
    void resetScale();
    void setDynamicsDisable();
    void setDynamicsEnable();
    void changeDynamics(const ModelDesc::DynamicsDesc& desc);
    void procFixPos();
    void registerScriptCallback(gobj::IScriptCallback& callback);
    void unregisterScriptCallback(gobj::IScriptCallback& callback);
    void onHitStopStart();
    void onHitStopEnd();
    void onObjStopStarted();
    void onObjStopFinished();
    ModelRotCtrl& rotCtrl();
    gobj::Anim& anim();
    gobj::Script& script();
    Shake& shake();
    bool isVisible() const;
    void resetViewOffset();
    void setCustomMtx(const hel::math::Matrix34& mtx);
    void unsetCustomMtx();
    u32 getCurrentScriptIndex() const;
    gobj::MeshFlip& meshFlip();
    void setDrawLayerForce(core::DrawLayerKind kind);
    void unsetDrawLayerForce();
};

}
}
}

#endif
