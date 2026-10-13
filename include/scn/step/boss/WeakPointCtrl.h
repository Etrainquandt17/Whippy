#ifndef SCN_STEP_BOSS_WEAKPOINTCTRL_H
#define SCN_STEP_BOSS_WEAKPOINTCTRL_H

#include "hel/common/MutableArray.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class WeakPointCtrl {
public:
    struct WeakPointData {
        WeakPointData() {}
        WeakPointData(u32 id, f32 rate) : mID(id), mRate(rate) {}

        u32 mID;
        f32 mRate;
    };

    WeakPointCtrl();
    ~WeakPointCtrl();

    f32 getDamageRate(u32 id) const;
    void add(u32 id, f32 rate);
    void clear();
    void remove(u32 id);

private:
    hel::common::MutableArray<WeakPointData, 4> mData;
};

}}}  // namespace scn::step::boss

#endif
