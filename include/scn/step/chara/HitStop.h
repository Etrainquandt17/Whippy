#ifndef SCN_STEP_CHARA_HITSTOP_H
#define SCN_STEP_CHARA_HITSTOP_H

namespace scn {
namespace step {
namespace chara {

class IHitStopCallback;

// TODO: members and the other functions.
class HitStop {
public:
    HitStop(IHitStopCallback& callback);

    bool isStopped() const;
    void clear();
    void set(u32 frame);
    void setArmor();
    void unsetArmor();
    u32 get() const;
};

}}}  // namespace scn::step::chara

#endif
