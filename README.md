# GINP — Global Injective Nonlinear Projection

> 私有研究项目 — 21岁独立开发者原创

---

## 项目简介
GINP 是一套全新非线性投影协议研究项目，探索屏幕空间度规干预、单射性和解析能量补偿。

## 核心特点
- 齐次空间度规注入
- 单射性约束与屏幕亮度补偿
- 极端边界退化安全
- Shader 原型验证和小规模模拟

## 使用方法

1. **理论验证**
   - 查看 `docs/core_definition.md` 获取核心定义
   - 使用 `docs/derivations.md` 验证 Jacobian、能量补偿公式

2. **Shader实验**
   - 编译 `shaders/GINP_Core.hlsl` 并加载测试场景
   - 调整 `HeightLUT` 和 `Strength` 参数，观察屏幕空间折叠/扭曲效果

3. **模拟验证**
   - `experiments/python/analytic_test.ipynb` 可用于快速验证单射性、能量补偿、极限退化
   - 可修改测试 LUT 或高度场数据以模拟不同场景

---

## 项目状态
- 理论验证与小规模实验阶段
- 私有研究：禁止未经授权传播
