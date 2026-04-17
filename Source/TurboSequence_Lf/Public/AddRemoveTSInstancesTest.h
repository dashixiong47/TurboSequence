// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_MinimalData_Lf.h"
#include "GameFramework/Actor.h"
#include "AddRemoveTSInstancesTest.generated.h"

USTRUCT()
struct TURBOSEQUENCE_LF_API FTestInstance
{
	GENERATED_BODY()

	FTurboSequence_MeshSpawnData_Lf UsedSpawnData;

	FTransform SpawnTransform = FTransform::Identity;
	FBoxSphereBounds Bounds;
	bool bSpawned = false;

	FTurboSequence_MinimalMeshData_Lf MeshData;

};


UCLASS()
class TURBOSEQUENCE_LF_API AAddRemoveTSInstancesTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAddRemoveTSInstancesTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="生成实例数量", ToolTip="设置测试中要批量生成的实例数量。"))
	int32 NumSpawnInstances = 10000;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="网格间距", ToolTip="设置测试生成时网格之间的间距。"))
	int32 DistanceBetweenMeshes = 700;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="生成数据列表", ToolTip="配置用于批量生成测试实例的生成数据列表。"))
	TArray<FTurboSequence_MeshSpawnData_Lf> SpawnData;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画序列", ToolTip="指定测试实例播放的动画序列。"))
	TObjectPtr<UAnimSequence> AnimSequence;

	TArray<FTestInstance> TestInstances;
};
