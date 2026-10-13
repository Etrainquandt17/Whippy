#ifndef MINTVM_MINTASSERT_H
#define MINTVM_MINTASSERT_H

namespace mintvm {

namespace MintSystemCall {

void panic(const char* file, int line, const char* message, ...);

}

}

// The file and line are written out because the originals were .hpp files with another layout.
#define MINT_ASSERT_MSG(file, line, cond, ...) \
    if (!(cond)) \
        mintvm::MintSystemCall::panic(file, line, __VA_ARGS__)

#define MINT_ASSERT(file, line, cond) MINT_ASSERT_MSG(file, line, cond, "Assertion failed.\n")

#endif
