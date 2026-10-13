#ifndef MINT_RUNNER_H
#define MINT_RUNNER_H

#include "mintvm/Runner.h"
#include "types.h"

namespace mint {

class Engine;

class Runner {
public:
    Runner(const Engine& engine);
    ~Runner();

    void reset();
    void setEntryPoint(const char* name);
    void execute();
    bool isRunning() const;
    bool isEnd() const;
    void setArgS32(unsigned long index, long value);

private:
    mintvm::Runner mRunner;
};

}  // namespace mint

#endif
