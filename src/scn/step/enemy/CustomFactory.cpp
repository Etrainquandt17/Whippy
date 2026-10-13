#include "scn/step/enemy/CustomFactory.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/CustomBase.h"
#include "scn/step/enemy/ICustom.h"
#include "scn/step/enemy/aquarock/Custom.h"
#include "scn/step/enemy/armordee/Custom.h"
#include "scn/step/enemy/babut/Custom.h"
#include "scn/step/enemy/barbar/Custom.h"
#include "scn/step/enemy/barracu/Custom.h"
#include "scn/step/enemy/bladeknight/Custom.h"
#include "scn/step/enemy/blipper/Custom.h"
#include "scn/step/enemy/bombmachinemissile/Custom.h"
#include "scn/step/enemy/bonkersbomb/Custom.h"
#include "scn/step/enemy/bouncy/Custom.h"
#include "scn/step/enemy/bowby/Custom.h"
#include "scn/step/enemy/bulby/Custom.h"
#include "scn/step/enemy/buraburadee/Custom.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "scn/step/enemy/cappyhat/Custom.h"
#include "scn/step/enemy/carrydee/Custom.h"
#include "scn/step/enemy/chasekeydegout/Custom.h"
#include "scn/step/enemy/chasekeyscarfy/Custom.h"
#include "scn/step/enemy/chilly/Custom.h"
#include "scn/step/enemy/clayn/Custom.h"
#include "scn/step/enemy/coconutbomb/Custom.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/craby/Custom.h"
#include "scn/step/enemy/degout/Custom.h"
#include "scn/step/enemy/doubterball/Custom.h"
#include "scn/step/enemy/doubterbomb/Custom.h"
#include "scn/step/enemy/dubiorjr/Custom.h"
#include "scn/step/enemy/dubiorspark/Custom.h"
#include "scn/step/enemy/elec/Custom.h"
#include "scn/step/enemy/fattybufferstalactite/Custom.h"
#include "scn/step/enemy/fattybufferwater/Custom.h"
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/foley/Custom.h"
#include "scn/step/enemy/gemra/Custom.h"
#include "scn/step/enemy/gigatzo/Custom.h"
#include "scn/step/enemy/glunk/Custom.h"
#include "scn/step/enemy/goliathiceball/Custom.h"
#include "scn/step/enemy/goliathicicle/Custom.h"
#include "scn/step/enemy/goliathsnowball/Custom.h"
#include "scn/step/enemy/gordo/Custom.h"
#include "scn/step/enemy/grandlowperbullet/Custom.h"
#include "scn/step/enemy/hothead/Custom.h"
#include "scn/step/enemy/juckle/Custom.h"
#include "scn/step/enemy/kabu/Custom.h"
#include "scn/step/enemy/knucklejoe/Custom.h"
#include "scn/step/enemy/landiasingle/Custom.h"
#include "scn/step/enemy/lanzer/Custom.h"
#include "scn/step/enemy/larpa/Custom.h"
#include "scn/step/enemy/leaper/Custom.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lupa/Custom.h"
#include "scn/step/enemy/mahoroahammer/Custom.h"
#include "scn/step/enemy/mahoroalowper/Custom.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"
#include "scn/step/enemy/mbossdead/Custom.h"
#include "scn/step/enemy/metalgeneralball/Custom.h"
#include "scn/step/enemy/metalgeneralbit/Custom.h"
#include "scn/step/enemy/metalgeneralbomb/Custom.h"
#include "scn/step/enemy/metalgeneralmissile/Custom.h"
#include "scn/step/enemy/metalgeneralpatriot/Custom.h"
#include "scn/step/enemy/metalgeneralthunder/Custom.h"
#include "scn/step/enemy/mopoo/Custom.h"
#include "scn/step/enemy/mumbies/Custom.h"
#include "scn/step/enemy/needlous/Custom.h"
#include "scn/step/enemy/nruff/Custom.h"
#include "scn/step/enemy/owgulf/Custom.h"
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/parasol/Custom.h"
#include "scn/step/enemy/parasoldee/Custom.h"
#include "scn/step/enemy/parasoldoo/Custom.h"
#include "scn/step/enemy/pierce/Custom.h"
#include "scn/step/enemy/pluid/Custom.h"
#include "scn/step/enemy/poppybrojr/Custom.h"
#include "scn/step/enemy/poppybrojrbomb/Custom.h"
#include "scn/step/enemy/puppetdee/Custom.h"
#include "scn/step/enemy/ridewaddledee/Custom.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rollball/Custom.h"
#include "scn/step/enemy/sandbag/Custom.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/searches/Custom.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sisterbound/Custom.h"
#include "scn/step/enemy/snowl/Custom.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "scn/step/enemy/sparky/Custom.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/stareffect/Custom.h"
#include "scn/step/enemy/starman/Custom.h"
#include "scn/step/enemy/strikeboxbullet/Custom.h"
#include "scn/step/enemy/sun/Custom.h"
#include "scn/step/enemy/togekuki/Custom.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/twister/Custom.h"
#include "scn/step/enemy/volcanorock/Custom.h"
#include "scn/step/enemy/waddledoo/Custom.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walky/Custom.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapodpod/Custom.h"
#include "scn/step/enemy/whispyapple/Custom.h"
#include "scn/step/enemy/zankibblecutter/Custom.h"
#include "std/tr1/reference_wrapper.h"

