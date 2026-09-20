# Roadmap

## Authoritative Game Settings acquisition and NVRAM audit

Status: planned.

Run a Service Menu acquisition campaign for every ROM set that currently
exposes Libretro `NVRAM Settings`. The implementation currently covers 57 sets:
22 parents and 35 clones. This first campaign is intentionally limited to the
settings already exposed by the core; other visible Service Menu rows may
appear in the evidence, but they are outside the catalog and implementation
audit until explicitly added to the scope.

The campaign must produce two repository documents modelled after the SM2-Emu
reference work:

- an authoritative `GAME_SETTINGS_CATALOG.md`, derived from Service Menu
  screenshots and recording each implemented setting's visible label, relative
  order, native default, and every observed selectable value;
- an `NVRAM_SETTINGS_AUDIT.md` comparing that catalog with
  `LibretroNvramSettings.h`, including option presence, order, labels, values,
  defaults, encoded values, integrity updates, template routing, and clone
  routing.

### Acquisition rules

1. Build the campaign inventory from the NVRAM options registered by the core
   at the start of the campaign. Record the exact core revision and `Games.xml`
   revision used for the evidence.
2. Acquire a clean native baseline for every supported set with `Automatic
   Initial NVRAM Setup` and `NVRAM Settings` disabled. Each option cycle must
   restart from that immutable baseline rather than from the preceding sample.
3. Capture the base Game Settings screen and every distinct value of each
   in-scope option. Screenshots are authoritative for visible presence, order,
   labels, values, and native defaults; implementation tables, TOML recipes,
   and parent metadata are secondary evidence.
4. Keep ROMs, generated Save RAM, raw screenshots, logs, and temporary frontend
   profiles outside Git. Commit the reproducible campaign definitions, the
   indexed catalog, the audit, and validation tooling.
5. Validate each observed selection against the generated `.srm`: confirm the
   expected byte encoding, checksum or mirror update, clean import, and
   persistence after a second launch.

### Parent and clone criteria

- Acquire every clone directly. A `parent` relationship in `Games.xml` does not
  prove that labels, order, values, defaults, offsets, checksums, or storage
  layout are compatible.
- A clone may share a parent catalog only after its own evidence confirms the
  same visible in-scope menu and every exposed value can be written and
  persisted with the parent encoding rules.
- A byte-identical native baseline alone is insufficient to authorize catalog
  inheritance. Conversely, a different baseline does not require a different
  catalog when direct menu acquisition and complete write validation prove the
  same option semantics.
- Any clone difference produces a clone-specific catalog or routing rule and is
  recorded in a parent/clone comparison matrix. No unacquired value is inferred
  from the parent.

### Default and override policy

Align Supermodel with the SM2-Emu distinction between native defaults and
deliberate policy overrides:

- the native default is the value visible in the clean Service Menu baseline;
- ordinary Core Option defaults must match that native value unless the setting
  is listed as a reviewed policy override;
- policy overrides are limited to region selection (USA when available,
  otherwise Export), a safe offline or stand-alone network state, and any
  Supermodel-specific cabinet or I/O choice that is explicitly approved and
  documented;
- the current Star Wars Trilogy Upright initialization and every other existing
  non-native default must be reclassified from evidence as either a reviewed
  override or a defect; undocumented exceptions are not retained;
- overrides apply only through the documented new-save initialization and
  NVRAM Settings paths. Existing saves are never rewritten implicitly;
- automated checks must compare ordinary defaults with the native catalog and
  test the reviewed override list separately, including its rationale and
  affected sets.

### Completion criteria

- 100% of the sets and settings in the campaign inventory have indexed Service
  Menu evidence, including every clone;
- every currently exposed NVRAM option is accounted for, and no unreviewed
  option or value remains exposed;
- catalog and implementation agree on presence, order, labels, accepted values,
  native defaults, encodings, and integrity handling;
- every clone route is supported by clone-specific evidence;
- native defaults and deliberate overrides are reported separately and covered
  by automated checks;
- clean initialization, option application, save import, and persistence pass
  for every supported set before the audit is marked complete.

## Cross-core widescreen assessment

Status: complete. No Model 3 title is known to have a native widescreen
presentation.

The Model 3 video path has a common 496x384 visible area. Supermodel identifies
496/384 as the Model 3 aspect ratio, defaults `WideScreen` to disabled, and
describes the optional implementation as a wide-screen hack. MAME likewise
configures the Model 3 driver with a 496x384 visible area and has no per-game
aspect-ratio override. The documented Twin and Deluxe cabinets use larger CRT
or projection displays, but no discovered game or cabinet setting selects a
native 16:9 presentation.

SM2-Emu's `Aspect Ratio` therefore has no Model 3 counterpart to adopt. That
option keeps the emulated 496x384 framebuffer unchanged and, in `Auto`, reports
4:3 or 16:9 from the active Indy 500/STCC cabinet setting in NVRAM.
Supermodel's `Widescreen Mode` instead expands the rendered 3D field of view,
changes the framebuffer width, and can optionally extend the lower 2D
background. It remains a separate, explicit opt-in emulator enhancement and is
never enabled automatically from a game or cabinet label.

The Game Settings acquisition campaign must still record any Cabinet, Display
Type, or equivalent setting it encounters. New primary evidence of a native
Model 3 widescreen mode would reopen this assessment before any automatic or
NVRAM-driven aspect policy is added.
