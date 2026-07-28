#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"
#include "AIController.h"
#include "NPCStateTreeConditions.generated.h"

// Условие 1: Has Target (Видит ли враг цель)

USTRUCT()
struct FSTCondition_HasTargetInstanceData
{
    GENERATED_BODY()

    // Автоматическая привязка к контроллеру из контекста схемы
    UPROPERTY(EditAnywhere, Category = "Context")
    TObjectPtr<AAIController> AIController;
};

USTRUCT(meta = (DisplayName = "Has Target", Category = "NPC AI"))
struct FSTCondition_HasTarget : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTCondition_HasTargetInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        // Здесь будет реальная логика запроса к AIController. 
        // Пока возвращаем false, чтобы просто собрать каркас.
        return false;
    }
};

// Условие 2: Has Last Known Location (Помнит ли, где игрок)

USTRUCT()
struct FSTCondition_HasLastKnownLocationInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Context")
    TObjectPtr<AAIController> AIController;
};

USTRUCT(meta = (DisplayName = "Has Last Known Location", Category = "NPC AI"))
struct FSTCondition_HasLastKnownLocation : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTCondition_HasLastKnownLocationInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        return false;
    }
};