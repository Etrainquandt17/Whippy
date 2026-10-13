#ifndef SEQ_SEQUENCEWMAPROOT_H
#define SEQ_SEQUENCEWMAPROOT_H

#include "file/FileClearDisableScope.h"
#include "scn/step/ContextMode.h"
#include "scn/step/LevelKind.h"
#include "scn/wmap/ItemKind.h"
#include "seq/ContextStory.h"
#include "seq/ISequence.h"
#include "types.h"

namespace seq {

class SequenceWMapRoot : public ISequence {
public:
    enum Mode {
        MODE_WMAP,
        MODE_LVMAP,
        MODE_SHIPMAP,
        MODE_3,
    };

    // TODO: name the values of both.
    enum ItemKind {
        ITEM_KIND_0,
    };

    enum InterruptKind {
        INTERRUPT_KIND_0,
        INTERRUPT_KIND_1,
    };

    class Recipe {
    public:
        static Recipe Create(const ContextStory& context, ItemKind item, InterruptKind interrupt, bool flag);

        ContextStory mContext;
        ItemKind mItemKind;
        InterruptKind mInterruptKind;
        bool _488;
    };

    struct Result {
        int _0;
        ContextStory mContext;
    };

    SequenceWMapRoot(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SequenceWMapRoot();
    virtual int nextAction() const;
    virtual std::auto_ptr<ISequence> createChildSequence() const;
    virtual void onChildSequenceEnd(ISequence& child);
    virtual std::auto_ptr<scn::IScene> createScene() const;
    virtual void onSceneEnd(scn::IScene& scene);

    void onChildSequenceEndForLvMap(ISequence& child);
    void onChildSequenceEndForShipMap(ISequence& child);
    void onSceneEndForWMap(scn::IScene& scene);
    Result result() const;
    void mfSetupClearDemo();
    void mfSetupClearDemoConnectToRepair();
    void mfSetupClearDemoConnectToLandiaInfo();

private:
    file::FileClearDisableScope mFileClearDisableScope;
    ItemKind _8;
    InterruptKind mInterruptKind;
    ContextStory mContext;
    scn::step::ContextMode mContextMode;
    scn::step::LevelKind mLevelKind;
    scn::wmap::ItemKind mItemKind;
    bool _4AC;
    Mode mMode;
    Result mResult;
};

}  // namespace seq

#endif
