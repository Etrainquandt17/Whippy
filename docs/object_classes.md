# Object Classes
Most of the game's own code is the classes of its characters. Every enemy, boss, weapon (anything a character shoots, throws or swings), copy ability, gimmick and item has a directory under `scn/step/`, with one small class per unit. That's a state per behavior, plus a few classes that set the thing up.

The good news is that they're regular. Once a directory's headers are right, most of its units match on the first compile, and the second state of a directory is mostly the first one again. This page says what each kind of class looks like in source and what order to write a directory in.

Read [Decompiling](decompiling.md) first for the tools, and [Code Merging](code_merging.md) for why a call in the disassembly names an unrelated function.

## Finding a Directory
```sh
python tools/unwritten.py scn/step/enemy/         # every unit without a source under a path, smallest first
python tools/unwritten.py scn/step/boss/goliath/
```

Each line is the unit's code size, its number of functions and its path. The fastest way in is to read a finished directory of the same family beside the one you're writing.

| Family | Read |
|---|---|
| Enemy | `src/scn/step/enemy/starman/` and `como/` (whole enemies), `common/` (the brains and states every enemy shares), `damage/` (the 16 damage states) |
| Boss | `src/scn/step/boss/bonkers/` (a small one) and `lowper/` (a large one), `common/` |
| Weapon | `src/scn/step/weapon/sparkshotlv1/`, `lowpersparkshot/`, `mahoroawarphole/` |
| Hero | `src/scn/step/hero/common/` (the states every hero has) and `sword/` (a whole copy ability) |

## Writing a Directory
1. List its units, and read the directory's `AddOnMint.cpp`. It's linked already, and it names the states and their constructor arguments.
2. Write all of the class headers first, from `AddOnMint.cpp` and the constructors' symbols.
3. Write the units from the small end. For an enemy that's `CharaParam`, `ModelDesc`, `Custom`, the brains and then the states. For a boss it's the small states, `ModelDesc`, the larger states, the controllers and `Custom` last. For a weapon it's `ModelDesc`, `Custom` and then the states.
4. Compare each one with `python tools/compare.py all src/<unit>.cpp` until it's complete. Always compare both versions.
5. When the directory is done, `python tools/link_complete.py src/<directory>` tests and marks its units, and `python tools/check_all.py` builds both versions.

Don't spend long on one function. Leave its closest form with a `// TODO:` that says what differs and go on, as the next 10 units are likely to match at once.

Many classes already have a header that somebody needed before the unit existed, like a state with just its constructor or a `Custom` padded to its size. Those are stand-ins, and most of them are wrong in detail (the wrong base class, a destructor that shouldn't be declared, an `int` counter that's a `u32`). Replace the stand-in with the real class when you write the unit. The one thing a new header has to keep is the size of a `Custom`, as the family's `CustomFactory.cpp` builds every `Custom` and stops matching when one is off. Compare that file and the directory's `AddOnMint.cpp` again after you replace a header.

## The Classes
The namespace is `scn::step::<family>::<name>`, with one class per unit and one header per class.

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

The base is the family's `StateBase`, and the class's own members start at offset 8. `obj()` and `objPtr()` are real functions and never inline. In the disassembly they show up as calls to `GetZeroBufferAddress`, which is one of the names from "Names You'll Keep Seeing" below.

A state overrides some of `procAnim`, `procMove`, `procConstraint`, `procFixPos` and `procObjCollReact`. The unit's vtable in `.data` tells you which, as an entry that names `StateBase` isn't overridden.

Whether the class declares its destructor is something you read from where the destructor sits. If it's directly behind the constructor, the class declares `virtual ~StateX();` and the source defines it there. If it's at the end of the unit, the class declares none. A destructor with a body undoes what the constructor did.

A state hands over to the next one like this, with any further arguments by value:

```cpp
obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
```

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

Its virtual functions are hooks (`onInit`, `onDamaged`, `onDead` and so on), and its plain accessors are real functions that the header only declares. A state reaches its `Custom` with `hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom())`.

The families differ in the details. An enemy's `Custom` usually declares its destructor, and a boss's or weapon's doesn't. A weapon only has a `Custom` at all where it keeps data or has several states, and for the others `CustomFactory` uses `CustomSimple<StateMain>`.

### `ModelDesc` and `CharaParam`
These 2 carry no logic. A `ModelDesc` is a namespace with a `Create()` function and 3 tables in an unnamed namespace, which are the node names, the animations and the scripts, in that order.

```cpp
const char* T_NODE_NAMES[] = { ... };
const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = { ... };
const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = { ... };
```

An enemy's `CharaParam` is a function that takes the common values and changes a few of them, with the stores in source order.

```cpp
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 8;
    ...
    return param;
}
```

### Parameters
The numbers a designer could tune come from parameter files. `obj().param().<name>()` returns a `const` reference to the character's parameter struct, which is declared in the character's own directory with its members named by offset until a state shows what they're for. Its 2-vectors are the plain `hel::math::Vec2` and its counters are `u32`.

### Brains and Controllers
An enemy's brain decides which state comes next. It's `class BrainX : public BrainBase` with no declared destructor, and its overrides (`onStart`, `onRecover`, `onLanding`, `update`) are mostly one state change and `return true;`.

A boss has controllers in place of brains. A controller (`XxxCtrl`) is a plain class with `Boss& mBoss` as its first member, and the boss's `Custom` holds its controllers by value, in the order its constructor lists them. That makes a large boss's `Custom` the last unit you write, as it needs every controller's real size.

## Functions That Are Somebody Else's
These classes are full of functions with identical code, and the original link folded them. 568 functions in the game are branches into the classes of `scn/step/enemy/common` alone. In the disassembly a function like that is a single `b other`, and in the source it has a body, which is the other function's with your class's names.

