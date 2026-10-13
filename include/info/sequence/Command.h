#ifndef INFO_SEQUENCE_COMMAND_H
#define INFO_SEQUENCE_COMMAND_H

#include "types.h"

namespace info {
namespace sequence {

class Command {
public:
    Command() : mIsFinished(false) {}
    virtual ~Command() {}
    virtual void start() {}
    virtual void proc() {}

    void reset() { mIsFinished = false; }
    void finish() { mIsFinished = true; }
    bool isFinished() const { return mIsFinished; }

private:
    bool mIsFinished;
};

}}  // namespace info::sequence

#endif
