#include "BossCharacter.h"

#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossCharacter::ABossCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = AAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate =
        FRotator(0.0f, 360.0f, 0.0f);

    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ABossCharacter::BeginPlay()
{
    Super::BeginPlay();
}


void ABossCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AAIController* AI = Cast<AAIController>(GetController());

    if (!Player || !AI)
    {
        return;
    }

    float Distance = FVector::Dist(
        GetActorLocation(),
        Player->GetActorLocation()
    );

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            20,
            1.0f,
            FColor::Yellow,
            FString::Printf(
                TEXT("Distance: %.0f | AttackRange: %.0f"),
                Distance,
                AttackRange
            )
        );
    }

    // If the player leaves detection range, return to Idle.
    if (Distance > DetectionRange)
    {
        AI->StopMovement();
        CurrentState = EBossState::Idle;
        ChaseUpdateTimer = 0.0f;
        return;
    }

    switch (CurrentState)
    {
    case EBossState::Idle:
    {
        CurrentState = EBossState::Chase;
        break;
    }

    case EBossState::Chase:
    {
        if (Distance <= AttackRange)
        {
            AI->StopMovement();
            CurrentState = EBossState::Attack;
            break;
        }

        ChaseUpdateTimer -= DeltaTime;

        if (ChaseUpdateTimer <= 0.0f)
        {
            AI->MoveToActor(Player, AttackRange);
            ChaseUpdateTimer = 0.2f;
        }

        break;
    }

    case EBossState::Attack:
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                2.0f,
                FColor::Red,
                TEXT("BOSS ATTACKING!")
            );
        }

        AttackTimer = AttackCooldown;
        CurrentState = EBossState::Recover;
        break;
    }

    case EBossState::Recover:
    {
        AttackTimer -= DeltaTime;

        if (AttackTimer <= 0.0f)
        {
            CurrentState = EBossState::Chase;
            ChaseUpdateTimer = 0.0f;
        }

        break;
    }
    }
}



void ABossCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent
)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
