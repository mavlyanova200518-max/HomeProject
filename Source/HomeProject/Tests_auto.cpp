
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

// Задаем имя класса и путь в меню Session Frontend
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHomeProjectSanityTest, "HomeProject.Basic.Sanity", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FHomeProjectSanityTest::RunTest(const FString& Parameters)
{
    // Входные данные системы
    float TargetValue = 100.0f;  // Заданное (желаемое) значение
    float CurrentValue = 90.0f;  // Текущее значение
    float Kp = 1.5f;             // Коэффициент пропорциональности

    // Вычисление статической ошибки прямым методом
    float Error = TargetValue - CurrentValue;

    // Вычисление управляющего воздействия (логика П-регулятора)
    float ActualOutput = Error * Kp;

    // Ожидаемый результат: (100 - 90) * 1.5 = 15.0
    float ExpectedOutput = 15.0f;

    TestEqual(TEXT("Проверка расчета управляющего воздействия П-регулятора"), ActualOutput, ExpectedOutput);

    return true;
}
#endif 