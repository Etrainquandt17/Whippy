# Object Classes: Enemies, Bosses, Weapons and Heroes
Most of the game's own code is the classes of its characters. Every enemy, boss, weapon (anything a character shoots, throws or swings) and copy ability has a directory under `scn/step/`, with one small class per unit. That's a state per behavior, and a few classes that set the character up. About half of the game units that don't have a source yet are of this kind.

The good news is that they're regular. Once a directory's class headers are right, most of its units match on the first compile, and the second state of a directory is mostly the first one again. This page says what each kind of class looks like in source, what order to write a directory in, and which names the disassembly shows for the functions these classes call.

Read [Decompiling](decompiling.md) first for the tools, and [Code Merging](code_merging.md) for why a call in the disassembly names an unrelated function.

## Finding the Work
```sh
python tools/unwritten.py scn/step/enemy/        # every unit without a source under a path, smallest first
python tools/unwritten.py scn/step/boss/goliath/
```

Each line is the unit's code size, its number of functions and its path. The size is what the original link left, so `scn/step/enemy/waddledoo/BrainWalkStraight` has 4 functions and 72 bytes, because 3 of them are branches into other classes.

These are finished directories you can read beside this page:

| Family | Read |
|---|---|
| enemy | `src/scn/step/enemy/starman/` and `como/` (whole enemies), `common/` (the brains and states every enemy shares), `damage/` (the sixteen damage states) |
| boss | `src/scn/step/boss/bonkers/` and `fattybuffer/`, `common/` |
| weapon | `src/scn/step/weapon/sparkshotlv1/`, `lowpersparkshot/`, `mahoroawarphole/`, and the base units `StateBase.cpp`, `CustomBase.cpp`, `StateNormal.cpp` |
| hero | `src/scn/step/hero/common/StateAirJump.cpp`, `StateCarryItemCatch.cpp`, `StateWakeUp.cpp`, `StateSuperJump.cpp` |

## A Directory, Step by Step
1. List its units, and read the directory's `AddOnMint.cpp`. It's linked already, and it names the states and their constructor arguments. The headers beside it under `include/` declare some of the classes, see "Stand-in Headers" below.
2. Write all of the class headers first, from `AddOnMint.cpp` and the constructors' symbols.
3. Write the units in this order:
   - enemy: `CharaParam`, `ModelDesc`, `Custom`, the brains, the states from the small end, helper classes last.
   - boss: the small states, `ModelDesc`, the larger states, the controllers, `Custom` last.
   - weapon: `ModelDesc`, `Custom`, the states from small to large.
   - hero: the states from the small end.
4. For one unit, `grep -n "<Unit>.o" orig/SUKE01/files/iuk.MAP` gives its functions and data in link order with sizes, and `UNUSED` lines for what the link dropped. Several objects share a file name (`BrainWalkStraight.o` exists in `common`, in `waddledoo` and elsewhere), so tell them apart by address, which is in the first lines of the unit's `.s` file. Compare with `python tools/compare.py all src/<unit>.cpp` until the unit is complete. Always compare both versions, as effect numbers from 0x61D up are one higher in the Korean build (a file-scope `const effect::Kind` under `#ifdef VERSION_SUKK01` serves both), and a few units have more code there (`boss/metalgeneral/DamageInfoCtrl` groups digits by region in the Korean build only).
5. When the directory is done, run `python tools/link_complete.py src/<directory>`. It link-tests every complete unit, un-exports the look-alikes that units with branches need, and marks the good ones `Matching` in `configure.py`. After that, `python tools/check_all.py` builds both versions. To test by hand, `python tools/linktest.py SUKE01 -u <unit> -u <unit> ... --out <dir>` links the named units from source, at most about 20 at a time (a test with 30 once ended without output). It's only meaningful for units without branches.
6. After replacing a header that existed before, compare the directory's `AddOnMint.cpp` and the family's `CustomFactory.cpp` again. Both are linked and have to stay complete.

Don't spend long on one function. Leave its closest form with a `// TODO:` line that says what differs, and go on, as the next 10 units are likely to match at once.

## Stand-in Headers
Earlier work on the script bindings left a header for many classes that had no source yet, which is a state declared as `: public IState` with a constructor, or a `Custom` padded to its size (`u32 _8[N]`). They were good enough to compile `AddOnMint.cpp` and the factories, however pretty much all of them are wrong in detail:

- The base of a state is `StateBase`, not `IState`.
- Most declare `virtual ~X()`, and whether a class declares its destructor has to be read from the unit (see "States").
- Counters declared `int` are `u32` (`cmplw`, and an int-to-float conversion without `xoris`).

Replace the stand-in with the real class when you write the unit. A `Custom` has to keep its size, because `CustomFactory.cpp` builds every `Custom` of the family and stops matching when one is wrong. Some directories hold their stand-ins in one `States.h`, so move a class out of it when it gets its own header.

A state that isn't written yet only needs a header with its constructor in order to be set by another state.

## Folding Between Directories
These classes are full of functions with identical code, and the original link folded them ([Code Merging](code_merging.md)). 568 functions in the game are branches into the classes of `scn/step/enemy/common` alone.

