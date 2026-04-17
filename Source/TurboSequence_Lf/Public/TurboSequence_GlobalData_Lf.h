// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_ComputeShaders_Lf.h"
#include "TurboSequence_Helper_Lf.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/DataAsset.h"
#include "Engine/TextureRenderTarget2DArray.h"
#include "TurboSequence_GlobalData_Lf.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTSEditorMeshGeneratedSignature);

/**
 * 
 */
UCLASS()
class TURBOSEQUENCE_LF_API UTurboSequence_GlobalData_Lf : public UObject
{
public:
	GENERATED_BODY()

	UTurboSequence_GlobalData_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 发射器名称", ToolTip="设置 TurboSequence 在 Niagara 中使用的发射器名称。"))
	FString NameNiagaraEmitter = FString("FXE_TurboSequence_Mesh_Unit_Lf");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 网格对象名称", ToolTip="设置 Niagara 用户参数中网格对象的名称模板。"))
	FString NameNiagaraMeshObject = FString("User.Mesh_{0}");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 材质对象名称", ToolTip="设置 Niagara 用户参数中材质对象的名称模板。"))
	FString NameNiagaraMaterialObject = FString("User.Material_{0}");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 粒子位置名称", ToolTip="设置 Niagara 粒子位置数据的参数名称。"))
	FString NameNiagaraParticleLocations = FString("User.Particle_Position");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 粒子 ID 名称", ToolTip="设置 Niagara 粒子 ID 映射数据的参数名称。"))
	FString NameNiagaraParticleIDMap = FString("User.Particle_ID_To_Index");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 粒子旋转名称", ToolTip="设置 Niagara 粒子旋转数据的参数名称。"))
	FString NameNiagaraParticleRotations = FString("User.Particle_Rotation");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 粒子缩放名称", ToolTip="设置 Niagara 粒子缩放数据的参数名称。"))
	FString NameNiagaraParticleScales = FString("User.Particle_Scale");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 细节层级名称", ToolTip="设置 Niagara 中用于传递 LOD 索引的参数名称。"))
	FString NameNiagaraLevelOfDetailIndex = FString("User.LevelOfDetail_Index");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 粒子移除名称", ToolTip="设置 Niagara 中用于移除粒子的参数名称。"))
	FString NameNiagaraParticleRemove = FString("User.Particle_Remove");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 自定义数据名称", ToolTip="设置 Niagara 中用于传递自定义数据的参数名称。"))
	FString NameNiagaraCustomData = FString("User.CustomData");
	
	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="Niagara 使用 Nanite 名称", ToolTip="设置 Niagara 中标记是否使用 Nanite 的参数名称。"))
	FString NameNiagaraUseNanite = FString("User.TS_UseNanite");

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="当前帧变换纹理", ToolTip="指定当前帧骨骼变换写入使用的纹理数组资源。"))
	TObjectPtr<UTextureRenderTarget2DArray> TransformTexture_CurrentFrame;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="前一帧变换纹理", ToolTip="指定上一帧骨骼变换使用的纹理数组资源。"))
	TObjectPtr<UTextureRenderTarget2DArray> TransformTexture_PreviousFrame;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="蒙皮权重纹理", ToolTip="指定存储蒙皮权重数据的纹理数组资源。"))
	TObjectPtr<UTextureRenderTarget2DArray> SkinWeightTexture;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画库纹理", ToolTip="指定存储动画库数据的纹理数组资源。"))
	TObjectPtr<UTextureRenderTarget2DArray> AnimationLibraryTexture;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="高精度动画模式", ToolTip="启用后会使用更高精度的动画数据格式。"))
	bool bUseHighPrecisionAnimationMode = true;

	FSettingsComputeShader_Params_Lf CachedMeshDataCreationSettingsParams;
	
	// Reserved for Delegates
	UPROPERTY(BlueprintAssignable)
	FOnTSEditorMeshGeneratedSignature OnTSMeshGenerated;
};
