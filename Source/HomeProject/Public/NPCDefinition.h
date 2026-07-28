#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCDefinition.generated.h"

// Создаем перечисление для отношения NPC к игроку
UENUM(BlueprintType)
enum class ENPCRelationship : uint8
{
    Friendly UMETA(DisplayName = "Friendly"),
    Neutral UMETA(DisplayName = "Neutral"),
    Hostile UMETA(DisplayName = "Hostile")
};

UCLASS()
class HOMEPROJECT_API UNPCDefinition : public UDataAsset
{
    GENERATED_BODY()

public:
    // Имя NPC
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Settings")
    FText DisplayName;

    // Отношение к игроку
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Settings")
    ENPCRelationship Relationship;

    // Радиус зрения (важно для врагов)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Settings")
    float SightRadius = 1500.0f;
};