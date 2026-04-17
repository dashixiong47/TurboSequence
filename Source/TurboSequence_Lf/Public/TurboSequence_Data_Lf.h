// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "TurboSequence_ComputeShaders_Lf.h"
#include "TurboSequence_Helper_Lf.h"
#include "TurboSequence_MeshAsset_Lf.h"
#include "TurboSequence_MinimalData_Lf.h"
#include "Animation/BlendSpace.h"
#include "Misc/Optional.h"

#include "TurboSequence_Data_Lf.generated.h"


/*	==============================================================================================================
												RENDERING
	==============================================================================================================	*/

USTRUCT()
struct TURBOSEQUENCE_LF_API FCameraView_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="视口尺寸", ToolTip="设置摄像机视口的尺寸。"))
	FVector2f ViewportSize = FVector2f::ZeroVector;

	TOptional<EAspectRatioAxisConstraint> AspectRatioAxisConstraint;

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="视场角", ToolTip="设置摄像机的视场角。"))
	float Fov = GET60_NUMBER;

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="近裁剪面", ToolTip="设置摄像机的近裁剪面距离。"))
	float NearClipPlane = GET1_NUMBER;

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="远裁剪面", ToolTip="设置摄像机的远裁剪面距离。"))
	float FarClipPlane = GET1000_NUMBER;

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="透视投影", ToolTip="设置该摄像机是否使用透视投影。"))
	bool bIsPerspective = true;

	UPROPERTY(EditAnywhere, Category="Aspect",
		meta=(DisplayName="正交宽度", ToolTip="设置正交投影模式下的宽度。"))
	float OrthoWidth = GET10_NUMBER;

	UPROPERTY(EditAnywhere, Category="Transform",
		meta=(DisplayName="摄像机变换", ToolTip="设置摄像机的世界空间变换。"))
	FTransform CameraTransform;

	FPlane Planes_Internal[GET6_NUMBER];
	FTransform InterpolatedCameraTransform_Internal;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FRenderData_Lf
{
	GENERATED_BODY()

	explicit FRenderData_Lf(const FString& EmitterName, const FString& ParticleIDName, const FString& PositionName, const FString& RotationName,
	                        const FString& ScaleName, const FString& MeshName, const FString& MaterialsName,
	                        const FString& LodName, const FString& CustomDataName, const FString& ParticleRemoveName,
	                        const FString& UseNaniteName)
		: EmitterName(EmitterName),
		  IDName(ParticleIDName),
		  PositionName(PositionName),
		  RotationName(RotationName),
		  ScaleName(ScaleName),
		  MeshName(MeshName),
		  MaterialsName(MaterialsName),
		  LodName(LodName),
		  CustomDataName(CustomDataName),
		  ParticleRemoveName(ParticleRemoveName),
		  UseNaniteName(UseNaniteName)
	{
	}

	FRenderData_Lf()
	{
	}

	~FRenderData_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="渲染参考", ToolTip="指定该渲染数据对应的 Niagara 渲染参考资源。"))
	TObjectPtr<UNiagaraSystem> RenderReference = nullptr;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="材质列表", ToolTip="设置该渲染数据使用的材质列表。"))
	TArray<TObjectPtr<UMaterialInterface>> Materials;

	// ID
	TMap<int32, int32> InstanceMap; // < MeshID | Renderer Instance Index >
	//TMap<int32, int32> InstanceMapCopy; // < MeshID | Renderer Instance Index > Needed to Keep the Indices correct
	//TArray<int32> MeshIDsToRemove;
	//TArray<int32> ParticleIDs; // < Unique ID > -> Used internally for Niagara finding the Index
	//TMap<int32, int32> ParticleIDMap; // < MeshID | UniqueID >

	// Transform
	TArray<FVector> ParticlePositions;
	TArray<FVector3f> ParticleScales;
	TArray<FVector4f> ParticleRotations;

	// Culling and Visibility
	TArray<uint8> ParticleLevelOfDetails; // Index 32 -> Not Visible
	//TArray<bool> ParticlesToRemove;
	// TArray<int32> ParticlesToRemoveIndices;

	// Custom Data
	TArray<float> ParticleCustomData;
	// ISM requires a different data structure -> < Instance Index < Data Chunk > >
	TArray<TArray<float>> ParticleCustomDataIsm;

	// Bounds Checking
	FVector MinBounds = FVector::ZeroVector;
	FVector MaxBounds = FVector::ZeroVector;

	bool bChangedCollectionSizeThisFrame = false;
	bool bChangedCollectionSizePreviousFrame = false;
	bool bChangedPositionCollectionThisFrame = false;
	bool bChangedRotationCollectionThisFrame = false;
	bool bChangedScaleCollectionThisFrame = false;
	bool bChangedLodCollectionThisFrame = false;
	bool bChangedCustomDataCollectionThisFrame = false;


