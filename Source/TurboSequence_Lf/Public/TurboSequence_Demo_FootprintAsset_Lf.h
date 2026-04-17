// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_FootprintAsset_Lf.h"
#include "TurboSequence_MeshActorConnection_Lf.h"
#include "Engine/DataAsset.h"
#include "TurboSequence_Demo_FootprintAsset_Lf.generated.h"

USTRUCT()
struct TURBOSEQUENCE_LF_API FDemoMeshInstance_Lf
{
	GENERATED_BODY()

	float FadeTimeRuntime = 0.3f;
	bool bIsInUERange = true;
	bool bInit = false;
	int8 NumFrames = 0;
	// bool bCallDelegateNextFrame = false;

	float MinFadeExitTime = 0;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="UE 网格 Actor", ToolTip="指定演示模式下生成的 UE Actor 实例。"))
	TObjectPtr<AActor> Mesh;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="骨骼组件列表", ToolTip="指定演示模式下需要同步的骨骼网格组件。"))
	TArray<USkinnedMeshComponent*> SkinnedComponents;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Actor 连接组件", ToolTip="指定演示模式下使用的 TurboSequence 连接组件。"))
	TObjectPtr<UTurboSequence_MeshActorConnection_Lf> ActorConnection;
};


/**
 *
 */
UCLASS(BlueprintType)
class TURBOSEQUENCE_LF_API UTurboSequence_Demo_FootprintAsset_Lf : public UTurboSequence_FootprintAsset_Lf
{
public:
	GENERATED_BODY()

	virtual void OnSetMeshIsVisible_Concurrent(ETurboSequence_IsVisibleOverride_Lf& IsVisibleOverride,
	                                           const bool bDefaultVisibility, const int32 MeshID,
	                                           const TObjectPtr<UTurboSequence_ThreadContext_Lf>&
	                                           ThreadContext) override;
	virtual void OnSetMeshIsUpdatingLod_Concurrent(bool& bIsUpdatingLodOverride, const int32 MeshID,
	                                               const TObjectPtr<UTurboSequence_ThreadContext_Lf>&
	                                               ThreadContext) override;

	virtual void OnSetMeshIsAnimated_Concurrent(ETurboSequence_IsAnimatedOverride_Lf& IsAnimatedOverride,
	                                            const bool bDefaultIsAnimated, const int32 MeshID,
	                                            const TObjectPtr<UTurboSequence_ThreadContext_Lf>&
	                                            ThreadContext) override;

	virtual void OnManagerEndPlay_GameThread(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnAddedMeshInstance_GameThread(const int32 MeshID,
	                                            const TObjectPtr<UTurboSequence_MeshAsset_Lf>& FromAsset) override;
	virtual void OnRemovedMeshInstance_GameThread(const int32 MeshID,
	                                              const TObjectPtr<UTurboSequence_MeshAsset_Lf>& FromAsset) override;

	virtual void OnMeshPreSolveAnimationMeta_Concurrent(const int32 MeshID,
	                                                    const TObjectPtr<UTurboSequence_ThreadContext_Lf>&
	                                                    ThreadContext) override;

	virtual void OnPostManagerUpdated_GameThread(const float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="淡入淡出时间", ToolTip="设置 UE 网格和 TurboSequence 网格切换时的淡入淡出时长。"))
	float FadeTime = 0.5f;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="淡入淡出距离", ToolTip="设置开始切换到 UE 网格的距离阈值。"))
	float FadeDistance = 1000;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Actor 生成旋转偏移", ToolTip="设置生成 UE Actor 时附加的旋转偏移。"))
	FRotator ActorSpawnRotationOffset = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="再次淡化前最短时间", ToolTip="设置再次触发淡入淡出前的最短等待时间。"))
	float MinTimeBeforeFadingAgain = 0;

	float LastDeltaTime = 0;

	TMap<int32, FDemoMeshInstance_Lf> MeshesOpen;
	TMap<int32, FDemoMeshInstance_Lf> MeshesClosed;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="网格 Actor 类", ToolTip="指定演示模式下用于实例化的 UE Actor 类。"))
	TSubclassOf<AActor> MeshActor = nullptr;

	virtual bool CanShowUEMesh(const int32 MeshID, const float MeshDistanceToCamera, const int32 MeshClosedID,
	                           TObjectPtr<UTurboSequence_ThreadContext_Lf> ThreadContext)
	{
		const bool bIsInRange = MeshDistanceToCamera < FadeDistance;
		bool bIsFadeTimeActive = false;
		ThreadContext->LockThread();
		if (MeshesClosed.Contains(MeshID))
		{
			FDemoMeshInstance_Lf& MeshClosed = MeshesClosed[MeshID];
			if (bIsInRange)
			{
				MeshClosed.MinFadeExitTime = MinTimeBeforeFadingAgain;
			}
			bIsFadeTimeActive = MeshClosed.MinFadeExitTime > 0 && MeshClosed.bIsInUERange;
		}
		ThreadContext->UnlockThread();
		return bIsInRange || bIsFadeTimeActive;
	}

	virtual void FadeMesh(const int32 MeshID, const FDemoMeshInstance_Lf& Instance,
	                      const TObjectPtr<USkinnedMeshComponent>& Mesh);
};
