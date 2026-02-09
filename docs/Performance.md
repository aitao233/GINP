# Performance & Runtime Boundary Statement (v1)

This document defines the **explicit performance boundaries** of GINP v1.

It does not propose optimizations, nor does it claim efficiency.
Its purpose is to clearly state **what is known, what is accepted, and what is deferred**
at the current stage of development.

---

## Scope of This Document

This document answers three questions only:

1. What performance risks are **known and acknowledged** in v1?
2. What behaviors are **intentionally accepted** in order to preserve correctness?
3. Where future optimization efforts are expected to occur (without committing to solutions)?

It does **not** describe architectural intent or theoretical foundations.
Those are intentionally deferred.

---

## Runtime Model (v1)

GINP v1 operates under the following runtime model:

- Per-Actor **Tick-based evaluation**
- Physics state sampling performed on the **Game Thread**
- Material synchronization via **Material Instance Dynamic (MID)**
- No batching, no caching across Actors
- No temporal decoupling between physics sampling and visual response

This model prioritizes **causal clarity and reproducibility** over throughput.

---

## Known Performance Risks

### 1. High-Frequency Material Parameter Updates

In v1, each active Actor may update one or more material parameters per Tick:

- `SetScalarParameterValue`
- `SetVectorParameterValue`

Under scenarios involving:
- 100+ Actors
- Multiple material slots per Actor
- Full Tick-rate execution

this may introduce measurable pressure on:

- Render Thread
- RHI submission path
- Material parameter update pipelines

This behavior is **intentional and unoptimized** in v1.

---

### 2. Actor Count Scaling

GINP v1 does not implement:

- Actor-level throttling
- Update frequency reduction
- Spatial or relevance-based culling

As a result, runtime cost scales approximately linearly with:

Actor Count × Material Slot Count × Update Frequency


No upper bound is enforced by the system.

---

### 3. Tick Granularity

All logic executes in `TickComponent`.

This guarantees deterministic, frame-aligned behavior,
but also couples system cost directly to frame rate.

No fixed-step simulation or temporal downsampling is applied in v1.

---

## Numerical Stability Boundaries

### Intensity Range Assumptions

GINP v1 assumes that all externally propagated scalar values remain within
a **finite and well-defined range**.

While Unreal Engine material parameters support large floating-point values,
the following risks are acknowledged:

- Extreme intensity amplification may lead to:
  - Visual instability
  - NaN or Inf propagation in material graphs
  - GPU-specific undefined behavior

v1 does not attempt to sanitize or clamp values beyond basic safeguards.

---

## Threading & Synchronization

GINP v1 adheres to the following constraints:

- Physics state is sampled from components accessible on the Game Thread
- Material parameter updates are performed on the Game Thread
- No direct interaction with async physics callbacks is performed

This avoids explicit cross-thread synchronization,
at the cost of tighter coupling between physics observation and rendering updates.

---

## Measurement & Observation (Recommended)

While no benchmarks are enforced in v1, the following Unreal Engine tools
are recommended for observation:

- `stat unit`
- `stat game`
- `stat rhi`
- `stat materials`
- `profilegpu`

Performance behavior should be evaluated under controlled scenarios
with varying Actor counts and material slot complexity.

---

## Deferred Optimization Areas

The following areas are **explicitly deferred** beyond v1:

- Update throttling or temporal downsampling
- Change-threshold–based material synchronization
- Cross-Actor batching or aggregation
- Render-thread–aware parameter submission strategies
- Alternative update paths outside of Tick

No implementation strategy is implied by this list.

---

## Design Position

GINP v1 makes a deliberate trade-off:

> **Truth and causal coherence are prioritized over performance efficiency.**

This version establishes a behavioral baseline.
Subsequent versions may introduce optimizations,
but only after correctness and reproducibility are firmly established.

---

## Status

- **Applies to:** v0.1.x
- **Optimization level:** None (by design)
- **Stability:** Experimental
- **Intent:** Boundary declaration, not performance guarantee