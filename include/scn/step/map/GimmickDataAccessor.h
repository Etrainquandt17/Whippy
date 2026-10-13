#ifndef SCN_STEP_MAP_GIMMICKDATAACCESSOR_H
#define SCN_STEP_MAP_GIMMICKDATAACCESSOR_H

#include "scn/step/map/BinGmkGeneralEntry.h"
#include "types.h"

namespace scn {
namespace step {
namespace map {

class GimmickDataAccessor {
public:
    bool isValid() const;
    u32 airFlowEntryCount() const;
    const BinGmkGeneralEntry& airFlowEntryAt(u32 index) const;
    u32 aquaRockEntryCount() const;
    const BinGmkGeneralEntry& aquaRockEntryAt(u32 index) const;
    u32 aquaRockSeaEntryCount() const;
    const BinGmkGeneralEntry& aquaRockSeaEntryAt(u32 index) const;
    u32 areaEventEntryCount() const;
    const BinGmkGeneralEntry& areaEventEntryAt(u32 index) const;
    u32 areaSEEntryCount() const;
    const BinGmkGeneralEntry& areaSEEntryAt(u32 index) const;
    u32 arrowBoardEntryCount() const;
    const BinGmkGeneralEntry& arrowBoardEntryAt(u32 index) const;
    u32 ballIceEntryCount() const;
    const BinGmkGeneralEntry& ballIceEntryAt(u32 index) const;
    u32 ballIronEntryCount() const;
    const BinGmkGeneralEntry& ballIronEntryAt(u32 index) const;
    u32 ballLavaEntryCount() const;
    const BinGmkGeneralEntry& ballLavaEntryAt(u32 index) const;
    u32 ballRockEntryCount() const;
    const BinGmkGeneralEntry& ballRockEntryAt(u32 index) const;
    u32 biteStatueEntryCount() const;
    const BinGmkGeneralEntry& biteStatueEntryAt(u32 index) const;
    u32 bombMachineEntryCount() const;
    const BinGmkGeneralEntry& bombMachineEntryAt(u32 index) const;
    u32 cameraLockEntryCount() const;
    const BinGmkGeneralEntry& cameraLockEntryAt(u32 index) const;
    u32 cannonEntryCount() const;
    const BinGmkGeneralEntry& cannonEntryAt(u32 index) const;
    u32 cannonBlowEntryCount() const;
    const BinGmkGeneralEntry& cannonBlowEntryAt(u32 index) const;
    u32 carryDeeEntryCount() const;
    const BinGmkGeneralEntry& carryDeeEntryAt(u32 index) const;
    u32 chainStarterEntryCount() const;
    const BinGmkGeneralEntry& chainStarterEntryAt(u32 index) const;
    u32 challengeDoorEntryCount() const;
    const BinGmkGeneralEntry& challengeDoorEntryAt(u32 index) const;
    u32 circuitBlockEntryCount() const;
    const BinGmkGeneralEntry& circuitBlockEntryAt(u32 index) const;
    u32 consecutiveBattleEntryCount() const;
    const BinGmkGeneralEntry& consecutiveBattleEntryAt(u32 index) const;
    u32 crushWallSuperEntryCount() const;
    const BinGmkGeneralEntry& crushWallSuperEntryAt(u32 index) const;
    u32 crushWallBellSuperEntryCount() const;
    const BinGmkGeneralEntry& crushWallBellSuperEntryAt(u32 index) const;
    u32 crystalWallEntryCount() const;
    const BinGmkGeneralEntry& crystalWallEntryAt(u32 index) const;
    u32 cutRopeStepEntryCount() const;
    const BinGmkGeneralEntry& cutRopeStepEntryAt(u32 index) const;
    u32 darkWallEntryCount() const;
    const BinGmkGeneralEntry& darkWallEntryAt(u32 index) const;
    u32 doorEntryCount() const;
    const BinGmkGeneralEntry& doorEntryAt(u32 index) const;
    u32 fallPoleEntryCount() const;
    const BinGmkGeneralEntry& fallPoleEntryAt(u32 index) const;
    u32 finalPopstarEntryCount() const;
    const BinGmkGeneralEntry& finalPopstarEntryAt(u32 index) const;
    u32 fuseEntryCount() const;
    const BinGmkGeneralEntry& fuseEntryAt(u32 index) const;
    u32 guideBoardEntryCount() const;
    const BinGmkGeneralEntry& guideBoardEntryAt(u32 index) const;
    u32 guidePlateEntryCount() const;
    const BinGmkGeneralEntry& guidePlateEntryAt(u32 index) const;
    u32 hangSwitchEntryCount() const;
    const BinGmkGeneralEntry& hangSwitchEntryAt(u32 index) const;
    u32 icePinEntryCount() const;
    const BinGmkGeneralEntry& icePinEntryAt(u32 index) const;
    u32 icicleEntryCount() const;
    const BinGmkGeneralEntry& icicleEntryAt(u32 index) const;
    u32 injectionBoxEntryCount() const;
    const BinGmkGeneralEntry& injectionBoxEntryAt(u32 index) const;
    u32 lavaGeyserEntryCount() const;
    const BinGmkGeneralEntry& lavaGeyserEntryAt(u32 index) const;
    u32 lightBlockEntryCount() const;
    const BinGmkGeneralEntry& lightBlockEntryAt(u32 index) const;
    u32 lockShutterEntryCount() const;
    const BinGmkGeneralEntry& lockShutterEntryAt(u32 index) const;
    u32 lvMapDoorEntryCount() const;
    const BinGmkGeneralEntry& lvMapDoorEntryAt(u32 index) const;
    u32 mahoroaEntryCount() const;
    const BinGmkGeneralEntry& mahoroaEntryAt(u32 index) const;
    u32 monitorEntryCount() const;
    const BinGmkGeneralEntry& monitorEntryAt(u32 index) const;
    u32 moveLandAttackEntryCount() const;
    const BinGmkGeneralEntry& moveLandAttackEntryAt(u32 index) const;
    u32 pinataEntryCount() const;
    const BinGmkGeneralEntry& pinataEntryAt(u32 index) const;
    u32 popFlowerEntryCount() const;
    const BinGmkGeneralEntry& popFlowerEntryAt(u32 index) const;
    u32 powerSourceEntryCount() const;
    const BinGmkGeneralEntry& powerSourceEntryAt(u32 index) const;
    u32 pressMachineEntryCount() const;
    const BinGmkGeneralEntry& pressMachineEntryAt(u32 index) const;
    u32 octpusShipEntryCount() const;
    const BinGmkGeneralEntry& octpusShipEntryAt(u32 index) const;
    u32 rockPillarEntryCount() const;
    const BinGmkGeneralEntry& rockPillarEntryAt(u32 index) const;
    u32 ropeFlatEntryCount() const;
    const BinGmkGeneralEntry& ropeFlatEntryAt(u32 index) const;
    u32 sandCastleSuperEntryCount() const;
    const BinGmkGeneralEntry& sandCastleSuperEntryAt(u32 index) const;
    u32 screwSuperEntryCount() const;
    const BinGmkGeneralEntry& screwSuperEntryAt(u32 index) const;
    u32 sCutRopeEntryCount() const;
    const BinGmkGeneralEntry& sCutRopeEntryAt(u32 index) const;
    u32 shipDoorEntryCount() const;
    const BinGmkGeneralEntry& shipDoorEntryAt(u32 index) const;
    u32 shipEntryCount() const;
    const BinGmkGeneralEntry& shipEntryAt(u32 index) const;
    u32 shootingEntryCount() const;
    const BinGmkGeneralEntry& shootingEntryAt(u32 index) const;
    u32 shutterEntryCount() const;
    const BinGmkGeneralEntry& shutterEntryAt(u32 index) const;
    u32 sIceVolcanoEntryCount() const;
    const BinGmkGeneralEntry& sIceVolcanoEntryAt(u32 index) const;
    u32 salamanderArmEntryCount() const;
    const BinGmkGeneralEntry& salamanderArmEntryAt(u32 index) const;
    u32 salamanderBodyEntryCount() const;
    const BinGmkGeneralEntry& salamanderBodyEntryAt(u32 index) const;
    u32 snowmanBodyEntryCount() const;
    const BinGmkGeneralEntry& snowmanBodyEntryAt(u32 index) const;
    u32 spikeBarEntryCount() const;
    const BinGmkGeneralEntry& spikeBarEntryAt(u32 index) const;
    u32 stageBoardEntryCount() const;
    const BinGmkGeneralEntry& stageBoardEntryAt(u32 index) const;
    u32 stakeEntryCount() const;
    const BinGmkGeneralEntry& stakeEntryAt(u32 index) const;
    u32 stakeMediumEntryCount() const;
    const BinGmkGeneralEntry& stakeMediumEntryAt(u32 index) const;
    u32 stakeSuperEntryCount() const;
    const BinGmkGeneralEntry& stakeSuperEntryAt(u32 index) const;
    u32 startPortalEntryCount() const;
    const BinGmkGeneralEntry& startPortalEntryAt(u32 index) const;
    u32 startPortalHerosEntryCount() const;
    const BinGmkGeneralEntry& startPortalHerosEntryAt(u32 index) const;
    u32 statueEntryCount() const;
    const BinGmkGeneralEntry& statueEntryAt(u32 index) const;
    u32 strikeBoxEntryCount() const;
    const BinGmkGeneralEntry& strikeBoxEntryAt(u32 index) const;
    u32 sunEntryCount() const;
    const BinGmkGeneralEntry& sunEntryAt(u32 index) const;
    u32 superBeamCenterEntryCount() const;
    const BinGmkGeneralEntry& superBeamCenterEntryAt(u32 index) const;
    u32 superBeamSwitchEntryCount() const;
    const BinGmkGeneralEntry& superBeamSwitchEntryAt(u32 index) const;
    u32 superBeamSwitchTargetEntryCount() const;
    const BinGmkGeneralEntry& superBeamSwitchTargetEntryAt(u32 index) const;
    u32 switchOnceEntryCount() const;
    const BinGmkGeneralEntry& switchOnceEntryAt(u32 index) const;
    u32 switchReturnEntryCount() const;
    const BinGmkGeneralEntry& switchReturnEntryAt(u32 index) const;
    u32 switchToggleEntryCount() const;
    const BinGmkGeneralEntry& switchToggleEntryAt(u32 index) const;
    u32 totemPoleEntryCount() const;
    const BinGmkGeneralEntry& totemPoleEntryAt(u32 index) const;
    u32 volcanoEntryCount() const;
    const BinGmkGeneralEntry& volcanoEntryAt(u32 index) const;
    u32 warpLowperEntryCount() const;
    const BinGmkGeneralEntry& warpLowperEntryAt(u32 index) const;
    u32 warpStarEntryCount() const;
    const BinGmkGeneralEntry& warpStarEntryAt(u32 index) const;
    u32 warpStarContinueEntryCount() const;
    const BinGmkGeneralEntry& warpStarContinueEntryAt(u32 index) const;
    u32 waterFlowEntryCount() const;
    const BinGmkGeneralEntry& waterFlowEntryAt(u32 index) const;
    u32 worldRectEntryCount() const;
    const BinGmkGeneralEntry& worldRectEntryAt(u32 index) const;
    u32 zoneSwitchEntryCount() const;
    const BinGmkGeneralEntry& zoneSwitchEntryAt(u32 index) const;

private:
    u32 _0;
};

}}}  // namespace scn::step::map

#endif
