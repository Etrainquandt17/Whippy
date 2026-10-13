#ifndef SCN_STEP_ENEMY_GLUNK_CUSTOM_H
#define SCN_STEP_ENEMY_GLUNK_CUSTOM_H

#include "hel/math/Matrix34.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

class Custom;

}}}}  // namespace scn::step::enemy::glunk

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::glunk::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual bool onOutWater();
    virtual void onCaptured();
    virtual void onProcFixPos();

    f32 rotate() const;
    void setRotate(f32 rotate);
    bool isCurrentFall() const;
    void setIsCurrentFall(bool isCurrentFall);
    bool checkExistLand();
    hel::math::Matrix34 rotateForce(f32 rotate);
    f32 normalizeAngle(f32 angle) const;

private:
    f32 mRotate;
    f32 mRotateTarget;
    f32 mLandAngle;
    f32 mCapturedRotate;
    bool mIsNoLand;
    bool mIsCurrentFall;
    bool mIsDamaged;
};

}}}}  // namespace scn::step::enemy::glunk

#endif
