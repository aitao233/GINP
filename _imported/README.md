# GINP — Causal-Driven Visual Feedback for Unreal Engine

GINP is a design-driven Unreal Engine plugin that maps **physical causality** (e.g., velocity / inertia) into **perceptual feedback** (emissive intensity & color) with **predictable cost** and **stable scaling**.

GINP is not a shader trick library.
It is a **causal control framework** that answers one question:

> When is an effect worth existing — and when should the system return to silence?

---

## Demo

This repository includes a performance demo showing **hundreds of physics-enabled emissive spheres** under continuous collisions while holding a stable frame rate (FPS locked at 60 in the test project).

- Demo video: see `Demo/`
- Notes: `Demo/demo_notes.md`

---

## Why GINP

Many visual effects pipelines scale by pushing complexity into:
- shaders
- bloom tuning
- post-process stacks
- particle systems

Those tools are powerful — and widely explored.

GINP explores a different axis:
- **system-level decision making**
- **explicit steady-state recovery**
- **avoidance of meaningless updates**
- **O(1) per-instance logic**

---

## Core Principles

### 1) Simple
No hidden state machines. No implicit magic.
Every visible result should be traceable to a clear cause.

### 2) Portable
Component-first design.
Attach to spheres, characters, props, ships — anything with a primitive component.

### 3) Efficient
GINP optimizes for **when to stop**.
When motion disappears, the system **explicitly returns to steady state** and skips redundant parameter submission.

---

## High-Level Architecture

**Cause → Mapping → Temporal Decay → Effect**

1. Sample physical signal (e.g., `GetPhysicsLinearVelocity()`)
2. Map to normalized causal space `[0..1]`
3. Apply temporal smoothing / decay
4. Drive material parameters (emissive intensity / color)
5. If stable & near-zero, **explicitly stop updating**

---

## Installation (Unreal Engine)

1. Copy the plugin folder into your project:
   - `YourProject/Plugins/GINP/`
2. Regenerate project files (if needed) and build.
3. Add the component to an actor with a `UPrimitiveComponent` root (or adjust to your mesh component).
4. Ensure the material uses parameters:
   - `GINP_Intensity`
   - `GINP_Color`

> Note: this repo focuses on architecture + validation. A minimal sample project may be provided under `Samples/` over time.

---

## Validation & Benchmarks

See:
- `Docs/Benchmarks.md`
- `Docs/Validation.md`

The key claim is not “the effect looks fancy”.
The key claim is:

> The system remains stable and predictable under scale because it avoids meaningless updates and treats steady state as a declared state.

---

## Design Trade-offs

GINP intentionally moves part of the “should we render with high fidelity?” decision
from GPU-side complexity to CPU-side **causal evaluation**.

This is not to “fight shaders”.
It is to make performance and system behavior **predictable, debuggable, and scalable**.

See `Docs/Design.md`.

---

## Documentation Map

- `Docs/Overview.md` — quick start & conceptual entry
- `Docs/Design.md` — trade-offs & engineering rationale
- `Docs/Theory/` — theory notes and derivations
- `Docs/Benchmarks.md` — how to reproduce performance tests
- `Docs/FAQ.md` — common questions

---

## License

Choose a license before public release:
- MIT (simple)
- Apache-2.0 (explicit patent grant)

See `LICENSE`.

---

## Contributing

This project is design-driven and aims to stay simple and stable.
See `CONTRIBUTING.md`.
