#ifndef METAFORTRESS_H
#define METAFORTRESS_H

// MetaFortress is the anti-tamper product this game was built with; see
// docs/metafortress.md. A protected function checksums another part of the
// program before it does its own work. The check is inline assembly, and the
// opword lines in it are data that the function jumps over.
//
// Most of that data is filler. The words a check reads (the bounds of what it
// sums, the sum it expects) were filled in after linking and differ in every
// version, so the build takes them from the disc: MF_WORD(offset) is the word at
// that offset from the start of MF_FUNCTION.
//
// On a mismatch most checks jump to MFortressDefaultResponseVariant_1. The others
// use the comparison where the game had a constant: `expected == hash` there
// stands for `true`, and a failed check makes the game misbehave instead.

#include "metafortress_words.h"

#define MF_PASTE_(function, offset) mf_##function##_##offset
#define MF_PASTE(function, offset) MF_PASTE_(function, offset)
#define MF_WORD(offset) MF_PASTE(MF_FUNCTION, offset)

#ifdef __cplusplus
extern "C" {
#endif

void MFortressDefaultResponseVariant_1(void);

#ifdef __cplusplus
}
#endif

#endif
