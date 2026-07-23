#include "InteractableActor.h"
#include "Components/StaticMeshComponent.h"

AInteractableActor::AInteractableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Создаем компонент меша и делаем его корнем актора
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    // Задаем стандартный текст подсказки
    PromptText = FText::FromString(TEXT("Взаимодействовать"));
}

void AInteractableActor::Interact_Implementation(AActor* Interactor)
{
    // Базовая логика взаимодействия
}

bool AInteractableActor::CanInteract_Implementation(AActor* Interactor) const
{
    return true;
}

FText AInteractableActor::GetInteractionPrompt_Implementation() const
{
    return PromptText;
}

void AInteractableActor::OnFocused_Implementation(AActor* Interactor)
{
    if (Mesh)
    {
        Mesh->SetRenderCustomDepth(true);
    }
}

void AInteractableActor::OnUnfocused_Implementation(AActor* Interactor)
{
    if (Mesh)
    {
        Mesh->SetRenderCustomDepth(false);
    }
}