namespace hel {
namespace common {

// TODO: each of these belongs in the header of its class. The original emits them in every unit that
// includes one, in the order of the includes, and the link keeps the copies of this unit.
#define CUSTOM_RUNTIME_TYPE_INFO(T) \
    template <> \
    const RuntimeTypeInfo& RuntimeTypeInfoImpl<T>() { \
        static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::enemy::ICustom>(), RuntimeTypeInfo::NoName()); \
        return ti; \
    }

CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::kabu::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::parasol::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::parasoldee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::parasoldoo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::nruff::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::scarfy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::stareffect::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::starman::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bouncy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::whispyapple::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::gigatzo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::como::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::rocky::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sisterbound::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::blipper::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sparky::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bladeknight::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::babut::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::hothead::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::flamer::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::doubterball::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::doubterbomb::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::togekuki::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::needlous::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::shotzo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::mumbies::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::glunk::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::pacto::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::cappy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::cappyhat::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::dubiorjr::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::poppybrojrbomb::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::puppetdee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::armordee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::gordo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bulby::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::foley::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::juckle::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::zankibblecutter::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bonkersbomb::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::owgulf::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::mopoo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::pluid::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bowby::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::degout::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::dubiorspark::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::tsukikage::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::rollball::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::metalgeneralbomb::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::metalgeneralthunder::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::chilly::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::twister::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::squishy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::fattybufferwater::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::fattybufferstalactite::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::barbar::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::barracu::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::wapodpod::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::wapod::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::pierce::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::searches::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::elec::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::snowl::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::goliathsnowball::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::goliathiceball::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::goliathicicle::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::bombmachinemissile::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::coconutbomb::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::buraburadee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::craby::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::walf::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::mbossdead::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::poppybrojr::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::larpa::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::liepa::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::lupa::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::leaper::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::waddledoo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::ridewaddledee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::chasekeydegout::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::chasekeyscarfy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::strikeboxbullet::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::carrydee::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sandbag::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sirkibble::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sun::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::volcanorock::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::mahoroahammer::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::mahoroalowper::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sheld::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::knucklejoe::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::lanzer::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::gemra::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::clayn::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::walky::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::sodory::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::enemy::aquarock::Custom)

