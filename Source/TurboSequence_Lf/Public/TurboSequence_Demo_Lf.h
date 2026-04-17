// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_FootprintAsset_Lf.h"
#include "TurboSequence_Manager_Lf.h"
#include "TurboSequence_MeshAsset_Lf.h"
#include "GameFramework/Actor.h"
#include "TurboSequence_Demo_Lf.generated.h"

struct FDemoMeshWrapper_Lf
{
	FTurboSequence_MinimalMeshData_Lf MeshData;
	float RandomRotationTimer;
	float RandomRotationYaw;
	float RandomAnimationTimer;
	float DeltaTimeAccumulator;
	float IKWeight;
	int32 AssetDataIndex;

	int32 DefaultUpdateGroupIndex;
	int32 CurrentUpdateGroupIndex;

	FTurboSequence_AnimMinimalCollection_Lf CurrentAnimation_0;
	FTurboSequence_AnimMinimalCollection_Lf CurrentAnimation_1;
	float RandomAnimationData_0;
	float RandomAnimationData_1;

	FTurboSequence_AnimMinimalBlendSpaceCollection_Lf CurrentBlendSpace;
	FVector3f RandomBlendSpacePosition;

	float CustomDataTimer;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FDemoMaterialData_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="材质列表", ToolTip="配置该演示材质条目使用的材质列表。"))
	TArray<TObjectPtr<UMaterialInterface>> Materials;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FDemoMeshSpawnData_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="分类名称", ToolTip="设置该演示网格条目的分类名称。"))
	FName CategoryName;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="排除该条目", ToolTip="启用后该演示网格条目不会参与随机生成。"))
	bool bExclude = false;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="网格资产", ToolTip="指定该演示条目使用的 TurboSequence 网格资产。"))
	TObjectPtr<UTurboSequence_MeshAsset_Lf> Asset;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="材质映射", ToolTip="按分类配置该演示条目的材质集合。"))
	TMap<FName, FDemoMaterialData_Lf> Materials;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FDemoCustomizationContainer_Lf
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="已分类数据", ToolTip="查看按分类整理后的演示生成数据。"))
	TArray<FDemoMeshSpawnData_Lf> CategorizedData;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FDemoAssetData_Lf
{
	GENERATED_BODY()

	FDemoAssetData_Lf()
	{
	}

	~FDemoAssetData_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="从系统中排除", ToolTip="启用后该演示资产数据不会参与 TurboSequence 系统。"))
	bool bExcludeFromSystem = false;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="启用根运动", ToolTip="设置该演示资产是否使用根运动。"))
	bool bUseRootMotion = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="使用可编程速度", ToolTip="设置该演示资产是否使用可编程动画速度。"))
	bool bUseProgrammableSpeed = false;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="随机旋转", ToolTip="设置生成实例时是否启用随机旋转。"))
	bool bUseRandomRotation = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="随机动画", ToolTip="设置生成实例时是否随机选择动画。"))
	bool bUseRandomAnimation = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="启用 IK", ToolTip="设置该演示资产是否启用 IK 演示。"))
	bool bUseIK = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="使用 Blend Space", ToolTip="设置该演示资产是否启用 Blend Space 演示。"))
	bool bUseBlendSpaces = false;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="头部骨骼", ToolTip="指定头部 IK 使用的骨骼名称。"))
	FName HeadBone = FName("head");

	UPROPERTY(EditAnywhere, Category="Demo", meta=(ClampMin="0", ClampMax="1", DisplayName="头部 IK 刚度", ToolTip="设置头部 IK 的刚度权重。"))
	float HeadIKStiffness = 1.0f;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="颈部骨骼", ToolTip="指定颈部 IK 使用的骨骼名称。"))
	FName NeckBone = FName("neck_01");

	UPROPERTY(EditAnywhere, Category="Demo", meta=(ClampMin="0", ClampMax="1", DisplayName="颈部 IK 刚度", ToolTip="设置颈部 IK 的刚度权重。"))
	float NeckIKStiffness = 0.75f;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="脊椎 2 骨骼", ToolTip="指定 Spine2 IK 使用的骨骼名称。"))
	FName Spine2Bone = FName("spine_02");

	UPROPERTY(EditAnywhere, Category="Demo", meta=(ClampMin="0", ClampMax="1", DisplayName="脊椎 2 IK 刚度", ToolTip="设置 Spine2 IK 的刚度权重。"))
	float Spine2IKStiffness = 0.5f;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="脊椎 1 骨骼", ToolTip="指定 Spine1 IK 使用的骨骼名称。"))
	FName Spine1Bone = FName("spine_01");

	UPROPERTY(EditAnywhere, Category="Demo", meta=(ClampMin="0", ClampMax="1", DisplayName="脊椎 1 IK 刚度", ToolTip="设置 Spine1 IK 的刚度权重。"))
	float Spine1IKStiffness = 0.25f;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="启用层混合", ToolTip="设置该演示资产是否启用分层混合。"))
	bool bUseLayer = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="启用参数调整", ToolTip="设置该演示资产是否启用动画参数调整。"))
	bool bUseTweaks = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="启用自定义数据", ToolTip="设置该演示资产是否写入材质自定义数据。"))
	bool bUseCustomData = true;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="骨骼层", ToolTip="配置该演示资产使用的骨骼层列表。"))
	TArray<FTurboSequence_BoneLayer_Lf> BoneLayers;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="生成偏移变换", ToolTip="设置该演示资产生成时的附加变换偏移。"))
	FTransform SpawnOffsetTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="根资产列表", ToolTip="配置演示中作为主网格的资产列表。"))
	TArray<FDemoMeshSpawnData_Lf> RootAssets;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="可自定义资产列表", ToolTip="配置演示中作为附加可替换部分的资产列表。"))
	TArray<FDemoMeshSpawnData_Lf> CustomizableAssets;

	FDemoCustomizationContainer_Lf CategorizedRootData;
	TMap<FName, FDemoCustomizationContainer_Lf> CategorizeCustomizableData;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="足迹资产", ToolTip="指定该演示资产使用的 Footprint 资产。"))
	TObjectPtr<UTurboSequence_FootprintAsset_Lf> FootprintAsset;
};


