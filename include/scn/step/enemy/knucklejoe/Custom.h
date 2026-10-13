#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_CUSTOM_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

class Custom;

}}}}  // namespace scn::step::enemy::knucklejoe

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::knucklejoe::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();

    f32 getSpeed() const;
    f32 getAnimRate() const;
    u32 getNowLoop() const;
    void resetNowLoop();
    void incNowLoop();
    int getAttack() const;
    void setAttack();
    void shot();
    void setHitWall(bool isHit);
    bool getHitWall();

private:
    int mAttack;
    u32 mAttackCount;
    f32 mSpeed;
    f32 mAnimRate;
    u32 mNowLoop;
    bool mHitWall;
};

}}}}  // namespace scn::step::enemy::knucklejoe

#endif
