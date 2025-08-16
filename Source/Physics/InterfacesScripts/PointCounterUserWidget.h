// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointCounterUserWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PHYSICS_API UPointCounterUserWidget : public UUserWidget
{
	GENERATED_BODY()

	const FString POINTS_TEXT = FString(TEXT("Points : "));

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock;

private:
	UFUNCTION()
	void SetNewPointCount(const int NewPoints);

	virtual bool Initialize() override;
};
