#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class HOMEPROJECT_API AWeaponActor : public AActor
{
    GENERATED_BODY()

public:
    AWeaponActor();

protected:
    // —келетный меш (или статик меш) дл€ отображени€ оружи€
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    class USkeletalMeshComponent* WeaponMesh;
};