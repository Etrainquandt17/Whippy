#include "metafortress.h"

// MetaFortress is the anti-tamper product this game was built with. About 1,300
// functions checksum the rest of the program while it runs, and most of them
// jump here when a checksum is wrong. See docs/metafortress.md.
void MFortressDefaultResponseVariant_1(void) {
    for (;;) {
    }
}

// Never read by the game. It differs between versions, so it was most likely
// filled in after linking, like the checksums.
unsigned long MFortressDefaultResponseVariant_1_0x0897f0fd_ResponseFnPtr_mfort6317_[3] = {
#if defined(VERSION_SUKE01)
    0xA0E17816, 0x46A03C97, 0x541348A3,
#elif defined(VERSION_SUKK01)
    0x788701B3, 0x244E3848, 0x32068EB1,
#endif
};

// TODO: the original object also had MFortressDiagnosticResponse (0xD4 bytes).
// The linker dropped it as unused, so its code is not on the disc.
