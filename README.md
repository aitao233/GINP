# GINP — Global Injective Nonlinear Projection

[![Status](https://img.shields.io/badge/Status-Validated-success.svg)]()
[![Mathematical Rigor](https://img.shields.io/badge/Logic-Formal_Proof-blue.svg)]()

**GINP** is a mathematically constrained rendering protocol designed to enable stable, non-Euclidean spatial transformations within standard GPU rasterization pipelines. 

By manipulating the homogeneous $w$-component through an injective metric, GINP allows for extreme spatial warping while maintaining 100% topological integrity and hardware compatibility.

---

## 🚀 Key Innovation: The "Safety First" Warp
Standard nonlinear distortions often break the rendering pipeline, causing spatial tearing and Z-fighting. GINP solves this by enforcing three foundational invariants:

1. **Global Injectivity**: Prevents spatial self-intersection (no "folding" of the world).
2. **Depth Consistency**: Preserves monotonic depth ordering for perfect Z-buffer rendering.
3. **Near-Plane Stability**: Eliminates numerical singularities near the camera clipping plane.

## 📊 Formal Validation
This repository provides reproducible numerical evidence for the protocol's stability.

| Property | Validation Status | Mathematical Tooling |
| :--- | :--- | :--- |
| **Global Injectivity** | ✅ Verified | Exponential Soft-Clamping ($\lambda$-constraint) |
| **Depth Monotonicity** | ✅ Verified | Homogeneous Re-alignment ($z' = z \cdot w'/w$) |
| **Near-Plane Safety** | ✅ Verified | Scale-Invariant Mollification ($\alpha = \eta \cdot w$) |

> **Documentation Index**:
> - [Core Definitions](./docs/theory/ginp_core_definitions.md): The mathematical "Constitution" of GINP.
> - [Proof of Injectivity](./docs/theory/injectivity_proof.md): How we prevent spatial collapse.
> - [Validation Summary](./docs/validation_summary.md): Full experimental results and figures.

## 🛠️ Repository Structure
- `/docs`: Formal proofs, core definitions, and high-resolution validation figures.
- `/src`: Reference implementations in HLSL and C++.
- `/validation`: Python-based numerical stress tests and experiment scripts.

---

## 📜 Academic & Engineering Context
GINP is designed for next-generation visual storytelling, VR lens correction, and non-Euclidean architectural rendering. It moves beyond simple vertex offsets by redefining the spatial metric at the projection stage.

---
*Verified by AI-enhanced formal logic & formal numerical simulation.*