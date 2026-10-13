#ifndef SCN_STEP_ENEMY_PLUID_CUSTOM_H
#define SCN_STEP_ENEMY_PLUID_CUSTOM_H

#include "hel/math/Matrix34.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

class Custom;

}}}}  // namespace scn::step::enemy::pluid

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::pluid::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual void onCaptured();
    virtual void onProcFixPos();

    void setRotate(f32 rotate);
    int setJumpNum();
    hel::math::Matrix34 rotateForce(f32 rotate);
    f32 normalizeAngle(f32 angle) const;
    void onRandomFall();
    bool isRandomFall() const;

private:
    f32 mRotate;
    f32 mRotateTarget;
    int mJumpNum[3];
    bool mIsRandomFall;
};

}}}}  // namespace scn::step::enemy::pluid

#endif
