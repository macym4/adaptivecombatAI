
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
    Idle,
    Chase,
    Attack,
    Recover
};

UCLASS()
class SOULSLIKEBOSS_API ABossCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Constructor
    ABossCharacter();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Input handling
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent
    ) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // Maximum distance at which boss detects player
    UPROPERTY(EditAnywhere, Category = "Boss AI")
    float DetectionRange = 1500.0f;

    // Distance at which boss stops chasing
    UPROPERTY(EditAnywhere, Category = "Boss AI")
    float AttackRange = 300.0f;

private:
    // Tracks whether boss has started chasing player
    bool bChasingPlayer = false;
    float ChaseUpdateTimer = 0.0f;
    EBossState CurrentState = EBossState::Idle;

    float AttackCooldown = 2.0f;
    float AttackTimer = 0.0f;
};
