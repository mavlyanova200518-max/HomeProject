#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreeExecutionContext.h"
#include "AIController.h"
#include "NPCStateTreeTasks.generated.h"

// Задача 1: Найти точку патрулирования

USTRUCT()
struct FSTTask_FindPatrolPointInstanceData
{
    GENERATED_BODY()

    // Автоматический биндинг AIController из контекста
    UPROPERTY(EditAnywhere, Category = "Context")
    TObjectPtr<AAIController> AIController;

    // Выходной параметр: куда именно идти
    UPROPERTY(EditAnywhere, Category = "Output")
    FVector Destination = FVector::ZeroVector;
};

USTRUCT(meta = (DisplayName = "Find Patrol Point", Category = "NPC AI"))
struct FSTTask_FindPatrolPoint : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTTask_FindPatrolPointInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override
    {
        FInstanceDataType& Inst = Context.GetInstanceData(*this);

        if (Inst.AIController)
        {
            // TODO: Здесь логика запроса случайной точки в радиусе от начальной позиции
            return EStateTreeRunStatus::Succeeded;
        }
        return EStateTreeRunStatus::Failed;
    }
};

// Задача 2: Поиск (идем в последнюю известную точку)

USTRUCT()
struct FSTTask_FindSearchPointInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Context")
    TObjectPtr<AAIController> AIController;

    UPROPERTY(EditAnywhere, Category = "Output")
    FVector Destination = FVector::ZeroVector;
};

USTRUCT(meta = (DisplayName = "Find Search Point", Category = "NPC AI"))
struct FSTTask_FindSearchPoint : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTTask_FindSearchPointInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override
    {
        // TODO: Запросить из памяти AIController последнюю позицию игрока
        return EStateTreeRunStatus::Succeeded;
    }
};

// Задача 3: Преследование (Combat)

USTRUCT()
struct FSTTask_ChasePlayerInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Context")
    TObjectPtr<AAIController> AIController;
};

USTRUCT(meta = (DisplayName = "Chase Current Target", Category = "NPC AI"))
struct FSTTask_ChasePlayer : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FSTTask_ChasePlayerInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override
    {
        FInstanceDataType& Inst = Context.GetInstanceData(*this);

        // TODO: Дать команду MoveTo к текущей цели (TargetPlayer)
        // Эта задача использует Tick, так как преследование идет непрерывно каждый кадр
        return EStateTreeRunStatus::Running;
    }
};