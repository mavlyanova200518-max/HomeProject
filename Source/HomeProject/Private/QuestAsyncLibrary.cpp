#include "QuestAsyncLibrary.h"
#include "Async/Async.h"
#include "Engine/Engine.h" // Нужно для вывода зеленого текста на экран

void UQuestAsyncLibrary::ProcessQuestsAsync()
{
    // 1. Уводим задачу в фоновый поток (чтобы игра не зависла)
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, []()
        {
            // Здесь обычно находится тяжелый код (парсинг квестов, поиск путей и т.д.)
            // сымитируем это, "усыпив" этот поток на 3 секунды
            FPlatformProcess::Sleep(3.0f);

            // 2. Когда тяжелая работа закончена, мы ОБЯЗАНЫ вернуться в основной поток (GameThread),
            // чтобы безопасно выдать награду игроку или обновить интерфейс
            AsyncTask(ENamedThreads::GameThread, []()
                {
                    // Выводим зеленое сообщение на экран как доказательство работы
                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Асинхронная проверка квестов успешно завершена!"));
                        UE_LOG(LogTemp, Warning, TEXT("Асинхронная проверка квестов успешно завершена!"));
                    }
                });
        });
}