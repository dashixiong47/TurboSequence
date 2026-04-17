// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_Demo_Lf.h"
#include "TurboSequence_MeshAsset_Lf.h"
#include "TurboSequence_MinimalData_Lf.h"
#include "GameFramework/Actor.h"
#include "TurboSequence_FeaturesDemo_Lf.generated.h"


USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="启用", ToolTip="设置该功能演示是否启用。"))
	bool bEnable = true;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动作变换列表", ToolTip="配置该功能演示使用的动作变换列表。"))
	TArray<FTransform> ActionTransforms;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="生成数据", ToolTip="配置该功能演示要生成的网格数据。"))
	TArray<FTurboSequence_MeshSpawnData_Lf> Spawns;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="网格数据", ToolTip="查看该功能演示当前生成出的网格数据列表。"))
	TArray<FTurboSequence_MinimalMeshData_Lf> MeshData;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoBlending_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="混合层", ToolTip="配置简单或分层混合演示使用的骨骼层。"))
	TArray<FTurboSequence_BoneLayer_Lf> BlendLayers;

	float RandomTimer = 0;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoTweaking_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="调整动画", ToolTip="查看或缓存参数调整演示使用的动画集合。"))
	FTurboSequence_AnimMinimalCollection_Lf TweakingAnimation;

	float RandomTimer = 0;
	float RandomAnimationData = 0;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoRootMotion_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoIK_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="IK 权重", ToolTip="配置 IK 演示中各骨骼的权重。"))
	TMap<FName, float> IKWeights;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="IK 总权重", ToolTip="设置 IK 演示使用的总权重。"))
	float MasterIKWeight = GET0_NUMBER;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="生成偏移", ToolTip="设置 IK 演示实例的生成偏移。"))
	FTransform SpawnOffset = FTransform::Identity;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoLod_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoSockets_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="插槽名称", ToolTip="指定插槽演示使用的插槽名称。"))
	FName SocketName = FName("Socket");
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoCustomization_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="目标动画", ToolTip="缓存自定义演示当前目标动画集合。"))
	FTurboSequence_AnimMinimalCollection_Lf TargetAnimations;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="提取动画数据", ToolTip="查看或缓存自定义演示提取出的动画数据。"))
	TArray<FAnimationMetaData_Lf> ExtractedAnimationsData;

	float RandomTimer = 0;
	int16 RandomIndex = 0;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="根资产列表", ToolTip="配置自定义演示的主资产列表。"))
	TArray<FDemoMeshSpawnData_Lf> RootAssets;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="可自定义资产列表", ToolTip="配置自定义演示的附加资产列表。"))
	TArray<FDemoMeshSpawnData_Lf> CustomizableAssets;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="已分类根数据", ToolTip="查看自定义演示整理后的主资产分类数据。"))
	FDemoCustomizationContainer_Lf CategorizedRootData;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="已分类自定义数据", ToolTip="查看自定义演示整理后的附加资产分类数据。"))
	TMap<FName, FDemoCustomizationContainer_Lf> CategorizeCustomizableData;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoBlendSpace_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示 Blend Space", ToolTip="指定 Blend Space 演示使用的 Blend Space 资源。"))
	TObjectPtr<UBlendSpace> DemoBlendSpace;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="调整中的 Blend Space", ToolTip="缓存 Blend Space 演示当前的运行时数据。"))
	FTurboSequence_AnimMinimalBlendSpaceCollection_Lf TweakingBlendSpace;

	float RandomTimer = 0;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoCurves_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定曲线演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画数据", ToolTip="缓存曲线演示当前的动画集合数据。"))
	FTurboSequence_AnimMinimalCollection_Lf DemoAnimationData;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="曲线名称", ToolTip="指定曲线演示读取的动画曲线名称。"))
	FName CurveName = FName("Curve");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="材质参数名称", ToolTip="指定曲线值写入的材质参数名称。"))
	FName MaterialParameterName = FName("bIsCurveValue");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="右侧材质实例", ToolTip="指定曲线演示右侧使用的动态材质实例。"))
	TObjectPtr<UMaterialInstanceDynamic> RfMaterialInstance;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="左侧材质实例", ToolTip="指定曲线演示左侧使用的动态材质实例。"))
	TObjectPtr<UMaterialInstanceDynamic> LfMaterialInstance;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoNormals_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoUpdateGroups_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;

	TArray<float> DeltaTime;
};


USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoHybridMode_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoNanite_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

USTRUCT()
struct TURBOSEQUENCE_LF_API FFeatureDemoRenderer_Lf : public FFeatureDemoBase_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="演示动画", ToolTip="指定该功能演示使用的动画资源。"))
	TObjectPtr<UAnimSequence> DemoAnimation;
};

