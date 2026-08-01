#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UNiagaraSystem;
class UMetaSoundSource;

UCLASS()
class HOMEPROJECT_API APlayerCharacter : public ABaseCharacter
{
    GENERATED_BODY()

public:
    APlayerCharacter();
    UFUNCTION(BlueprintCallable, Category = "Testing")
    void SpawnModuleActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UAnimMontage* ReloadMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UAnimMontage* HitMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
    UAnimMontage* InteractMontage;

    UFUNCTION(BlueprintCallable, Category = "Animations")
    void PlayReloadAnim();

    UFUNCTION(BlueprintCallable, Category = "Animations")
    void PlayHitAnim();

    UFUNCTION(BlueprintCallable, Category = "Animations")
    void PlayInteractAnim();

    // Слот эффекта NS_BulletImpact
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX|Weapons")
    UNiagaraSystem* BulletImpactVFX;

    // Функция выстрела
    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void FireWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // --- Компоненты камеры ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    // --- Настройки Enhanced Input ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* IA_Crouch;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* IA_Jump;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* IA_Sprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio|Ambient")
    class USoundBase* DesertWindSound;

    // Переменная, которая позволит выбирать класс оружия в свойствах блюпринта
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<class AWeaponActor> DefaultWeaponClass;

    // Ссылка на уже созданное в игре оружие
    UPROPERTY()
    class AWeaponActor* CurrentWeapon;

    // --- Функции управления ---
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartCrouching();
    void StopCrouching();
    void StartSprint();
    void StopSprint();
};