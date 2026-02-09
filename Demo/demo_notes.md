# Demo Notes

This demo shows GINP running under scale with physics collisions.

Key points:
- Visual feedback is driven by CPU-side causal evaluation
- O(1) per-instance computation
- Temporal decay + explicit steady-state recovery to avoid meaningless updates
