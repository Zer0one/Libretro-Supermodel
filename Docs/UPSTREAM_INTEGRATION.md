# Upstream Integration And Release Identity

Review Date: 2026-10-13

## Sources And Coverage

The port is based on `libretro/Libretro-Supermodel`, retaining the frontend
lineage of `sgiannop/Libretro-Supermodel`. Standalone `trzy/Supermodel` supplies
machine and renderer reference changes; a fetch is not an integration.

Port baseline before this delivery: `4566c9470ab89ec8e2738bfb43c18281df580971`.
Current reviewed standalone tip: `ed608de1c5f0f61dcad957cffe0ff8234cbc8e6c`.
The changes below are included in the 2026-10-18 source delivery on
`supermodel-modern`; this delivery does not assign a new release tag.
This ledger records the reviewed delta, not a claim that every older upstream
commit or future platform has been reconciled.

| Source Change | Disposition | Evidence / Boundary |
| --- | --- | --- |
| Libretro master `84bc106`; dev `f2e1e7d` — MinGW dependency/default-target fix | Integrated in `4566c94` | Existing Makefile has the default goal and generated-header prerequisites. No new import required. |
| Standalone `7d3b6f4`, PR #339 — Quad on OpenGL 4.1 | Adapted in this source delivery | Native shader body matches the same-revision upstream after removing its inline version directives. The port's central GLSL prefix is retained and also applied to geometry shaders. macOS now compiles the existing option; published default remains Disabled. |
| Standalone `b5125ca`, PR #327 — vs298 corrected dump | Integrated in this source delivery | CRC `969E4BDA` replaces `C3BBB270` in XML/DAT and the embedded catalogue. Local old-dump rejection is verified; corrected-dump gameplay is unavailable. |
| Standalone PR #336 — GUI preservation of per-game INI sections | Excluded from current Libretro delivery; optional roadmap review | The adapter does not write the user INI. No standalone configuration writer is introduced. |
| Standalone `44404c2`, PR #340 — GUI labels/custom values and helpers | Excluded from current Libretro delivery; optional roadmap review | RetroArch owns the option UI. Shared helper additions and mechanical cleanups stay in the optional review; they are not imported as emulator fixes. |

The LCF changes are port-specific frontend adaptations. They do not establish
additional standalone upstream coverage; their status is recorded only in
`ROADMAP.md`.

## WIP Version Scheme

Supermodel's upstream identifies snapshots as
`v0.3a-YYYYMMDD-git-SHA`, rather than a sequence such as SM2's `0.9.44`.
For a future snapshot-based port release, use the reviewed upstream snapshot
identity plus `-libretro.N`, where N is the port revision. Advance N for
port-only releases; restart it when the reconciled snapshot advances. The
release notes must state the exact integrated/adapted/excluded scope and any
applicable pending changes before assigning that identity.

This review assigns no new public tag and rewrites no historical release.
The existing public `0.3.0-beta` tag and runtime `v0.3a-libretro` remain
historical/current identities respectively. A later authorized release must
align runtime version, .info, tag/title and release notes in one scoped change.
Do not present the latest fetched upstream tag as the built port's version.

## Package Gate

Reuse the normal Makefile and existing binary format/export/dependency gate.
The CI then calls `.github/scripts/package-libretro-core.py CORE OUTPUT`;
`--check` verifies an already assembled directory. The package includes the
core, .info, Games.xml, Music.xml, license notices, source provenance and
SHA-256 checksums. Source provenance distinguishes a clean committed source
from a modified tracked working tree and records its fingerprint.

There is no additional runtime database/manifest or packaged default INI.
Embedded fallback and non-overwriting user overrides retain their existing
runtime ownership. The package gate compares actual runtime library identity
with metadata and checks every shipped file's hash and exact inventory.

The standalone desktop Linux identity probe preloads the system OpenGL library,
matching the frontend's host dependency while retaining eager symbol resolution.
The Windows MSYS2 environment explicitly installs Git for build identity and
source provenance; the checkout action's separate Git is not on that shell's PATH.

Historical multi-platform binary validation is complete: [GitHub run
36183994220](https://github.com/Zer0one/Libretro-Supermodel/actions/runs/36183994220),
commit `4566c9470ab89ec8e2738bfb43c18281df580971`, passed Linux x86_64, Windows
x86_64, macOS ARM64 and macOS x86_64 on 2026-09-25. Each job passed build,
format/API/dependency validation, artifact assembly and upload. The corresponding
0.3.0-beta artifacts were packaged and published; job results were reconfirmed
on 2026-10-18. They are not pending verification.

The 2026-10-18 source delivery (`14a740d6`, followed by package prerequisites
in `c12cd392`) passed [GitHub run 39134741470](https://github.com/Zer0one/Libretro-Supermodel/actions/runs/39134741470) on Linux x86_64, Windows
x86_64, macOS ARM64 and macOS x86_64. All four jobs passed binary validation,
package inventory/runtime identity/provenance/checksums and artifact upload.
The initial run exposed missing host OpenGL for the isolated Linux identity
probe and missing Git inside Windows MSYS2; both were corrected and the full
matrix rerun successfully. The final documentation-only record retains this
tested production source and skips a redundant rebuild.

This supersedes the previous pending status of the new checker; it does not
expand native gameplay qualification or update the existing release. CI success,
native gameplay, Libretro-hosted distribution and publication remain different
claims.