UCLASS()
class TURBOSEQUENCE_LF_API ATurboSequence_Demo_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurboSequence_Demo_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void SpawnCharactersDelayed();

	void SolveGroup(int32 GroupIndex, float DeltaTime, const FRotator& CameraRotation, const FVector& CameraLocation,
	                TMap<FTurboSequence_MinimalMeshData_Lf, bool>& SwitchingGroups);

	const uint8 QualityGroupIndex = 10;

	/*
    < - - - - - - - - - - - - - - - - - - - - >
                    DEMO LOGIC
    < - - - - - - - - - - - - - - - - - - - - >
*/
	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="更新管理器", ToolTip="设置该演示 Actor 是否在 Tick 中驱动 TurboSequence 管理器更新。"))
	bool bUpdateManager = false;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="保持生成高度", ToolTip="设置生成实例时是否保持在当前地面高度。"))
	bool bKeepHeightOnSpawnLevel = false;
	float DemoComponentHeight = 0;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="每组实例数量", ToolTip="设置每个更新组要生成的实例数量。"))
	int32 NumInstancesPerUpdateGroup = 21000;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="高质量求解半径", ToolTip="设置高质量求解区域的半径。"))
	int32 RadiusOfHighQualitySolving = 25000;

	int32 UpdateGroupIndex = 0;

	TArray<float> UpdateGroupDeltaTimes;

	int32 CurrentMeshCount_Internal = 0;
	FVector LastSpawnLocation_Internal = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="生成网格数量", ToolTip="设置演示要生成的总网格数量。"))
	int32 AmountOfMeshesToSpawn = 0;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="生成帧延迟", ToolTip="设置分批生成实例时的帧延迟。"))
	uint16 SpawnFrameDelay = 10;

	uint16 SpawnFrameDelay_Internal = 0;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="网格间距", ToolTip="设置演示实例之间的间距。"))
	float DistanceBetweenMeshes = 300;;

	UPROPERTY(EditAnywhere, Category="Demo",
		meta=(DisplayName="资产数据", ToolTip="配置演示中可用的资产数据列表。"))
	TArray<FDemoAssetData_Lf> AssetData;

	TArray<FDemoAssetData_Lf*> AssetDataRuntime;

	UPROPERTY(EditAnywhere, Category="Test",
		meta=(DisplayName="使用测试旋转变换", ToolTip="启用后使用测试旋转变换替代默认朝向。"))
	bool bUseTestRotationTransform = false;

	UPROPERTY(EditAnywhere, Category="Test",
		meta=(DisplayName="测试旋转变换", ToolTip="设置用于测试的旋转变换。"))
	FTransform TestRotationTransform = FTransform::Identity;


	TMap<FTurboSequence_MinimalMeshData_Lf, FDemoMeshWrapper_Lf> Meshes;

	static void GetRandomMeshSpawnData(FTurboSequence_MeshSpawnData_Lf& Data,
	                                   const FDemoCustomizationContainer_Lf& CategorizedRootData,
	                                   const TMap<FName, FDemoCustomizationContainer_Lf>& CategorizeCustomizableData,
	                                   const TObjectPtr<UTurboSequence_FootprintAsset_Lf> FootprintAsset);

	static void SolveLookAtIKBone(const FTurboSequence_MinimalMeshData_Lf& MeshData,
	                              const FName& BoneName, const FVector& TargetLocation,
	                              float Weight, float OffsetWeight, float AnimationDeltaTime,
	                              const FTransform& StartOffsetTransform);

	UFUNCTION(BlueprintCallable, Category="TurboSequence")
	static void SolveBlueprintDemoMeshesInCpp(const TArray<FTurboSequence_MinimalMeshData_Lf>& MeshData,
	                                          UPARAM(ref) TArray<FVector4>& AnimData, UAnimSequence* AnimA,
	                                          UAnimSequence* AnimB,
	                                          const FTurboSequence_AnimPlaySettings_Lf& AnimSettingsA,
	                                          const FTurboSequence_AnimPlaySettings_Lf& AnimSettingsB,
	                                          const float DeltaTime, const bool bMultiThreaded);
};
