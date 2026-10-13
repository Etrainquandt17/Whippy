#ifndef SCN_STEP_HERO_RUNCHECKER_H
#define SCN_STEP_HERO_RUNCHECKER_H

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class RunChecker {
public:
    bool isEnableRun() const;
    bool isGroundContinue() const;
    bool isAirContinue() const;
    void setGroundContinue();
    void setAirContinue();
    void cancelContinue();
};

}}}  // namespace scn::step::hero

#endif
