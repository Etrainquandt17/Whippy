#ifndef SCN_STEP_BOSS_PARAM_H
#define SCN_STEP_BOSS_PARAM_H

namespace scn {
namespace step {
namespace boss {

namespace bonkers {

struct Param;

}

namespace common {

struct Param;

}

namespace doubter {

struct Param;

}

namespace dubior {

struct Param;

}

namespace fattybuffer {

struct Param;

}

namespace gigantedge {

struct Param;

}

namespace whispy {

struct Param;

}

namespace kingsdoo {

struct Param;

}

namespace moundeath {

struct Param;

}

namespace watergalboros {

struct Param;

}

namespace zankibble {

struct Param;

}

namespace roah {

struct Param;

}

namespace landia {

struct Param;

}

namespace mahoroaroah {

struct Param;

}

namespace metalgeneral {

struct Param;

}

namespace hrd3 {

struct Param;

}

namespace galactaknight {

struct Param;

}

namespace lowper {

struct Param;

}

namespace grandlowper {

struct Param;

}

namespace goliath {

struct Param;

}

namespace mahoroabattle1 {

struct Param;

}

namespace mahoroabattle2 {

struct Param;

}

// TODO: members and the accessors of the other bosses.
class Param {
public:
    Param();
    // TODO: the destructor is a function of Boss.o in the map; whether it is declared is not known.
    ~Param();

    const roah::Param& roah() const;
    const landia::Param& landia() const;
    const bonkers::Param& bonkers() const;
    const doubter::Param& doubter() const;
    const dubior::Param& dubior() const;
    const fattybuffer::Param& fattybuffer() const;
    const whispy::Param& whispy() const;
    const gigantedge::Param& gigantedge() const;
    const kingsdoo::Param& kingsdoo() const;
    const moundeath::Param& moundeath() const;
    const watergalboros::Param& watergalboros() const;
    const zankibble::Param& zankibble() const;
    const common::Param& common() const;
    const mahoroaroah::Param& mahoroaroah() const;
    const metalgeneral::Param& metalgeneral() const;
    const hrd3::Param& hrd3() const;
    const galactaknight::Param& galactaknight() const;
    const lowper::Param& lowper() const;
    const grandlowper::Param& grandlowper() const;
    const goliath::Param& goliath() const;
    const mahoroabattle1::Param& mahoroabattle1() const;
    const mahoroabattle2::Param& mahoroabattle2() const;

private:
    // TODO: a bool at 0x0, then 23 file handles of 0x10 bytes, one per parameter file.
    u32 _0[0x174 / 4];
};

}
}
}

#endif