```sh
grep "<Class>" orig/SUKE01/files/iuk.MAP | grep "replaced by a branch"
```

That lists a class's branches and where they go. A destructor that's a branch links right away. Most other branches only link once the unit of their target is written too, so it pays to write the targets early, and a few of them sit in another directory than the units that branch into them.

Once in a while it goes the other way, and the linker folds your function into a look-alike that the original kept apart. The 2 functions then differ in something the bytes don't show, and the usual one is `&obj()` in one where the other has `objPtr()`. [Code Merging](code_merging.md) has the details.

## The Families
### Enemies
What's above is the whole picture for most of them. The states that every enemy shares are in `common/` and the 16 damage states in `damage/`, so an enemy's own directory is usually a `Custom`, a `CharaParam`, a `ModelDesc`, a brain or 2 and a few states.

### Bosses
Small bosses look like enemies. The large ones (`lowper`, `grandlowper`, `goliath`, and Mahoroa, who has `mahoroabattle1` and `mahoroabattle2` for the 2 phases) have about 50 to 65 units each, most of them states. Nearly every state begins by fetching its `Custom` and requesting a script, and does its work through the controllers.

### Weapons
Most weapons are one `StateMain` and a `ModelDesc`. The state's constructor sets up its collision, effect and sound in one chain of calls, and its other functions are often branches into another weapon's (a `procFixPos` that's `if (obj().mapColl().isHit()) obj().dead();`, for example, belongs to `StateNormal`).

### Heroes and Copy Abilities
A hero state is like an enemy state with 2 differences, which are that `procObjCollReact` returns `bool` and that there's a `procEnd`. Many states also have a `static bool TryToChangeState(Hero*)` as their first function, which checks whether the hero may enter the state and sets it.

Each copy ability has a directory with its states and one ability class (`Sword`, `Whip` and so on, derived from `AbilityBase`). The ability class's `tryToChangeState` is where a button press becomes a state, and it's a protected function in many of them ([Decompiling](decompiling.md) has what that means).

### Gimmicks
A gimmick directory has 2 classes, the gimmick itself and a `Manager`. The manager holds its gimmicks in a `mem::ExplicitAutoDeleteArray<T, N>`, fills it from the map's entries in its constructor, and forwards `registerToRoot`, `procAnim` and the like to each of them. `gimmick::Manager` in turn holds every directory's manager.

The gimmick class has no base and no vtable, unless it listens to a switch (`SwitchReceiver`). Its members are a `Component&`, its position, and then the parts it's made of, which are a `gimmick::Model`, `gimmick::Effect`s and a `gimmick::Stop`.

### Carry Items and Items
A carry item (the key, the candle, the stomper boot) has no `Custom`. Its kind is a `ModelDesc`, usually a `Utility` and 2 or 3 states, and the states are thin wrappers round 3 classes of the base directory that do the real work, `FallAlgorithm`, `UseAlgorithm` and `BoundAlgorithm`.

```cpp
StateFall::StateFall(CarryItem* carryItem) : StateBase(carryItem), mFallAlgorithm(*carryItem) {
    obj().mapColl().setValid(true);
}

void StateFall::procMove() {
    mFallAlgorithm.procMove();
}
```

Items (food, ability stars, energy spheres) have no kinds at all. There's one flat parameter struct, and 21 states in `item::state` that every item shares.

### Subgames
`scn/subgame/` isn't built like the rest, but it's just as regular. Its small classes come in a few kinds. A parameter class copies its data out of a parameter file once, and its unit holds only the constructor. An accessor class holds one pointer and forwards every call to the real class behind it. A requestor does the same through a singleton. The 2 subgames (`gunshoot` is Scope Shot and `setsuna` is Ninja Dojo) mirror each other, so a class you've written for one is usually there for the other too.

## Names You'll Keep Seeing
Because of code merging, the same few survivors turn up as callees everywhere. You don't need to know whose they were, only what they do.

| The Call Names | What It Does |
|---|---|
| `GKI_getfirst` | returns the word at offset 0 |
| `GetZeroBufferAddress` | returns the word at offset 4 (a state's `obj()` and `objPtr()`) |
| `ARCGetLength` | returns the word at offset 8 |
| `DefaultSwitchThreadCallback` | nothing (any empty function) |
| `CanCancel` of `DvdFileStream` | returns true |
| `__wpadNoAlloc` | returns false |
| `OSCreateAlarm` | sets 2 words to 0 (a small constructor) |
| `hel::geo::Rect::~Rect` | an empty destructor that isn't virtual |

For any other name, read the body of the function that's called. `grep "is duplicated by <name>" orig/SUKE01/files/iuk.MAP` lists everything the link folded into it, and your function's real name is usually in that list.

## Known Issues
### The large units of each family have no source yet
That's `Enemy`, `Boss`, `Weapon`, `Hero`, and their `Manager`, `Param`, `Utility` and `MapColl`. Their headers are stand-ins that grow as the small classes need them.

### `weapon/StateCallback` waits for `scn/step/boss/Boss`
It's finished and can't be linked. Its destructor has to fold into one that the original link kept in `Boss.o`, and that only works once `Boss` is compiled from source.

### The super abilities wait for `SuperSword`
`superbeam`, `superfire`, `superhammer` and `superice` are finished too, and their hooks are branches into `supersword::SuperSword`, which has one function that doesn't match yet ([Decompiling](decompiling.md) has it under its own Known Issues).

### 5 units wait for `vacuum::ReceiverBase`
`gimmick/popflower/VacuumReceiver` and `ItemGen`, and `VacuumReceiver`, `Custom` and `StateVacuumReceive` of the weapon `vacuumedblock`, derive from or use `scn::step::vacuum::ReceiverBase`, which has 18 virtual functions and no header yet.
