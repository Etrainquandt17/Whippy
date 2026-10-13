#ifndef SCN_STEP_WEAPON_BURABURAROPE_ICUSTOMRECEIVER_H
#define SCN_STEP_WEAPON_BURABURAROPE_ICUSTOMRECEIVER_H

namespace scn {
namespace step {
namespace weapon {
namespace buraburarope {

class Custom;

class ICustomReceiver {
public:
    virtual ~ICustomReceiver() {}
    virtual void onRopeRequireUnsetReceiver(Custom& rope) = 0;
};

}}}}  // namespace scn::step::weapon::buraburarope

#endif
