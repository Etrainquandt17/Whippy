#ifndef SCN_TITLEMENUNEW_SCENETITLEMENU_H
#define SCN_TITLEMENUNEW_SCENETITLEMENU_H

#include "scn/IScene.h"
#include "seq/EntryInfo.h"
#include "types.h"

namespace scn {
namespace titlemenunew {

class SceneTitleMenu : public IScene {
public:
    struct Recipe {
        u32 _0;
        int _4;
        bool _8;
        seq::EntryInfo mEntryInfo;
    };

    struct Result {
        int _0;
        int _4;
        int _8;
        bool _C;
    };

    SceneTitleMenu(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneTitleMenu();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4[0xB2D];
};

}}  // namespace scn::titlemenunew

#endif
