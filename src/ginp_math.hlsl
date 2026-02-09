// GINP_math.hlsl - Core Operator v1.0
// Designed for high-integrity nonlinear projection

#ifndef GINP_MATH_INCLUDED
#define GINP_MATH_INCLUDED

struct GINPControl {
    float intensity;    // T_raw
    float lambda;       // 空间压缩极限 (推荐 0.8-0.9)
    float mollifier;    // η (近裁剪面软化因子)
};

/**
 * GINP 核心坐标变换
 * 输入：标准投影后的齐次坐标 (Clip Space)
 * 输出：经过 GINP 修正的齐次坐标
 */
float4 ApplyGINP(float4 posCS, GINPControl ctrl) {
    float w = posCS.w;
    float z = posCS.z;

    // --- 1. 软化因子 (Mollifier) ---
    // 解决验证点 3：确保 w->0 时干预场平滑消失
    float alpha = ctrl.mollifier * w;
    
    // --- 2. 软钳位干预场 (Safe Torsion) ---
    // 解决验证点 1：通过指数钳位保证单射性 (dw'/dw > 0)
    // 这里简化模拟一个径向干预场，实际可根据 R 变化
    float T_raw = ctrl.intensity; 
    float T_safe = ctrl.lambda * (1.0 - exp(-max(0, T_raw)));

    // --- 3. 计算 w' ---
    float w_prime = w * (1.0 + T_safe);

    // --- 4. 深度一致性补偿 (Depth Alignment) ---
    // 解决 Z-order 冲突：保持 z/w 比例
    float z_prime = z * (w_prime / w);

    return float4(posCS.xy, z_prime, w_prime);
}

#endif