// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Timer.h"


// Sets default values
ATimer::ATimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);

	}
	MeshComp->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	MeshComp->AttachTo(RootComponent);

	TheFinalCountdown = 5.0f;

}

// Called when the game starts or when spawned
void ATimer::BeginPlay()
{
	Super::BeginPlay();

	//quando o jogo iniciar, starta o carinha
	//gerenciador de tempo da pr�pria unreal
	//par�metros: o timer handler, classe respons�vel pelo timer, qual m�todo ser� chamado a cada tanto tempo, a cada tempo ser� chamado o m�todo, boolean para "ativar" o m�todo
	
	//GetWorldTimerManager().SetTimer(CountdownTimerHandle, &ATimer::TimerManager, 1.0f, true);
	
}

// Called every frame
void ATimer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATimer:: TimerManager() {

	//decrementa o contador
	TheFinalCountdown -= 1.0f;

	if (TheFinalCountdown <= 0.0f) {
		//cancela o timer quando chega em 0 / passa por par�metro qual timer ser� reiniciado
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("MORREU"));
		Destroy();
	}
}


