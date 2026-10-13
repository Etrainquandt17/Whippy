#include "mintvm/VMCore.h"

#include "mintvm/MintSystemCall.h"
#include "mintvm/Runner.h"
#include "mintvm/TmpSymbol.h"
#include "mintvm/VMModule.h"
#include "mintvm/VMTmpKey.h"
#include "mintvm/stdc.h"

namespace mintvm {

void N_Mint_Debug_Assert(MintFuncProxy& proxy);
void N_Mint_Debug_Assert_i(MintFuncProxy& proxy);
void N_Mint_Debug_Assert_f(MintFuncProxy& proxy);
void N_Mint_Debug_Assert_ft(MintFuncProxy& proxy);
void N_Mint_Debug_Test_i(MintFuncProxy& proxy);
void N_Mint_Debug_Test_f(MintFuncProxy& proxy);
void N_Mint_Debug_Test_ft(MintFuncProxy& proxy);
void N_Mint_Debug_Dump_i(MintFuncProxy& proxy);
void N_Mint_Debug_Dump_f(MintFuncProxy& proxy);
void N_Mint_Debug_print(MintFuncProxy& proxy);
void N_Mint_Debug_puts(MintFuncProxy& proxy);
void N_Mint_Debug_StackDump(MintFuncProxy& proxy);
void N_Mint_Cast_i2f(MintFuncProxy& proxy);
void N_Mint_Cast_f2i(MintFuncProxy& proxy);

VMCore::VMCore(unsigned int moduleMax)
    : mModules(allocator(), moduleMax) {
    mRunner = createRunner(0x80, 0);
    addStandardLib();
}

VMCore::~VMCore() {
    delete mRunner;
}

void VMCore::addScript(const void* script) {
    VMModule* module = new VMModule(script);
    mModules.add(module);
    registerSymbolMap(*module);
    callInitFunction(*module);
}

void VMCore::registerSymbolMap(VMModule& module) {
    for (unsigned int i = 0; i < module.objectTypeList().count(); i++) {
        VMObjectType* type = module.objectTypeList().objectType(i);
        mScriptModules.add(VMKey(type->path(), ""), &module);
        for (unsigned int j = 0; j < type->functionList().count(); j++) {
            VMFunction* function = type->functionList().function(j);
            mFunctions.add(VMKey(type->path(), function->name()), function);
        }
        for (unsigned int j = 0; j < type->variableList().count(); j++) {
            VMVariable* variable = type->variableList().variable(j);
            mVariables.add(VMKey(type->path(), variable->mName), variable);
        }
    }
}

void VMCore::callInitFunction(const VMModule& module) {
    for (unsigned int i = 0; i < module.objectTypeList().count(); i++) {
        TmpSymbol symbol(module.objectTypeList().objectType(i)->path(), ".", "__Init()");
        mRunner->execute(symbol.c_str());
    }
}

void VMCore::addStandardLib() {
    addNativeFunction("Mint.Debug", "void Assert(bool)", N_Mint_Debug_Assert);
    addNativeFunction("Mint.Debug", "void AssertEq(int,int)", N_Mint_Debug_Assert_i);
    addNativeFunction("Mint.Debug", "void AssertEq(float,float)", N_Mint_Debug_Assert_f);
    addNativeFunction("Mint.Debug", "void AssertEq(float,float,float)", N_Mint_Debug_Assert_ft);
    addNativeFunction("Mint.Debug", "void TestEq(int,int)", N_Mint_Debug_Test_i);
    addNativeFunction("Mint.Debug", "void TestEq(float,float)", N_Mint_Debug_Test_f);
    addNativeFunction("Mint.Debug", "void TestEq(float,float,float)", N_Mint_Debug_Test_ft);
    addNativeFunction("Mint.Debug", "void Dump(int)", N_Mint_Debug_Dump_i);
    addNativeFunction("Mint.Debug", "void Dump(float)", N_Mint_Debug_Dump_f);
    addNativeFunction("Mint.Debug", "void print(string)", N_Mint_Debug_print);
    addNativeFunction("Mint.Debug", "void puts(string)", N_Mint_Debug_puts);
    addNativeFunction("Mint.Debug", "void StackDump()", N_Mint_Debug_StackDump);
    addNativeFunction("Mint.Cast", "void i2f(int)", N_Mint_Cast_i2f);
    addNativeFunction("Mint.Cast", "void f2i(float)", N_Mint_Cast_f2i);
}

VMVariable* VMCore::findVariable(const char* name) const {
    VMTmpKey key(name);
    VMVariable* variable = mVariables.find(key);
    if (variable != 0) {
        return variable;
    }
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Not Found Variable Symbol", name);
    return 0;
}

bool VMCore::isBuiltInType(const char* type) {
    static const char* table[] = {"bool", "int", "float", "string"};
    for (u32 i = 0; i < 4; i++) {
        if (strcmp(type, table[i]) == 0) {
            return true;
        }
    }
    return false;
}

u32 VMCore::sizeOf(const char* type) const {
    if (isBuiltInType(type)) {
        return 4;
    }
    VMKey key(type, "");
    u32 size = mNativeSizes.find(key);
    if (size != 0xFFFFFFFF) {
        return size;
    }
    VMModule* module = mScriptModules.find(key);
    if (module != 0) {
        return module->objectTypeList().sizeOf(*this, type);
    }
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Not Found VMCore::sizeOf", type);
    return 0;
}

u32 VMCore::offsetOf(const char* name) const {
    VMTmpKey key(name);
    u32 offset = mNativeSizes.find(key);
    if (offset != 0xFFFFFFFF) {
        return offset;
    }
    VMModule* module = mScriptModules.find(key.moduleKey());
    if (module != 0) {
        return module->objectTypeList().offsetOf(*this, key);
    }
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Not Found VMCore::offsetOf", name);
    return 0;
}

VMFunction* VMCore::findFunction(const char* name, const VMModule** module) const {
    VMTmpKey key(name);
    if (TmpSymbol::find(name, '(') == -1) {
        key = VMTmpKey(TmpSymbol(name, "()").c_str());
    }
    VMFunction* function = findFunctionIN(key);
    if (function != 0) {
        if (module != 0) {
            if (function->isMint()) {
                *module = mScriptModules.find(key.moduleKey());
            } else {
                *module = 0;
            }
        }
        return function;
    }
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Not Found Function Symbol", TmpSymbol("ns   : ", key.ns(), "\n* name : ", key.name()).c_str());
    return 0;
}

VMFunction* VMCore::findFunctionIN(const VMKey& key) const {
    VMFunction* function = mFunctions.find(key);
    if (function != 0) {
        return function;
    }
    return 0;
}

Runner* VMCore::createRunner(unsigned long stackSize, IAllocator* allocator) const {
    return new Runner(*this, stackSize, allocator);
}

void VMCore::addNativeFunction(const char* module, const char* declaration, void (*function)(MintFuncProxy&)) {
    VMModule* native = findNativeModule(module);
    if (native == 0) {
        native = new VMModule(module);
        mModules.add(native);
        mNativeModules.add(VMKey(module, ""), native);
    }
    addNativeFunctionIN(native, module, declaration, function);
}

void VMCore::addNativePod(const char* type, unsigned long size) {
    MINT_ASSERT("VMCore.cpp", 313, !findNativeModule(type));
    VMModule* native = new VMModule(type);
    mModules.add(native);
    mNativeModules.add(VMKey(type, ""), native);
    mNativeSizes.add(VMKey(type, ""), size);
}

void VMCore::addNativePod_Property(const char* type, const char* name, unsigned long offset) {
    findNativeModuleMust(type);
    mNativeSizes.add(VMKey(type, name), offset);
}

void VMCore::addNativePod_Method(const char* type, const char* declaration, void (*function)(MintFuncProxy&)) {
    addNativeFunctionIN(findNativeModuleMust(type), type, declaration, function);
}

void VMCore::addNativeFunctionIN(VMModule* module, const char* ns, const char* declaration, void (*function)(MintFuncProxy&)) {
    VMKey key(ns, declaration);
    chkSpellMiss(key);
    if (mFunctions.find(key) != 0) {
        // "A function of the same name was registered twice."
        MintSystemCall::messageHandler(MINT_MSG_ERROR, "\x93\xAF\x82\xB6\x96\xBC\x91\x4F\x82\xCC\x8A\xD6\x90\x94\x82\xAA\x93\xF1\x89\xF1\x93\x6F\x98\x5E\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42", key.tmpSymbol().c_str());
    }
    VMFunction* added = module->objectTypeList().objectType(0)->functionList().addNativeFunction(declaration, function);
    mFunctions.add(key, added);
}

void VMCore::chkSpellMiss(const VMKey& key) const {
    TmpSymbol symbol = key.tmpSymbol();
    if (TmpSymbol::find(symbol.c_str(), '*') != -1) {
        // "An asterisk ('*') has got in"
        MintSystemCall::messageHandler(MINT_MSG_ERROR, "VMCore::addNativeFunction", TmpSymbol("\x83\x41\x83\x58\x83\x5E\x83\x8A\x83\x58\x83\x4E\x28\x27\x2A\x27\x29\x82\xAA\x8D\xAC\x93\xFC\x82\xB5\x82\xC4\x82\xA2\x82\xDC\x82\xB7\x0A\x2A\x20", symbol.c_str()).c_str());
    }
    if (TmpSymbol::find(symbol.c_str(), '(') == -1) {
        // "There is no left parenthesis ('(')"
        MintSystemCall::messageHandler(MINT_MSG_ERROR, "VMCore::addNativeFunction", TmpSymbol("\x8D\xB6\x8A\x87\x8C\xCA\x28\x27\x28\x27\x29\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x0A\x2A\x20", symbol.c_str()).c_str());
    }
    if (TmpSymbol::find(symbol.c_str(), ')') == -1) {
        // "There is no right parenthesis (')')"
        MintSystemCall::messageHandler(MINT_MSG_ERROR, "VMCore::addNativeFunction", TmpSymbol("\x89\x45\x8A\x87\x8C\xCA\x28\x27\x29\x27\x29\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x0A\x2A\x20", symbol.c_str()).c_str());
    }
}

VMModule* VMCore::findNativeModule(const char* name) {
    VMKey key(name, "");
    return mNativeModules.find(key);
}

VMModule* VMCore::findNativeModuleMust(const char* name) {
    VMModule* module = findNativeModule(name);
    MINT_ASSERT_MSG("VMCore.cpp", 424, module, "Not found %s\n", name);
    return module;
}

}
