// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_MinimalData_Lf.h"
#include "Components/ActorComponent.h"
#include "TurboSequence_MeshActorConnection_Lf.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TURBOSEQUENCE_LF_API UTurboSequence_MeshActorConnection_Lf : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTurboSequence_MeshActorConnection_Lf();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="Actor 网格数据 ID", ToolTip="查看当前 Actor 关联的 TurboSequence 网格数据 ID。"))
	FTurboSequence_MinimalMeshData_Lf ActorTSMeshDataID;

	UPROPERTY(VisibleAnywhere, Category="TurboSequence",
		meta=(DisplayName="足迹资产", ToolTip="查看当前连接组件关联的 Footprint 资产。"))
	TObjectPtr<UTurboSequence_FootprintAsset_Lf> FootprintAsset;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="骨骼网格组件", ToolTip="指定需要和 TurboSequence 联动的骨骼网格组件列表。"))
	TArray<USkinnedMeshComponent*> SkinnedMeshComponents;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	virtual void OnMeshDataIDSend_GameThread(const FTurboSequence_MinimalMeshData_Lf& MeshData);

	virtual const FTurboSequence_MinimalMeshData_Lf& GetTsMeshData() const
	{
		return ActorTSMeshDataID;
	}

	virtual void OnFootprintAssetTick_GameThread(const float DeltaTime);
};
