# GINP 核心定义

## 核心映射
- w 轴度规干预：w' = w * M(P, h)
- 单射性约束：Jacobian determinant > 0
- 尺度无关 Mollification：α(w) = η * w
- 能量补偿：σ = |1 + Strength * dHeight/dr|^{-1}

## 目标
- 保持几乎处处单射
- 保证屏幕亮度解析补偿
- 支持极端边界退化
