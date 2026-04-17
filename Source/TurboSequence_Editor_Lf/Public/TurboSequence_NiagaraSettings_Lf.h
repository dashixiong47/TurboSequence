// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TurboSequence_NiagaraSettings_Lf.generated.h"

/**
 * 
 */
UCLASS(config = "TurboSequence_Lf")
class TURBOSEQUENCE_EDITOR_LF_API UTurboSequence_NiagaraSettings_Lf : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// Constructors / Destructors

	UTurboSequence_NiagaraSettings_Lf();
	virtual ~UTurboSequence_NiagaraSettings_Lf() override;

	//~ Begin UDeveloperSettings Interface
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	// End of UDeveloperSettings

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 发射器名称", ToolTip="设置 TurboSequence 使用的 Niagara 发射器名称。"), Category="Niagara 设置")
	FString NameNiagaraEmitter = FString("FXE_TurboSequence_Mesh_Unit_Lf");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 网格对象名称", ToolTip="设置 Niagara 用户参数里网格对象的名称模板。"), Category="Niagara 设置")
	FString NameNiagaraMeshObject = FString("User.Mesh_{0}");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 材质对象名称", ToolTip="设置 Niagara 用户参数里材质对象的名称模板。"), Category="Niagara 设置")
	FString NameNiagaraMaterialObject = FString("User.Material_{0}");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 粒子 ID 名称", ToolTip="设置 Niagara 粒子 ID 参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraParticleIDs = FString("User.Particle_ID_To_Index");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 粒子位置名称", ToolTip="设置 Niagara 粒子位置参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraParticleLocations = FString("User.Particle_Position");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 粒子旋转名称", ToolTip="设置 Niagara 粒子旋转参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraParticleRotations = FString("User.Particle_Rotation");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 粒子缩放名称", ToolTip="设置 Niagara 粒子缩放参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraParticleScales = FString("User.Particle_Scale");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 细节层级名称", ToolTip="设置 Niagara LOD 参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraLevelOfDetailIndex = FString("User.LevelOfDetail_Index");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 自定义数据名称", ToolTip="设置 Niagara 自定义数据参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraCustomData = FString("User.CustomData");

	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 粒子移除名称", ToolTip="设置 Niagara 粒子移除参数的名称。"), Category="Niagara 设置")
	FString NameNiagaraParticleRemove = FString("User.Particle_Remove");
	
	UPROPERTY(EditAnywhere, Config, meta = (DisplayName = "Niagara 使用 Nanite 名称", ToolTip="设置 Niagara 中标记 Nanite 状态的参数名称。"), Category="Niagara 设置")
	FString NameUseNanite = FString("User.TS_UseNanite");
};
