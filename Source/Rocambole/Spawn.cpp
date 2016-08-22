// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Spawn.h"



// Sets default values
ASpawn::ASpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	
	//inidica tamanho inicial
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);

		}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MeshComp->AttachTo(RootComponent);

	//definir tempo de vida
	InitialLifeSpan = 5.0f;

	//movimenta o projétil
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//indica onde o update será feito
	ProjectileMovement->UpdatedComponent = Root;
	//velocidade inicial e máxima
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 2500.0f;

}

// Called when the game starts or when spawned
void ASpawn::BeginPlay()
{
	Super::BeginPlay();

	//quando iniciar o jogo, define o Z do projétil
	DefaultZ = GetActorLocation().Z;
	
}

// Called every frame
void ASpawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//seta a posição Z para a cada frame ele mantenha a localização no eixo z
	FVector Location = GetActorLocation();
	Location.Z = DefaultZ;
	SetActorLocation(Location);

}

