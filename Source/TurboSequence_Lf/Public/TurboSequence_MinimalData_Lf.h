// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_MeshAsset_Lf.h"
#include "UObject/Object.h"

#include "TurboSequence_MinimalData_Lf.generated.h"

/*	==============================================================================================================
												DATA
	==============================================================================================================	*/

UENUM(BlueprintType)
enum class ETurboSequence_AnimationForceMode_Lf : uint8
{
	None,
	PerLayer,
	AllLayers
};

UENUM(BlueprintType)
enum class ETurboSequence_RootMotionMode_Lf : uint8
{
	None,
	OnRootBoneAnimated,
	Force
};

UENUM(BlueprintType)
enum class ETurboSequence_ManagementMode_Lf : uint8
{
	Auto,
	SelfManaged
};

UENUM(BlueprintType)
enum class ETurboSequence_IsVisibleOverride_Lf : uint8
{
	Default,
	IsVisible,
	IsNotVisible,
	ScaleToZero
};

UENUM(BlueprintType)
enum class ETurboSequence_IsAnimatedOverride_Lf : uint8
{
	Default,
	IsAnimated,
	IsNotAnimated
};

UCLASS(BlueprintType)
class TURBOSEQUENCE_LF_API UTurboSequence_ThreadContext_Lf : public UObject
{
	GENERATED_BODY()

public:
	FCriticalSection CriticalSection;

	UFUNCTION(BlueprintCallable, Category="TurboSequence")
	void LockThread()
	{
		CriticalSection.Lock();
	}

	UFUNCTION(BlueprintCallable, Category="TurboSequence")
	void UnlockThread()
	{
		CriticalSection.Unlock();
	}
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_BoneLayer_Lf
{
	GENERATED_BODY()

	FTurboSequence_BoneLayer_Lf()
	{
	}

	~FTurboSequence_BoneLayer_Lf()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="骨骼层名称", ToolTip="指定该骨骼层使用的根骨骼名称。"))
	FName BoneLayerName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="骨骼深度", ToolTip="设置骨骼层向下影响的骨骼深度。"))
	uint8 BoneDepth = GET2_NUMBER;
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_AnimPlaySettings_Lf
{
	GENERATED_BODY()

	FTurboSequence_AnimPlaySettings_Lf()
	{
	}

	~FTurboSequence_AnimPlaySettings_Lf()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="骨骼层遮罩", ToolTip="配置该动画播放设置使用的骨骼层遮罩列表。"))
	TArray<FTurboSequence_BoneLayer_Lf> BoneLayerMasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="动画时间自管理", ToolTip="启用后由外部手动管理动画时间。"))
	bool bAnimationTimeSelfManaged = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="动画权重", ToolTip="设置动画播放时的混合权重。"))
	float AnimationWeight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="动画播放时间（秒）", ToolTip="设置动画当前播放时间，单位为秒。"))
	float AnimationPlayTimeInSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="动画速度", ToolTip="设置动画播放速度倍率。"))
	float AnimationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="强制模式", ToolTip="设置动画在层级中的强制覆盖模式。"))
	ETurboSequence_AnimationForceMode_Lf ForceMode = ETurboSequence_AnimationForceMode_Lf::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="开始过渡时间（秒）", ToolTip="设置动画开始混合时的过渡时间。"))
	float StartTransitionTimeInSeconds = GET1_NUMBER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="结束过渡时间（秒）", ToolTip="设置动画结束或移除时的过渡时间。"))
	float EndTransitionTimeInSeconds = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="根运动模式", ToolTip="设置动画根运动的处理方式。"))
	ETurboSequence_RootMotionMode_Lf RootMotionMode = ETurboSequence_RootMotionMode_Lf::OnRootBoneAnimated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="动画管理模式", ToolTip="设置动画由系统管理还是由外部自行管理。"))
	ETurboSequence_ManagementMode_Lf AnimationManagementMode = ETurboSequence_ManagementMode_Lf::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="覆盖权重", ToolTip="当需要覆盖默认权重时，在此填写新的权重值。"))
	float OverrideWeight = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="覆盖开始时间", ToolTip="当需要覆盖默认开始时间时，在此填写新的开始时间。"))
	float OverrideStartTime = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="覆盖结束时间", ToolTip="当需要覆盖默认结束时间时，在此填写新的结束时间。"))
	float OverrideEndTime = -1.0f;
};

