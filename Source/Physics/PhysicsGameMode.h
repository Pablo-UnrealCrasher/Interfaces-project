#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PhysicsGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPointCountChange, int, NewPointCount);

class ABreakableTarget;

UCLASS(minimalapi)
class APhysicsGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData, meta = (AllowPrivateAccess = "true"))
	int PointCount = 0;

public:
	FPointCountChange OnPointCountChange;

	
	// FUNCTIONS
	
	APhysicsGameMode();
	
	UFUNCTION(BlueprintCallable)
	void SetPointCount(const int NewPointCount);

	UFUNCTION(BlueprintCallable)
	int GetPointCount() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};



