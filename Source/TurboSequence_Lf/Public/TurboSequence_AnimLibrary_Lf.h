// Copyright Lukas Fratzl, 2022-2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"
#include "UObject/Object.h"
#include "TurboSequence_AnimLibrary_Lf.generated.h"

USTRUCT()
struct TURBOSEQUENCE_LF_API FAnimationLibraryItem_Lf
{
	GENERATED_BODY()

	FAnimationLibraryItem_Lf()
	{
	}

	~FAnimationLibraryItem_Lf()
	{
	}

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画序列", ToolTip="选择要收录到 TurboSequence 动画库中的动画序列。"))
	TObjectPtr<UAnimSequence> Animation;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画种子速度（厘米/秒）", ToolTip="设置该动画的参考移动速度，单位为厘米每秒。"))
	FVector AnimationSeed_CM_Per_Second = FVector(600, 0, 0);
};


/**
 * 
 */
UCLASS()
class TURBOSEQUENCE_LF_API UTurboSequence_AnimLibrary_Lf : public UObject
{
	GENERATED_BODY()

public:
	UTurboSequence_AnimLibrary_Lf();

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="动画列表", ToolTip="配置该动画库包含的动画序列条目。"))
	TArray<FAnimationLibraryItem_Lf> Animations;

	UPROPERTY(EditAnywhere, Category="TurboSequence",
		meta=(DisplayName="混合空间列表", ToolTip="配置该动画库包含的 Blend Space 资源。"))
	TArray<TObjectPtr<UBlendSpace>> BlendSpaces;
};
