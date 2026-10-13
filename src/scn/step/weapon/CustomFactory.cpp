#include "scn/step/weapon/CustomFactory.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/CustomBase.h"
#include "scn/step/weapon/CustomSimple.h"
#include "scn/step/weapon/ICustom.h"
#include "scn/step/weapon/airball/StateMain.h"
#include "scn/step/weapon/beamcaptureshot/StateMain.h"
#include "scn/step/weapon/beamshot/StateMain.h"
#include "scn/step/weapon/beamsuperball/Custom.h"
#include "scn/step/weapon/beamwaveshot/StateMain.h"
#include "scn/step/weapon/bombbomb/Custom.h"
#include "scn/step/weapon/bowbyarrow/StateMain.h"
#include "scn/step/weapon/bulbypollen/StateMain.h"
#include "scn/step/weapon/buraburarope/Custom.h"
#include "scn/step/weapon/combinationairball/StateMain.h"
#include "scn/step/weapon/combinationdededebomber/StateMain.h"
#include "scn/step/weapon/combinationdeeshot/StateMain.h"
#include "scn/step/weapon/combinationmetabeam/StateMain.h"
#include "scn/step/weapon/comothread/Custom.h"
#include "scn/step/weapon/crackershot/StateMain.h"
#include "scn/step/weapon/cutter/StateMain.h"
#include "scn/step/weapon/cutterfinalwave/StateMain.h"
#include "scn/step/weapon/cutterlv2/StateMain.h"
#include "scn/step/weapon/dededehammer/StateMain.h"
#include "scn/step/weapon/deespear/StateMain.h"
#include "scn/step/weapon/doubterfire/StateMain.h"
#include "scn/step/weapon/enemywaterbullet/StateMain.h"
#include "scn/step/weapon/enemywaterbulletwarp/StateMain.h"
#include "scn/step/weapon/fattybuffercannonsplash/StateMain.h"
#include "scn/step/weapon/fattybufferwatercannon/Custom.h"
#include "scn/step/weapon/fattybufferwaterwarp/StateMain.h"
#include "scn/step/weapon/fighterhadoushot/Custom.h"
#include "scn/step/weapon/fighterkickshot/StateMain.h"
#include "scn/step/weapon/fightersmashshot/StateMain.h"
#include "scn/step/weapon/fireburningbullet/StateMain.h"
#include "scn/step/weapon/floweffect/StateMain.h"
#include "scn/step/weapon/foleyleaf/StateMain.h"
#include "scn/step/weapon/galactacrystal/StateMain.h"
#include "scn/step/weapon/galactamoonshot/StateMain.h"
#include "scn/step/weapon/galactarevolutionsword/Custom.h"
#include "scn/step/weapon/galactashockwave/StateMain.h"
#include "scn/step/weapon/galactaswordbeam/Custom.h"
#include "scn/step/weapon/galactathunderspine/Custom.h"
#include "scn/step/weapon/gianttornado/Custom.h"
#include "scn/step/weapon/gigantedgeshot/StateMain.h"
#include "scn/step/weapon/gigatzobullet/Custom.h"
#include "scn/step/weapon/glunkbullet/StateMain.h"
#include "scn/step/weapon/goliathblizzard/StateMain.h"
#include "scn/step/weapon/goliathenergyball/Custom.h"
#include "scn/step/weapon/grandlowperhole/Custom.h"
#include "scn/step/weapon/grandlowpersparkshot/StateMain.h"
#include "scn/step/weapon/hammerhammer/StateMain.h"
#include "scn/step/weapon/hotheadfire/StateMain.h"
#include "scn/step/weapon/hrd3eyelaser/Custom.h"
#include "scn/step/weapon/hrd3laser/StateMain.h"
#include "scn/step/weapon/icecube/StateMain.h"
#include "scn/step/weapon/jucklecutter/StateMain.h"
#include "scn/step/weapon/kingsdoowaveshot/StateMain.h"
#include "scn/step/weapon/knucklejoehadou/StateMain.h"
#include "scn/step/weapon/landiaburst/Custom.h"
#include "scn/step/weapon/landiacannon/Custom.h"
#include "scn/step/weapon/landiafirebreath/StateMain.h"
#include "scn/step/weapon/landiasinglefireball/Custom.h"
#include "scn/step/weapon/landiasinglefirerain/StateMain.h"
#include "scn/step/weapon/landiasinglegrandcross/StateMain.h"
#include "scn/step/weapon/landiastar/Custom.h"
#include "scn/step/weapon/landiatwinbreath/StateMain.h"
#include "scn/step/weapon/landiawindcutter/StateMain.h"
#include "scn/step/weapon/leafanpollen/StateMain.h"
#include "scn/step/weapon/leafcutter/StateMain.h"
#include "scn/step/weapon/leafcutter2/StateMain.h"
#include "scn/step/weapon/leaperexp/StateMain.h"
#include "scn/step/weapon/leapershot/StateMain.h"
#include "scn/step/weapon/leaperthorn/Custom.h"
#include "scn/step/weapon/liepashot/StateMain.h"
#include "scn/step/weapon/lowperblackhole/StateMain.h"
#include "scn/step/weapon/lowperbulletburst/StateMain.h"
#include "scn/step/weapon/lowperbulletlandhit/StateMain.h"
#include "scn/step/weapon/lowpericespine/Custom.h"
#include "scn/step/weapon/lowperrollingspark/Custom.h"
#include "scn/step/weapon/lowpersparkshot/StateMain.h"
#include "scn/step/weapon/lupashot/StateMain.h"
#include "scn/step/weapon/mahoroablackhole/Custom.h"
#include "scn/step/weapon/mahoroablackholebg/StateMain.h"
#include "scn/step/weapon/mahoroafrozenarea/StateMain.h"
#include "scn/step/weapon/mahoroahammershockwave/StateMain.h"
#include "scn/step/weapon/mahoroaicethorn/StateMain.h"
#include "scn/step/weapon/mahoroaicicle/StateMain.h"
#include "scn/step/weapon/mahoroalaser/Custom.h"
#include "scn/step/weapon/mahoroamagicballdemometeor/StateMain.h"
#include "scn/step/weapon/mahoroaneedle/Custom.h"
#include "scn/step/weapon/mahoroarevolutionball/StateMain.h"
#include "scn/step/weapon/mahoroastormeffect/StateMain.h"
#include "scn/step/weapon/mahoroasuperbeamball/Custom.h"
#include "scn/step/weapon/mahoroasuperfire/Custom.h"
#include "scn/step/weapon/mahoroawarphole/StateMain.h"
#include "scn/step/weapon/mahoroawarphole2/Custom.h"
#include "scn/step/weapon/mahoroawarpholemagicball/StateMain.h"
#include "scn/step/weapon/mahoroawarpneedle/Custom.h"
#include "scn/step/weapon/metabeam/StateMain.h"
#include "scn/step/weapon/metalgeneralbitshot/Custom.h"
#include "scn/step/weapon/metalgeneralneedle/Custom.h"
#include "scn/step/weapon/metalgeneralpatriotexp/StateMain.h"
#include "scn/step/weapon/metalgeneralpatriotfire/Custom.h"
#include "scn/step/weapon/metashockwave/StateMain.h"
#include "scn/step/weapon/missileexp/StateMain.h"
#include "scn/step/weapon/needleshot/StateWait.h"
#include "scn/step/weapon/ninjablossomstorm/StateMain.h"
#include "scn/step/weapon/ninjadasheffect/StateMain.h"
#include "scn/step/weapon/ninjakunai/StateMain.h"
#include "scn/step/weapon/ninjawaveshot/StateMain.h"
#include "scn/step/weapon/owgulffeather/StateMain.h"
#include "scn/step/weapon/roahboomerang/Custom.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahoar/Custom.h"
#include "scn/step/weapon/roahstar/Custom.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "scn/step/weapon/shotzobullet/StateMain.h"
#include "scn/step/weapon/sirkibblecutter/StateMain.h"
#include "scn/step/weapon/sleepsnotbubble/StateMain.h"
#include "scn/step/weapon/snowlball/StateMain.h"
#include "scn/step/weapon/sparkshotlv1/StateMain.h"
#include "scn/step/weapon/sparkshotlv2/StateMain.h"
#include "scn/step/weapon/sparkshotlv3/StateMain.h"
#include "scn/step/weapon/spearspear/StateMain.h"
#include "scn/step/weapon/starshotlv1/Custom.h"
#include "scn/step/weapon/superfiredragon/StateMain.h"
#include "scn/step/weapon/superhammerquake/StateWait.h"
#include "scn/step/weapon/swordbeam/StateMain.h"
#include "scn/step/weapon/tornadogust/StateMain.h"
#include "scn/step/weapon/tsukikageshuriken/StateMain.h"
#include "scn/step/weapon/vacuumedblock/Custom.h"
#include "scn/step/weapon/walkynote/StateMain.h"
#include "scn/step/weapon/waterbigwave/StateMain.h"
#include "scn/step/weapon/waterbullet/StateMain.h"
#include "scn/step/weapon/waterbulletwarp/StateMain.h"
#include "scn/step/weapon/watergalboroswater/StateMain.h"
#include "scn/step/weapon/waterpistol/StateMain.h"
#include "scn/step/weapon/waterunderwater/Custom.h"
#include "scn/step/weapon/whispyairball/StateMain.h"
#include "scn/step/weapon/whispyroot/StateMain.h"
#include "scn/step/weapon/whispytornado/StateMain.h"
#include "scn/step/weapon/wingshockwave/StateMain.h"
#include "scn/step/weapon/wingshot/StateMain.h"
#include "std/tr1/reference_wrapper.h"