- A function that's a single `b other` in the original has a body in the source, which is the look-alike's, with this class's names. `compare.py` reports it as replaced by a branch when the compiled size is the one the map gives. `grep "<Class>" orig/SUKE01/files/iuk.MAP | grep "replaced by a branch"` lists a class's branches and where they go.
- A unit with a branch links once its look-alike is un-exported in `symbols.txt`. `tools/link_complete.py` does that by itself, so a destructor that's a branch links before the unit of its target has a source. That's not true for most other branches. The linker only folds a compiled function into an un-exported original when both call their functions by the same names, and a body that calls `obj()` or anything else the link folded doesn't ([Code Merging](code_merging.md) explains why). A unit like that is complete and, as far as we can tell, waits until its target's unit is written from source too. The 4 super abilities besides Super Sword don't link while `supersword::SuperSword` is unfinished, and `cutter::StateCutterDrop` doesn't while `captured::StateCapturedMahoroaBlackHoleVomit` has no source. So it does pay to write the targets in the branch table below early. A plain `linktest.py` run un-exports nothing. With a branch whose target isn't compiled from source in the same test, everything behind the first unfolded function shifts. The first difference is then at `_rom_copy_info` or `__init_registers`, with some 600,000 words differing, and `--map` names the function. That's this case and not a wrong unit.
- Check which function the map says a branch goes to before you write its body. Two functions can have the same bytes and still be kept apart by the original link, because they call differently named functions with the same code (`obj()` and `objPtr()` for example). `sword::StateSwordAttackFinish::procFixPos` and `common::StateGuard::procFixPos` are a pair like that, 14 functions are branches into the first one and none into the second. If you write one of those 14 with `objPtr()` like `StateGuard` has it, the linker folds it into `StateGuard`'s and the unit can't link, even though `compare.py` calls it complete. With `setNextState<common::StateFall, Hero*>(&obj())` it links.
- A one-line getter or setter that the link folded or dropped is still a real function of its class's source. The map's `Code folded in file: <Unit>.o` list and its `UNUSED` lines name them. Define all of them, in order, or the unit emits other code than the original.
- A member the link removed can stay without a body where nothing in the unit needs it, as the linker script maps its name (`barracu/Custom::mfMapCheckPoint`).

These are the bodies behind the most common branches:

| Family | Function | Body | The Branch Goes To |
|---|---|---|---|
| enemy | state destructor | `{}` | `common::StateFall`'s |
| enemy | brain destructor | implicit | `common::BrainFlushPursuit`'s |
| enemy | brain `onRecover` (16 bytes) | `return onStart();` | |
| boss | state destructor | `{}` | `bonkers::StateBomb`'s |
| boss | `procFixPos` | `common::StateFall::TryToChangeState(objPtr());` | `bonkers::StateBomb::procFixPos` |
| boss | `procMove` | `obj().move().groundDecel(obj().param().<boss>().<decel>);` | the boss's own `StateAnger::procMove` (fattybuffer, doubter) |
| boss | `procAnim` | `if (obj().model().isAllEnd()) obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());` | `bonkers::StateSwingEnd::procAnim` |
| boss | `Custom::onDamage` | `obj().model().shake().request(4);` | bonkers', in 12 bosses |
| boss | `Custom::onAppear` | `obj().shadow().setVisibility(true);` | `dubior::Custom::onAppear` |
| weapon | state destructor | `{}` | `StateNormal`'s |
| weapon | `procMove` | `obj().move().decel(gobj::MoveParamDecel::Zero());` | `kingsdoowaveshot::StateMain::procMove` |
| weapon | `procMove` | `const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero(); const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero(); obj().move().airDecelFall(decel, fall);` | `starshotlv1::StateMain::procMove` |
| weapon | `procFixPos` | `if (obj().mapColl().isHit()) obj().dead();` | `StateNormal::procFixPos` |
| weapon | `procFixPos` | `if (obj().mapColl().result().isDead()) obj().dead();` | `waterbigwave::StateMain::procFixPos` |
| weapon | `procAnim` | `mLifetime.update(); if (mLifetime.isDead()) obj().dead();` | `lowpersparkshot::StateMain::procAnim` |
| weapon | `Custom` destructor | implicit | the `CustomSimple<mahoroawarpholemagicball::StateMain>` destructor in `CustomFactory` |
| hero | state destructor | `{}` | `common::StateAirJump`'s |
| hero | `procMove` | `Utility::MoveDefaultBrake(obj());` | `common::StateCarryItemCatch::procMove` |
| hero | `procMove` | `Utility::MoveDefault(obj());` | `common::StateAirJump::procMove` |
| hero | `procFixPos` | `Utility::MapCollReactDefaultAction(obj());` | `common::StateCarryItemCatch::procFixPos` |
| hero | `procAnim` | `if (obj().model().isAllEnd()) Utility::ChangeStateWaitOrFall(obj());` | `common::StateWakeUp::procAnim` |

An empty override is a `blr` of the class's own, not a branch.

## The Classes
The namespace is `scn::step::<family>::<name>`, with one class per unit and one header per class. `Obj` below stands for `Enemy`, `Boss`, `Weapon` or `Hero`.

### States
```cpp
class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual ~StateFall();
    virtual void procMove();
    virtual void procFixPos();
};

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().model().rotCtrl().setValid(false);
}

StateFall::~StateFall() {
    obj().model().rotCtrl().setValid(true);
}
```

