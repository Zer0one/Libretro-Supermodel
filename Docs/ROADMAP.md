# Roadmap

## Authoritative Game Settings acquisition and NVRAM audit

Status: visual catalog in progress; supplemental NVRAM validation complete.
All 22 parent sets have been acquired and matched against their existing
recipes; 38/40 clones have direct structural evidence. The two Sega Rally 2
prototypes fail before reaching the Service Menu. Current coverage and findings are tracked in
[`GAME_SETTINGS_CATALOG.md`](GAME_SETTINGS_CATALOG.md) and
[`NVRAM_SETTINGS_AUDIT.md`](NVRAM_SETTINGS_AUDIT.md).
The Model 3 workbook now contains separate `Cloni` and `Copertura cloni`
worksheets derived only after direct clone menu acquisition, with parent-derived
value cycles labelled by provenance.

Prototype and location-test sets are part of the campaign whenever they can be
run. Their status is never an exclusion criterion. At present only `mgtrkbad`
is excluded because it is a known bad dump; `srally2p` and `srally2pa` remain
open acquisition failures rather than exclusions.

This applies to the authoritative visual catalog. Prototype, location-test and
other pre-release sets are deliberately excluded from Libretro NVRAM
management, from automatic initialization and from the supplemental binary
campaign.

Run a Service Menu acquisition campaign for every runnable ROM set in
`Games.xml` and catalog every setting available for each title. The source
inventory contains 63 sets, but the known bad dump `mgtrkbad` is excluded. The
campaign therefore covers 62 sets: 22 parents and 40 clones. The catalog is not
limited to settings already exposed by the core.

The narrower initial scope applies only to supplemental samples and binary
validation. Reuse the tested parent recipes and their existing `.srm` samples
as the starting point for the settings currently exposed as Libretro `NVRAM
Settings`; generate a new sample only when an exposed photographed value has no
corresponding recipe/sample, when the existing artifact is not verifiable, or
when the comparison finds a discrepancy. That implementation currently covers
56 sets: 22 parents and 34 clones. Settings found in the Service Menu but not
yet exposed must still be recorded in the catalog and identified as
implementation gaps; they do not require supplemental `.srm` samples during
this first campaign.

The supplemental clone campaign is complete for all 34 released clones managed
by the core: 461/461 values were acquired from clone-specific baselines and
matched uniquely with valid structure, integrity, and persistence. Direct
evidence removed the inherited Asia value from `vf3a` and changed `dayto2pe`
Cabinet Type from Twin/Deluxe to Twin/Special with its clone-specific Backup
RAM route. Prototype, location-test, and other pre-release sets remain outside
this binary NVRAM scope.

The campaign must produce two repository documents modelled after the SM2-Emu
reference work:

- an authoritative [`GAME_SETTINGS_CATALOG.md`](GAME_SETTINGS_CATALOG.md), derived from Service Menu
  screenshots and recording every available setting's visible label, relative
  order, native default, and every observed selectable value for each set;
- an [`NVRAM_SETTINGS_AUDIT.md`](NVRAM_SETTINGS_AUDIT.md) comparing that catalog with
  `LibretroNvramSettings.h`, including option presence, order, labels, values,
  defaults, encoded values, integrity updates, template routing, and clone
  routing. Settings present in the catalog but absent from the implementation
  must be listed explicitly without expanding the initial sample scope.

### Acquisition rules

1. Build the full catalog inventory from every set in `Games.xml`. Build a
   separate supplemental-sample inventory from the NVRAM options registered by
   the core at the start of the campaign. Exclude known bad dumps explicitly
   rather than treating them as missing evidence. Record the exact core revision and
   `Games.xml` revision used for the evidence.
2. Acquire a clean native baseline for every supported set with `Automatic
   Initial NVRAM Setup` and `NVRAM Settings` disabled. Each option cycle must
   restart from that immutable baseline rather than from the preceding sample.
3. Capture every Game Settings page and enumerate every distinct selectable
   value for every setting. Screenshots are authoritative for visible presence,
   order, labels, values, and native defaults; implementation tables, TOML
   recipes, and parent metadata are secondary evidence.
4. Keep ROMs, generated Save RAM, raw screenshots, logs, and temporary frontend
   profiles outside Git. Commit the reproducible campaign definitions, the
   indexed catalog, the audit, and validation tooling.
5. For settings in the supplemental-sample inventory, first match every
   photographed value to the current recipe suffix and existing `.srm` sample.
   Reuse that sample to confirm byte encoding, checksum or mirror update, clean
   import, and persistence after a second launch. Generate a replacement or
   additional sample only for a demonstrated gap. Catalog-only settings do not
   require generated samples in this first campaign.

### Parent and clone criteria

- Acquire every clone directly. A `parent` relationship in `Games.xml` does not
  prove that labels, order, values, defaults, offsets, checksums, or storage
  layout are compatible.
- A clone may share a parent catalog only after its own evidence confirms the
  same complete visible menu. For settings in the supplemental-sample
  inventory, every exposed value must also be written and persisted with the
  parent encoding rules.
- The 38 clone `menu-structure.srm` files are native baselines used to document
  menu structure and defaults. They are not per-value samples and do not, by
  themselves, complete the supplemental clone campaign.
- A byte-identical native baseline alone is insufficient to authorize catalog
  inheritance. Conversely, a different baseline does not require a different
  catalog when direct menu acquisition and complete write validation prove the
  same option semantics.
- Any clone difference produces a clone-specific catalog or routing rule and is
  recorded in a parent/clone comparison matrix. No unacquired value is inferred
  from the parent.
- Derive clone diagnostic definitions and sampling recipes from the parent only
  after the clone's own Test Menu and Game Settings pages have established its
  visible rows, order, and defaults. Use the tested parent recipe as navigation
  scaffolding, not as evidence of clone equivalence.

### Default and override policy

Align Supermodel with the SM2-Emu distinction between native defaults and
deliberate policy overrides:

- the native default is the value visible in the clean Service Menu baseline;
- ordinary Core Option defaults must match that native value unless the setting
  is listed as a reviewed policy override;
- policy overrides are limited to region selection (Export when available,
  otherwise USA), a safe offline or stand-alone network state, and any
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

- 100% of the 62 runnable sets and every available setting have indexed Service Menu
  evidence, including every clone;
- every currently exposed NVRAM option is accounted for, and no unreviewed
  option or value remains exposed;
- every catalog setting absent from the implementation is listed explicitly;
- for the currently exposed subset, catalog and implementation agree on
  presence, order, labels, accepted values, native defaults, encodings, and
  integrity handling;
- every clone route is supported by clone-specific evidence;
- native defaults and deliberate overrides are reported separately and covered
  by automated checks;
- clean initialization, option application, save import, and persistence pass
  for every set and setting in the supplemental-sample inventory before the
  audit is marked complete.

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
