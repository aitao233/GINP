// 如果你的头文件名叫 AGINP_CausalSphere.h
#include "AGINP_CausalSphere.h" 

// 如果你决定把文件名改成 UGINPCausalComponent.h (推荐)
// #include "UGINPCausalComponent.h" 

#include "CoreMinimal.h"
// ... 其他 include

UGINPCausalComponent::UGINPCausalComponent() : InternalIntensityBuffer(0.0f)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

void UGINPCausalComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (!Owner) return;

    CachedPhysicsBody = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
    if (CachedPhysicsBody.IsValid())
    {
        // [优化] 全槽位因果注入：解决你提到的多材质 Slot 问题
        const int32 MaterialCount = CachedPhysicsBody->GetNumMaterials();
        for (int32 i = 0; i < MaterialCount; ++i)
        {
            CausalMaterialChain.Add(CachedPhysicsBody->CreateDynamicMaterialInstance(i));
        }
    }
}

void UGINPCausalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!CachedPhysicsBody.IsValid()) return;

    // 1. 物理采样
    const float VelocityMagnitude = CachedPhysicsBody->GetPhysicsLinearVelocity().Size();

    // 2. 显式因果判断与自愈 (Self-Healing Logic)
    // 如果动量低于极小值，强制目标归零，触发熵减回归
    const float TargetIntensity = (VelocityMagnitude < 0.1f) ? 0.0f : FMath::Clamp(VelocityMagnitude * Sensitivity, 0.0f, 1.0f);

    // 3. 熵减平滑计算
    InternalIntensityBuffer = FMath::FInterpTo(InternalIntensityBuffer, TargetIntensity, DeltaTime, EntropyRate);

    // [高级优化] 显式停机：如果系统已回归稳态，跳过 GPU 昂贵的参数提交
    if (InternalIntensityBuffer < CAUSAL_EPSILON && TargetIntensity == 0.0f)
    {
        if (InternalIntensityBuffer != 0.0f)
        {
            InternalIntensityBuffer = 0.0f;
            SynchronizeCausalState(0.0f); // 确保最后一次回归纯黑
        }
        return;
    }

    // 4. 执行状态同步
    SynchronizeCausalState(InternalIntensityBuffer);
}

void UGINPCausalComponent::SynchronizeCausalState(float NewIntensity)
{
    const FLinearColor TruthColor = FLinearColor::LerpUsingHSV(FLinearColor::Black, FLinearColor::White, NewIntensity);

    // 遍历因果链：确保复杂模型的所有部分感知一致
    for (auto& MatPtr : CausalMaterialChain)
    {
        if (MatPtr.IsValid())
        {
            MatPtr->SetScalarParameterValue(TEXT("GINP_Intensity"), NewIntensity);
            MatPtr->SetVectorParameterValue(TEXT("GINP_Color"), TruthColor);
        }
    }
}