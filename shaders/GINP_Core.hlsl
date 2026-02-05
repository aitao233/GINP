// GINP_Core.hlsl
float heightWeight = HeightLUT.Sample(LutSampler, WorldPos.y).r;
float mirrW = ScreenPos.w * (1.0 + heightWeight * Strength);
// TODO: Jacobian 能量补偿 & 空间扭转