private:
	FString EmitterName;
	FString IDName;
	FString PositionName;
	FString RotationName;
	FString ScaleName;
	FString MeshName;
	FString MaterialsName;
	FString LodName;
	FString CustomDataName;
	FString ParticleRemoveName;
	FString UseNaniteName;

	// int32 UniqueID = 0;

public:
	// FORCEINLINE int32 GetUniqueID() const
	// {
	// 	return UniqueID;
	// }
	//
	// FORCEINLINE void IncrementUniqueID()
	// {
	// 	UniqueID++;
	// }

	FORCEINLINE FString& GetEmitterName()
	{
		return EmitterName;
	}

	FORCEINLINE FString& GetPositionName()
	{
		return PositionName;
	}

	FORCEINLINE FString& GetParticleIDName()
	{
		return IDName;
	}

	FORCEINLINE FString& GetRotationName()
	{
		return RotationName;
	}

	FORCEINLINE FString& GetScaleName()
	{
		return ScaleName;
	}

	FORCEINLINE FString& GetMeshName()
	{
		return MeshName;
	}

	FORCEINLINE FString& GetMaterialsName()
	{
		return MaterialsName;
	}

	FORCEINLINE FString& GetLodName()
	{
		return LodName;
	}

	FORCEINLINE FString& GetCustomDataName()
	{
		return CustomDataName;
	}

	FORCEINLINE FString& GetParticleRemoveName()
	{
		return ParticleRemoveName;
	}
	FORCEINLINE FString& GetUseNaniteName()
	{
		return UseNaniteName;
	}
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FCPUAnimationPose_Lf
{
	GENERATED_BODY()

	int32 BelongsToKeyframe = GET0_NUMBER;

	FAnimPose_Lf Pose;

	//TArray<FVector4f> RawData;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationLibraryDataAllocationItem_Lf
{
	GENERATED_BODY()

	FVector4f Data = FVector4f::Zero();

	int32 ColIndex = GET0_NUMBER;
	int32 RowIndex = GET0_NUMBER;
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationLibraryData_Lf
{
	GENERATED_BODY()

	int32 MaxFrames = GET0_NUMBER;

	uint16 NumBones = GET0_NUMBER;

	// < Keyframe Index | Pose >
	TMap<int32, FCPUAnimationPose_Lf> AnimPoses;

	TArray<int32> KeyframesFilled;
	int32 IndexInCollection = GET0_NUMBER;

	TMap<FName, int16> BoneNameToAnimationBoneIndex;


	int32 AnimationDensity = GET0_NUMBER;

	FAnimPoseEvaluationOptions_Lf PoseOptions;

	bool bHasPoseData = false;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationMetaData_RenderThread_Lf
{
	GENERATED_BODY()

	FAnimationMetaData_RenderThread_Lf()
	{
	}

	~FAnimationMetaData_RenderThread_Lf()
	{
	}

	int32 GPUAnimationIndex_0 = GET0_NUMBER;

	uint16 FinalAnimationWeight = GET0_NUMBER;

	uint16 LayerMaskIndex = GET0_NUMBER;
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationMetaData_Lf
{
	GENERATED_BODY()

	FAnimationMetaData_Lf()
	{
	}

	~FAnimationMetaData_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="动画", ToolTip="指定该动画元数据对应的动画资源。"))
	UAnimSequence* Animation = nullptr;

	UPROPERTY(EditAnywhere, Category="Settings",
		meta=(DisplayName="播放设置", ToolTip="设置该动画的播放参数。"))
	FTurboSequence_AnimPlaySettings_Lf Settings;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="动画时间", ToolTip="查看或设置该动画当前帧的播放时间。"))
	float AnimationTime = GET0_NUMBER;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="最终动画权重", ToolTip="查看或设置该动画当前帧的最终混合权重。"))
	float FinalAnimationWeight = GET1_NUMBER;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="动画权重时间", ToolTip="设置动画权重过渡持续时间。"))
	float AnimationWeightTime = 0.25f;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="动画权重开始时间", ToolTip="设置动画权重开始过渡的时间点。"))
	float AnimationWeightStartTime = 0.25f;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="动画移除时间", ToolTip="设置动画淡出移除的持续时间。"))
	float AnimationRemoveTime = 0.25f;

	UPROPERTY(EditAnywhere, Category="Current Frame",
		meta=(DisplayName="动画移除开始时间", ToolTip="设置动画开始移除的时间点。"))
	float AnimationRemoveStartTime = 0.25f;

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="循环播放", ToolTip="设置该动画是否循环播放。"))
	bool bIsLoop = false;

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="旧动画标记", ToolTip="标记该动画是否已进入旧动画状态。"))
	bool bIsOldAnimation = false;

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="层遮罩索引", ToolTip="设置该动画当前使用的层遮罩索引。"))
	uint16 LayerMaskIndex = GET0_NUMBER;

	bool bNeedRebuildAnimationLayers = false;
	// < Hash >
	uint32 AnimationLayerHash = GET0_NUMBER;

	uint32 AnimationGroupLayerHash = GET0_NUMBER;

	FUintVector AnimationLibraryHash = FUintVector::ZeroValue;

	float AnimationNormalizedTime = GET0_NUMBER;
	float AnimationMaxPlayLength = GET1_NUMBER;
	int32 CurrentFrame = GET0_NUMBER;

	bool bIsRootBoneAnimation = false;
	bool bIsSelfManagedAnimation = false;

	int32 CPUAnimationIndex_0 = GET0_NUMBER;

	uint32 AnimationID = GET0_NUMBER;

	FORCEINLINE uint32 SetHash(uint32 SecurityIndex) const
	{
		uint32 Hash = GET0_NUMBER;
		Hash = HashCombine(Hash, GetTypeHash(FGuid::NewGuid()));
		Hash = HashCombine(Hash, GetTypeHash(SecurityIndex));
		return Hash;
	}

	FORCEINLINE void SetAnimationID(const TMap<uint32, int32>& InputCollection, int32 BelongsToMeshID)
	{
		uint32 SecurityNumber = FMath::RandRange(GET0_NUMBER, INT32_MAX);
		// Set the hash
		AnimationID = SetHash(SecurityNumber);
		// We don't want a 0 Hash because it's the Instance Return type when the function cancel unexpected
		// Here we check if the hash is unique, if not we run the loop again,
		// usually on the 1st try it already pass the check fine
		while (InputCollection.Contains(AnimationID) || (!InputCollection.Contains(AnimationID) && AnimationID <=
			GET0_NUMBER))
		{
			SecurityNumber = FMath::RandRange(GET0_NUMBER, INT32_MAX);
			SecurityNumber++;
			AnimationID = SetHash(SecurityNumber);
		}

		AnimationID = HashCombine(AnimationID, BelongsToMeshID);
	}

	FORCEINLINE void SetAnimationID(const uint32 ID)
	{
		AnimationID = ID;
	}
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationGroup_Lf
{
	GENERATED_BODY()

	int16 NumAnimationsInGroup = GET0_NUMBER;

	float TotalAnimWeightRuntime = GET0_NUMBER;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FIKBoneData_Lf
{
	GENERATED_BODY()

	FTransform IKWriteTransform = FTransform::Identity;
	bool bIsInUsingWriteDataThisFrame = false;
	uint8 AliveCount = GET0_NUMBER;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FRenderingMaterialKeyValue_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="源材质", ToolTip="指定需要被替换的源材质。"))
	TObjectPtr<UMaterialInterface> MaterialKey;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="目标材质", ToolTip="指定与源材质对应的替换目标材质。"))
	TObjectPtr<UMaterialInterface> MaterialValue;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FRenderingMaterialItem_Lf
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 渲染器", ToolTip="查看该材质项绑定的 Niagara 组件。"))
	TObjectPtr<UNiagaraComponent> NiagaraRenderer;
	
	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="ISM 渲染器", ToolTip="查看该材质项绑定的 Instanced Static Mesh 组件。"))
	TObjectPtr<UInstancedStaticMeshComponent> IsmRenderer;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="材质映射", ToolTip="配置该渲染项使用的材质替换映射。"))
	TArray<FRenderingMaterialKeyValue_Lf> Materials;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FRenderingMaterialMap_Lf
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="渲染器映射", ToolTip="查看材质哈希到渲染材质项的映射。"))
	TMap<uint32, FRenderingMaterialItem_Lf> Renderer;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationBlendSpaceData_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="采样点映射", ToolTip="设置 Blend Space 动画 ID 到采样索引的映射。"))
	// < Animation ID | Sampler Index >
	TMap<uint32, int32> Points;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="当前位置", ToolTip="设置或查看 Blend Space 当前的混合位置。"))
	FVector3f CurrentPosition = FVector3f::ZeroVector;

	TArray<FBlendSampleData> CachedBlendSampleData;
	FBlendFilter BlendFilter;

	float LongestPlayLength = GET0_NUMBER;
	float CurrentTime = GET0_NUMBER;

	FAnimTickRecord Tick;
	FMarkerTickRecord Record;
	FAnimNotifyQueue NotifyQueue;
	FDeltaTimeRecord DeltaTimeRecord = FDeltaTimeRecord();
};

