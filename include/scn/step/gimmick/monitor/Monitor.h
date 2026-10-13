#ifndef SCN_STEP_GIMMICK_MONITOR_MONITOR_H
#define SCN_STEP_GIMMICK_MONITOR_MONITOR_H

#include "hel/math/Vector2.h"
#include "scn/step/gimmick/Model.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace map {
struct BinGmkGeneralEntry;
}

namespace gimmick {
namespace monitor {

class Monitor {
public:
    Monitor(const map::BinGmkGeneralEntry& entry, Component& component);
    ~Monitor();

    void seReq();
    void viewNoise();
    void viewCaution();
    void viewMap();
    void viewShip();

private:
    Component& mComponent;
    hel::math::Vector2 mPos;
    Model mModel;
    snd::SERequestor mSE;
};

}}}}  // namespace scn::step::gimmick::monitor

#endif
