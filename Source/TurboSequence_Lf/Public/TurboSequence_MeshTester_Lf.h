// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurboSequence_MinimalData_Lf.h"
#include "GameFramework/Actor.h"
#include "TurboSequence_MeshTester_Lf.generated.h"

UCLASS()
class TURBOSEQUENCE_LF_API ATurboSequence_MeshTester_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurboSequence_MeshTester_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Mesh Tester",
		meta=(DisplayName="生成数据", ToolTip="配置测试 Actor 生成 TurboSequence 网格时使用的数据。"))
	// The spawn data to give spawn info in the Actor Details panel
	FTurboSequence_MeshSpawnData_Lf SpawnData;

	UPROPERTY(EditAnywhere, Category="Mesh Tester",
		meta=(DisplayName="测试动画", ToolTip="指定测试 Actor 启动后要播放的动画。"))
	// The Animation to Play
	TObjectPtr<UAnimSequence> MeshAnimation;

	UPROPERTY(EditAnywhere, Category="Mesh Tester",
		meta=(DisplayName="动画设置", ToolTip="配置测试动画的播放设置。"))
	// The Animation settings to play
	FTurboSequence_AnimPlaySettings_Lf MeshAnimationSettings = FTurboSequence_AnimPlaySettings_Lf();

	UPROPERTY(EditAnywhere, Category="Mesh Tester",
		meta=(DisplayName="更新上下文", ToolTip="配置测试 Actor 参与求解时使用的更新上下文。"))
	FTurboSequence_UpdateContext_Lf MeshUpdateContext = FTurboSequence_UpdateContext_Lf();

	void TestMesh(float DeltaTime);
	FTurboSequence_MeshSpawnData_Lf LastSpawnData;

	UPROPERTY(VisibleAnywhere, Category="Mesh Tester",
		meta=(DisplayName="当前网格 ID", ToolTip="查看当前测试实例生成后的 TurboSequence 网格 ID。"))
	FTurboSequence_MinimalMeshData_Lf CurrentMeshID;

	UPROPERTY(VisibleAnywhere, Category="Mesh Tester",
		meta=(DisplayName="当前动画 ID", ToolTip="查看当前测试实例正在使用的动画集合 ID。"))
	FTurboSequence_AnimMinimalCollection_Lf CurrentAnimationID;
};
