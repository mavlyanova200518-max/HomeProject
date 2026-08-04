
#include "QuestAsyncLibrary.h"
#include "Async/Async.h"
#include "Async/ParallelFor.h"
#include "Engine/Engine.h"

void UQuestAsyncLibrary::ProcessQuestsAsync()
{
    // 1. Уводим задачу в фоновый поток (Асинхронность)
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, []()
        {
            // Имитируем, что мы получили большой массив данных квестов
            // Например, 10 000 квестов с базовой наградой в 100 монет
            TArray<int32> QuestRewards;
            QuestRewards.Init(100, 10000);

            // 2. ПАРАЛЛЕЛЬНАЯ обработка
            // ParallelFor раскидывает вычисления массива по всем свободным ядрам процессора
            ParallelFor(QuestRewards.Num(), [&QuestRewards](int32 Index)
                {
                    // Симулируем "тяжелую работу" по перерасчету наград для каждого квеста
                    int32 CurrentReward = QuestRewards[Index];

                    // Нагружаем процессор математикой, чтобы оправдать потоки
                    for (int32 i = 0; i < 500; ++i)
                    {
                        CurrentReward += (CurrentReward % 2 == 0) ? 1 : -1;
                    }

                    QuestRewards[Index] = CurrentReward;
                });

            // 3. Возвращаемся в основной поток (GameThread), чтобы обновить интерфейс
            AsyncTask(ENamedThreads::GameThread, [ProcessedCount = QuestRewards.Num()]()
                {
                    if (GEngine)
                    {
                        // Выводим зеленое сообщение с количеством обработанных квестов
                        FString Message = FString::Printf(TEXT("Параллельная обработка квестов успешно завершена!"), ProcessedCount);
                        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
                        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
                    }
                });
        });
}



