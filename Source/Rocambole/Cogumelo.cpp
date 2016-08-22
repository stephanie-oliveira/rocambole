// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Cogumelo.h"
#include "Robson.h"


// Sets default values
ACogumelo::ACogumelo()
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
	Root->OnComponentBeginOverlap.AddDynamic(this, &ACogumelo::OnOverlapBegin);
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));	
	//Nada vai colidir com a forma para não haver conflitos
	MeshComp->SetCollisionProfileName("NoCollision");
	//Liga a forma à área
	MeshComp->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ACogumelo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACogumelo::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACogumelo::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//Se o ator for diferente de um ponteiro nulo / se o ator não for ele mesmo / se o comp for difertente de nulo
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		//Converter objeto de um tipo generalizado para um mais específico (cast)
		ARobson* Robson = Cast<ARobson>(OtherActor);
		
		//Acrescentar na vida
		Robson->SetLife(Robson->GetLife() + LifeAmount);

		//LOG
		//Parâmetros: categoria, tipo, conteúdo (%d -> indica que ali haverá um int, que deve ser indicado no próximo parâmetro)
		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());

		//UE_LOG(LogTemp, Warning, TEXT("Posição = %d"), Robson->GetActorLocation());


		//Quando ocorrer a colisão e acrescentar a vida, destrói o objeto
		Destroy();




	}
}
