// Fill out your copyright notice in the Description page of Project Settings.


#include "C_VisualActor.h"

// Sets default values
AC_VisualActor::AC_VisualActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Визуальный компонент
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

    if (CubeAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeAsset.Object);
    }

}

// Called when the game starts or when spawned
void AC_VisualActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_VisualActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

