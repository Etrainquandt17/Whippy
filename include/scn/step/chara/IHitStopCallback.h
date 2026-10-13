#ifndef SCN_STEP_CHARA_IHITSTOPCALLBACK_H
#define SCN_STEP_CHARA_IHITSTOPCALLBACK_H

namespace scn {
namespace step {
namespace chara {

class IHitStopCallback {
public:
    virtual ~IHitStopCallback();
    virtual void onStart() = 0;
    virtual void onEnd() = 0;
};

}}}  // namespace scn::step::chara

#endif
