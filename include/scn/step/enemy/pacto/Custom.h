#ifndef SCN_STEP_ENEMY_PACTO_CUSTOM_H
#define SCN_STEP_ENEMY_PACTO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

class Custom;

}}}}  // namespace scn::step::enemy::pacto

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::pacto::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    bool chkDeadHero();
    void releaseCaptureHero();
    void vomitCaptureHero();
    void setDamageCaptureHero(u32 damage, bool isLast);
    void enableResistCaptureHero();
    void disableResistCaptureHero();
    bool chkReleaseHero();
    void setSuccessCaptureHero();
    hel::math::Vector2 initPos() const;
    bool isCaptureHero();
    bool chkCaptureHero();

private:
    u32 _8[19];
};

}}}}  // namespace scn::step::enemy::pacto

#endif
