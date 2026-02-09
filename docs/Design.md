# Design

## Principles
- Simple
- Portable
- Efficient

## Key idea
GINP is not a shader trick library.
It is a causal control layer that decides when effects should exist and when the system should return to silence.

## Trade-offs
We intentionally avoid heavy GPU-side branching and complex post-process chains.
Instead, we use O(1) per-instance causal evaluation + temporal decay and an explicit steady-state stop condition.