#undef CUSTOM_RUNTIME_TYPE_INFO

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {

void CustomFactory::Create(Enemy& enemy, mem::ExplicitScopedPtr<ICustom>& custom) {
    switch (enemy.kind()) {
    case map::BinEnemyKind_Kabu:
        custom.constructE<kabu::Custom>(std::tr1::ref(enemy));
        break;
    case 113:
        custom.constructE<parasol::Custom>(std::tr1::ref(enemy));
        break;
    case 40:
        custom.constructE<parasoldee::Custom>(std::tr1::ref(enemy));
        break;
    case 42:
        custom.constructE<parasoldoo::Custom>(std::tr1::ref(enemy));
        break;
    case 22:
    case 87:
        custom.constructE<nruff::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Scarfy:
        custom.constructE<scarfy::Custom>(std::tr1::ref(enemy));
        break;
    case 100:
        custom.constructE<stareffect::Custom>(std::tr1::ref(enemy));
        break;
    case 28:
        custom.constructE<starman::Custom>(std::tr1::ref(enemy));
        break;
    case 17:
    case 94:
        custom.constructE<bouncy::Custom>(std::tr1::ref(enemy));
        break;
    case 102:
    case 103:
    case 104:
    case 105:
        custom.constructE<lowperbullet::Custom>(std::tr1::ref(enemy));
        break;
    case 116:
        custom.constructE<grandlowperbullet::Custom>(std::tr1::ref(enemy));
        break;
    case 106:
    case 107:
        custom.constructE<whispyapple::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Como:
        custom.constructE<como::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Rocky:
        custom.constructE<rocky::Custom>(std::tr1::ref(enemy));
        break;
    case 37:
        custom.constructE<sisterbound::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Blipper:
        custom.constructE<blipper::Custom>(std::tr1::ref(enemy));
        break;
    case 18:
        custom.constructE<sparky::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Bladeknight:
        custom.constructE<bladeknight::Custom>(std::tr1::ref(enemy));
        break;
    case 35:
        custom.constructE<babut::Custom>(std::tr1::ref(enemy));
        break;
    case 5:
        custom.constructE<hothead::Custom>(std::tr1::ref(enemy));
        break;
    case 23:
        custom.constructE<flamer::Custom>(std::tr1::ref(enemy));
        break;
    case 108:
    case 109:
        custom.constructE<doubterball::Custom>(std::tr1::ref(enemy));
        break;
    case 112:
        custom.constructE<doubterbomb::Custom>(std::tr1::ref(enemy));
        break;
    case 11:
        custom.constructE<togekuki::Custom>(std::tr1::ref(enemy));
        break;
    case 19:
        custom.constructE<needlous::Custom>(std::tr1::ref(enemy));
        break;
    case 14:
        custom.constructE<shotzo::Custom>(std::tr1::ref(enemy));
        break;
    case 39:
        custom.constructE<mumbies::Custom>(std::tr1::ref(enemy));
        break;
    case 36:
        custom.constructE<glunk::Custom>(std::tr1::ref(enemy));
        break;
    case 13:
    case 76:
        custom.constructE<pacto::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Cappy:
    case 146:
        custom.constructE<cappy::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Cappyhat:
        custom.constructE<cappyhat::Custom>(std::tr1::ref(enemy));
        break;
    case 114:
        custom.constructE<dubiorjr::Custom>(std::tr1::ref(enemy));
        break;
    case 115:
        custom.constructE<poppybrojrbomb::Custom>(std::tr1::ref(enemy));
        break;
    case 7:
        custom.constructE<puppetdee::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Armordee:
    case map::BinEnemyKind_HalcandleArmordee:
        custom.constructE<armordee::Custom>(std::tr1::ref(enemy));
        break;
    case 10:
        custom.constructE<gordo::Custom>(std::tr1::ref(enemy));
        break;
    case 27:
        custom.constructE<bulby::Custom>(std::tr1::ref(enemy));
        break;
    case 44:
        custom.constructE<foley::Custom>(std::tr1::ref(enemy));
        break;
    case 45:
        custom.constructE<juckle::Custom>(std::tr1::ref(enemy));
        break;
    case 117:
        custom.constructE<zankibblecutter::Custom>(std::tr1::ref(enemy));
        break;
    case 118:
        custom.constructE<bonkersbomb::Custom>(std::tr1::ref(enemy));
        break;
    case 47:
        custom.constructE<owgulf::Custom>(std::tr1::ref(enemy));
        break;
    case 43:
        custom.constructE<mopoo::Custom>(std::tr1::ref(enemy));
        break;
    case 53:
        custom.constructE<pluid::Custom>(std::tr1::ref(enemy));
        break;
    case 46:
    case 95:
        custom.constructE<bowby::Custom>(std::tr1::ref(enemy));
        break;
    case 48:
        custom.constructE<degout::Custom>(std::tr1::ref(enemy));
        break;
    case 119:
        custom.constructE<dubiorspark::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Tsukikage:
        custom.constructE<tsukikage::Custom>(std::tr1::ref(enemy));
        break;
    case 38:
    case 56:
    case 91:
    case 99:
        custom.constructE<rollball::Custom>(std::tr1::ref(enemy));
        break;
    case 34:
    case 57:
    case 73:
        custom.constructE<gigatzo::Custom>(std::tr1::ref(enemy));
        break;
    case 120:
        custom.constructE<metalgeneralball::Custom>(std::tr1::ref(enemy));
        break;
    case 121:
        custom.constructE<metalgeneralbit::Custom>(std::tr1::ref(enemy));
        break;
    case 122:
        custom.constructE<metalgeneralbomb::Custom>(std::tr1::ref(enemy));
        break;
    case 123:
        custom.constructE<metalgeneralmissile::Custom>(std::tr1::ref(enemy), true);
        break;
    case 124:
        custom.constructE<metalgeneralpatriot::Custom>(std::tr1::ref(enemy));
        break;
    case 125:
        custom.constructE<metalgeneralthunder::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Chilly:
        custom.constructE<chilly::Custom>(std::tr1::ref(enemy));
        break;
    case 29:
        custom.constructE<twister::Custom>(std::tr1::ref(enemy));
        break;
    case 60:
        custom.constructE<squishy::Custom>(std::tr1::ref(enemy));
        break;
    case 127:
        custom.constructE<fattybufferwater::Custom>(std::tr1::ref(enemy));
        break;
    case 128:
        custom.constructE<fattybufferstalactite::Custom>(std::tr1::ref(enemy));
        break;
    case 58:
    case 77:
        custom.constructE<barbar::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Barracu:
        custom.constructE<barracu::Custom>(std::tr1::ref(enemy));
        break;
    case 55:
        custom.constructE<wapodpod::Custom>(std::tr1::ref(enemy));
        break;
    case 129:
        custom.constructE<wapod::Custom>(std::tr1::ref(enemy));
        break;
    case 62:
        custom.constructE<pierce::Custom>(std::tr1::ref(enemy));
        break;
    case 63:
        custom.constructE<searches::Custom>(std::tr1::ref(enemy));
        break;
    case 65:
        custom.constructE<elec::Custom>(std::tr1::ref(enemy));
        break;
    case 70:
        custom.constructE<snowl::Custom>(std::tr1::ref(enemy));
        break;
    case 130:
        custom.constructE<goliathsnowball::Custom>(std::tr1::ref(enemy));
        break;
    case 131:
        custom.constructE<goliathiceball::Custom>(std::tr1::ref(enemy));
        break;
    case 132:
        custom.constructE<goliathicicle::Custom>(std::tr1::ref(enemy));
        break;
    case 133:
        custom.constructE<bombmachinemissile::Custom>(std::tr1::ref(enemy));
        break;
    case 134:
        custom.constructE<mahoroamagicball::Custom>(std::tr1::ref(enemy));
        break;
    case 74:
        custom.constructE<coconutbomb::Custom>(std::tr1::ref(enemy));
        break;
    case 66:
    case 67:
        custom.constructE<buraburadee::Custom>(std::tr1::ref(enemy));
        break;
    case 75:
        custom.constructE<craby::Custom>(std::tr1::ref(enemy));
        break;
    case 78:
        custom.constructE<walf::Custom>(std::tr1::ref(enemy));
        break;
    case 136:
        custom.constructE<mbossdead::Custom>(std::tr1::ref(enemy));
        break;
    case 137:
    case 138:
        custom.constructE<landiasingle::Custom>(std::tr1::ref(enemy));
        break;
    case 30:
        custom.constructE<poppybrojr::Custom>(std::tr1::ref(enemy));
        break;
    case 81:
        custom.constructE<larpa::Custom>(std::tr1::ref(enemy));
        break;
    case 82:
        custom.constructE<liepa::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Lupa:
        custom.constructE<lupa::Custom>(std::tr1::ref(enemy));
        break;
    case 84:
        custom.constructE<leaper::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Waddledoo:
        custom.constructE<waddledoo::Custom>(std::tr1::ref(enemy));
        break;
    case 139:
        custom.constructE<ridewaddledee::Custom>(std::tr1::ref(enemy));
        break;
    case 88:
        custom.constructE<chasekeydegout::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_ChaseKeyScarfy:
        custom.constructE<chasekeyscarfy::Custom>(std::tr1::ref(enemy));
        break;
    case 140:
        custom.constructE<strikeboxbullet::Custom>(std::tr1::ref(enemy));
        break;
    case 90:
        custom.constructE<carrydee::Custom>(std::tr1::ref(enemy));
        break;
    case 92:
        custom.constructE<sandbag::Custom>(std::tr1::ref(enemy));
        break;
    case 93:
        custom.constructE<parasoldee::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_0:
        custom.constructE<sirkibble::Custom>(std::tr1::ref(enemy));
        break;
    case 142:
        custom.constructE<metalgeneralmissile::Custom>(std::tr1::ref(enemy), false);
        break;
    case 96:
    case 97:
    case 98:
        custom.constructE<sun::Custom>(std::tr1::ref(enemy));
        break;
    case 143:
        custom.constructE<volcanorock::Custom>(std::tr1::ref(enemy));
        break;
    case 144:
        custom.constructE<mahoroahammer::Custom>(std::tr1::ref(enemy));
        break;
    case 135:
        custom.constructE<mahoroalowper::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Sheld:
        custom.constructE<sheld::Custom>(std::tr1::ref(enemy));
        break;
    case 6:
        custom.constructE<knucklejoe::Custom>(std::tr1::ref(enemy));
        break;
    case 50:
        custom.constructE<lanzer::Custom>(std::tr1::ref(enemy));
        break;
    case 54:
        custom.constructE<gemra::Custom>(std::tr1::ref(enemy));
        break;
    case 61:
        custom.constructE<clayn::Custom>(std::tr1::ref(enemy));
        break;
    case 64:
        custom.constructE<walky::Custom>(std::tr1::ref(enemy));
        break;
    case 68:
        custom.constructE<sodory::Custom>(std::tr1::ref(enemy));
        break;
    case map::BinEnemyKind_Aquarock:
    case map::BinEnemyKind_AquarockSea:
        custom.constructE<aquarock::Custom>(std::tr1::ref(enemy));
        break;
    default:
        custom.constructE<CustomBase>(std::tr1::ref(enemy));
        break;
    }
}

}}}  // namespace scn::step::enemy
