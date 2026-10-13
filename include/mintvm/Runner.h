#ifndef MINTVM_RUNNER_H
#define MINTVM_RUNNER_H

#include "mintvm/IAllocator.h"
#include "mintvm/MArray.h"
#include "mintvm/MintAssert.h"
#include "mintvm/RNObject.h"
#include "mintvm/Regset.h"
#include "types.h"

namespace mintvm {

class VMCore;
class VMModule;

class Runner : public RNObject {
public:
    Runner(const VMCore& core, unsigned long stackSize, IAllocator* allocator);

    virtual ~Runner() {}

    void setEntryPoint(const char* name);
    void reset();
    void execute();
    void execute(const char* name);
    bool isEnd() const;
    void call(const char* name);

    const VMModule* currentModule() const {
        return mModules[mModuleCount - 1];
    }

    void pushModule(const VMModule* module) {
        mModules[mModuleCount++] = module;
    }

    void popModule() {
        MINT_ASSERT("Runner.hpp", 102, mModuleCount != 0);
        mModuleCount--;
    }

    Regset& regset() {
        return mRegset;
    }

private:
    // TODO: the names of these two are guesses; execute() expands each of them once.
    unsigned long constant(unsigned short offset) const;
    const void* constantAddress(unsigned short offset) const;

    const VMCore& mCore;
    MArray<const VMModule*> mModules;
    u32 mModuleCount;
    Regset mRegset;
};

}  // namespace mintvm

#endif
