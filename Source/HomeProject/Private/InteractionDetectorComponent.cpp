#include "InteractionDetectorComponent.h"
#include "Interactable.h"
#include "GameFramework/Actor.h" // Добавлено для уверенности компилятора

UInteractionDetectorComponent::UInteractionDetectorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // ИСПРАВЛЕНИЕ: Безопасное задание радиуса для конструктора
    InitSphereRadius(200.0f);
}

void UInteractionDetectorComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UInteractionDetectorComponent::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UInteractionDetectorComponent::OnOverlapEnd);
}

void UInteractionDetectorComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->Implements<UInteractable>())
    {
        if (IInteractable::Execute_CanInteract(OtherActor, GetOwner()))
        {
            OverlappingActors.AddUnique(OtherActor);
            RecomputeFocus();
        }
    }
}

void UInteractionDetectorComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OverlappingActors.Contains(OtherActor))
    {
        // Просто удаляем предмет из списка и вызываем пересчет. 
        // Функция RecomputeFocus сама поймет, что фокус пропал, и отправит виджету пустой текст.
        OverlappingActors.Remove(OtherActor);
        RecomputeFocus();
    }
}

void UInteractionDetectorComponent::RecomputeFocus()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    AActor* BestActor = nullptr;
    float MinDistance = MAX_FLT;

    for (AActor* Actor : OverlappingActors)
    {
        if (!Actor) continue;

        float Dist = FVector::Dist(Owner->GetActorLocation(), Actor->GetActorLocation());
        if (Dist < MinDistance)
        {
            MinDistance = Dist;
            BestActor = Actor;
        }
    }

    if (FocusedActor != BestActor)
    {
        if (FocusedActor && FocusedActor->Implements<UInteractable>())
        {
            IInteractable::Execute_OnUnfocused(FocusedActor, Owner);
        }

        FocusedActor = BestActor;

        FText Prompt = FText::GetEmpty();
        if (FocusedActor && FocusedActor->Implements<UInteractable>())
        {
            IInteractable::Execute_OnFocused(FocusedActor, Owner);
            Prompt = IInteractable::Execute_GetInteractionPrompt(FocusedActor);
        }

        OnFocusChanged.Broadcast(FocusedActor, Prompt);
    }
}

void UInteractionDetectorComponent::TryInteract(AActor* InstigatorActor)
{
    if (FocusedActor && FocusedActor->Implements<UInteractable>())
    {
        // Если взаимодействовать можно — просто взаимодействуем!
        if (IInteractable::Execute_CanInteract(FocusedActor, InstigatorActor))
        {
            IInteractable::Execute_Interact(FocusedActor, InstigatorActor);

            // Движок сам поймет, когда мы отойдем, и вызовет OnOverlapEnd.
        }
    }
}