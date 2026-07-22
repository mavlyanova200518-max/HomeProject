#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponActor::AWeaponActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Создаем компонент меша и делаем его корневым
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
}