/*	==============================================================================================================
												REFERENCE
	==============================================================================================================	*/

USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshReferenceLodElement_Lf
{
	GENERATED_BODY()

	FSkinnedMeshReferenceLodElement_Lf()
	{
	}

	~FSkinnedMeshReferenceLodElement_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="静态网格", ToolTip="指定该 LOD 参考元素使用的静态网格。"))
	TObjectPtr<UStaticMesh> Mesh;

	uint32 SkinWeightOffset = GET0_NUMBER;
	uint8 MeshIndex = GET0_NUMBER;
	uint8 GPUMeshIndex = GET0_NUMBER;
	uint8 CollectionIndex = GET0_NUMBER;

	uint32 MinLodDistance = GET0_NUMBER;
	uint32 MaxLodDistance = GET0_NUMBER;

	bool bIsRenderStateValid = false;
	bool bIsAnimated = true;
	bool bIsFrustumCullingEnabled = true;

	// CPU Indices, GPU Indices > -> Only contains bones with skin weight and Lod with mesh
	TMap<uint16, uint16> CPUBoneToGPUBoneIndicesMap;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshReference_RenderThread_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="数据资产", ToolTip="指定该引用数据对应的 TurboSequence 网格资产。"))
	TObjectPtr<UTurboSequence_MeshAsset_Lf> DataAsset;

	// CPU Indices, GPU Indices > -> Only contains bones with skin weight and Lod with mesh
	TMap<uint16, uint16> FirstLodGPUBonesCollection;

	int32 ReferenceCollectionIndex = GET0_NUMBER;

	// Since we have Async Chunked dynamic loading of all data we need to store skin weights locally
	// in the reference to async chunked load it into the GPU
	TArray<FVector4f> LocalMeshSkinWeights;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshReference_Lf : public FSkinnedMeshReference_RenderThread_Lf
{
	GENERATED_BODY()

	FSkinnedMeshReference_Lf()
	{
	}

	~FSkinnedMeshReference_Lf()
	{
	}

	explicit FSkinnedMeshReference_Lf(const TObjectPtr<UTurboSequence_MeshAsset_Lf> Asset)
	{
		DataAsset = Asset;
	}

	FORCEINLINE bool operator==(const FSkinnedMeshReference_Lf& Rhs) const
	{
		return this->DataAsset == Rhs.DataAsset;
	}

	FORCEINLINE bool operator!=(const FSkinnedMeshReference_Lf& Rhs) const
	{
		return !(*this == Rhs);
	}

	FORCEINLINE uint32 GetClassHash() const
	{
		return GetTypeHash(DataAsset);
	}

	TMap<uint8, FSkinnedMeshReferenceLodElement_Lf> LevelOfDetails;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="首个有效 LOD 网格", ToolTip="指定该引用数据中第一个有效的 LOD 静态网格。"))
	TObjectPtr<UStaticMesh> FirstValidMeshLevelOfDetail;

	uint16 NumCPUBones = GET0_NUMBER;

	uint16 NumFirstLodGPUBones = GET0_NUMBER;
	uint8 NumLevelOfDetailsWithMesh = GET0_NUMBER;

	FTransform FirstReferenceBone;

	TArray<FTransform> ComponentSpaceRestPose;

	// < Material Hash | Data >
	TMap<uint32, FRenderData_Lf> RenderData;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="来源世界", ToolTip="记录该引用数据所属的世界对象。"))
	TObjectPtr<UWorld> FromWorld = nullptr;
};

