// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "TurboSequence_AnimLibrary_Lf.h"
#include "TurboSequence_GlobalData_Lf.h"
#include "TurboSequence_Helper_Lf.h"
#include "UObject/Object.h"
#include "TurboSequence_MeshAsset_Lf.generated.h"


UENUM(BlueprintType)
enum class ETurboSequence_RenderMode_Lf : uint8
{
	InstancedStaticMeshComponent,
	NiagaraParticle
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FMeshData_Lf
{
	GENERATED_BODY()

	FMeshData_Lf()
	{
	}

	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="顶点数量", ToolTip="查看该网格数据条目记录的顶点数量。"))
	int32 NumVertices = GET0_NUMBER;
	
	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="Nanite 顶点数量", ToolTip="查看该网格数据条目记录的 Nanite 顶点数量。"))
	int32 NumNaniteVertices = GET0_NUMBER;

	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="CPU 到 GPU 骨骼映射", ToolTip="查看 CPU 骨骼索引到 GPU 骨骼索引的映射关系。"))
	TMap<int32, int32> CPUBoneToGPUBoneIndicesMap;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FMeshDataOrderView_Lf
{
	GENERATED_BODY()

	FMeshDataOrderView_Lf()
	{
	}

	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="静态网格索引", ToolTip="查看用于排序显示的静态网格索引列表。"))
	TArray<int32> StaticMeshIndices;
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FMeshItem_Lf
{
	GENERATED_BODY()

	FMeshItem_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="Instance",
		meta=(DisplayName="静态网格", ToolTip=
			"设置该细节层级使用的静态网格。替换为其他网格后需要重新烘焙 Mesh Asset。"
			, ShortTooltip=
			"设置该细节层级使用的静态网格。替换为其他网格后需要重新烘焙 Mesh Asset。"
		))
	// The Static Mesh for this Level Of Detail, when you replace it with a different mesh, you need to re-bake the Mesh Asset
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditAnywhere, Category="Settings",
		meta=(DisplayName="启用动画", ToolTip=
			"设置该网格在该 LOD 下是否需要继续播放动画。远距离时可关闭以节省性能。",
			ShortTooltip=
			"设置该网格在该 LOD 下是否需要继续播放动画。远距离时可关闭以节省性能。"))
	// Does the Mesh needs to be Animated because on 300 meters it may does not make a difference for the view
	bool bIsAnimated = true;

	UPROPERTY(EditAnywhere, Category="Settings",
		meta=(DisplayName="显示网格", ToolTip="设置该 LOD 网格是否在场景中显示，适合调试 LOD 效果。",
			ShortTooltip="设置该 LOD 网格是否在场景中显示，适合调试 LOD 效果。"))
	// Does the Mesh needs to be shown in the level, useful for debugging Level of Details
	bool bShowMesh = true;

	UPROPERTY(EditAnywhere, Category="Settings",
		meta=(DisplayName="启用视锥剔除", ToolTip=
			"设置该 LOD 网格是否参与视锥剔除。某些近距离 LOD 可关闭以避免阴影问题。"
			, ShortTooltip=
			"设置该 LOD 网格是否参与视锥剔除。某些近距离 LOD 可关闭以避免阴影问题。"
		))
	// Does the Mesh needs to be enabled for frustum culling, it makes sense to not cull the LOD 0 because of the shadows
	bool bIsFrustumCullingEnabled = true;

	UPROPERTY(EditAnywhere, Category="Settings",
		meta=(DisplayName="从系统中排除该 LOD", ToolTip=
			"设置该 LOD 是否从 TurboSequence 系统中排除，适合多边形数异常的网格。"
			, ShortTooltip=
			"设置该 LOD 是否从 TurboSequence 系统中排除，适合多边形数异常的网格。"
		))
	// Does the Mesh needs to be part of the system, useful if the poly count is too high or to low, in this case the mesh can getting hidden
	bool bExcludeLodFromSystem = false;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TURBOSEQUENCE_LF_API UTurboSequence_MeshAsset_Lf : public UObject
{
	GENERATED_BODY()

public:
	UTurboSequence_MeshAsset_Lf();

	/*	==============================================================================================================
												GAMEPLAY
	==============================================================================================================	*/
	UPROPERTY(EditAnywhere, Category="Global",
		meta=(DisplayName="从系统中排除", ToolTip="启用后该网格资产不会参与 TurboSequence 运行时系统。"))
	bool bExcludeFromSystem = false;

	UPROPERTY(EditAnywhere, Category="Global",
		meta=(DisplayName="全局数据", ToolTip="指定该网格资产使用的 TurboSequence 全局数据对象。"))
	TObjectPtr<UTurboSequence_GlobalData_Lf> GlobalData;

	UPROPERTY(EditAnywhere, Category="Reference",
		meta=(DisplayName="渲染系统", ToolTip="指定该网格资产使用的 Niagara 渲染系统。"))
	TObjectPtr<UNiagaraSystem> RendererSystem;
	
	UPROPERTY(EditAnywhere, Category="Rendering",
		meta=(DisplayName="渲染模式", ToolTip="选择该网格资产使用的渲染模式。"))
	ETurboSequence_RenderMode_Lf RenderMode = ETurboSequence_RenderMode_Lf::NiagaraParticle;

	UPROPERTY(EditAnywhere, Category="Reference",
		meta=(DisplayName="原始参考骨骼网格", ToolTip="指定原始参考的 SkeletalMesh 资源。"))
	TObjectPtr<USkeletalMesh> ReferenceMeshNative;

	UPROPERTY(EditAnywhere, Category="Reference",
		meta=(DisplayName="编辑后参考骨骼网格", ToolTip="指定用于编辑或生成流程的参考 SkeletalMesh 资源。"))
	TObjectPtr<USkeletalMesh> ReferenceMeshEdited;

	UPROPERTY(EditAnywhere, Category="Reference",
		meta=(DisplayName="网格数据纹理", ToolTip="指定该网格资产生成出的 Mesh Data 纹理资源。"))
	TObjectPtr<UTexture2DArray> MeshDataTexture;

	UPROPERTY(EditAnywhere, Category="Nanite",
		meta=(ClampMin = "0", ClampMax = "100000", DisplayName="Nanite 最大动画距离", ToolTip="设置使用 Nanite 渲染器时，距离摄像机多远仍继续计算动画。"
			, ShortTooltip=
			"设置使用 Nanite 渲染器时，距离摄像机多远仍继续计算动画。"
		))
	// Max Animation Distance in Meter from the camera when using the Nanite Renderer
	float NaniteMaxAnimationDistance = 17000.0f;

	UPROPERTY(EditAnywhere, Category="Optimization",
		meta=(ClampMin = "0.001", ClampMax = "0.2", DisplayName="动画库帧间隔", ToolTip=
			"设置动画库线性抽帧时的时间间隔，越小质量越高但内存占用越大。"
			, ShortTooltip=
			"设置动画库线性抽帧时的时间间隔，越小质量越高但内存占用越大。"
		))
	// Turbo Sequence makes linear Keyframe Reduction, 1 Keyframe happens in this interval, ( Quality | Memory Usage ) <- -> ( Low Memory Usage )
	float TimeBetweenAnimationLibraryFrames = 0.05f;

	UPROPERTY(EditAnywhere, Category="Optimization",
		meta=(DisplayName="启用距离更新", ToolTip="启用后，离摄像机更近的实例会以更高频率更新。",
			ShortTooltip="启用后，离摄像机更近的实例会以更高频率更新。"))
	// If Enabled Instances close the camera update more frequent
	bool bUseDistanceUpdating = true;


	UPROPERTY(EditAnywhere, Category="Optimization",
		meta=(ClampMin = "0.05", ClampMax = "1.9", DisplayName="距离更新比例", ToolTip=
			"值越小，实例会根据距离获得更高的求解频率。", ShortTooltip=
			"值越小，实例会根据距离获得更高的求解频率。"))
	// Lower means More Solver Ticks relative to the distance of the Instance
	float DistanceUpdatingRatio = 0.25f;

	UPROPERTY(EditAnywhere, Category="Lod",
		meta=(ClampMin = "0", ClampMax = "10000", DisplayName="最高细节绘制距离", ToolTip=
			"设置最高细节 LOD 的绘制距离。0 表示禁用该级别。",
			ShortTooltip=
			"设置最高细节 LOD 的绘制距离。0 表示禁用该级别。"
		))
	// Draw Range of the Highest Detail LOD, 0 Means it's disabled | Otherwise Average range is from 2000 - 6000
	int32 HighestDetailDrawDistance = 0;

	UPROPERTY(EditAnywhere, Category="Lod",
		meta=(ClampMin = "500", ClampMax = "10000", DisplayName="自动 LOD 比例", ToolTip=
			"值越大，LOD 之间的切换距离分布越分散。", ShortTooltip=
			"值越大，LOD 之间的切换距离分布越分散。"))
	// Higher Value means More Spread-out LODs, means MinLOD = AutoLodRatio * LOD_Percentage
	int32 AutoLodRatio = 3000;

	UPROPERTY(EditAnywhere, Category="Lod",
		meta=(DisplayName="实例化网格列表", ToolTip="配置该资产各个 LOD 使用的静态网格条目。"))
	TArray<FMeshItem_Lf> InstancedMeshes;

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="默认覆盖动画", ToolTip="指定该网格资产默认使用的覆盖动画。"))
	TObjectPtr<UAnimSequence> OverrideDefaultAnimation;

	UPROPERTY(EditAnywhere, Category="Animation",
		meta=(DisplayName="动画库", ToolTip="指定该网格资产绑定的 TurboSequence 动画库。"))
	TObjectPtr<UTurboSequence_AnimLibrary_Lf> AnimationLibrary;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="网格数据模式", ToolTip="查看该网格资产当前生成出的网格数据模式。"))
	ETurboSequence_MeshDataMode_Lf MeshDataMode = ETurboSequence_MeshDataMode_Lf::UV;

	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="网格数据", ToolTip="查看该网格资产当前生成的网格数据列表。"))
	TArray<FMeshData_Lf> MeshData;

	int32 MeshDataCustomData = GET0_NUMBER;

	UPROPERTY(VisibleAnywhere, SaveGame, Category="TurboSequence",
		meta=(DisplayName="网格数据排序视图", ToolTip="查看该网格资产生成的网格数据排序视图。"))
	TArray<FMeshDataOrderView_Lf> MeshDataOrderView;

	const FReferenceSkeleton& GetReferenceSkeleton() const
	{
		return ReferenceMeshNative->GetRefSkeleton();
	}

	TObjectPtr<USkeleton> GetSkeleton() const
	{
		return ReferenceMeshNative->GetSkeleton();
	}

	bool IsMeshAssetValid() const
	{
		if (!IsValid(this))
		{
			UE_LOG(LogTurboSequence_Lf, Warning,
			       TEXT("Can't create Mesh Instance, the Asset you use is not valid...."));
			return false;
		}

		if (!IsValid(GetSkeleton()))
		{
			UE_LOG(LogTurboSequence_Lf, Warning,
			       TEXT("Can't create Mesh Instance, the Asset you use has no Skeleton assigned...."));
			return false;
		}

		if (!MeshData.Num())
		{
			UE_LOG(LogTurboSequence_Lf, Warning,
			       TEXT("Can't create Mesh Instance, the Asset you use has no Mesh Data, please bake the mesh fist...."
			       ));
			return false;
		}

		if (!InstancedMeshes.Num())
		{
			UE_LOG(LogTurboSequence_Lf, Warning, TEXT("Can't create Mesh Instance, the Asset you use has no LODs...."));
			return false;
		}

		if (bExcludeFromSystem)
		{
			UE_LOG(LogTurboSequence_Lf, Warning,
			       TEXT(
				       "Can't create Mesh Instance, the Asset you use is excluded from the system because bExcludeFromSystem is true"
			       ));
			return false;
		}

		return true;
	}

	/*	==============================================================================================================
												UI
	==============================================================================================================	*/

	UPROPERTY(EditAnywhere, Category="UI",
		meta=(DisplayName="最大 LOD 数量", ToolTip="设置编辑器界面中允许生成的最大 LOD 数量。"))
	int32 MaxLevelOfDetails = 10;
	
	UPROPERTY(EditAnywhere, Category="UI",
		meta=(DisplayName="使用 Nanite", ToolTip="设置该资产在生成时是否默认启用 Nanite。"))
	bool bUseNanite = true;

	/*	==============================================================================================================
												COMPATIBILITY
	==============================================================================================================	*/

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="下次启动需重新生成", ToolTip="查看该资产是否标记为下次启动引擎时需要重新生成。"))
	bool bNeedGeneratedNextEngineStart = false;
};
