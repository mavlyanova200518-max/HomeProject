#include "ModuleTestActor.h"
#include "Components/StaticMeshComponent.h"

AModuleTestActor::AModuleTestActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Создаем компонент
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // Автоматически подгружаем стандартный куб из папки Engine
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(CubeMeshAsset.Object);
    }
}

// Called when the game starts or when spawned
void AModuleTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModuleTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

