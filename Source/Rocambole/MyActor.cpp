// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "MyActor.h"
#include "Robson.h"



// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->OnComponentHit.AddDynamic(this, &AMyActor::OnHit);

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector LocalizacaoAtual = GetActorLocation();

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	LocalizacaoAtual.Z += DeltaHeight * 700.0f;
	//LocalizacaoAtual.X += DeltaHeight * 300.0f;
	RunningTime += DeltaTime;
	SetActorLocation(LocalizacaoAtual);

}

void AMyActor::	OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		
		ARobson* Robson = Cast<ARobson>(OtherActor);

		Robson->SetLife(Robson->GetLife() - LifeAmount);

		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());
	}

}


