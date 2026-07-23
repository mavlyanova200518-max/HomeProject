#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponActor.h"
#include "TestModule/ModuleTestActor.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Настройка вращения персонажа
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    // Создаем SpringArm (штатив камеры)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Создаем саму камеру
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Подключаем Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    // Проверяем, задан ли класс оружия в настройках
    if (DefaultWeaponClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // Спавним оружие на сцене
        CurrentWeapon = GetWorld()->SpawnActor<AWeaponActor>(DefaultWeaponClass, GetTransform(), SpawnParams);

        if (CurrentWeapon)
        {
            // Прикрепляем оружие к мешу персонажа в сокет правой руки "hand_rSocket"
            CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_rSocket"));
        }
    }
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
        // Биндим приседание: нажали кнопку — сели, отпустили — встали
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &APlayerCharacter::StartCrouching);
        EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &APlayerCharacter::StopCrouching);
        // Биндим прыжок ко встроенным функциям ACharacter
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ThisClass::StartSprint);
        EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
    }
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void APlayerCharacter::StartCrouching()
{
    Crouch();
}

void APlayerCharacter::StopCrouching()
{
    UnCrouch();
}

void APlayerCharacter::StartSprint()
{
    // Меняем максимальную скорость на 1000 (быстрый бег)
    GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void APlayerCharacter::StopSprint()
{
    // Возвращаем стандартную скорость
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::SpawnModuleActor()
{
    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200.0f;
    FRotator SpawnRotation = GetActorRotation();

    GetWorld()->SpawnActor<AModuleTestActor>(AModuleTestActor::StaticClass(), SpawnLocation, SpawnRotation);
}