- The base is the family's `StateBase`. The class's own members start at 8.
- `obj()` and `objPtr()` are real functions of `StateBase`, never inline. In the disassembly they're `bl GetZeroBufferAddress__Q44nw4r3snd6detail9AxManagerFv`. `objPtr()` is what a state change gets as its argument.
- The overrides are among `procAnim`, `procMove`, `procConstraint`, `procFixPos`, `procObjCollReact` (and `procEnd` for heroes, where `procObjCollReact` returns `bool`). The unit's vtable in `.data` says which ones, as an entry that names `StateBase` isn't overridden.
- The destructor's place tells you whether the class declares it. If it's directly behind the constructor, the class declares `virtual ~StateX();` and the source defines it there. If it's at the unit's end, behind the last override, with or without a factory in between, the class declares none. Pretty much every boss state and every hero state written so far declares it, while enemy and weapon states vary.
- A destructor with a body undoes the constructor (`rotCtrl().setValid(true)`, `bodyColl().setStateNormal()`, `stateChecker().setRun(false)`).
- A state change is `obj().stateChanger().setNextState<StateY, Obj*>(objPtr());`, with further arguments by value, like `setNextState<StateDashEnd, Boss*, StateDashDesc, unsigned long>(objPtr(), mDesc, mScriptKindEnd)`. The factory's `create`, destructor and vtable come by themselves, and so does an out-of-line `setNextState<>` where the unit uses one instance twice. A class value goes into the call directly, a named local adds a copy.
- A factory with one argument for a constructor with two means a default argument, whose value is the `li r5` in the factory's `create`, like `StateLanding(Boss*, u32 scriptKind = 2)`.
- Member initializers can call `obj()`, like `mStartX(obj().location().pos().x)`. Where the constructor takes `r4` again behind the base constructor, the initializer uses the parameter, like `mPrevPosX(weapon->location().pos().x)`.
- A state with two constructors has a private helper that both call (`init(bool)`, `construct()`), defined ahead of the destructor or at the unit's end.
- A state with a `Config` argument keeps it as a member, `mConfig(config)`.
- A shared abstract base in a unit of its own (`whispy::StateShotAirBallBase`) declares no destructor and a pure virtual, and the derived classes declare none either.

### Brains (Enemies)
A brain is `class BrainX : public BrainBase`, with `BrainX(Enemy& enemy) : BrainBase(enemy) {}` and no declared destructor. The overrides are among `bool onStart()`, `bool onRecover()`, `bool onLanding()` and `void update()`. A body is a state change, with `&obj()` as the argument, plus `return true;`.

- A walker's `update` is `Utility::ChkNururiTurn(obj()); Utility::ChkCliffTurn(obj());`.
- A brain whose `onStart` and `onLanding` set the same state has both bodies written out.
- A water enemy's brain is `if (obj().water().isInWater()) setNextState<StateX> else setNextState<StateFall>`.

### `Custom`
This is the class that sets a character up and holds what its states share.

```cpp
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    ...
};
```