/*	==============================================================================================================
												RUNTIME
	==============================================================================================================	*/

USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshRuntime_RenderThread_Lf
{
	GENERATED_BODY()

	FSkinnedMeshRuntime_RenderThread_Lf()
	{
	}

	~FSkinnedMeshRuntime_RenderThread_Lf()
	{
	}

	explicit FSkinnedMeshRuntime_RenderThread_Lf(int32 WantedMeshID,
	                                             const TObjectPtr<UTurboSequence_MeshAsset_Lf> Asset)
	{
		MeshID = WantedMeshID;
		DataAsset = Asset;
	}

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="数据资产", ToolTip="指定该运行时网格实例对应的 TurboSequence 网格资产。"))
	TObjectPtr<UTurboSequence_MeshAsset_Lf> DataAsset;

	bool bIsVisible = true;
	bool bIsVisibleInFrustum = true;
	ETurboSequence_IsVisibleOverride_Lf EIsVisibleOverride = ETurboSequence_IsVisibleOverride_Lf::Default;
	ETurboSequence_IsAnimatedOverride_Lf EIsAnimatedOverride = ETurboSequence_IsAnimatedOverride_Lf::Default;
	uint8 CurrentGPUMeshIndex = GET0_NUMBER;

	TArray<FAnimationMetaData_RenderThread_Lf> AnimationMetaData_RenderThread;

	bool bIKDataInUse = false;
	TMap<uint16, FIKBoneData_Lf> IKData;

