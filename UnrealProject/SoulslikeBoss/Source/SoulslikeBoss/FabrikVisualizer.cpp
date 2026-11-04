#include "FabrikVisualizer.h"

#include "DrawDebugHelpers.h"
// Fill out your copyright notice in the Description page of Project Settings.

// Sets default values
AFabrikVisualizer::AFabrikVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFabrikVisualizer::BeginPlay()
{
    Super::BeginPlay();

    Chain = MakeUnique<jointChain>(
        3,
        2.0,
        std::vector<double>{0.0, 0.0, 0.0},
        std::vector<std::vector<double>>{
            {0.0, 0.0, 0.0},
            { 1.0, 0.0, 0.0 },
            { 2.0, 0.0, 0.0 }
    },
        std::vector<double>{1.0, 1.0}
    );
}

// Called every frame
void AFabrikVisualizer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            1,
            0.0f,
            FColor::Green,
            TEXT("FABRIK ACTOR IS RUNNING!")
        );
    }

    if (!Chain)
        return;

    // Convert Unreal target coordinates to solver coordinates.
    const FVector Target = TargetOffset / 100.0;

    std::vector<double> SolverTarget = {
        Target.X,
        Target.Y,
        Target.Z
    };

    // Run your custom FABRIK solver.
    Chain->calculateNewPositions(SolverTarget);

    // Convert solver coordinates to Unreal world coordinates.
    auto ToWorld = [this](const std::vector<double>& P) {
        return GetActorLocation() +
            FVector(P[0], P[1], P[2]) * 100.0;
        };

    // Draw the target.
    DrawDebugSphere(
        GetWorld(),
        GetActorLocation() + TargetOffset,
        12.0f,
        12,
        FColor::Green,
        false,
        0.0f
    );

    // Draw joints and bones.
    for (std::size_t i = 0; i < Chain->jointPositions.size(); ++i)
    {
        FVector Position = ToWorld(Chain->jointPositions[i]);

        DrawDebugSphere(
            GetWorld(),
            Position,
            8.0f,
            12,
            FColor::Red,
            false,
            0.0f
        );

        if (i > 0)
        {
            FVector Previous =
                ToWorld(Chain->jointPositions[i - 1]);

            DrawDebugLine(
                GetWorld(),
                Previous,
                Position,
                FColor::Blue,
                false,
                0.0f,
                0,
                3.0f
            );
        }
    }
}

