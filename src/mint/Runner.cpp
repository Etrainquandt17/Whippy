#include "mint/Runner.h"

#include "mint/Engine.h"
#include "mintvm/MintFuncProxy.h"

namespace mint {

Runner::Runner(const Engine& engine) : mRunner(engine.core(), 0x80, 0) {}

Runner::~Runner() {}

void Runner::reset() {
    mRunner.reset();
}

void Runner::setEntryPoint(const char* name) {
    mRunner.setEntryPoint(name);
}

void Runner::execute() {
    mRunner.execute();
}

bool Runner::isRunning() const {
    return !mRunner.isEnd();
}

bool Runner::isEnd() const {
    return mRunner.isEnd();
}

void Runner::setArgS32(unsigned long index, long value) {
    mintvm::MintFuncProxy(mRunner.regset(), false).setArg_s32(index, value);
}

}
