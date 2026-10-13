#ifndef MINTVM_VMCORE_H
#define MINTVM_VMCORE_H

#include "mintvm/IAllocator.h"
#include "mintvm/MPtrArray.h"
#include "mintvm/VMFunction.h"
#include "mintvm/VMKey.h"
#include "mintvm/VMMap.h"
#include "mintvm/VMModule.h"
#include "mintvm/VMObject.h"
#include "mintvm/VMVariable.h"
#include "types.h"

namespace mintvm {

class MintFuncProxy;
class Runner;

class VMCore : public VMObject {
public:
    explicit VMCore(unsigned int moduleMax);
    virtual ~VMCore();

    void addScript(const void* script);
    void registerSymbolMap(VMModule& module);
    void callInitFunction(const VMModule& module);
    void addStandardLib();

    VMVariable* findVariable(const char* name) const;
    static bool isBuiltInType(const char* type);
    u32 sizeOf(const char* type) const;
    u32 offsetOf(const char* name) const;
    VMFunction* findFunction(const char* name, const VMModule** module) const;
    VMFunction* findFunctionIN(const VMKey& key) const;
    Runner* createRunner(unsigned long stackSize, IAllocator* allocator) const;

    void addNativeFunction(const char* module, const char* declaration, void (*function)(MintFuncProxy&));
    void addNativePod(const char* type, unsigned long size);
    void addNativePod_Property(const char* type, const char* name, unsigned long offset);
    void addNativePod_Method(const char* type, const char* declaration, void (*function)(MintFuncProxy&));
    void addNativeFunctionIN(VMModule* module, const char* ns, const char* declaration, void (*function)(MintFuncProxy&));
    void chkSpellMiss(const VMKey& key) const;
    VMModule* findNativeModule(const char* name);
    VMModule* findNativeModuleMust(const char* name);

private:
    MPtrArray<VMModule> mModules;
    VMMapPtr<VMModule> mScriptModules;
    VMMapPtr<VMModule> mNativeModules;
    VMMapPtr<VMFunction> mFunctions;
    VMMapPtr<VMVariable> mVariables;
    // Sizes of native types by name, and offsets of their properties.
    VMMap<unsigned long, 0xFFFFFFFF> mNativeSizes;
    Runner* mRunner;
};

}

#endif