//
USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_AnimMinimalData_Lf
{
	GENERATED_BODY()

	FTurboSequence_AnimMinimalData_Lf()
	{
	}

	explicit FTurboSequence_AnimMinimalData_Lf(bool bValid)
	{
		bIsValid = bValid;
	}

	~FTurboSequence_AnimMinimalData_Lf()
	{
	}

	uint32 AnimationID = GET0_NUMBER;
	int32 BelongsToMeshID = GET0_NUMBER;

protected:
	bool bIsValid = false;

public:
	FORCEINLINE bool IsAnimationValid() const
	{
		return bIsValid;
	}
};


USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_AnimMinimalCollection_Lf
{
	GENERATED_BODY()

	FTurboSequence_AnimMinimalCollection_Lf()
	{
	}

	~FTurboSequence_AnimMinimalCollection_Lf()
	{
	}

	explicit FTurboSequence_AnimMinimalCollection_Lf(bool bValid)
	{
		bIsValid = bValid;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="根运动动画", ToolTip="查看根运动网格对应的动画最小数据。"))
	FTurboSequence_AnimMinimalData_Lf RootMotionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="可自定义网格动画", ToolTip="查看可自定义网格对应的动画最小数据列表。"))
	TArray<FTurboSequence_AnimMinimalData_Lf> CustomizableMeshes;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="是否有效", ToolTip="查看该动画集合是否有效。"))
	bool bIsValid = false;

public:
	FORCEINLINE bool IsAnimCollectionValid() const
	{
		return bIsValid;
	}
};


USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_AnimMinimalBlendSpace_Lf
{
	GENERATED_BODY()

	FTurboSequence_AnimMinimalBlendSpace_Lf()
	{
	}

	~FTurboSequence_AnimMinimalBlendSpace_Lf()
	{
	}

	explicit FTurboSequence_AnimMinimalBlendSpace_Lf(bool bValid)
	{
		bIsValid = bValid;
	}

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="采样列表", ToolTip="设置 Blend Space 使用的采样动画 ID 列表。"))
	TArray<uint32> Samples;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Blend Space", ToolTip="指定要播放的 Blend Space 资源。"))
	TObjectPtr<UBlendSpace> BlendSpace;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="所属网格 ID", ToolTip="记录该 Blend Space 数据所属的网格 ID。"))
	int32 BelongsToMeshID = GET0_NUMBER;

protected:
	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="是否有效", ToolTip="查看该 Blend Space 数据是否有效。"))
	bool bIsValid = false;

public:
	FORCEINLINE bool IsAnimBlendSpaceValid() const
	{
		return bIsValid;
	}
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_AnimMinimalBlendSpaceCollection_Lf
{
	GENERATED_BODY()

	FTurboSequence_AnimMinimalBlendSpaceCollection_Lf()
	{
	}

	~FTurboSequence_AnimMinimalBlendSpaceCollection_Lf()
	{
	}

	explicit FTurboSequence_AnimMinimalBlendSpaceCollection_Lf(bool bValid)
	{
		bIsValid = bValid;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="根运动 Blend Space", ToolTip="查看根运动网格对应的 Blend Space 最小数据。"))
	FTurboSequence_AnimMinimalBlendSpace_Lf RootMotionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="可自定义网格 Blend Space", ToolTip="查看可自定义网格对应的 Blend Space 最小数据列表。"))
	TArray<FTurboSequence_AnimMinimalBlendSpace_Lf> CustomizableMeshes;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="是否有效", ToolTip="查看该 Blend Space 集合是否有效。"))
	bool bIsValid = false;

public:
	FORCEINLINE bool IsAnimCollectionValid() const
	{
		return bIsValid;
	}
};


USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_MeshMetaData_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="网格资产", ToolTip="指定要生成或使用的 TurboSequence 网格资产。"))
	TObjectPtr<UTurboSequence_MeshAsset_Lf> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="覆盖材质", ToolTip="为该网格指定要覆盖的材质列表。"))
	TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="足迹资产", ToolTip="指定该网格实例使用的 Footprint 资产。"))
	TObjectPtr<class UTurboSequence_FootprintAsset_Lf> FootprintAsset;
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_MeshSpawnData_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="根运动网格", ToolTip="配置根运动主网格的生成数据。"))
	FTurboSequence_MeshMetaData_Lf RootMotionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="可自定义网格", ToolTip="配置附加可自定义网格的生成数据列表。"))
	TArray<FTurboSequence_MeshMetaData_Lf> CustomizableMeshes;

	uint32 GetHash() const // TODO: Make GET and SET to assign the the hash only when values are changing
	{
		uint32 Hash = GET0_NUMBER;

		Hash = HashCombineFast(GetTypeHash(RootMotionMesh.Mesh), Hash);
		for (const TObjectPtr<UMaterialInterface>& OverrideMaterial : RootMotionMesh.OverrideMaterials)
		{
			Hash = HashCombineFast(GetTypeHash(OverrideMaterial), Hash);
		}
		Hash = HashCombineFast(GetTypeHash(RootMotionMesh.FootprintAsset), Hash);

		for (const FTurboSequence_MeshMetaData_Lf& CustomizableMeshMeta : CustomizableMeshes)
		{
			Hash = HashCombineFast(GetTypeHash(CustomizableMeshMeta.Mesh), Hash);
			for (const TObjectPtr<UMaterialInterface>& OverrideMaterial : CustomizableMeshMeta.OverrideMaterials)
			{
				Hash = HashCombineFast(GetTypeHash(OverrideMaterial), Hash);
			}
			Hash = HashCombineFast(GetTypeHash(CustomizableMeshMeta.FootprintAsset), Hash);
		}

		return Hash;
	}

	FORCEINLINE bool operator==(const FTurboSequence_MeshSpawnData_Lf& Other) const
	{
		return Equals(Other);
	}

	FORCEINLINE bool operator!=(const FTurboSequence_MeshSpawnData_Lf& Other) const
	{
		return !Equals(Other);
	}

	FORCEINLINE bool Equals(const FTurboSequence_MeshSpawnData_Lf& Other) const
	{
		return GetHash() == Other.GetHash();
	}

	FORCEINLINE bool IsSpawnDataValid() const
	{
		return IsValid(RootMotionMesh.Mesh);
	}
};
#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FTurboSequence_MeshSpawnData_Lf& MetaData);
#else // optimize by inlining in shipping and development builds
FORCEINLINE_DEBUGGABLE uint32 GetTypeHash(const FTurboSequence_MeshSpawnData_Lf& MetaData)
{
	return MetaData.GetHash();
}
#endif

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_MinimalMeshData_Lf
{
	GENERATED_BODY()

	FTurboSequence_MinimalMeshData_Lf()
	{
	}

	~FTurboSequence_MinimalMeshData_Lf()
	{
	}

	explicit FTurboSequence_MinimalMeshData_Lf(bool bValid)
	{
		bIsValid = bValid;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="根运动网格 ID", ToolTip="查看根运动网格实例的运行时 ID。"))
	int32 RootMotionMeshID = GET0_NUMBER;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="可自定义网格 ID", ToolTip="查看附加可自定义网格实例的运行时 ID 列表。"))
	TArray<int32> CustomizableMeshIDs;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="是否有效", ToolTip="查看该最小网格数据是否有效。"))
	bool bIsValid = false;

public:
	FORCEINLINE bool IsMeshDataValid() const
	{
		return bIsValid && RootMotionMeshID > INDEX_NONE;
	}

	FORCEINLINE bool operator==(const FTurboSequence_MinimalMeshData_Lf& Other) const
	{
		return Equals(Other);
	}

	FORCEINLINE bool operator!=(const FTurboSequence_MinimalMeshData_Lf& Other) const
	{
		return !Equals(Other);
	}

	FORCEINLINE bool Equals(const FTurboSequence_MinimalMeshData_Lf& Other) const
	{
		return RootMotionMeshID == Other.RootMotionMeshID;
	}

	FORCEINLINE FString ToString() const
	{
		FString String = FString::Printf(
			TEXT("bIsValid -> %s | Root Mesh ID -> %d"), IsMeshDataValid() ? TEXT("True") : TEXT("False"),
			RootMotionMeshID);
		for (int32 MeshID : CustomizableMeshIDs)
		{
			String += FString::Printf(TEXT(" | Customizable ID -> %d"), MeshID);
		}
		return String;
	}
};
#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FTurboSequence_MinimalMeshData_Lf& MeshData);
#else // optimize by inlining in shipping and development builds
FORCEINLINE_DEBUGGABLE uint32 GetTypeHash(const FTurboSequence_MinimalMeshData_Lf& MeshData)
{
	return MeshData.RootMotionMeshID;
}
#endif


USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_PoseCurveData_Lf
{
	GENERATED_BODY()

	FTurboSequence_PoseCurveData_Lf()
	{
	}

	FTurboSequence_PoseCurveData_Lf(const TObjectPtr<UAnimSequence>& CurveAnimation, const FName& CurveID,
	                                float CurveFrame0)
		: CurveAnimation(CurveAnimation),
		  CurveName(CurveID),
		  CurveFrame_0(CurveFrame0)
	{
	}

	~FTurboSequence_PoseCurveData_Lf()
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="曲线动画", ToolTip="查看该姿态曲线数据对应的动画资源。"))
	TObjectPtr<UAnimSequence> CurveAnimation = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="曲线名称", ToolTip="查看该姿态曲线数据对应的曲线名称。"))
	FName CurveName = FName("");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="曲线第 0 帧值", ToolTip="查看该姿态曲线在第 0 帧的取值。"))
	float CurveFrame_0 = GET0_NUMBER;

	FORCEINLINE bool IsCurveValid() const
	{
		return IsValid(CurveAnimation);
	}
};


UENUM(BlueprintType)
enum class ETurboSequence_TransformSpace_Lf : uint8
{
	BoneSpace,
	ComponentSpace,
	WorldSpace
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_UpdateGroup_Lf
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="原始 ID 列表", ToolTip="查看该更新组中记录的原始网格 ID 列表。"))
	TArray<int32> RawIDs;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="原始 ID 数据", ToolTip="查看该更新组中原始网格 ID 的索引映射。"))
	TMap<int32, int32> RawIDData;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="最小数据映射", ToolTip="查看更新组中网格最小数据到区间的映射。"))
	TMap<FTurboSequence_MinimalMeshData_Lf, FIntVector2> MeshIDToMinimal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TurboSequence",
		meta=(DisplayName="原始最小数据", ToolTip="查看更新组中的最小网格数据列表。"))
	TArray<FTurboSequence_MinimalMeshData_Lf> RawMinimalData;
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_CameraInfo_Lf
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="视图信息", ToolTip="设置该摄像机信息使用的视图参数。"))
	FMinimalViewInfo ViewInfo = FMinimalViewInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="本地玩家尺寸", ToolTip="设置该本地玩家视口子区域的尺寸比例。"))
	// The size of the primary viewport subregion allocated to this player. 0-1
	FVector2D LocalPlayerSize = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="视场角", ToolTip="设置该摄像机信息的视场角。"))
	float Fov = GET0_NUMBER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="宽高比约束", ToolTip="设置该摄像机信息的宽高比约束方式。"))
	TEnumAsByte<enum EAspectRatioAxisConstraint> AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MAX;
};

USTRUCT(BlueprintType)
struct TURBOSEQUENCE_LF_API FTurboSequence_UpdateContext_Lf
{
	GENERATED_BODY()

	FTurboSequence_UpdateContext_Lf()
	{
	}

	~FTurboSequence_UpdateContext_Lf()
	{
	}

	FTurboSequence_UpdateContext_Lf(const int32 GroupIndex)
		: GroupIndex(GroupIndex)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="组索引", ToolTip="设置本次更新要处理的更新组索引。"))
	int32 GroupIndex = GET0_NUMBER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurboSequence",
		meta=(DisplayName="自定义摄像机信息", ToolTip="配置参与本次更新的自定义摄像机信息列表。"))
	TArray<FTurboSequence_CameraInfo_Lf> CustomCameraInfo;
};
