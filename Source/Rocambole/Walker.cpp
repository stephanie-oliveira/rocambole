// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Walker.h"


// Sets default values
AWalker::AWalker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->OnComponentHit.AddDynamic(this, &AWalker::OnHit);

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AWalker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector LocalizacaoAtual = GetActorLocation();
	float Range = 5.0f;
	if (Right && Cont < 30) {
		LocalizacaoAtual.Y += Range;
		Cont++;
		if (Cont == 30) {
			Right = false;
			Down = true;
		}
	} 

	if (Down && Cont >= 30) {
		LocalizacaoAtual.X -= Range;
		Cont++;
		if (Cont == 60) {
			Down = false;
			Left = true;
		}

	}
	
	if (Left && Cont >= 60) {
		LocalizacaoAtual.Y -= Range;
		Cont++;
		if (Cont == 90) {
			Left = false;
			Up = true;
		}

	}
	
	if (Up && Cont >= 90) {
		LocalizacaoAtual.X += Range;
		Cont++;
		if (Cont == 120) {
			Up = false;
			Right = true;
			Cont = 0;
		}

	}


	RunningTime += DeltaTime;
	SetActorLocation(LocalizacaoAtual);

}

void AWalker::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		AWalker* Walker = Cast<AWalker>(OtherActor);


		//UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());
	}

}


