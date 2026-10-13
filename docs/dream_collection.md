# Engine Code From Kirby's Dream Collection
Kirby's Dream Collection (Wii, 2012) was built on this game's engine, and its decompilation, [kdc](https://github.com/Swiftshine/kdc) (CC0-1.0, commit `e5bd14dcb01`), has 111 source files for classes this game has too. Those are in `src/donut` (`app`, `file`, `font`, `g3d`, `gfx`, `gobj`, `hid`, `mem`, `msg`, `scn`, `util`, ...) and `src/hel` (`common`, `geo`, `math`). Where one of them compiles to this game's code, we brought it in under this project's names and conventions (headers as `.h` under `include/`, existing classes extended, comments cut down).

## What Came From There
85 units, and all of them are linked:

- `Main`
- `app/`: `Locale`, `Message`, `Random`, `RomFontWrapper`
- `file/`: `FileAccessor`, `FileClearDisableScope`, `FileLoader`, `FileManager`
- `font/`: `Font`, `FontKindUtil`, `FontLoader`, `FontManager`
- `g3d/`: `AutoReqAnimReqInfo`, `CameraAccessor`, `FogAccessor`, `LightSetAccessor`, `ModelAnimContext`, `ModelBufferOption`, `ModelContext`, `ModelMultiAnimContext`, `NodeLocalMtx`, `NodeLocalMtxAccessor`, `ResFile`, `ResModel`, `ResModelContext`, `ResNode`, `RootContext`
- `gfx/`: `FullScreenPlate`, `GXFifoMemoryManager`, `GXFifoProtectCanceler`, `GameScreen`, `RenderSetting`, `TPLTexture`, `TPLTexturePlate`, `TexBuffer`, `VISetting`, `XFBManager`
- `gobj/`: `FootState`, `MoveParamAccel`
- `hel/`: `common/Color`, `geo/Rect`, `math/Direction3`, `math/Matrix34`, `math/Matrix44`, `math/Point2`, `math/Random`, `math/Vector2`, `math/Vector3`
- `hid/`: `Accel`, `Button`, `DPD`, `LibInitializer`, `RumbleResource`, `SimpleGCHID`, `Stick`
- `mem/`: `AutoHeapExp`, `DataBlock`, `GlobalNewDeleteChanger`, `HeapCompactionNode`, `HeapCompactionNodeHandle`, `HeapExp`, `MemBlock`, `OperatorNewDelete`
- `msg/`: `Message`, `Project`
- `scn/step/`: `GridPos`, `boss/IState`, `chara/Invincible`, `enemy/CustomBase`, `enemy/Desc`, `enemy/StateBase`, `enemy/SuperStop`, `enemy/waddledoo/Custom`, `hero/Guard`, `hero/IndiviUtil`, `spstop/Manager`
- `util/`: `Alarm`, `AnimController`, `CharacterEncodeUtil`, `CurveUtility`, `FrameCounter`, `Mutex`, `StateChanger`, `Thread`

`mem/HeapExp` waited a day for `info/sequence/Sequence.cpp`, as one of its destructors is a branch to a look-alike there, and the link only folds the two when both are compiled from source (see [Code Merging](code_merging.md)).

## What Was Different
Very few files went in as they were. The two games differ, and this game's disassembly decided every time.

- This game protects functions that Dream Collection's source has plain. `Mutex`, `Thread`, `Alarm`, `AnimController`, `RomFontWrapper`, `Font`, `FontLoader` and `LibInitializer` all carry MetaFortress checks here.
- `app::Locale`, `app::Message`, `font::FontKindUtil` and `font::FontManager` hold this game's data and differ between its versions.
- `Matrix34` and `Matrix44` `Create...` and `MoveParamAccel::Create` and `Zero` are static and return by value here. The non-static `void` versions in their source were a matching device.
- `GXFifoMemoryManager` has no mutex and is 0x10 bytes, and `GXFifoProtectCanceler` is a `PrivateSingleton`.
- `Thread`, `StateChangerBase`, `FileClearDisableScope` and every `ExplicitSingleton<T>` are `NonCopyable`.
- `enemy::Desc` is 0x30 bytes with one constructor, and `hid::Stick` has no `normalized()`.
- Their notes on which functions the linker folded are right, but the look-alikes have other names here. The map decides.
- Their flags (`-O3 -inline noauto`) aren't this game's. Every unit matched with the game's own flags, with one stand-in. `IndiviUtil::CanHover` calls two helpers that have a single caller each, and only `#pragma dont_inline` reproduces that.
- Several units have functions here that theirs lacks or leaves undone, which are `HeapExp`, `FontManager`, `IndiviUtil`, `spstop/Manager`, `SuperStop`, `waddledoo/Custom`, `Direction3` and `LibInitializer`.
- `mem::HeapExp` derives from `mem::IHeap`, a class between it and `mem::IAllocator` that their headers don't have.
- `hel::common::ExplicitSingleton<T>` has an empty constructor and destructor. Each singleton stores itself in its own constructor body and clears the pointer first in its own destructor body (12 classes checked).
- `hel::common::FixedString<N>` derives from `FixedStringIN<char, N>`, and `Array::operator[]` always checks its index.
- This game's `nw4r::g3d` accessors assert, so the game-side declarations in `include/nw4r/g3d` carry the assertions with the library's file names and line numbers.

## Not Used Yet
13 of their files have a unit here and aren't written:

- `ocoll/Gimmick`, `seq/SequenceLvMapRoot`
- `g3d/`: `MaterialAccessor`, `ResFileAccessor`, `ResFileRepository`
- `gfx/`: `EFBToLetterBox`, `EasyRender3D`, `Utility`
- `scn/step/`: `Component`, `enemy/Enemy`, `enemy/Param`, `enemy/damage/StateDeadInWater`, `enemy/waddledoo/ModelDesc`

4 of their files aren't in this game at all (`scn/step/block/BlockInfo` and the 3 under `scn/vc`), and 5 hold only functions the link folded away, so they have no unit.

### What's in the way
Game code is compiled with `include/` only and can't reach the library headers under `libs/`. What it needs of the SDK and of `nw4r` is declared by hand under `include/revolution` and `include/nw4r`. The `g3d` basics (camera, fog, light, state, `ResFile`, `ResMdl`, `ResNode`) and the GX prototypes are there now. The rest isn't:

- `g3d/ResFileAccessor` needs `ResAnmAutoReq` and 7 of `nw4r`'s `ResAnm...` classes, and `ResFileRepository` builds on it.
- `g3d/MaterialAccessor` needs `ScnMdl::CopiedMatAccess` and parts of `ResMat`.
- The 3 `gfx` files need the `nrel::ezrender` classes (`GXSettingFor2D`, `OrthoCameraSetting`), and a `RoundUp<unsigned short>` that comes from an unnamed namespace in a precompiled header.

`ocoll/Gimmick` is missing because their source has no `chkCollide`. `seq/SequenceLvMapRoot` (34 functions), `scn/step/Component` (115), `enemy/Enemy` (99) and `enemy/Param` (105) are stubs in their source, so they're just ordinary decompilation here.

## Known Issues
### Two functions in `hel/math/Vector3.cpp` aren't verified
`getVertical` and `projection` were written from their names and sizes in the link map, as the original link dropped what would verify them. Without them the compiler expands 3 small functions that the original calls.
### `hel::math::Matrix44(const MTX44&)` is marked never-inline in its header
The original keeps the calls to it. We don't know why this compiler expands them.
### `hel::math::Direction3`'s three-vector constructor has a macro to choose its form
It's an ordinary function of `Direction3.cpp` by its place in the unit, however 3 linked enemy units only match with it inline. `HEL_MATH_DIRECTION3_CONSTRUCTOR_OUT_OF_LINE` chooses, and it's a stand-in because linked units depend on the header as it is.
### `g3d::StdModelContext` has assumed constructor arguments
It derives from `g3d::ModelContext` now, with constructor arguments that are assumed, and `ModelContext.h` still has the conversion operator from before.
### Some functions sit behind opt-in macros
Functions that the original expands in one unit and calls in another sit behind opt-in macros (`mem::MemBlock`'s assignment, the `Matrix34` constructor, `nw4r::g3d::ResFile`'s constructor). [Decompiling](decompiling.md) lists them.
