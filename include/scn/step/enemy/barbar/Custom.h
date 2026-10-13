#ifndef SCN_STEP_ENEMY_BARBAR_CUSTOM_H
#define SCN_STEP_ENEMY_BARBAR_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    bool isPlayerInArea();
    void setStepBackSpeed();
    void reqCameraInSoundSE(u32 id);
    bool isHidden();
    hel::math::Vector3 getInitPos();
    f32 getSize() const;

private:
    // TODO: members.
    u32 _8[88];
};

}}}}  // namespace scn::step::enemy::barbar

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::barbar::Custom>();

}}  // namespace hel::common

#endif
