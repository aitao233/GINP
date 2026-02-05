// GINP_Core.hlsl — 基础实验Shader
float heightWeight = HeightLUT.Sample(LutSampler, WorldPos.y).r;
float mirrW = ScreenPos.w * (1.0 + heightWeight * Strength);

// TODO: 补充 Jacobian 能量补偿逻辑
// TODO: 空间扭转 (Spatial Torsion) 实现
