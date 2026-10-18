# Roadmap

Updated: 2026-10-18

Reference: [Libretro Core Framework 0.1.37](/Users/andrea/dev/libretro-core-framework/FRAMEWORK.md).

This is the sole current implementation roadmap. Completed means the stated
scope and evidence are complete; it does not imply all-platform gameplay or a
published release. The user authorized commit, push and a GitHub project-page update on
2026-10-18. No new tag or release was requested. Generated local evidence and
build artifacts remain outside the source publication.

Legend: 🟢 Completed · 🟡 Partial · ⚪ Not Started · 🔵 Deferred

| Status | Activity | Remaining Work |
| --- | --- | --- |
| 🟢 | F04 — Frontend Option Ordering | Implemented and installed locally. Profile/Rumble precede specialized Input groups; Star Wars controls are last. Approved Video follow-up groups Rendering, Image, then Timing/Diagnostics. Original whole-menu UI acceptance retained; follow-up API 0/1/2 and four header configurations pass. System/native order retained. |
| 🟢 | F04 — Final Registered Menu Wording Audit | 255 definitions and 36 applicable workbook rows pass; full per-key metadata preserved. V2/V1/V0 order, 22 network pairs, exact help and four conditional header configurations checked. |
| 🟢 | F14 — Two-Option Networking | Native authority, handover and retained transport are implemented; initial real two-peer exchange is verified. User-approved fallback retains immediate effective-change application during non-pausing Netplay menus. See the 2026-10-18 feasibility follow-up for the explicit timing limit. |
| 🟢 | F05/F12 — Effective NVRAM Reset | Paused menus coalesce effective edits into one reset on Resume; unchanged/alias-equivalent settings do not reset. Explicit Restart consumes pending choices. During non-pausing Netplay, effective edits apply immediately; the user accepted retaining this behavior if reliable menu-exit deferral is unavailable. |
| 🟢 | Audio Recovery After Machine Reset | Startup and reset share the primed audio-queue initialization. Old/new PCM regression, real RetroArch recording, matching Multi-threaded + GPU playback before/after reset confirmed by the user, and existing Daytona 2 network lifecycle regression pass. Standard local core installed; no driver or user-configuration change. |
| 🟢 | F09 — Global Controller Profile Type | Full default and Normal mode implemented; paused metadata, both ports, remapping/None and legacy behavior checked. |
| 🟢 | F09 — Service/Test Order And VR1 | L3 Service / R3 Test retained. Single-View profiles bind D-Pad Up and Down to Change View where neither conflicts; native/keyboard bindings and VR4 distinctions retained. |
| 🟢 | F10 — Lightgun Standard And Reload | Combined-source arbitration and The Lost World reload behavior implemented; constant off-screen status alone does not take Lightgun ownership. Existing dedicated modes retained. |
| 🟢 | F21 — RetroArch Notifications | Extended notifications and fallback paths verified; actual Resume/reset OSD inspected. |
| 🟢 | F04/F05/F07 — Reviewed Names And Help | Canonical wording applied with documented Sound Volume and Internal Resolution exceptions. Values/defaults and native operator labels retained. |
| 🟢 | F06 — NVRAM Master Visibility | Per-set reviewed-field gating and saved selections retained; managed network fields use ANRS authority while unrelated fields keep normal management. |
| 🟢 | F13 — Supplemental Release-Clone NVRAM Campaign | 472/472 acquired values across 35 release clones validate. Existing valid samples are retained; no regeneration required by menu ordering. |
| 🟢 | F13 — Scud Australia Correction And Acquisition | Eight settings, thirty distinct values, 52 primary photographs and eleven native-committed/fresh-reloaded samples. Recipe, YAML, workbook, two network overrides and initial seed reconciled. |
| 🟢 | F13 — Common Campaign Workbook | Common four-sheet summary adopted, with Framework 0.1.33 core-specific verification columns: 605 native setting rows, 62 sets, all 177 implemented controls and 50 actual EEPROM seeds reconciled with source. Four obsolete Country exposure flags corrected. Historical records preserved in notes; five replaced summary files removed. |
| 🟢 | Selected Upstream Quad/Catalogue Integration | OpenGL 4.1/macOS Quad adaptation and corrected vs298 catalogue CRC integrated locally. Reviewed upstream snapshot and exclusions remain in the integration ledger; no fresh upstream review is implied. |
| 🟢 | Quad Rendering Performance Investigation | Closed by the user. The Mac geometry-stage/draw-path penalty was isolated; tested workarounds did not produce a safe production correction. |
| 🟢 | Existing Multi-Platform CI And Release Artifacts | Commit 4566c94 / release 0.3.0-beta already passed Linux x86_64, Windows x86_64 and both macOS jobs, including format/API/dependencies and artifact assembly. Reconfirmed from GitHub run 36183994220 on 2026-10-18. |
| 🟢 | F18/F19 — New Package Checks | Source `c12cd392` passed all four desktop CI jobs, including runtime identity, inventory, XML, notices, provenance, checksums and artifact upload. Linux host-GL and Windows Git prerequisites corrected. [CI evidence](https://github.com/Zer0one/Libretro-Supermodel/actions/runs/39134741470). |
| 🟢 | Source Publication And GitHub Page | Accumulated source/docs committed and pushed; README and repository description updated. `supermodel-modern` is the default branch; `master` is retained. Four-platform CI passed. The existing release is unchanged. |
| 🟡 | F13 — Complete Visual Game Settings Catalogue | 120/130 pending parent cycles completed, plus Bass Fishing Event Game Time; 720 cycle photographs and two contexts archived. YAML/Excel/catalogue reconciled. Only ten vs298 rows remain blocked by the local ROM CRC mismatch. |
| 🔵 | Optional Standalone GUI/Configuration Changes | Review upstream GUI/configuration changes only if a core-owned writer needs them. RetroArch owns the option GUI; the current adapter does not rewrite user INI files. |
| 🔵 | F15 — Multi-Core Launcher | Owned by the separate launcher project. Do not build a second launcher in this repository. |

## Current Local Delivery

The 2026-10-18 audio-reset correction is the current installed macOS ARM build:
`5cca917dc93bcc9ea9b65377d5f87658533038c14c1bee20506b4e04442c7862`.
It includes the earlier menu delivery (`ca0360e3…eef235`).
The configured standard `supermodel_libretro.dylib` matches the build; .info and
external System assets are unchanged by the menu/audio deliveries.

See [the menu ordering/audit report](CORE_OPTIONS_ORDER_AUDIT_2026-10-18.md).
Its Video follow-up records eight changed Video positions with all 255 per-key
definitions preserved and the new build installed. The original audit records
28 changed positions, unchanged metadata for all 255 definitions and
177 native operator fields, System's exact 225-definition sequence, the full
workbook audit and actual RetroArch ARM 1.22.2 / Ozone page inspection. The shared
review workbook and per-core workbook Order IDs are unchanged. Earlier installed
hashes identify historical deliveries, not additional cores to deploy.

The implementation uses the existing definition sequence rather than a new
runtime ordering layer. Scoped source/rebuild rollback follows F20; binary
backups are not routine. Before future delivery, reread active RetroArch paths,
resolve symlinks and verify installed hashes. The active external System root
last resolved to `/Volumes/MacBook External Drive/Retro/_Media/_Multi (RetroArch)/system`.

## Current Networking Contract And Limits

The [two-option integration report](NETWORK_TWO_OPTION_2026-10-17.md) is the
current networking baseline. Earlier Network Board / ANS instructions are
superseded, not pending work.

- Exactly two controls are visible: Linked Cabinets and Auto Network Role
  Settings (ANRS); unsupported games show the Not Supported pair.
- Linked Cabinets defaults to -1 Disabled, with 0/1 aliases. All currently
  reviewed Model 3 boards are optional, so Disabled disconnects the board.
  Required-board local loopback is the conditional Framework rule, not a claim
  that these Model 3 games require fitted boards.
- ANRS independently defaults to the native Single / Stand Alone / No Link role.
  Disabled returns manual authority to the last applied native values. Active
  ANRS works with NVRAM Settings disabled and hides only its managed fields.
  Topology does not silently convert the selected role.
- Effective topology/role/identity changes reset once on the next emulation
  frame: on Resume for paused menus, immediately for non-pausing Netplay menus.
  Explicit Restart consumes pending choices too. Content and the frontend lobby
  stay loaded; connected clients/callback ownership survive and transient
  staggered setup can recover.
- Per-title totals are reviewed/theoretical: Daytona 2–17, Scud 2–8,
  Dirt Devils/Le Mans/Rally/Virtual On 2–5, Harley/Ski Champ/Spikeout 2–4.
  These totals are not multiplayer gameplay qualification.
- Protocol v3 peers must use matching updated cores. Source/native/ABI checks
  cover 22 sets and 159 presets. Actual two-instance Scud tests establish a
  2/2 roster and first data exchange, including frontend host/native Master on
  different peers. Synchronized racing, every role combination, maximum totals,
  linked-board Save States and other platforms remain unqualified.

The current activity does not open another networking implementation or imply
that those additional qualifications are complete.

## Remaining Visual Catalogue Work

Use the [Service Menu and NVRAM summary](Service_Menu_NVRAM_Summary.xlsx),
diagnostic YAML and reviewed recipes. This is the sole current campaign
summary: Core options, Campaign, Calibration and Automatic setup. It has
209 parent setting rows and 396 clone setting rows. Implementation flags,
selector defaults, raw keys/encodings and startup overrides are checked against
the current code, including all 171 native logical settings and six operational
calibration controls. The 50 EEPROM seeds are read from the actual template
header, separately from the fields applied by automatic initialization.
The original workbook rows, clone coverage and four replaced narrative reports
are preserved losslessly in cell notes, with source hashes and historical
status. Current table status supersedes older conclusions. Native defaults
remain bold in Observed Values and distinct from frontend defaults.

The summary records 121 newly verified cycles, including one newly discovered
conditional field; ten vs298 cycles remain pending. Thirteen other clone rows
still lack direct value cycles; 250 clone value lists explicitly cite parent
evidence. The supplemental binary
campaign is complete at 35 release clones / 472 acquired values; this does not
complete every photographic value cycle.

Campaign uses Model 3 evidence-specific columns: Sample Validation, Persistence
Verification and Integrity Verification. The 22 parent recipe campaigns retain
their accepted 355 samples and photographic reconciliation; a separate frontend
reload or per-sample integrity report is not inferred. The 35-clone results
distinguish native encoding/integrity checks from save-container persistence
simulation. Scud Australia additionally records eleven fresh RetroArch reloads
and explicit CRC/mirror checks. Backup RAM families are not labelled as EEPROM
CRC tests. Fixed frame checkpoints are not imposed on unrelated methods. This
documentary adaptation opens no new acquisition campaign and changes neither
the core, existing valid samples nor runtime policy.

1. Resume only the ten blocked vs298 cycles after the required ROM is available.
   The other 120 previously pending parent cycles and Bass Fishing Event Game
   Time are photographed and reconciled; reuse their validated manifest records.
2. Reconcile photographs against the existing YAML/recipes and samples. Preserve
   valid artifacts; generate supplemental SRM samples only for currently exposed
   settings with missing, invalid or contradicted evidence.
3. Propagate verified native mapping/default/integrity corrections to NVRAM
   Settings and Automatic Initial NVRAM when applicable. Separate native factory
   defaults from deliberate frontend overrides; retain Export-before-USA policy.
4. Keep parent evidence and direct clone evidence explicit. Do not infer a
   clone's field presence, ordering or encodings solely from its parent.
5. Check ROM availability when resuming acquisition. The vs298 catalogue expects
   `epr-20917.17` CRC `969E4BDA`. On 2026-10-18 both the Model 3 working copy
   and original MAME archive still contained CRC `C3BBB270`. Existing historical
   photographs and valid binary samples were retained; no ROM bypass was used.

For Scud Australia, normal operator-menu routing is restored. Native default is
Master / Car 1, while frontend ANRS defaults to Single. Only Link ID and Car
Number are exposed as overrides; the other six inventoried fields are documented
but remain unexposed. The old debug-menu photographs are historical diagnostics.

## Scope Exclusions And Deferred Decisions

Prototype analysis, inventories, acquisition, tests, implementation and maintenance
are excluded unless explicitly requested. Existing prototype records/support are
retained; old srally2p/srally2pa failures are not active completeness blockers.
Prototype and other pre-release sets remain outside the established automatic
NVRAM/override campaign. `mgtrkbad` was removed from the catalogue by user request;
Royal Ascot II is non-working and outside operational qualification.

The native widescreen assessment is complete: no verified Model 3 native widescreen
setting supports an SM2-style automatic aspect policy. Widescreen Mode remains an
explicit rendering enhancement. New primary evidence can reopen this assessment.
Synthetic cornering rumble has no counterpart to adopt: Supermodel forwards its
native drive-board commands. Neither result authorizes inventing a replacement.

Any future Quad rendering correction needs a demonstrated cause, preserved native
interpolation and controlled image validation. The completed investigation does
not authorize a replacement renderer or Vulkan backend.

## Package, Upstream And Publication Boundaries

[Upstream integration and release identity](UPSTREAM_INTEGRATION.md) records the
2026-10-13 reviewed snapshot, integrated/adapted/excluded changes and future
version scheme. This roadmap refresh is not an upstream update check. Optional
standalone GUI changes remain deferred; Libretro ownership is preserved.

The existing package gate assembles core, .info, Games.xml, Music.xml, notices,
source provenance and checksums. The existing [GitHub run 36183994220](https://github.com/Zer0one/Libretro-Supermodel/actions/runs/36183994220),
on commit 4566c94, already passed all four platform jobs on 2026-09-25, including
format/API/dependency validation and artifact assembly/upload. This was reconfirmed
on 2026-10-18; the published 0.3.0-beta binaries are not an outstanding task.

The 2026-10-18 source delivery is now committed and pushed: `14a740d6` contains
the accumulated implementation and documentation, followed by `c12cd392` for
the package-probe Linux host dependency and Windows MSYS2 Git prerequisite.
[GitHub run 39134741470](https://github.com/Zer0one/Libretro-Supermodel/actions/runs/39134741470) passed all four platform jobs on `c12cd392`,
including build, format/API/dependencies, package checks and artifact upload.
The final documentation-only publication record does not change that tested
production source. It skips a redundant rebuild.

The public README and repository description are updated, and the default
branch is `supermodel-modern`; the old `master` branch remains intact. Local
ROMs, saves, build products and raw test outputs were excluded from the push.
Platform runtime validation, Libretro distribution and publication remain
distinct. A later authorized release must reconcile runtime version, .info,
tag/title and release notes; no new release was created by this source delivery.

## Framework Reporting And Historical Evidence

The user authorized meaningful progress/finding/delivery reports to Framework
chat `01a13152-dbfa-7e30-bc9d-0477abc2cccc`, host `local`. Report source/registration,
actual frontend and installed identity separately, with paths/hashes and limits.
This authorization does not permit work in other core chats or publication.

The [historical roadmap snapshot](ROADMAP_HISTORY_2026-10-18.md) retains the prior
requirements, old counts/hashes and detailed provenance without presenting them
as active instructions. Referenced delivery reports remain evidence at their
recorded dates; their scope is not silently expanded by this reconciliation.

## Active Netplay Menu Lifecycle Follow-Up — 2026-10-18

The required workflow is to start both instances as native Standalone in an
existing lobby, edit Linked Cabinets and ANRS while the local Quick Menu is open,
then commit only the final effective choices with one local machine reset on
menu exit. The lobby, callbacks and connected roster must survive. Continuing
emulation for transport does not justify applying each intermediate edit.

Actual Daytona 2 checks distinguish paused offline menus from active Netpacket
menus. The first passes; the latter currently resets immediately per effective
ANRS change. The same symptom is reproduced in installed TGPulse with Virtua
Racing. SM2 has the same next-retro_run application pattern by source review;
its runtime behavior in this scenario is not yet qualified here.

The existing ABI runner treats its next retro_run as Resume and therefore does
not establish real menu-exit timing in Netplay. No supported menu-exit signal was
identified in the current ABI; throttle state cannot distinguish a non-pausing
Netplay menu. The user explicitly approved retaining current behavior if reliable
deferral is unavailable. Accordingly, immediate effective-change application is
retained in that context; paused-session behavior and lobby preservation remain
unchanged. A frontend lifecycle extension is a possible future investigation,
not an approved frontend implementation task. Details and evidence are
in [the networking report](NETWORK_TWO_OPTION_2026-10-17.md#active-netplay-menu-lifecycle-follow-up--2026-10-18)
and `outputs/anrs-menu-20261018/`. No production-code change, new core build,
commit or push is claimed by this investigation.

## Audio Reset Recovery — 2026-10-18

Fixed a persistent silent-output state caused by clearing the Libretro ring
buffer to identical read/write positions during reset. Reuse the existing
startup initialization, including its two silent packets, so the asynchronous
producer and consumer can restart. No emulated sound-board, gain, DSP, transport
or frontend-driver change is involved.

The installed old core produced only zero PCM throughout eight ten-second
windows after two resets. The corrected core recovered nonzero PCM after both.
Actual RetroArch recordings passed two resets in Single and one in the user's
Multi-threaded + GPU mode; the user also confirmed correct live sound before
and after reset in Multi-threaded + GPU without recording. Initial distorted
live playback under the first Single/recording trial was not reproduced under
the aligned no-recording setup; the recordings themselves were confirmed
correct. Its exact output-path cause is not established and no driver fix is
claimed.

Build/export/dependency checks and the reused Daytona 2 lifecycle regression
(18 presets, native/reset/handover/client retention) pass. Standard installed
core matches the build: `5cca917dc93bcc9ea9b65377d5f87658533038c14c1bee20506b4e04442c7862`. The two user instances
were closed normally after authorization; all QA instances exited normally.
Evidence: `outputs/audio-reset-20261018/verification.json`. No commit or push.
