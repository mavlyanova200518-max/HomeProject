#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h" // Подключаем наш интерфейс
#include "InteractableActor.generated.h"

UCLASS()
class HOMEPROJECT_API AInteractableActor : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AInteractableActor();

protected:
    // Меш предмета (видимая часть)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* Mesh; // Назван Mesh согласно архитектуре с вебинара

    // Переменная для текста подсказки, которую дизайнер сможет менять в блюпринтах
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FText PromptText;


public:
    // Переопределяем функции интерфейса
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual bool CanInteract_Implementation(AActor* Interactor) const override;
    virtual FText GetInteractionPrompt_Implementation() const override;
    virtual void OnFocused_Implementation(AActor* Interactor) override;
    virtual void OnUnfocused_Implementation(AActor* Interactor) override;

};