UENUM(BlueprintType)
enum class EFeatureDemoEnableFeature_Lf : uint8
{
	None,
	SimpleBlending,
	LayerBlending,
	Tweaking,
	RootMotion,
	IK,
	LevelOfDetails,
	Sockets,
	Customization,
	BlendSpaces,
	//Additive,
	Curves,
	Normals,
	UpdateGroups,
	HybridMode,
	Nanite,
	Renderer
};


UCLASS()
class TURBOSEQUENCE_LF_API ATurboSequence_FeaturesDemo_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurboSequence_FeaturesDemo_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="更新管理器", ToolTip="设置该功能演示 Actor 是否在 Tick 中驱动管理器更新。"))
	bool bUpdateManager = false;


	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="启用功能标记", ToolTip="选择需要启用的功能演示集合。"))
	TArray<EFeatureDemoEnableFeature_Lf> EnableFlags;

	FORCEINLINE bool ShouldEnableFeature(const EFeatureDemoEnableFeature_Lf& Feature)
	{
		if (!EnableFlags.Num())
		{
			return true;
		}

		for (const EFeatureDemoEnableFeature_Lf& Other : EnableFlags)
		{
			if (Feature == Other)
			{
				return true;
			}
		}

		return false;
	}

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="根组件", ToolTip="查看功能演示 Actor 使用的根场景组件。"))
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="简单混合演示", ToolTip="配置简单混合功能演示。"))
	FFeatureDemoBlending_Lf SimpleBlendingDemo = FFeatureDemoBlending_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="分层混合演示", ToolTip="配置分层混合功能演示。"))
	FFeatureDemoBlending_Lf LayerBlendingDemo = FFeatureDemoBlending_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画调整演示", ToolTip="配置动画参数调整功能演示。"))
	FFeatureDemoTweaking_Lf AnimationTweaksDemo = FFeatureDemoTweaking_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="根运动演示", ToolTip="配置根运动功能演示。"))
	FFeatureDemoRootMotion_Lf RootMotionDemo = FFeatureDemoRootMotion_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="IK 演示", ToolTip="配置 IK 功能演示。"))
	FFeatureDemoIK_Lf IKDemo = FFeatureDemoIK_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="LOD 演示", ToolTip="配置 LOD 功能演示。"))
	FFeatureDemoLod_Lf LodDemo = FFeatureDemoLod_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="插槽演示", ToolTip="配置插槽功能演示。"))
	FFeatureDemoSockets_Lf SocketsDemo = FFeatureDemoSockets_Lf();

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="插槽演示网格", ToolTip="查看插槽演示使用的静态网格组件。"))
	TObjectPtr<UStaticMeshComponent> SocketsDemoMesh;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="自定义演示", ToolTip="配置自定义替换功能演示。"))
	FFeatureDemoCustomization_Lf CustomizationDemo = FFeatureDemoCustomization_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Blend Space 演示", ToolTip="配置 Blend Space 功能演示。"))
	FFeatureDemoBlendSpace_Lf BlendSpaceDemo = FFeatureDemoBlendSpace_Lf();

	inline static FVector3f LastDemoBlendSpacePosition = FVector3f::ZeroVector;

	UFUNCTION(BlueprintCallable, Category="TurboSequence")
	static FVector3f GetFeatureDemoBlendSpacePosition_TurboSequence_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="曲线演示", ToolTip="配置动画曲线功能演示。"))
	FFeatureDemoCurves_Lf CurveDemo = FFeatureDemoCurves_Lf();

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="右侧曲线演示网格", ToolTip="查看曲线演示右侧使用的静态网格组件。"))
	TObjectPtr<UStaticMeshComponent> RfCurveDemoMesh;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="左侧曲线演示网格", ToolTip="查看曲线演示左侧使用的静态网格组件。"))
	TObjectPtr<UStaticMeshComponent> LfCurveDemoMesh;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="法线演示", ToolTip="配置法线功能演示。"))
	FFeatureDemoNormals_Lf NormalsDemo = FFeatureDemoNormals_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="更新组演示", ToolTip="配置更新组功能演示。"))
	FFeatureDemoUpdateGroups_Lf UpdateGroupsDemo = FFeatureDemoUpdateGroups_Lf();

	int32 CurrentUpdateGroupIndex = 1;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Hybrid 模式演示", ToolTip="配置 Hybrid Mode 功能演示。"))
	FFeatureDemoHybridMode_Lf HybridMode = FFeatureDemoHybridMode_Lf();
	
	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Nanite 演示", ToolTip="配置 Nanite 功能演示。"))
	FFeatureDemoNanite_Lf NaniteDemo = FFeatureDemoNanite_Lf();
	
	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="渲染器演示", ToolTip="配置渲染器功能演示。"))
	FFeatureDemoRenderer_Lf RendererDemo = FFeatureDemoRenderer_Lf();
};
