// GINP_Core.hlsl - Global Injective Nonlinear Projection Core v1.0
// ----------------------------------------------------------------

#ifndef GINP_CORE_INCLUDED
#define GINP_CORE_INCLUDED

// 核心参数：可以由 Material Property 或 Constant Buffer 传入
// _GinpStrength: 干预强度
// _GinpEta: 软化因子 (推荐值 0.05 - 0.1)
// _GinpCenter: 扭转中心 (屏幕空间 UV)

float4 ApplyGINP(float4 clipPos, float strength, float eta, float2 centerUV)
{
    // 1. 提取原始齐次坐标
    float w_orig = clipPos.w;
    
    // 2. 尺度无关 Mollification (基于你验证的 alpha = eta * w)
    float alpha = eta * w_orig;
    
    // 3. 计算屏幕投影距离 r
    // 将 clip space 映射到 [-1, 1] 的 UV 空间进行计算
    float2 uv = clipPos.xy / (w_orig + 0.00001f);
    float r = length(uv - centerUV);
    
    // 4. 原始干预场计算
    float rawTorsion = strength / sqrt(r * r + alpha * alpha);
    
    // 5. 【单射性保护】核心公式 (基于你验证的绿色曲线)
    // T_safe = 0.95 * (1 - exp(-T_raw))
    float safeTorsion = 0.95f * (1.0f - exp(-max(0.0f, rawTorsion)));
    
    // 6. 执行 w 轴干预
    float4 ginpPos = clipPos;
    ginpPos.w = w_orig * (1.0f + safeTorsion);
    
    // 7. 【深度一致性修正】核心公式 (基于你验证的 Z-Order 单调性)
    // z' = z * (w' / w)
    ginpPos.z *= (ginpPos.w / w_orig);
    
    return ginpPos;
}

#endif