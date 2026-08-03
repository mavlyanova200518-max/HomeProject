// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestAsyncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HOMEPROJECT_API UQuestAsyncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    // ќбъ€вл€ем функцию, которую будет видно в Ѕлюпринтах
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    static void ProcessQuestsAsync();
};