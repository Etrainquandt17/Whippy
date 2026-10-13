#ifndef SCN_STEP_ENEMY_CAPTURERECEIVER_H
#define SCN_STEP_ENEMY_CAPTURERECEIVER_H

namespace scn {
namespace step {
namespace enemy {

// TODO: members and the other functions.
class CaptureReceiver {
public:
    void setCanCapture(bool canCapture);
    void setIsIgnoredNonSuper(bool isIgnored);
    bool isCaptured() const;
};

}}}  // namespace scn::step::enemy

#endif