- Enemy: the source order is constructor, hooks, `GetRuntimeTypeInfo`, `Custom::~Custom() {}`, then the plain accessors as real functions that the header only declares. A `Custom` with a factory's `create` between `GetRuntimeTypeInfo` and the destructor declares no destructor.
- Boss: no declared destructor (the implicit one comes out between the factories' `create` functions and destructors). The source order is constructor, hooks in vtable order, own helpers and accessors, `GetRuntimeTypeInfo` last. The source ends with `template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();` (include `hel/common/RuntimeTypeInfoImpl.h`). Without it the string `no name class` is missing and the link shifts `.data` by 0x10, while `compare.py` only says `.data differs at +0x108`.
- Weapon: no declared destructor, and no tail like that. The source order is constructor, `onInit` (`obj().stateChanger().setNextState<StateMain, Weapon*>(&obj()); return true;`), accessors, `GetRuntimeTypeInfo`. A weapon only has a `Custom` where it keeps data or has several states, for the others `CustomFactory` uses `CustomSimple<StateMain>`.
- A state reaches its `Custom` by `hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom())`, with `#include "hel/common/RuntimeTypeInfoInline.h"`, or by `DynamicCast<Custom*, ICustom>` where the code keeps a null.
- Hooks that are one jump through the vtable are `return onInit();` for a bool hook and `onInit();` for a void one. `bctr` through slot 0x24 is `return onInWater();`, slot 0x20 is `onDamaged`. `bctrl` through slot 0x10 followed by `li r3, 0` is `onInit(); return false;`. An `onDamaged` that's one `b` is `return isCaptureHero();` or something like it, so read the target.
- The removed accessors of a `Custom` only show in its states under look-alike names. Their real names and order are in the map's `duplicated code: symbol ...6Custom...` lines.
- A `Custom` with a second base (`: public CustomBase, public weapon::buraburarope::ICustomReceiver`) gets its `@8@` thunks by itself.
- States can be written ahead of their `Custom`, just declare the methods they call in the padded stand-in. `grep -rho "bl [A-Za-z0-9_]*__Q53scn4step5enemy<n><name>6Custom[A-Za-z0-9_]*" build/SUKE01/asm/scn/step/enemy/<name>/` lists them with their signatures.
- A `Custom.o` that has the strings `NW4R:Pointer must not be NULL (p)` and `LinkList.h` twice in `.data` needs `template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();` at its end beside `#include "util/ObjList.h"`.

### `CharaParam` (Enemies)
A namespace with one function, and sometimes a second one for a variant:

```cpp
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 8;
    ...
    return param;
}
```

The stores stand in source order. The struct is in `scn/step/enemy/CharaParam.h` (0x50 bytes). A second function (`CreateYellow`, `CreatePoison`) starts from the unit's own `Create()`. A `CharaParam` that's one `b` into another enemy's has that enemy's stores.

### `ModelDesc`
A namespace with `chara::ModelDesc& Create...()`, and 3 tables in an unnamed namespace, in this order:

```cpp
const char* T_NODE_NAMES[] = { ... };
const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = { ... };
const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = { ... };
```

- A script entry's first field is `gobj::AnimScript::PLAY_LOOP`, `PLAY_ONE_SHOT`, or a script's name. In the object they're zero words that `__sinit` fills, and `__sinit` shows which.
- Enemy and weapon: `ModelDescUtil::CreateTmpl<kind, variation>(path, name, n, nodes, n, anims, n, scripts)`. The numbers are in the `@LOCAL@CreateTmpl<16,0>` symbol. A weapon's goes on with `desc.mModel._18 = hel::common::FixedString<40>("TopL");`.
- Boss: `chara::ModelDesc& CreateNormal(u32, bool isExtra)` with `boss::ModelDesc::CreateTmpl<kind, 0, variation>(isExtra ? "...ModelEx" : "...Model", "...Motion", "Name", ...)`, where `kind` is the boss's `map::BinBossKind`. A boss without an Ex model still has the ternary, with the same string twice.
- Without animations: `const Entry* T_ANIM_ENTRIES = 0;` (`.sbss`), and zero-filled scripts in `.rodata`.
- A function 2 instructions longer than these is `desc.mModel._40 = n; return desc;`.
- A table whose symbol has no namespaces in it (`NAME__23@unnamed@StateMain_cpp@`) stands in an unnamed namespace at global scope, ahead of `namespace scn`.

### Parameters
`obj().param().<name>()` returns a `const` reference to the character's parameter struct. The accessor is declared in the family's `Param.h` and the struct in the character's directory (`<name>/ParamData.h` for enemies, `<name>/Param.h` for bosses and weapons), with members named as the states show them.

- Its 2-vectors are the plain `hel::math::Vec2`, and `Vector2 v = param.x;` is the `Vector2(const Vec2&)` conversion. Its counters are `u32`.
- A boss state begins with `const Param& param = obj().param().<boss>();`, and the reference is loaded first even where it's used last.
- `if (++mFrame >= obj().param().x()._0)` loads the parameter first. `const Param& param = ...; mFrame++; if (mFrame == param._8)` loads the member first.
- An unused `const ParamData& param = obj().param().x();` still emits its calls.
- Level tables are `switch (static_cast<u32>(obj().level())) { case 0: ... default: }` with one member per level.
- A hero reads `obj().param().common()._1A0` and `IndiviUtil::Param(obj())._48`, written out at each use. A call with several of them has one `param().common()` per argument, right to left.

### Controllers and Components (Bosses)
- A controller (`XxxCtrl`, a member of `Custom`) has `Boss& mBoss` first. Its constructor `(Boss&)` is a real function of its own source even when it folds to 8 bytes. `Custom`'s constructor lists the controllers in member order, and their accessors stand in member order ahead of `GetRuntimeTypeInfo`.
- Whether a controller declares a destructor depends on where it is. One in the controller's own fold list is declared (68 bytes, folded into `Rect::~Rect`, for an empty one), one emitted in `Custom.o` is implicit.
- A request buffer is `hel::common::MutableArray<ReqData, 10>` with `add`, `clear`, `isEmpty`, `pick` as real functions, in that order behind the constructor.
- A controller that owns another boss looks like `Desc desc(kind, variation, level, false, pos.getXY(), Vector2::ZERO); util::ObjRefHandle<Boss> h = mBoss.comp().bossManager().request(desc); if (h.isAlive()) { mHandle = h; }`, with `UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS` and `NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE` defined ahead of the includes.
- The units directly in `scn/step/boss/` are plain classes with `Boss& mBoss` first, and their one-line accessors are real functions.

## By Family
### Enemies
- The GrandLowper set is the same in every enemy that has it. Copy `bladeknight`'s and change the script numbers and the parameter offsets. The set is `BrainGrandLowper`, `StateGrandLowperAppear` (a member `algorithm::AlgorithmGrandLowperAppear mAlgorithm` at 8), `StateGrandLowperEscapeStart` and `StateGrandLowperEscape`.
- A neighbor's finished unit often adapts mechanically. `degout::StateChase` is `chasekeydegout`'s with 3 edits, `pluid::Custom` is `clayn`'s, `flamer::StateMove` is `elec`'s, and the parasoldee and parasoldoo states are the same code pairwise.
- A damage state (`scn/step/enemy/damage`) has the constructor `Utility::OnDamageStart(&obj()); reqScript(5 or 6); EmDamageUtility_InitTarget/InitVelocity; obj().damageFlash().set(element)`, the destructor `rotCtrl().setRotV(0); setRotH(0); Utility::OnDamageEnd(&obj())`, and a `procMove` that's `UpdateMoveRate` plus `EmDamageUtility_Move`.
- Shooting is `weapon::Desc desc;` filled member by member, from `g3d::NodeAccessor node = obj().model().model().nodes().at(n);` with `desc.mPos = node.worldMtx().getT().getXY();`. Of the 3 `lfs` offsets, column 3 is `getT` and column 2 is `getZ`.
- A handle member assigned from `weaponManager().request(desc)` needs `UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS` and `NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE`.
- A `MoveParamFall` handed to `airDecelFall` is `const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(...)`, as a named local costs a temporary and 3 word copies.
- A unit whose class the link dropped whole can still own a factory, and a stand-in body that sets that state makes it link (`StateMahoroa2CallingShotAppear`).

### Bosses
- `Custom::onInit` sets the hit points by level (`std::min<u32>(maxLevel, obj().level())` with `static const u32 maxLevel = 2;`), the brain names, map and body collision and the vacuum ability, and ends with `setNextState<common::StateAppear, Boss*>`. A boss without a super form has no `hitPoint` local, it's `obj().hitPoint().init(hitPoints[level] * commonParam.mExtraHitPointRate);`. whispy and roah take theirs by variation with `init(Utility::IsVariationExtra(obj()) ? param.mHitPointExtra : param.mHitPoint)`, then `obj().handicap().setup()`.
- `onStart` is the world cage plus `StateWait`, and `onDead` is `setNextState<common::StateDead, Boss*, NodeKind>(objPtr(), NODE_KIND_x)`.
- The `Param` of a boss starts `u32 mHitPoint[3]; f32 _C, _10, _14; f32 mBodyCollRadius; Vec2 mBodyCollOffset;`.
- The common states keep their description as a reference member (`StateDashDesc& mDesc`) and hand it on by value.
- Flying bosses (dubior, whispy) have empty `procFixPos` and no foot state. landia never sets its position directly, every state moves through `custom.waftCtrl()`.
- Moving between two points over a count of frames recurs in 3 forms, which are the smooth step `f32 t = (f32)mCount / (f32)n; f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);`, the sine `f32 rate = Math::SinDegF(90.0f * t);`, and `Math::InterpolationParamMinToMax(t)`. Each is followed by `setPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3())`.
- Landing is `chara::MapCollResult result = obj().mapColl().result(); if (result.mIsHitFloor) {...}`. Stars are two `GenerateStarEffect` calls with `pos.x *= -1.0f; speed.x *= -1.0f;` between them.
- A helper in an unnamed namespace (`const StampParam& t_param(Boss&)`) exists once per unit that uses it and folds into one unit's copy. The disassembly shows it as a call into another unit's `@unnamed@`.

### Weapons
- Most weapons are one `StateMain` and a `ModelDesc`. The constructor's body is a chain, `obj().mapColl().setValid(false); obj().objColl().setAttackType(static_cast<ocoll::AttackType>(n)); obj().objColl().addAttack(0, r); obj().objColl().addHit(0, r); obj().effect().normal().requestN(static_cast<effect::Kind>(n), 0); obj().soundSE().start(n);`.
- Per-variation helpers are const members at the unit's end, which are `const LevelParam& param() const` with a `switch` over the variation, and `const ocoll::AttackType& attackType() const` returning literals, which gives the anonymous `@NNNNN` objects in `.sdata`.
- For a state with an extra constructor argument, `<dir>/Variation.h` holds `enum Variation`, the member is `Variation mVariation` at 8, and `Custom::onInit` switches over `obj().variation()`.
- For weapons that a boss spawns, `Custom::onInit` hides the weapon and returns false, and `reqStart(hel::math::Vector2 pos, hel::math::Vector2 velocity)` takes its vectors by value.
- Following the owner is `util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().objColl().owner().rootUid());`, with the uid written in the argument.
- Spawning a weapon is `::ocoll::Owner& owner = obj().objColl().owner(); Desc desc(static_cast<Kind>(n), 0, static_cast<ostop::Flag>(8), obj().location().pos().getXY(), hel::math::Vector2::ZERO, owner); obj().comp().weaponManager().request(desc);`.
- A weapon can read its parameters through a file-local `Param param(Weapon& weapon) { return weapon.param().x(); }` that returns by value. That gives a word-copy loop as the unit's first function, and uses that read stack slots.
- A `MutableArray` member needs `HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS`, `..._DESTRUCTOR_IN_CLASS` and `..._REMOVEATINDEX_IN_CLASS` in the state's header. The shift loop `m[i - 1] = m[i]` is `removeAtIndex(0)`.

### Heroes
`scn/step/hero/` has a directory per copy ability, and `common` (the states every character shares), `damage`, `captured`, `gimmick` and `modeldesc`.

- The unit order is `static bool TryToChangeState(Hero* hero)` first where there is one, then constructor, destructor, `procAnim`, `procMove`, `procFixPos`.
- `TryToChangeState` is one `if (...) return false;` per refusal, then `hero->stateChanger().setNextState<StateX, Hero*>(hero); return true;`.
- A run of state tests is one `||` chain, `if (A::TryToChangeState(objPtr()) || B::TryToChangeState(objPtr()) ...) { return; }`. Separate `if`s give `bne end` everywhere.
- `Hero`'s own accessors are real functions. `StateChecker`'s setters and getters are inline, so used once they're a store, and used twice they're a call to a look-alike or a weak function in the middle of the unit. The functions of `RunChecker`, `Hang`, `Kiss`, `Stepping`, `Water` and `AdditionalMove` are real.
- `hero::MapColl::result()` is inline and returns by value. Once in a unit it expands to 10 byte copies, 2 vector assignments and 3 colour constructors, twice it's a call.
- The model is `obj().model().script().start(n)`, `scriptTrigger().get(n)`. `procAnim` usually opens with `obj().abilityManager().chkDiscardAbility();`.
- Inside `hero::damage`, `Utility` is `damage::Utility`, and the hero one is written `hero::Utility::`.
- Ground states (`StateWait`, `StateWalk`, `StateRun`, `StateSquat`, `StateSliding`, `StateGuard`) have a constructor that's `footState().setGround()` then `Utility::SwitchBombDangerMotionInit(obj(), script)`, a `procAnim` that ends with `SwitchBombDangerMotionProc(obj(), script)`, and a `procFixPos` that's `if (obj().mapColl().result().mIsHitFloor) { move().resetSpeedV(); } else { setNextState<StateFall, Hero*>(objPtr()); }`.
- The fall counter is the same in 3 states, `f32 y = obj().location().pos().y; f32 prevY = obj().location().prevPos().y; if (y < prevY) { mFallLength += prevY - y; } else { mFallLength = 0.0f; }`.
- The 4 damage states `StateSparkLv2`, `StateSparkLv3`, `StateFireLv2`, `StateFireLv3`, and `StateFireBlock` and `StateExtreme`, are one class with `f32 mRot; bool mIsLanded; u32 mWait; u32 mFrame;`.
- `Hero::location() const` from a state is `static_cast<const Hero&>(obj()).location()`.
- `lwz r3, 0x1b8(r3); bl DefaultSwitchThreadCallback; lwz r3, 0x1b8(r31)` on the gimmick manager is the inline `gimmickManager().shipeventManager()`, and the unit defines `MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE` ahead of its includes.

### Copy Abilities
Each ability directory under `scn/step/hero/` has one ability class named after it, its states, sometimes a `Utility` class of statics, and a `Custom` where the ability keeps data. `src/scn/step/hero/tornado/` and `leaf/` are whole.

- The ability class is `class Tornado : public AbilityBase`, with its members from 0xC and `bool mIsSetup` first. The unit order is constructor, destructor, `setup`, `tryToChangeState`, the `on...` hooks in vtable order, `procAnim`, private helpers.
- `setup` registers the ability's motion file and sets up the hat with `motion.bind(base, false); mHero.model().mAnim.registerResFile(N, motion);`, `hat().set(modeldesc::X::HatPath(), modeldesc::X::HatModel())`, `mIsSetup = true`. `N` is the ability kind. The destructor is `if (mIsSetup) mHero.model().mAnim.unregisterResFile(N);`.
- `tryToChangeState()` is how an ability is entered. It's `if (mHero.water().isInWater()) return false; if (mHero.stateChecker().isFloat()) return false;`, then one `if (StateX::TryToChangeState(&mHero)) { ...; return true; }` per state. In a normal ability it's a protected function, and so are `procAnim` and the hat effect functions, so start from `tools/metafortress_c.py`.
- A state's `TryToChangeState(Hero*)` tests the buttons, which is `hero->hid().isTrigger(0x20)` for attack (guard is 0x40), with `isHold(8)` for up and `isHold(4)` for down. A state that only another state enters has none.
- An ability state's constructor starts with `obj().model().setFixDir(true)`, `script().start(n)`, `Utility::AirAttackInitSpeedV(obj())`. It leaves with `if (obj().model().isAllEnd()) { obj().abilityManager().setActionInterval(param._N); Utility::ChangeStateWaitOrFall(obj()); }`. One-use abilities end with `abilityManager().clearAbility()`.
- Parameters are `obj().param().<ability>()`, one struct per ability in `hero/<X>Param.h`. A state reads its part through a file-local `param(Hero&)` that returns a sub-struct.
- A `Custom` derives from `AbilityCustomBase`, whose vtable is `GetRuntimeTypeInfo`, destructor.
- The super abilities (`supersword`, `superfire`, `superbeam`, `superhammer`, `superice`) share their hooks. `onHideHero`, `procAnim` (`super::Utility::SuperLeakFuel(mHero);`) and `isDepleted` are branches into `supersword::SuperSword`. Each of the 5 ability units includes `scn/step/hero/AbilityCustomBaseInfo.h` for the `no name class` string at the tail of its `.data`.
- There are more branches. `procMove() { Utility::MoveDefaultAction(obj()); }` goes to `cutter::StateCutterThrow::procMove` in most attack states, `procMove() { obj().move().decel(gobj::MoveParamDecel::Zero()); }` to `interference::StateHang::procMove`, `procMove() { Utility::MoveGuard(obj()); }` to `common::StateGuard::procMove`, and `bool procObjCollReact() { return false; }` to `__wpadNoAlloc`.

## Names in the Disassembly
A call in these units seldom names the function the source called. The linker kept one copy of every group of identical functions, and a getter of the word at offset 8 has the same code in every class that has one. So read a look-alike's name as a shape (a getter at an offset, a bool setter, a constructor that zeroes one word), and take the class from the object the call is made on. For a name that isn't in the tables, `grep "is duplicated by <callee>," orig/SUKE01/files/iuk.MAP | grep <YourClass>` finds the real one.

### On Any Object of the Family
| The Call Names | It Is |
|---|---|
| `GetZeroBufferAddress__...AxManagerFv` | `obj()`, `objPtr()`; on a `FrameCounter` member `frame()` |
| `GKI_getfirst` | `comp()` on `Enemy`, `Boss`, `Weapon`, `Hero`; `Signal::get` |
| `DvdFileStream::Tell` | `Enemy::level`, `Boss::level`; a `u32` getter at 0x18; `vacuum::Attacker::vacuumCount` |
| `GXGetTexObjUserData` | `Enemy::kind`, `Boss::kind`, `Weapon::variation` |
| `DvdFileStream::GetSize` | `Enemy::variation`, `Boss::variation` |
| `Pane::GetParent` | `Weapon::kind` |
| `gui::Component::getID` | `Enemy::size` |
| `CharWriter::GetFont` | `Enemy::objGenerator` |
| `DetectResult::collidedLogCount` | `Enemy::dirType` |
| `isTriggerTarger` | `Enemy::isSuper` |
| `ResPart::gridWidth` | `Boss::isSuper`; `chara::Water::isInWater`; a bool getter at 0x1C |
| `ExplicitScopedPtr::isConstruct` | `Boss::isGeneratorExist`; an `isValid()` that is `mFrame != 0` |
| `LandConstraint::prevVelocity` | `Weapon::targetPos` |
| `MoveGroupCtrlOrderData::moveRate` | `Weapon::isVisible` |
| `CliffChecker::isCliff` | `Weapon::isDead`; `RunChecker::isAirContinue`; a bool getter at 0x14 |
| `Script::currentScriptIndex` on the hero | `Hero::kind` |
| `CarryItem::setUseCount` | `Enemy::setPotentialCount`, `VacuumReceiver::setResistLevelStep` |
| `MoveAlgorithmVacuumReceive::getNextOffs` | `Enemy::getBasePos` |

### On the Parts Every Object Has
| The Call Names | It Is |
|---|---|
| `file::DNOption::DNOption` | `gobj::FootState::setAir` |
| `GenContext::dataType` | `gobj::Target::isRightDir`; on `footState()`, `isGround` |
| `mint_wrapNative_helper<b>` constructor | `gobj::Target::setIsRightDir` |
| `boss::Boss::param` | `chara::ObjColl::bodyColl` |
| `HeapCompaction::heapName` | `chara::DamageInfo::data`, `ObjColl::owner` |
| `NandManager::isOK` | `HitPoint::isDead`; an `isEmpty` |
| `VMFunction::isMint` | `chara::Lifetime::isDead`; an `isEmpty` |
| `MainCamera::getOffset` | `chara::Model::rotCtrl` |
| `Pane::GetMaterial` | `gobj::Anim::currentG3DAnimIndex` |
| `Controller::setSpeakerVol` | `Move::setSpeedH` |
| `Move::setSpeedV` | a float setter at 8 |
| `Move::setSpeedD` | a float setter at 0xC: `ModelRotCtrl::setRotHTarget`, `Culling::setHeight` |
| `Move::setMoveRate` | a float setter at 0x10; `ModelRotCtrl::setRotHIntpRate`; `CliffChecker::changeFrontDist` |
| `WaftMoveCtrl::setMoveIntpRate` | `ModelRotCtrl::setRotV` |
| `WaftMoveCtrl::setWaveWidth` | `ModelRotCtrl::setRotVIntpRate`; `sfx::DarknessLight::setCustomScale` |
| `AnmObjVisRes::SetUpdateRate` | `ModelRotCtrl::setRotVTarget` |
| `AnmObjVisRes::GetFrame` | `ModelRotCtrl::getRotV` |
| `roah::RotCtrl::setRotYMax` | `ModelRotCtrl::setRotHTargetDefault`; an `f32` setter at 0x14 |
| `CharWriter::SetCursorX` | `ModelRotCtrl::setRotDTarget` |
| `SeqTrack::SetPlayerTrackNo` | `ModelRotCtrl::setValid` |
| `StateCallback::setCanClearAttack` | `chara::Culling::setValid`; any bool setter at 8 |
| `CarryItem::setIsGathered` | `Nururi::setCanNururi`, `Nururi::setValid` |
| `CarryItem::setIsEnableCarry` | `Water::setUseCallback` |
| `Command::finish`, `Command::reset` | `ObjCollReact::setDamageState` or `InterruptStateChanger::deny`; `DamageFlash::unset` |
| `NodeLocalMtx::setCalcOp` | `VacuumReceiver::setResistLevel` |
| `ActorDiamond::actorCurrentPos` | `GroundChecker::getFloorPos` |
| `gobj::Location::prevPos` | a `Vector3` getter at 0xC |
| `ocoll::Gimmick` constructor | `chara::Shake::request`; `util::FrameCounter(u32)` |
| `BasicSound::DetachPlayerHeap` | `FrameCounter::reset` |
| `TagUtil::onNormalChar` | `FrameCounter::advance` |
| `OSCreateAlarm` at `this + 8` | a `FrameCounter` constructor |
| `ocoll::Hit::isCollide` behind `+8` | `bodyColl().hit().isCollide()` |
| `GetYoungestParticle`, `ARCGetLength` | `ObjCollLite::hit`, `ObjCollLite::owner`; a getter at 8 |
| `app::Reset::canFrameUpdate` | `WorldCage::isCorrected`; a bool getter at 0xA |
| `FileTree::wasSetParent` | `ObjRefHandle::isAlive` |
| `ObjListNode::isLink` | `m != 0` at 8 |
| `gameover::Component::seRequestor` | `Component::objStopManager` |
| `gameover::Component::kirby` | `Component::areaOperation` |
| `DefaultSwitchThreadCallback` | `SoundSE::normal`; behind `mapLandManager()`, `.native()` |
| `__wpadNoAlloc` | `return false;`; a `DebugStepSettingProxy::Get...()`; `Utility::IsAppearDemoCancelRequested` |

### Effects and Sounds
| The Call Names | It Is |
|---|---|
| `font::PairFont::name` | `enemy::Effect::super`, `boss::Effect::super`, `weapon::Effect::normal` |
| `font::Font::name` | `enemy::Effect::state`, `boss::Effect::normalWarp` |
| `CollidedDetectionInfo::collideTarget` | `enemy::Effect::normal`, `boss::Effect::normal`, `weapon::Effect::warp` |
| `boss::Effect::state` | `enemy::Effect::charaBack` |
| `PlayerSet::rootInfo` | `boss::Effect::stateWarp` |
| `font::Font::font` | `SoundSE::state` |
| `addi r3, r3, 8` behind `permEffect()` | `.normal()` |

### Vectors and Parameters
| The Call Names | It Is |
|---|---|
| `Vector2::set` | `Vector2(f32, f32)` |
| `Vector2::operator=` | also the `Vector2` copy constructor and `Vector2(const Vec2&)` |
| `Vector3::operator=` | the implicit `MoveParamAccel::operator=` |
| `VEC3(f, f, f)` | `Vector3(f, f, f)` |
| `Rect(f, f, f, f)` on a built `Rect` | `Rect::set` |
| `LightObj()` | a `clear()`, or a constructor that zeroes offset 0 |
| `MoveParamAccel::Create` with a fall as its user | `MoveParamFall::Create` |
| `hero::Param::superBeam`, `hammer`, `superFire`, `parasol`, `carryitem::Param::common` behind a weapon's `param()` | weapon `Param` accessors with the same offset |

### Shapes Without an Owner
The class is the one the call is made on.

| The Call Names | It Is |
|---|---|
| `ShapeDiamondContext::getToLeftDist` | a float getter at 8 |
| `AnmScnRes::GetFrame`, `GetUpdateRate` | float getters at 0xC and 0x10 |
| `RenderSetting::getViewPortTop` | an `f32` getter at 0x14 |
| `CollidedDetectionInfo::velocity` | an accessor at 0x14 |
| `nururi::Nururi::isValid` | a bool getter at 8 |
| `Invincible::setMighty`, `unsetMighty`, `isMighty` | a bool at 9 |
| `cappy::Custom::setValidTurn` | a bool setter at 0xA |
| `SuperStop::unsetAutoSpecial` | a bool at 0xA set false |
| `GXFifoMemoryManager::isWriteEnable`, `Actor::isStoppedNormal` | bool getters at 0xC and 0xD |
| `ModelTree::disable`, `enable` | a bool at 0x14 set false, true |
| `BasicSound::DetachSoundActor`, `DetachExternalSoundPlayer` | a `u32` at 0x14, 0x18 set to 0 |
| `Owner::unsetParentInterim` | a bool at 0x1C set false |
| `ResPart::gridHeight` | a bool getter at 0x1D |
| `ButtonPanel::isEnable` | `Angry::isAngry`, `hero::Water::isInWater` |
| `MoveGridGroupId::isValid`, `Camera(CameraData*)` | `Signal::isValid`, `Signal::set`; a controller's constructor |
| `SeqPlayer::OnShutdownSoundThread`, `bg::Manager::onStopPowerfulStarted` | `return onInit();`, `return onStart();` |

### The Hero's `StateChecker` and Its Neighbors
| The Call Names | It Is |
|---|---|
| `StateCallback::setCanClearAttack` | `StateChecker::setRun`; on `infoControl()`, `setIsPlayerOut` |
| `WorldCage::setIsOnlyOut` | `StateChecker::setFloat` |
| `knucklejoe::Custom::setHitWall` | `StateChecker::setIsForbidSpaceJump` |
| `tsukikage::Custom::setWarp` | `StateChecker::setPlancher` |
| `CaptureAttacker::setIgnoreMapColl` | `StateChecker::setChallengeDoorWait` |
| `CaptureReceiver::setIsIgnoredNonSuper` | `StateChecker::setHover` |
| `DetectArg::setIsPassThroughLand` | `Water::setForbidChangeState`, `Hang::setCanReceive`, `Piggyback::setEnableReceive`, `StateChecker::setSquat` |
| `DetectArg::setIsGenerateFloorToOneSpaceGrid` | `Hang::setCanHang`, `Piggyback::setEnableRide`, `StateChecker::setCannon`, `Water::setForbidEffect` |
| `setUsePrivateCharButtonPushed` | `Kiss::setCanReceive`, `Stepping::setEnableStep` |
| `SeqTrack::SetPlayerTrackNo` | `Kiss::setCanKiss`, `Stepping::setEnableReceive` |
| `SubAnimCtrl::setIsValidAnimEye` | `Dead::setForbid` |
| `hid::Button::isTrigger` | `hero::Hid::isHold` |
| a boss's `Custom::enemyCtrl` behind `infoManager()` | `info::Manager::gameStatus` |

## Generating Units
`CharaParam` and `ModelDesc` units carry no logic, they're just a list of stores, and 3 tables with a call. They've been written by throwaway scripts that read the disassembly, and about 9 in 10 compiled complete as generated. The same goes for a state's skeleton (the class header from the vtable and the constructor's symbol, the state changes, the call chains). None of those scripts is in `tools/` yet. Whatever a script writes, compare it before it stays in `src/`, as the build compiles every source that exists.

