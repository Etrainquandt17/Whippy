#ifndef NAND_NANDMANAGER_H
#define NAND_NANDMANAGER_H

#include "types.h"

namespace nand {

class NandManager {
public:
    bool isOK();
    bool isBusy();
    bool isError();
    u32 getState();
    void saveData();
    void loadData();
    bool isDisable() const;
};

}  // namespace nand

#endif
