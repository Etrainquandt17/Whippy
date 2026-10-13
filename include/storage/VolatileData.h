#ifndef STORAGE_VOLATILEDATA_H
#define STORAGE_VOLATILEDATA_H

#include "storage/SaveTiming.h"
#include "types.h"

namespace storage {

class VolatileData {
public:
    // TODO: the size is not known, so _1518 may be a member of it.
    class StepStageData {
    public:
        void clearIgnoreObj();

    private:
        u32 _0[0x543];
    };

    void init();
    void onSoftReset();
    void onEnterStage();
    void updateSaveTiming(SaveTiming timing);

    u32 _0[3];
    StepStageData mStepStageData;
    u32 _1518;
    u32 _151C[0x200];
};

}  // namespace storage

#endif
