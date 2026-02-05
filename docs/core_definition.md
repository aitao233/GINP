# GINP 核心协议定义 (v1.0 - Stable)

## 1. 核心公式 (Core Formula)
基于投影空间 w 轴的非线性度规干预：
$$w' = w \cdot (1.0 + T_{safe})$$

其中，$T_{safe}$ 采用 **Exponential Smooth-Clamping** 逻辑：
$$T_{safe} = 0.95 \cdot (1.0 - e^{-T_{raw}})$$
$$T_{raw} = \frac{Strength}{\sqrt{r^2 + (\eta \cdot w)^2}}$$

## 2. 物理安全性证明 (Safety Guarantee)
经 Python 解析验证（见 `experiments/python/analytic_test.ipynb`）：
- **单射性 (Injective)**：对于任意 $Strength > 0$，导数 $\frac{\partial w'}{\partial r}$ 始终满足 $> -1.0$。
- **结果**：空间拓扑结构在任何强度下均不会发生折叠、自交或塌陷。

## 3. 数值防御边界 (Boundary Defense)
- **数值下界**：$w'_{min} = d_{near}$ (强制对齐近裁剪面)。
- **尺度无关性**：引入 $\eta \cdot w$ 作为 Mollification 项，确保干预场随距离线性缩放。