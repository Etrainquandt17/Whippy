#ifndef MINT_ENGINE_H
#define MINT_ENGINE_H

#include "hel/common/NonCopyable.h"
#include "mintvm/VMCore.h"

namespace mint {

class Manager;

class Engine : private hel::common::NonCopyable {
public:
    explicit Engine(Manager& manager);
    ~Engine();

    void addModuleBellow(const char* name);
    const mintvm::VMCore& core() const;

private:
    Manager& mManager;
    mintvm::VMCore mCore;
};

}  // namespace mint

#endif
