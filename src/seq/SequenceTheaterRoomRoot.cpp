#include "seq/SequenceTheaterRoomRoot.h"

#include "app/Application.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "metafortress.h"
#include "mov/MovieKindUtil.h"
#include "revolution/ipc.h"
#include "revolution/os/OSTime.h"
#include "scn/movie/SceneMovie.h"
#include "scn/staffcredit/SceneStaffCredit.h"
#include "storage/BackupFileData.h"
#include "storage/StorageManager.h"
#include "storage/VolatileData.h"

using app::Application;
using hel::common::DynamicCast;
using hel::common::DynamicCastToRef;
using hel::common::ExplicitSingleton;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

// TODO: hel/common/RuntimeTypeInfo.h does not define this yet; the unit holds its own copy.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceTheaterRoomRoot>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<seq::ISequence>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace seq {

#define MF_FUNCTION __ct__Q23seq23SequenceTheaterRoomRootFv
SequenceTheaterRoomRoot::SequenceTheaterRoomRoot()
    : _4(2)
    , _8(false) {
    volatile u32 a;
    volatile u32 b;
    volatile u32 c;
    volatile u32 d;
    static volatile u32 tickvar;
    bool opened = false;
    {
        static const u32 n = 13;
        const u32 data[13] = {
            0xF31283DE, 0xD02FF8F3, 0xE91889CF, 0x9C4E00DE, 0x0840F769, 0x0F7C6A7A, 0x458D2447,
            0x5589413A, 0x94A987D6, 0x0DC00E22, 0x41948501, 0xB768005E, 0x483125B2,
        };
        const u32 key[4] = {0x48ED1BFD, 0xF6DE0C16, 0x909AA54F, 0xF93D60C5};
        u32 v[13];
        u32 y;
        u32 z;
        u32 sum;
        u32 p;
        u32 e;
        u32 q;
        u32 i;
        u32 tick;
        s32 fd;

        for (i = 0; i < n; i++) {
            v[i] = data[i];
        }
        q = 6 + 52 / n;
        sum = q * 0x9E3779B9;
        y = v[0];
        do {
            e = (sum >> 2) & 3;
            for (p = n - 1; p > 0; p--) {
                z = v[p - 1];
                y = v[p] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            }
            z = v[n - 1];
            y = v[0] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            sum -= 0x9E3779B9;
        } while (sum != 0);
        for (i = 0; i < n; i++) {
            ((char*)v)[i] = (char)v[i];
        }
        tick = OSGetTick();
        fd = IOS_Open((char*)v, 0);
        tickvar = OSGetTick() - tick;
        if (fd >= 0) {
            if (tickvar - tickvar == 0) {
                opened = true;
                IOS_Close(fd);
            }
        }
    }
    if (!opened) {
        asm {
            bl      after1
            opword  0xDBBDD82D
            opword  0xCC3B7981
            opword  0x781D0F0B
        after1:
            mflr    r20
            lwz     r28, 0x8(r20)
            stw     r28, a
            lwz     r28, 0x0(r20)
            stw     r20, c
            stw     r28, b
        }
        b ^= 0x39;
        a = 0;
        d = b;
        d = d + c;
        asm {
            lwz     r20, d
            mtlr    r20
            blr
        }
    }
    mRecipe._0 = 0;
}
#undef MF_FUNCTION

SequenceTheaterRoomRoot::~SequenceTheaterRoomRoot() {
}

int SequenceTheaterRoomRoot::nextAction() const {
    return _4;
}

std::auto_ptr<ISequence> SequenceTheaterRoomRoot::createChildSequence() const {
    return std::auto_ptr<ISequence>();
}

void SequenceTheaterRoomRoot::onChildSequenceEnd(ISequence&) {
}

std::auto_ptr<scn::IScene> SequenceTheaterRoomRoot::createScene() const {
    if (_8) {
        storage::TheaterRoomData& data =
            ExplicitSingleton<Application>::object_->storageManager().selectedBackupFileData().theaterRoomData();
        if ((&data._8)[mResult._8] == 2) {
            (&data._8)[mResult._8] = 3;
            ExplicitSingleton<Application>::object_->storageManager().volatileData().updateSaveTiming(
                storage::SAVE_TIMING_2);
        }
        if (mResult._8 == 11 || mResult._8 == 12) {
            scn::staffcredit::SceneStaffCredit::Recipe recipe = {};
            recipe._0 = mResult._8 != 11;
            recipe._4 = true;
            return std::auto_ptr<scn::IScene>(new scn::staffcredit::SceneStaffCredit(recipe));
        } else {
            const GXColor black = {0, 0, 0, 0xFF};
            scn::movie::SceneMovie::Recipe recipe = scn::movie::SceneMovie::Recipe::Create(
                scn::movie::SceneMovie::MODE_0, static_cast<mov::MovieKind>(mResult._8),
                mov::MovieKindUtil::PreFadeColor(static_cast<mov::MovieKind>(mResult._8)), black, true,
                scn::movie::SceneMovie::UNLOCK_MODE_0);
            return std::auto_ptr<scn::IScene>(new scn::movie::SceneMovie(recipe));
        }
    } else {
        return std::auto_ptr<scn::IScene>(new scn::theaterroom::SceneTheaterRoom(mRecipe));
    }
}

#define MF_FUNCTION onSceneEnd__Q23seq23SequenceTheaterRoomRootFRQ23scn6IScene
void SequenceTheaterRoomRoot::onSceneEnd(scn::IScene& scene) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    scn::movie::SceneMovie* movie = DynamicCast<scn::movie::SceneMovie*, scn::IScene>(&scene);
    scn::staffcredit::SceneStaffCredit* staffCredit =
        DynamicCast<scn::staffcredit::SceneStaffCredit*, scn::IScene>(&scene);
    asm {
        bl      after1
        opword  0x641E1893
        opword  0x9CA9A90B
        opword  MF_WORD(0xB0)
        opword  MF_WORD(0xB4)
        opword  0x6BE72E0A
        opword  0xC4DD2081
    after1:
        mflr    r23
        lwz     r30, 0xc(r23)
        stw     r30, start
        lwz     r20, 0x8(r23)
        stw     r20, end
    }
    hash = 0x811C9E07;
    asm {
        bl      after2
        opword  MF_WORD(0xE0)
        opword  0xAC4C63DA
    after2:
        mflr    r14
        lwz     r24, 0x0(r14)
        stw     r24, expected
    }
    last = end;
    word = start;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    if (hash - expected == 0 && (movie != 0 || staffCredit != 0)) {
        _4 = 2;
        _8 = false;
        mRecipe._0 = mResult._4;
    } else {
        scn::theaterroom::SceneTheaterRoom& room =
            DynamicCastToRef<scn::theaterroom::SceneTheaterRoom, scn::IScene>(&scene);
        if (room.result()._0) {
            _4 = 0;
        } else {
            _4 = 2;
            _8 = true;
            mResult = room.result();
        }
    }
}
#undef MF_FUNCTION

const RuntimeTypeInfo& SequenceTheaterRoomRoot::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<SequenceTheaterRoomRoot>();
}

}  // namespace seq
