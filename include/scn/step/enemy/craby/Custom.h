#ifndef SCN_STEP_ENEMY_CRABY_CUSTOM_H
#define SCN_STEP_ENEMY_CRABY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

class Custom;

}}}}  // namespace scn::step::enemy::craby

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::craby::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace craby {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual bool onOutWater();

    bool isPlayerInAimArea();
    void reset();
    void setAttackValid(bool isValid);
    void setBasePosX(f32 x);
    f32 getBasePosX();

private:
    util::FrameCounter mCounter;
    bool mIsAimValid;
    bool mIsAttackValid;
    f32 mBasePosX;
};

}}}}  // namespace scn::step::enemy::craby

#endif
