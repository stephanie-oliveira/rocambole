// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "CogumeloDoMau.h"
#include "Robson.h"


// Sets default values
ACogumeloDoMau::ACogumeloDoMau()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Cria a área de colisão
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	//Permite que aconteçam eventos de sobreposição
	Root->bGenerateOverlapEvents = true;
	//Diz que pode sobrepor qualquer objeto
	Root->SetCollisionProfileName("OverlapAllDynamic");
	//Diz qual método será chamado quando acontecer a sobreposição
	Root->OnComponentBeginOverlap.AddDynamic(this, &ACogumeloDoMau::ColisaoDoMau);
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//Nada vai colidir com a forma para não haver conflitos
	MeshComp->SetCollisionProfileName("NoCollision");
	//Liga a forma à área
	MeshComp->AttachTo(RootComponent);


}

// Called when the game starts or when spawned
void ACogumeloDoMau::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACogumeloDoMau::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACogumeloDoMau::ColisaoDoMau(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->IsA(ARobson::StaticClass()))) {
		//Converter objeto de um tipo generalizado para um mais específico (cast)
		ARobson* Robson = Cast<ARobson>(OtherActor);
		//Decrementar na vida

		Robson->SetLife(Robson->GetLife() - 50);
		Robson->GameOver();

		//LOG
		//Parâmetros: categoria, tipo, conteúdo (%d -> indica que ali haverá um int, que deve ser indicado no próximo parâmetro)
		UE_LOG(LogTemp, Warning, TEXT("Damage, life = %d"), Robson->GetLife());

		//Quando ocorrer a colisão e acrescentar a vida, destrói o objeto
		Destroy();


	}
}

