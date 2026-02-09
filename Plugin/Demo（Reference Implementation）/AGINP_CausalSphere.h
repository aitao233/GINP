#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// 把所有其他的 include 都放在上面

// 必须放在最后一行！
#include "AGINP_CausalSphere.generated.h" 

UCLASS(ClassGroup = (GINP), meta = (BlueprintSpawnableComponent))
class GINP_PROJECT_API UGINPCausalComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGINPCausalComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // --- 协议阈值 (Entropy Thresholds) ---
    static constexpr float CAUSAL_EPSILON = 0.001f; // 显式熵减阈值：低于此值视为回归虚无

    // --- 注入参数 ---
    UPROPERTY(EditAnywhere, Category = "GINP | Logic")
    float Sensitivity = 0.0005f;

    UPROPERTY(EditAnywhere, Category = "GINP | Logic")
    float EntropyRate = 12.0f; // 即原 ResponseDecay，语境升级为“熵减速率”

    // --- 资源感知 (Multi-Slot Support) ---
    UPROPERTY()
    TArray<TWeakObjectPtr<UMaterialInstanceDynamic>> CausalMaterialChain;

    TWeakObjectPtr<UPrimitiveComponent> CachedPhysicsBody;

    float InternalIntensityBuffer;

    // --- 内部算子 ---
    void SynchronizeCausalState(float NewIntensity);
};