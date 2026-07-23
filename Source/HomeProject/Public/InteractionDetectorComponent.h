#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionDetectorComponent.generated.h"

// ИСПРАВЛЕНИЕ: FText теперь передается по константной ссылке, чтобы компилятор был счастлив
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFocusChanged, AActor*, NewFocusedActor, const FText&, InteractionPrompt);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOMEPROJECT_API UInteractionDetectorComponent : public USphereComponent
{
    GENERATED_BODY()

public:
    UInteractionDetectorComponent();

    // Событие для оповещения виджета при смене фокуса
    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnFocusChanged OnFocusChanged;

    // Метод попытки взаимодействия с текущим сфокусированным предметом
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void TryInteract(AActor* InstigatorActor);

protected:
    virtual void BeginPlay() override;

    // Списки и методы для отслеживания перекрытий
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    void RecomputeFocus();

    UPROPERTY()
    TArray<AActor*> OverlappingActors;

    UPROPERTY()
    AActor* FocusedActor;
};