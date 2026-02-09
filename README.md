# GINP — Causal Impulse Sensing Framework (v1)

> **GINP** is an experimental Unreal Engine–based causal sensing framework.  
> It observes physical state changes at runtime and propagates them into
> material-level visual responses through a deterministic, entropy-controlled pipeline.

This repository represents **Version 1** of the project:  
a *demo-aligned*, *research-first* release intended to establish a reproducible
baseline before performance and architectural optimizations are introduced.

---

## Core Idea

GINP implements a **causal sensing loop** driven by physics:

Physical Motion → Causal Mapping → Entropy-Controlled Smoothing → Material Response


At runtime, the system:

1. Listens to physical state changes (e.g. velocity magnitude)
2. Maps them into a scalar “causal intensity”
3. Applies entropy-reducing temporal smoothing
4. Synchronizes the result across all relevant material slots

The goal is **not visual effects**, but **causal coherence**:
visual state reflects physical truth in a stable, reversible manner.

---

## Technical Stack

- **Unreal Engine 5**
- **C++ Actor Component**
- **Material Instance Dynamic (MID)**
- **Physics-driven Tick evaluation**

The current implementation focuses on **correctness and reproducibility**,
not maximum performance.

---

## Repository Structure

GINP/
├─ Plugin/ # Core Unreal Engine source (source-library style)
├─ Demo/ # Demonstration assets / videos
├─ docs/ # Architecture notes and design rationale
├─ experiments/ # Exploratory or unstable research code
├─ validation/ # Verification, comparison, or sanity checks
├─ src/ # Auxiliary or non-UE source code
├─ tools/ # Python and utility scripts
├─ _imported/ # Archived original source materials


### Structure Notes

- This project intentionally **does not follow a Marketplace-style plugin layout**.
- The `Plugin/` directory contains **source-level library code**, designed to be
  integrated into existing Unreal Engine projects or plugins.
- `_imported/` preserves original materials for traceability and auditability.
- `experiments/` and `validation/` coexist by design:
  exploration and verification are treated as separate concerns.

---

## Demo Alignment (v1 Focus)

Version 1 prioritizes **behavioral alignment with the demo**:

- The code path is intentionally simple and explicit
- Tick-based updates are used for clarity
- Known performance limitations are accepted at this stage

If the demo behaves correctly, v1 is considered successful.

---

## Known Limitations (v1)

The following aspects are **explicitly acknowledged** and deferred:

- Performance impact under large actor counts (100+)
- High-frequency material parameter updates
- Advanced threading or async optimization
- API stability for external users

These are planned for **post-v1 incremental patches**, not silent refactors.

---

## Design Philosophy

- **Truth before optimization**
- **Reproducibility over cleverness**
- **Architecture before polish**
- **Versioned improvement instead of premature perfection**

This project explores a path that has little prior art.
As such, clarity and auditability are prioritized over convention.

---

## License

This project is released under the terms specified in the `LICENSE` file.

---

## Status

- **Current Version:** v0.1.0 (initial public baseline)
- **Stability:** Experimental
- **Intended Audience:** Engine developers, technical artists, researchers
