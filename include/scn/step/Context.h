#ifndef SCN_STEP_CONTEXT_H
#define SCN_STEP_CONTEXT_H

#include "scn/step/ContextChallenge.h"
#include "scn/step/ContextHero.h"
#include "scn/step/ContextMode.h"
#include "scn/step/map/Kind.h"
#include "types.h"

namespace scn {
namespace step {

class Context {
public:
    // The implicit assignment copies each of these as an object of its own (seq/SequenceStep.cpp), which
    // gives the boundaries. Two units still index _0 beyond its end to reach mChallenge.
    u32 _0[0xD6];
    ContextChallenge mChallenge;
    u32 _3E4[5];
    ContextHero mHero;
    u32 _50C[5];
    map::Kind mapKind;
    ContextMode _524;
    int _538;
    bool _53C;
    u32 _540[0x11];
    u32 _584[0x96];
};

}
}

#endif
