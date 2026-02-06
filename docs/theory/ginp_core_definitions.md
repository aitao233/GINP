# GINP Core Definitions (v1.0)

## 1. Abstract
The **Global Injective Nonlinear Projection (GINP)** is a rendering protocol designed to enable stable, non-Euclidean spatial transformations within standard GPU rasterization pipelines. Unlike vertex-offset-based FX, GINP operates on the **Homogeneous Degree of Freedom ($w$)**, ensuring global topological integrity through rigorous injective constraints.

---

## 2. Theoretical Foundation: The GINP Transform
The core of GINP is the manipulation of the four-dimensional clip-space vector $V_{clip} = [x, y, z, w]^T$. 

### 2.1 The Homogeneous Modification
We define the transformed homogeneous coordinate $w'$ as:
$$w' = w \cdot (1 + \Phi(P, \alpha))$$

Where:
- $w$: The original view-space depth (standard $Z_{view}$).
- $\Phi$: The **Torsion Field**, a spatial interference function based on position $P$.
- $\alpha$: The **Scale-Invariant Mollifier**, ensuring near-plane stability.

### 2.2 The Depth Alignment (Isomorphism)
To preserve the occlusion order (Z-Buffer integrity), the $z$ component must be re-scaled to maintain the projective ratio:
$$z' = z \cdot \frac{w'}{w}$$

---

## 3. Core Constraints (The Three Pillars)

To be "GINP-Compliant," an implementation must satisfy the following three mathematical invariants:

### Pillar I: Global Injectivity (C1 Continuity)
The spatial gradient must never reach the folding point. For any radial distance $r$:
$$\frac{dw'}{dr} > -1.0$$
*This prevents geometry from self-intersecting or "flipping" inside out.*

### Pillar II: Depth Monotonicity
The post-projection depth $Z_{ndc}$ must remain a strictly monotonic function of the world-space distance $Z_{world}$:
$$\frac{\partial (z'/w')}{\partial Z_{world}} > 0$$
*This ensures that Early-Z culling and Depth Testing function correctly.*

### Pillar III: Near-Plane Mollification
As the distance to the camera approaches zero ($w \to 0$), the torsion field $\Phi$ must decay such that the projection remains locally Euclidean:
$$\lim_{w \to 0} \Phi(P, \alpha) = 0$$
*This prevents numerical singularities and unintended clipping near the lens.*

---

## 4. Logical Pipeline Flow


1. **Input:** View Space Position $V_{view}$.
2. **Project:** Apply standard Projection Matrix $\mathbf{P} \cdot V_{view} \to [x, y, z, w]$.
3. **Inject:** Apply GINP Torsion Field $w \to w'$.
4. **Align:** Compensate $z \to z'$.
5. **Output:** $V'_{clip} = [x, y, z', w']$.

---

## 5. Glossary
- **Torsion ($T$):** The magnitude of spatial stretching or compression.
- **Mollifier ($\alpha$):** A damping factor used to maintain numerical stability at singularities.
- **Injective Mapping:** A mathematical property ensuring each point in view-space maps to exactly one point in clip-space.