A generator got a few kinds of unit wrong. Those were a `CharaParam` that's a branch (it has the look-alike's stores, not none), a `ModelDesc` with a dynamics table, with two `CreateTmpl` instances, or with function-local `static` node names, and the 3 strings of a boss without an Ex model.

## Known Issues
### The capture controllers' constructors have two saved registers swapped
That's doubter's `CaptureCtrl` and fattybuffer's `CannonCaptureCtrl`. `ExplicitAutoDeleteArray::add<A1, A2>` comes out with two saved registers swapped, and we don't know why yet.
### `Math::Interpolate` is a guessed name
The inline `rate * (target - value) + value` is `hel::math::Math::Interpolate(value, target, rate)` now, with its parameters by `const T&`. No copy of it survives in the map, so the name is a guess with a TODO. Don't mix it up with `Math::LinearInterpolation`, which is `(b - a) * rate + a` and gives the other operand order in `fmadds`.
### Some hero headers are stand-ins
`hero/CommonParam.h` and `hero/IndiviParam.h` are stand-ins that grow as states name their members. `hero/MapCollResult.h` isn't one anymore, it's a typedef of `chara::MapCollResult`.
### `liepa/Custom` is one instruction short
`getNearestHeroInAttackRange` is the function. The original keeps the address of the negated `BASIS_X` temporary in r29 across the loop, and a `const Vector2&` local doesn't do it.
### `roah/StateZPassThrough` trades stack slots
The helper objects of `Direction3::restructFrontUp()` trade stack slots when `restructFrontLeft()` follows. The original has Left at 0x10 and Up at 0x14, then Up at 0xC and Left at 0x8.
### The hero `modeldesc` units can't be generated
Each one has guarded function-local statics and a dynamics description, so they aren't generator work.
### The large units of each family have no source yet
That's `Enemy`, `Boss`, `Weapon`, `Hero`, their `Manager`, `Param`, `Utility` and `MapColl`.
