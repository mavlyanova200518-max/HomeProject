#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// Этот класс не трогаем, он нужен движку для рефлексии
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

// А вот здесь мы пишем наши функции
class HOMEPROJECT_API IInteractable
{
    GENERATED_BODY()

public:
    // Вызывается при самом взаимодействии (нажатии кнопки)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AActor* Instigator);

    // Проверка, можно ли сейчас взаимодействовать
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    bool CanInteract(AActor* Instigator) const;

    // Получение текста для UI-подсказки (например, "Открыть дверь")
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    FText GetInteractionPrompt() const;

    // Вызывается, когда игрок смотрит на предмет (для подсветки)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnFocused(AActor* Instigator);

    // Вызывается, когда игрок отворачивается от предмета
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnUnfocused(AActor* Instigator);
};