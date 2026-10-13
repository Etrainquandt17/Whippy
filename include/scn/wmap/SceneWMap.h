#ifndef SCN_WMAP_SCENEWMAP_H
#define SCN_WMAP_SCENEWMAP_H

#include "scn/IScene.h"
#include "scn/step/ContextHero.h"
#include "scn/step/LevelKind.h"
#include "scn/wmap/ItemKind.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace scn {
namespace wmap {

class SceneWMap : public IScene {
public:
    class Recipe {
    public:
        static Recipe Create(storage::StoryMode mode, step::ContextHero hero, ItemKind item);

    private:
        u32 _0[0x47];
    };

    struct Result {
        int _0;
        ItemKind mItemKind;
        step::LevelKind mLevelKind;
        storage::StoryMode mStoryMode;
        step::ContextHero mHero;
    };

    SceneWMap(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneWMap();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u8 _4[0x32E4];
};

}}  // namespace scn::wmap

#endif
