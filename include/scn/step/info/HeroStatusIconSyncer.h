#ifndef SCN_STEP_INFO_HEROSTATUSICONSYNCER_H
#define SCN_STEP_INFO_HEROSTATUSICONSYNCER_H

#include "hel/common/ExplicitSingleton.h"

namespace scn {
namespace step {
namespace info {

class HeroStatusIcon;

class HeroStatusIconSyncer : public hel::common::ExplicitSingleton<HeroStatusIconSyncer> {
public:
    void notifyStartPinchAnim(HeroStatusIcon* icon);
    void notifyStopPinchAnim(HeroStatusIcon* icon);
};

}}}  // namespace scn::step::info

#endif
