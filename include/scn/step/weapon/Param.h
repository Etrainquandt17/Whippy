#ifndef SCN_STEP_WEAPON_PARAM_H
#define SCN_STEP_WEAPON_PARAM_H

namespace scn {
namespace step {
namespace weapon {

namespace airball {
struct Param;
}
namespace beamcaptureshot {
struct Param;
}
namespace beamshot {
struct Param;
}
namespace beamsuperball {
struct Param;
}
namespace beamwaveshot {
struct Param;
}
namespace bombbomb {
struct Param;
}
namespace bowbyarrow {
struct Param;
}
namespace buraburarope {
struct Param;
}
namespace combinationairball {
struct Param;
}
namespace combinationdededebomber {
struct Param;
}
namespace combinationdeeshot {
struct Param;
}
namespace combinationmetabeam {
struct Param;
}
namespace cutter {
struct Param;
}
namespace cutterfinalwave {
struct Param;
}
namespace cutterlv2 {
struct Param;
}
namespace dededehammer {
struct Param;
}
namespace deespear {
struct Param;
}
namespace doubterfire {
struct Param;
}
namespace enemywaterbullet {
struct Param;
}
namespace fighterhadoushot {
struct Param;
}
namespace fighterkickshot {
struct Param;
}
namespace fightersmashshot {
struct Param;
}
namespace fireburningbullet {
struct Param;
}
namespace floweffect {
struct Param;
}
namespace foleyleaf {
struct Param;
}
namespace galactamoonshot {
struct Param;
}
namespace galactarevolutionsword {
struct Param;
}
namespace galactashockwave {
struct Param;
}
namespace galactaswordbeam {
struct Param;
}
namespace gigantedgeshot {
struct Param;
}
namespace gigatzobullet {
struct Param;
}
namespace goliathblizzard {
struct Param;
}
namespace goliathenergyball {
struct Param;
}
namespace grandlowperhole {
struct Param;
}
namespace hammerhammer {
struct Param;
}
namespace icecube {
struct Param;
}
namespace jucklecutter {
struct Param;
}
namespace kingsdoowaveshot {
struct Param;
}
namespace knucklejoehadou {
struct Param;
}
namespace landiaburst {
struct Param;
}
namespace landiacannon {
struct Param;
}
namespace landiafirebreath {
struct Param;
}
namespace landiasinglefireball {
struct Param;
}
namespace landiasinglefirerain {
struct Param;
}
namespace landiasinglegrandcross {
struct Param;
}
namespace landiastar {
struct Param;
}
namespace landiatwinbreath {
struct Param;
}
namespace landiawindcutter {
struct Param;
}
namespace leafanpollen {
struct Param;
}
namespace leafcutter {
struct Param;
}
namespace leafcutter2 {
struct Param;
}
namespace leaperexp {
struct Param;
}
namespace leapershot {
struct Param;
}
namespace leaperthorn {
struct Param;
}
namespace liepashot {
struct Param;
}
namespace lupashot {
struct Param;
}
namespace mahoroaneedle {
struct Param;
}
namespace mahoroarevolutionball {
struct Param;
}
namespace metabeam {
struct Param;
}
namespace metalgeneralbitshot {
struct Param;
}
namespace metalgeneralneedle {
struct Param;
}
namespace metalgeneralpatriotexp {
struct Param;
}
namespace metalgeneralpatriotfire {
struct Param;
}
namespace metashockwave {
struct Param;
}
namespace missileexp {
struct Param;
}
namespace needleshot {
struct Param;
}
namespace ninjablossomstorm {
struct Param;
}
namespace ninjadasheffect {
struct Param;
}
namespace ninjakunai {
struct Param;
}
namespace ninjawaveshot {
struct Param;
}
namespace roahboomerang {
struct Param;
}
namespace roahbullet {
struct Param;
}
namespace roahoar {
struct Param;
}
namespace roahstar {
struct Param;
}
namespace rollexp {
struct Param;
}
namespace shotzobullet {
struct Param;
}
namespace sirkibblecutter {
struct Param;
}
namespace sleepsnotbubble {
struct Param;
}
namespace sparkshotlv1 {
struct Param;
}
namespace sparkshotlv2 {
struct Param;
}
namespace sparkshotlv3 {
struct Param;
}
namespace spearspear {
struct Param;
}
namespace starshotlv1 {
struct Param;
}
namespace starshotlv2 {
struct Param;
}
namespace starshotlv3 {
struct Param;
}
namespace superhammerquake {
struct Param;
}
namespace swordbeam {
struct Param;
}
namespace tornadogust {
struct Param;
}
namespace tsukikageshuriken {
struct Param;
}
namespace vacuumedblock {
struct Param;
}
namespace walkynote {
struct Param;
}
namespace waterbigwave {
struct Param;
}
namespace waterbullet {
struct Param;
}
namespace watergalboroswater {
struct Param;
}
namespace waterpistol {
struct Param;
}
namespace waterunderwater {
struct Param;
}
namespace whispyairball {
struct Param;
}
namespace whispyroot {
struct Param;
}
namespace whispytornado {
struct Param;
}
namespace wingshockwave {
struct Param;
}
namespace wingshot {
struct Param;
}

// TODO: members. The struct of an accessor is taken to be named after it; the accessors' bodies do not show it.
class Param {
public:
    const airball::Param& airBall() const;
    const beamcaptureshot::Param& beamCaptureShot() const;
    const beamshot::Param& beamShot() const;
    const beamsuperball::Param& beamSuperBall() const;
    const beamwaveshot::Param& beamWaveShot() const;
    const bombbomb::Param& bombBomb() const;
    const bowbyarrow::Param& bowbyArrow() const;
    const buraburarope::Param& buraburarope() const;
    const combinationairball::Param& combinationAirBall() const;
    const combinationdededebomber::Param& combinationDededeBomber() const;
    const combinationdeeshot::Param& combinationDeeShot() const;
    const combinationmetabeam::Param& combinationMetaBeam() const;
    const cutter::Param& cutter() const;
    const cutterfinalwave::Param& cutterFinalWave() const;
    const cutterlv2::Param& cutterLv2() const;
    const dededehammer::Param& dededeHammer() const;
    const deespear::Param& deeSpear() const;
    const doubterfire::Param& doubterFire() const;
    const enemywaterbullet::Param& enemyWaterBullet() const;
    const fighterhadoushot::Param& fighterHadouShot() const;
    const fighterkickshot::Param& fighterKickShot() const;
    const fightersmashshot::Param& fighterSmashShot() const;
    const fireburningbullet::Param& fireBurningBullet() const;
    const floweffect::Param& flowEffect() const;
    const foleyleaf::Param& foleyLeaf() const;
    const galactamoonshot::Param& galactaMoonShot() const;
    const galactarevolutionsword::Param& galactaRevolutionSword() const;
    const galactashockwave::Param& galactaShockWave() const;
    const galactaswordbeam::Param& galactaSwordBeam() const;
    const gigantedgeshot::Param& gigantEdgeShot() const;
    const gigatzobullet::Param& gigatzoBullet() const;
    const goliathblizzard::Param& goliathBlizzard() const;
    const goliathenergyball::Param& goliathEnergyBall() const;
    const grandlowperhole::Param& grandLowperHole() const;
    const hammerhammer::Param& hammerHammer() const;
    const icecube::Param& iceCube() const;
    const jucklecutter::Param& juckleCutter() const;
    const kingsdoowaveshot::Param& kingsDooWaveShot() const;
    const knucklejoehadou::Param& knucklejoeHadou() const;
    const landiaburst::Param& landiaBurst() const;
    const landiacannon::Param& landiaCannon() const;
    const landiafirebreath::Param& landiaFireBreath() const;
    const landiasinglefireball::Param& landiaSingleFireBall() const;
    const landiasinglefirerain::Param& landiaSingleFireRain() const;
    const landiasinglegrandcross::Param& landiaSingleGrandCross() const;
    const landiastar::Param& landiaStar() const;
    const landiatwinbreath::Param& landiaTwinBreath() const;
    const landiawindcutter::Param& landiaWindCutter() const;
    const leafcutter::Param& leafCutter() const;
    const leafcutter2::Param& leafCutter2() const;
    const leafanpollen::Param& leafanPollen() const;
    const leaperexp::Param& leaperExp() const;
    const leapershot::Param& leaperShot() const;
    const leaperthorn::Param& leaperThorn() const;
    const liepashot::Param& liepaShot() const;
    const lupashot::Param& lupaShot() const;
    const mahoroaneedle::Param& mahoroaNeedle() const;
    const mahoroarevolutionball::Param& mahoroaRevolutionBall() const;
    const metabeam::Param& metaBeam() const;
    const metashockwave::Param& metaShockWave() const;
    const metalgeneralbitshot::Param& metalGeneralBitShot() const;
    const metalgeneralneedle::Param& metalGeneralNeedle() const;
    const metalgeneralpatriotexp::Param& metalGeneralPatriotExp() const;
    const metalgeneralpatriotfire::Param& metalGeneralPatriotFire() const;
    const missileexp::Param& missileExp() const;
    const needleshot::Param& needleShot() const;
    const ninjablossomstorm::Param& ninjaBlossomStorm() const;
    const ninjadasheffect::Param& ninjaDashEffect() const;
    const ninjakunai::Param& ninjaKunai() const;
    const ninjawaveshot::Param& ninjaWaveShot() const;
    const roahboomerang::Param& roahBoomerang() const;
    const roahbullet::Param& roahBullet() const;
    const roahoar::Param& roahOar() const;
    const roahstar::Param& roahStar() const;
    const rollexp::Param& rollExp() const;
    const shotzobullet::Param& shotzoBullet() const;
    const sirkibblecutter::Param& sirkibbleCutter() const;
    const sleepsnotbubble::Param& sleepSnotBubble() const;
    const sparkshotlv1::Param& sparkShotLv1() const;
    const sparkshotlv2::Param& sparkShotLv2() const;
    const sparkshotlv3::Param& sparkShotLv3() const;
    const spearspear::Param& spearSpear() const;
    const starshotlv1::Param& starShotLv1() const;
    const starshotlv2::Param& starShotLv2() const;
    const starshotlv3::Param& starShotLv3() const;
    const superhammerquake::Param& superHammerQuake() const;
    const swordbeam::Param& swordBeam() const;
    const tornadogust::Param& tornadoGust() const;
    const tsukikageshuriken::Param& tsukikageshuriken() const;
    const vacuumedblock::Param& vacuumedBlock() const;
    const walkynote::Param& walkyNote() const;
    const waterbigwave::Param& waterBigWave() const;
    const waterbullet::Param& waterBullet() const;
    const watergalboroswater::Param& waterGalborosWater() const;
    const waterpistol::Param& waterPistol() const;
    const waterunderwater::Param& waterUnderWater() const;
    const whispyairball::Param& whispyAirBallBig() const;
    const whispyairball::Param& whispyAirBallNormal() const;
    const whispyairball::Param& whispyAirBallSensitive() const;
    const whispyroot::Param& whispyRoot() const;
    const whispytornado::Param& whispyTornado() const;
    const wingshockwave::Param& wingShockWave() const;
    const wingshot::Param& wingShot() const;
};

}
}
}

#endif
