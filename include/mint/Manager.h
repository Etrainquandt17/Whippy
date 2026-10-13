#ifndef MINT_MANAGER_H
#define MINT_MANAGER_H

#include "hel/common/PrivateSingleton.h"
#include "mint/Heap.h"
#include "mint/ScriptArchive.h"
#include "mintvm/MintSetting.h"

namespace mint {

class Manager : private hel::common::PrivateSingleton<Manager> {
public:
    Manager();
    ~Manager();

    const ScriptArchive& scriptArchive() const;

private:
    mintvm::MintSetting mSetting;
    Heap mHeap;
    ScriptArchive mArchive;
};

}  // namespace mint

#endif