protected:
	int32 MeshID = GET0_NUMBER;

public:
	FORCEINLINE int32 GetMeshID() const
	{
		return MeshID;
	}
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshRuntime_Lf : public FSkinnedMeshRuntime_RenderThread_Lf
{
	GENERATED_BODY()

	FSkinnedMeshRuntime_Lf()
	{
	}

	~FSkinnedMeshRuntime_Lf()
	{
	}

	explicit FSkinnedMeshRuntime_Lf(const TMap<int32, FSkinnedMeshRuntime_Lf>& InputCollection,
	                                const TMap<int32, bool>& BlacklistedMeshIDs,
	                                const TObjectPtr<UTurboSequence_MeshAsset_Lf> Asset,
	                                const int32 OverrideMeshID = INDEX_NONE)
	{
		if (OverrideMeshID > INDEX_NONE && !InputCollection.Contains(OverrideMeshID) && !BlacklistedMeshIDs.Contains(OverrideMeshID))
		{
			MeshID = OverrideMeshID;
		}
		else
		{
			MeshID = FMath::RandRange(0, INT32_MAX - 1);
			MeshID++;
			while ((InputCollection.Contains(MeshID) || BlacklistedMeshIDs.Contains(MeshID)) || ((!InputCollection.Contains(MeshID) && !BlacklistedMeshIDs.Contains(MeshID)) && MeshID < GET0_NUMBER))
			{
				MeshID = FMath::RandRange(0, INT32_MAX - 1);
				MeshID++;
			}
		}

		DataAsset = Asset;
	}

	// uint32 SetHash(uint32 SecurityIndex) const
	// {
	// 	uint32 Hash = GET0_NUMBER;
	// 	Hash = HashCombine(Hash, GetTypeHash(FGuid::NewGuid()));
	// 	Hash = HashCombine(Hash, GetTypeHash(SecurityIndex));
	// 	return Hash;
	// }

	FORCEINLINE bool operator==(const FSkinnedMeshRuntime_Lf& Rhs) const
	{
		return this->MeshID == Rhs.MeshID;
	}

	FORCEINLINE bool operator!=(const FSkinnedMeshRuntime_Lf& Rhs) const
	{
		return !(*this == Rhs);
	}

	FTransform WorldSpaceTransform = FTransform::Identity;

	TArray<FAnimationMetaData_Lf> AnimationMetaData;
	// < Animation ID | Animation Index >
	TMap<uint32, int32> AnimationIDs;

	// < Animation Group Layer Hash | Animation Group >
	TMap<uint32, FAnimationGroup_Lf> AnimationGroups;

	TMap<TObjectPtr<UBlendSpace>, FAnimationBlendSpaceData_Lf> AnimationBlendSpaceMetaData;

	int16 LodIndex = GET0_NUMBER;
	bool bIsDistanceUpdatingThisFrame = true;

	float ClosestCameraDistance = GET0_NUMBER;
	float DeltaTimeAccumulator = GET0_NUMBER;

	uint32 MaterialsHash = GET0_NUMBER;

	bool bForceVisibilityUpdatingThisFrame = false;

	int64 LastFrameAnimationSolved = GET0_NUMBER;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="足迹资产", ToolTip="指定该运行时网格实例使用的 Footprint 资产。"))
	TObjectPtr<UTurboSequence_FootprintAsset_Lf> FootprintAsset;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Hybrid 网格实例", ToolTip="指定该运行时实例关联的 Hybrid Actor。"))
	TObjectPtr<AActor> HybridMeshInstance;

	bool bSpawnedHybridActor = false;

	int32 UpdateGroupIndex = INDEX_NONE;
};


