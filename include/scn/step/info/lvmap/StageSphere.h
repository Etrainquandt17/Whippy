#ifndef SCN_STEP_INFO_LVMAP_STAGESPHERE_H
#define SCN_STEP_INFO_LVMAP_STAGESPHERE_H

#include "hel/math/Vector3.h"
#include "lyt/Layout.h"
#include "scn/step/info/SphereBase.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {

class Component;

namespace info {
namespace lvmap {

class StageSphere {
public:
    StageSphere(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Component& component);

    void updateFrame();
    void bgStartAnim(const hel::math::Vector3& pos, StageKind stage, bool isStart);
    void appear(const hel::math::Vector3& pos, StageKind stage);
    void wait(const hel::math::Vector3& pos, StageKind stage);
    void disappear();
    void getDemo(const hel::math::Vector3& pos, StageKind stage);
    bool isDemoEnd() const;
    void constraintPos();
    void stateAppear();
    void stateSphereGetWait();
    void stateSphereGet();
    void normalPanelVisible(bool visible);
    void bossPanelVisible(bool visible);
    void adjustBgSize();
    void centerBase();
    u32 getNextFlashSphere(u32) const;

private:
    Component& mComponent;
    int _4;
    u32 _8;
    util::FrameCounter _C;
    u32 _14;
    bool _18;
    snd::SERequestor _1C;
    lyt::Layout _90;
    SphereBase _220;
    lyt::Layout _3D8;
    SphereBase _568;
    hel::math::Vector3 _720;
};

}}}}  // namespace scn::step::info::lvmap

#endif
