// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IK/VectorMath.hpp"

#include "FabrikVisualizer.generated.h"

UCLASS()
class SOULSLIKEBOSS_API AFabrikVisualizer : public AActor
{
	GENERATED_BODY()
	
private:
	TUniquePtr<jointChain> Chain;

public:
	UPROPERTY(EditAnywhere, Category = "FABRIK")
	FVector TargetOffset = FVector(100.0, 100.0, 0.0);
public:	
	// Sets default values for this actor's properties
	AFabrikVisualizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
