#include "BaseCharacter.h"

// Конструктор по умолчанию
ABaseCharacter::ABaseCharacter()
{
    // Указываем, должен ли этот персонаж обновляться каждый кадр
    PrimaryActorTick.bCanEverTick = true;
}

// Вызывается при старте игры или появлении на уровне
void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Вызывается каждый кадр
void ABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Вызывается для настройки кнопок управления
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