/*	==============================================================================================================
												GLOBAL
	==============================================================================================================	*/

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationBlendLayerMask_Lf
{
	GENERATED_BODY()

	// We need a way to track how many animations are using this animation layer
	int32 AnimationLayerCounter = GET0_NUMBER;

	// < Skeleton Layer of Max CPU Bones * 0xFF >
	TArray<uint16> RawAnimationLayers;

	// After Creating the Layer, We can Hash the Value
	// < Hash >
	uint32 AnimationLayerHash = GET0_NUMBER;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FAsyncTextureGenerationChunk_Lf
{
	GENERATED_BODY()

	TArray<FUintVector3> LodDimensions;

	int32 NumPixelsPerIteration = GET0_NUMBER;

	int32 NumPixelsComputed = GET0_NUMBER;

	TMap<int32, bool> TestValue;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="数据资产", ToolTip="指定该异步纹理生成块对应的网格资产。"))
	TObjectPtr<UTurboSequence_MeshAsset_Lf> DataAsset;


	FORCEINLINE void Init(const TObjectPtr<UTextureRenderTarget2DArray> Tex, int32 MaxPixelIndex,
	                      int16 NumRowsFree, int16 Index)
	{
		int32 CeilRows = FMath::CeilToInt(
			static_cast<float>(LodDimensions[Index].X + MaxPixelIndex) / static_cast<float>(Tex->SizeY)) + NumRowsFree;
		int32 ChunkSizeY = CeilRows * Tex->SizeX;

		LodDimensions[Index].Z = CeilRows;

		LodDimensions[Index].Y = ChunkSizeY;
	}
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshGlobalLibrary_RenderThread_Lf
{
	GENERATED_BODY()

	FSkinnedMeshGlobalLibrary_RenderThread_Lf()
	{
		SkinWeightParams = FSettingsComputeShader_Params_Lf();
		BoneTransformParams = FMeshUnitComputeShader_Params_Lf();
		AnimationLibraryParams = FSettingsComputeShader_Params_Lf();
	}

	~FSkinnedMeshGlobalLibrary_RenderThread_Lf()
	{
	}


	FSettingsComputeShader_Params_Lf SkinWeightParams;
	FMeshUnitComputeShader_Params_Lf BoneTransformParams;

	FSettingsComputeShader_Params_Lf AnimationLibraryParams;

	uint32 NumMeshesVisibleCurrentFrame = GET0_NUMBER;
	uint32 NumIKPixelCurrentFrame = GET0_NUMBER;
	uint32 NumAnimationsCurrentFrame = GET0_NUMBER;

	TMap<int32, FSkinnedMeshRuntime_RenderThread_Lf> RuntimeSkinnedMeshes;
	TArray<int32> RuntimeSkinnedMeshesHashMap;

	uint32 AnimationLibraryMaxNum = GET0_NUMBER;

	// < MeshID | Index >
	TMap<int32, int32> MeshIDToGlobalIndex;

	TMap<TObjectPtr<UTurboSequence_MeshAsset_Lf>, FSkinnedMeshReference_RenderThread_Lf> PerReferenceData;
	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="引用数据键", ToolTip="查看渲染线程全局库中记录的引用数据资产键列表。"))
	TArray<TObjectPtr<UTurboSequence_MeshAsset_Lf>> PerReferenceDataKeys;
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FSkinnedMeshGlobalLibrary_Lf
{
	GENERATED_BODY()

	FSkinnedMeshGlobalLibrary_Lf()
	{
	}

	~FSkinnedMeshGlobalLibrary_Lf()
	{
	}

	TMap<int32, FSkinnedMeshRuntime_Lf> RuntimeSkinnedMeshes;
	TArray<int32> RuntimeSkinnedMeshesHashMap;
	TMap<int32, bool> BlackListedMeshIDs;

	// < MeshID | Data >
	TMap<int32, FTurboSequence_MinimalMeshData_Lf> MeshIDToMinimalData;

	TMap<TObjectPtr<UTurboSequence_MeshAsset_Lf>, FSkinnedMeshReference_Lf> PerReferenceData;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="引用数据键", ToolTip="查看全局库中记录的引用数据资产键列表。"))
	TArray<TObjectPtr<UTurboSequence_MeshAsset_Lf>> PerReferenceDataKeys;

	// -> Key -> < USkeleton | UTurboSequence_MeshAsset_Lf | UAnimSequence >
	TMap<FUintVector, FAnimationLibraryData_Lf> AnimationLibraryData;
	uint32 AnimationLibraryMaxNum = GET0_NUMBER;
	TArray<FVector4f> AnimationLibraryDataAllocatedThisFrame;
	// // Sum of -> ( Values * Library Hash, Mesh Bones ) is the Keyframe index
	// // We need this construct to easy determinate the index when we remove an animation from the GPU
	// // We need an alpha type to copy the new Library Data over
	// TMap<FUintVector, int32> AnimationLibraryAlphaKeyframeDimensions;

	TArray<FCameraView_Lf> CameraViews;

	TArray<FAnimationBlendLayerMask_Lf> AnimationBlendLayerMasks;
	// Contains the Runtime ID which is having dirty Animation Data
	TMap<FUintVector2, bool> AnimationBlendLayerMasksRuntimeDirty;

	uint16 MaxNumCPUBones = GET0_NUMBER;
	uint16 MaxNumGPUBones = GET0_NUMBER;
	uint16 MaxNumLevelOfDetailsWithMesh = GET0_NUMBER;
	bool bMaxNumCPUBonesChanged = false;

	TArray<FTurboSequence_UpdateGroup_Lf> UpdateGroups;

	// < MeshID | Index >
	TMap<int32, int32> MeshIDToGlobalIndex;

	int16 NumGroupsUpdatedThisFrame = GET0_NUMBER;
};