namespace hel {
namespace common {

// TODO: each of these belongs in the header of its class. The original emits them in every unit that
// includes one, in the order of the includes, and the link keeps the copies of this unit.
#define CUSTOM_RUNTIME_TYPE_INFO(T) \
    template <> \
    const RuntimeTypeInfo& RuntimeTypeInfoImpl<T>() { \
        static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName()); \
        return ti; \
    }

CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::waterunderwater::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::fighterhadoushot::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::gigatzobullet::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::metalgeneralneedle::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::metalgeneralbitshot::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::metalgeneralpatriotfire::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::roahboomerang::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::roahoar::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::landiasinglefireball::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::lowpericespine::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::weapon::gianttornado::Custom)

#undef CUSTOM_RUNTIME_TYPE_INFO

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {

void CustomFactory::Create(Weapon& weapon, mem::ExplicitScopedPtr<ICustom>& custom) {
    switch (weapon.kind()) {
    case KIND_0:
    case KIND_STARSHOTLV2:
    case KIND_STARSHOTLV3:
        custom.constructE<starshotlv1::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_AIRBALL:
        custom.constructE<CustomSimple<airball::StateMain> >(std::tr1::ref(weapon));
        break;
    case 4:
        custom.constructE<CustomSimple<waterpistol::StateMain> >(std::tr1::ref(weapon));
        break;
    case 5:
        custom.constructE<CustomSimple<swordbeam::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_CUTTER:
        custom.constructE<CustomSimple<cutter::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_CUTTER_2:
        custom.constructE<CustomSimple<cutterlv2::StateMain> >(std::tr1::ref(weapon));
        break;
    case 8:
        custom.constructE<CustomSimple<cutterfinalwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LEAFCUTTER:
        custom.constructE<CustomSimple<leafcutter::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LEAFCUTTER2:
        custom.constructE<CustomSimple<leafcutter2::StateMain> >(std::tr1::ref(weapon));
        break;
    case 11:
        custom.constructE<CustomSimple<fireburningbullet::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_WHISPYAIRBALL:
        custom.constructE<CustomSimple<whispyairball::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_COMOTHREAD:
        custom.constructE<comothread::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_SIRKIBBLECUTTER:
        custom.constructE<CustomSimple<sirkibblecutter::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_SHOTZOBULLET:
        custom.constructE<CustomSimple<shotzobullet::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LEAFANPOLLEN:
        custom.constructE<CustomSimple<leafanpollen::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_NEEDLESHOT:
        custom.constructE<CustomSimple<needleshot::StateWait> >(std::tr1::ref(weapon));
        break;
    case KIND_SLEEPSNOTBUBBLE:
        custom.constructE<CustomSimple<sleepsnotbubble::StateMain> >(std::tr1::ref(weapon));
        break;
    case 19:
        custom.constructE<CustomSimple<sparkshotlv1::StateMain> >(std::tr1::ref(weapon));
        break;
    case 20:
        custom.constructE<CustomSimple<sparkshotlv2::StateMain> >(std::tr1::ref(weapon));
        break;
    case 21:
        custom.constructE<CustomSimple<sparkshotlv3::StateMain> >(std::tr1::ref(weapon));
        break;
    case 22:
        custom.constructE<CustomSimple<beamshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 23:
        custom.constructE<CustomSimple<beamwaveshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 24:
        custom.constructE<CustomSimple<beamcaptureshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_WATERBULLET:
        custom.constructE<CustomSimple<waterbullet::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_WATERBULLETWARP:
        custom.constructE<CustomSimple<waterbulletwarp::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_WATERUNDERWATER:
        custom.constructE<waterunderwater::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_WATERBIGWAVE:
        custom.constructE<CustomSimple<waterbigwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case 51:
        custom.constructE<CustomSimple<watergalboroswater::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_BOMBBOMB:
        custom.constructE<bombbomb::Custom>(std::tr1::ref(weapon));
        break;
    case 30:
        custom.constructE<beamsuperball::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_SPEARSPEAR:
        custom.constructE<CustomSimple<spearspear::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_HAMMERHAMMER:
        custom.constructE<CustomSimple<hammerhammer::StateMain> >(std::tr1::ref(weapon));
        break;
    case 33:
        custom.constructE<CustomSimple<icecube::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_WINGSHOT:
        custom.constructE<CustomSimple<wingshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 35:
        custom.constructE<CustomSimple<wingshockwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case 36:
        custom.constructE<CustomSimple<ninjablossomstorm::StateMain> >(std::tr1::ref(weapon));
        break;
    case 37:
        custom.constructE<CustomSimple<ninjadasheffect::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_NINJAKUNAI:
        custom.constructE<CustomSimple<ninjakunai::StateMain> >(std::tr1::ref(weapon));
        break;
    case 39:
        custom.constructE<CustomSimple<ninjawaveshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 40:
        custom.constructE<CustomSimple<fightersmashshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 41:
        custom.constructE<CustomSimple<fighterkickshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 42:
        custom.constructE<fighterhadoushot::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_CRACKERSHOT:
        custom.constructE<CustomSimple<crackershot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 44:
        custom.constructE<CustomSimple<gigantedgeshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_ENEMYWATERBULLET:
        custom.constructE<CustomSimple<enemywaterbullet::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_ENEMYWATERBULLETWARP:
        custom.constructE<CustomSimple<enemywaterbulletwarp::StateMain> >(std::tr1::ref(weapon));
        break;
    case 47:
        custom.constructE<rollexp::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_GLUNKBULLET:
        custom.constructE<CustomSimple<glunkbullet::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_GIGATZOBULLET:
    case KIND_GIGATZOBULLET_VOLT:
    case KIND_GIGATZOBULLET_COLD:
        custom.constructE<gigatzobullet::Custom>(std::tr1::ref(weapon));
        break;
    case 50:
        custom.constructE<CustomSimple<kingsdoowaveshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 52:
        custom.constructE<CustomSimple<bulbypollen::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_OWGULFFEATHER:
        custom.constructE<CustomSimple<owgulffeather::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_FOLEYLEAF:
        custom.constructE<CustomSimple<foleyleaf::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_BOWBYARROW:
        custom.constructE<CustomSimple<bowbyarrow::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_JUCKLECUTTER:
        custom.constructE<CustomSimple<jucklecutter::StateMain> >(std::tr1::ref(weapon));
        break;
    case 57:
        custom.constructE<CustomSimple<superhammerquake::StateWait> >(std::tr1::ref(weapon));
        break;
    case 58:
        custom.constructE<CustomSimple<superfiredragon::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_TSUKIKAGESHURIKEN:
        custom.constructE<CustomSimple<tsukikageshuriken::StateMain> >(std::tr1::ref(weapon));
        break;
    case 61:
        custom.constructE<CustomSimple<knucklejoehadou::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_METALGENERALNEEDLE:
        custom.constructE<metalgeneralneedle::Custom>(std::tr1::ref(weapon));
        break;
    case 63:
        custom.constructE<metalgeneralbitshot::Custom>(std::tr1::ref(weapon));
        break;
    case 64:
        custom.constructE<CustomSimple<metalgeneralpatriotexp::StateMain> >(std::tr1::ref(weapon));
        break;
    case 65:
        custom.constructE<metalgeneralpatriotfire::Custom>(std::tr1::ref(weapon));
        break;
    case 66:
        custom.constructE<CustomSimple<walkynote::StateMain> >(std::tr1::ref(weapon));
        break;
    case 67:
        custom.constructE<CustomSimple<snowlball::StateMain> >(std::tr1::ref(weapon));
        break;
    case 68:
        custom.constructE<CustomSimple<goliathblizzard::StateMain> >(std::tr1::ref(weapon));
        break;
    case 69:
        custom.constructE<goliathenergyball::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_ROAHBOOMERANG:
        custom.constructE<roahboomerang::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_ROAHBULLET:
        custom.constructE<roahbullet::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_ROAHOAR:
        custom.constructE<roahoar::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_ROAHSTAR:
        custom.constructE<roahstar::Custom>(std::tr1::ref(weapon));
        break;
    case 74:
        custom.constructE<CustomSimple<floweffect::StateMain> >(std::tr1::ref(weapon));
        break;
    case 75:
        custom.constructE<CustomSimple<missileexp::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROANEEDLE:
    case KIND_MAHOROANEEDLE_2:
        custom.constructE<mahoroaneedle::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_BURABURAROPE:
        custom.constructE<buraburarope::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_LANDIASTAR:
        custom.constructE<landiastar::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_LANDIABURST:
        custom.constructE<landiaburst::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_LANDIACANNON:
        custom.constructE<landiacannon::Custom>(std::tr1::ref(weapon));
        break;
    case 83:
        custom.constructE<CustomSimple<whispytornado::StateMain> >(std::tr1::ref(weapon));
        break;
    case 84:
        custom.constructE<CustomSimple<mahoroarevolutionball::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROALASER:
    case KIND_MAHOROALASER_WARPHOLE:
        custom.constructE<mahoroalaser::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_WHISPYROOT:
        custom.constructE<CustomSimple<whispyroot::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_COMBINATIONAIRBALL:
        custom.constructE<CustomSimple<combinationairball::StateMain> >(std::tr1::ref(weapon));
        break;
    case 88:
        custom.constructE<CustomSimple<combinationmetabeam::StateMain> >(std::tr1::ref(weapon));
        break;
    case 89:
        custom.constructE<CustomSimple<combinationdededebomber::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_COMBINATIONDEESHOT:
        custom.constructE<CustomSimple<combinationdeeshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 91:
        custom.constructE<CustomSimple<tornadogust::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROABLACKHOLE:
        custom.constructE<mahoroablackhole::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROABLACKHOLEBG:
        custom.constructE<CustomSimple<mahoroablackholebg::StateMain> >(std::tr1::ref(weapon));
        break;
    case 94:
        custom.constructE<CustomSimple<metabeam::StateMain> >(std::tr1::ref(weapon));
        break;
    case 95:
        custom.constructE<CustomSimple<metashockwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_DEDEDEHAMMER:
        custom.constructE<CustomSimple<dededehammer::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_DEESPEAR:
        custom.constructE<CustomSimple<deespear::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_FATTYBUFFERWATERWARP:
        custom.constructE<CustomSimple<fattybufferwaterwarp::StateMain> >(std::tr1::ref(weapon));
        break;
    case 99:
        custom.constructE<fattybufferwatercannon::Custom>(std::tr1::ref(weapon));
        break;
    case 100:
        custom.constructE<CustomSimple<fattybuffercannonsplash::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAWARPHOLE:
        custom.constructE<CustomSimple<mahoroawarphole::StateMain> >(std::tr1::ref(weapon));
        break;
    case 102:
        custom.constructE<CustomSimple<landiafirebreath::StateMain> >(std::tr1::ref(weapon));
        break;
    case 103:
        custom.constructE<CustomSimple<landiatwinbreath::StateMain> >(std::tr1::ref(weapon));
        break;
    case 104:
        custom.constructE<CustomSimple<landiawindcutter::StateMain> >(std::tr1::ref(weapon));
        break;
    case 105:
        custom.constructE<landiasinglefireball::Custom>(std::tr1::ref(weapon));
        break;
    case 106:
        custom.constructE<CustomSimple<landiasinglefirerain::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LANDIASINGLEGRANDCROSS:
        custom.constructE<CustomSimple<landiasinglegrandcross::StateMain> >(std::tr1::ref(weapon));
        break;
    case 108:
        custom.constructE<CustomSimple<doubterfire::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_VACUUMEDBLOCK_STAR:
    case KIND_VACUUMEDBLOCK_HEAVY1X1:
    case KIND_VACUUMEDBLOCK_HEAVY2X2:
    case KIND_VACUUMEDBLOCK_HEAVY3X3:
    case KIND_VACUUMEDBLOCK_HEAVY4X4:
    case KIND_VACUUMEDBLOCK_HEAVYA1X2X1:
    case KIND_VACUUMEDBLOCK_HEAVYB1X2X1:
    case KIND_VACUUMEDBLOCK_HEAVY1X2X3:
    case KIND_VACUUMEDBLOCK_HEAVY1X3:
    case KIND_VACUUMEDBLOCK_HEAVY3X1:
    case KIND_VACUUMEDBLOCK_HEAVY2X4X4X2:
    case KIND_VACUUMEDBLOCK_HEAVY3X2X1:
        custom.constructE<vacuumedblock::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_LIEPASHOT:
        custom.constructE<CustomSimple<liepashot::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LUPASHOT:
        custom.constructE<CustomSimple<lupashot::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LEAPERSHOT:
        custom.constructE<CustomSimple<leapershot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 124:
        custom.constructE<CustomSimple<leaperexp::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_LEAPERTHORN:
        custom.constructE<leaperthorn::Custom>(std::tr1::ref(weapon));
        break;
    case 126:
        custom.constructE<CustomSimple<lowperbulletlandhit::StateMain> >(std::tr1::ref(weapon));
        break;
    case 127:
        custom.constructE<CustomSimple<lowperbulletburst::StateMain> >(std::tr1::ref(weapon));
        break;
    case 128:
        custom.constructE<CustomSimple<lowpersparkshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 129:
        custom.constructE<CustomSimple<lowperblackhole::StateMain> >(std::tr1::ref(weapon));
        break;
    case 130:
        custom.constructE<lowperrollingspark::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_LOWPERICESPINE:
        custom.constructE<lowpericespine::Custom>(std::tr1::ref(weapon));
        break;
    case 132:
        custom.constructE<gianttornado::Custom>(std::tr1::ref(weapon));
        break;
    case 133:
        custom.constructE<galactathunderspine::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_GALACTAREVOLUTIONSWORD:
        custom.constructE<galactarevolutionsword::Custom>(std::tr1::ref(weapon));
        break;
    case 135:
        custom.constructE<galactaswordbeam::Custom>(std::tr1::ref(weapon));
        break;
    case 136:
        custom.constructE<CustomSimple<galactamoonshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 137:
        custom.constructE<CustomSimple<galactashockwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_GALACTACRYSTAL:
        custom.constructE<CustomSimple<galactacrystal::StateMain> >(std::tr1::ref(weapon));
        break;
    case 139:
        custom.constructE<grandlowperhole::Custom>(std::tr1::ref(weapon));
        break;
    case 140:
        custom.constructE<CustomSimple<grandlowpersparkshot::StateMain> >(std::tr1::ref(weapon));
        break;
    case 141:
        custom.constructE<mahoroasuperfire::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAWARPHOLE2:
        custom.constructE<mahoroawarphole2::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAWARPNEEDLE:
        custom.constructE<mahoroawarpneedle::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_HRD3LASER:
        custom.constructE<CustomSimple<hrd3laser::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_HRD3EYELASER:
        custom.constructE<hrd3eyelaser::Custom>(std::tr1::ref(weapon));
        break;
    case KIND_BOWBYARROW_HALCAN:
        custom.constructE<CustomSimple<bowbyarrow::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_HOTHEADFIRE:
        custom.constructE<CustomSimple<hotheadfire::StateMain> >(std::tr1::ref(weapon));
        break;
    case 148:
        custom.constructE<CustomSimple<mahoroamagicballdemometeor::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAICETHORN:
        custom.constructE<CustomSimple<mahoroaicethorn::StateMain> >(std::tr1::ref(weapon));
        break;
    case 150:
        custom.constructE<CustomSimple<mahoroahammershockwave::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAICICLE:
        custom.constructE<CustomSimple<mahoroaicicle::StateMain> >(std::tr1::ref(weapon));
        break;
    case 152:
        custom.constructE<CustomSimple<mahoroafrozenarea::StateMain> >(std::tr1::ref(weapon));
        break;
    case 153:
        custom.constructE<mahoroasuperbeamball::Custom>(std::tr1::ref(weapon));
        break;
    case 154:
        custom.constructE<CustomSimple<mahoroastormeffect::StateMain> >(std::tr1::ref(weapon));
        break;
    case KIND_MAHOROAWARPHOLEMAGICBALL:
        custom.constructE<CustomSimple<mahoroawarpholemagicball::StateMain> >(std::tr1::ref(weapon));
        break;
    default:
        custom.constructE<CustomBase>(std::tr1::ref(weapon));
        break;
    }
}

}}}  // namespace scn::step::weapon
