#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_SCRIPTDATA_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_SCRIPTDATA_H

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

// TODO: members.
class ScriptData {
public:
    ScriptData();
    ~ScriptData();

    void setPrevWarpNeedleType(int type);
    int getPrevWarpNeedleType() const;
    void setPrevAnotherDimensionType(int type);
    int getPrevAnotherDimensionType() const;
    void setPrevWarpHoleLaserType(int type);
    int getPrevWarpHoleLaserType() const;
    void setPrevMagicBallType(int type);
    int getPrevMagicBallType() const;
};

}}}}  // namespace scn::step::boss::mahoroabattle2

#endif
