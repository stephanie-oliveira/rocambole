// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Cogumelo.h"
#include "Robson.h"


// Sets default values
ACogumelo::ACogumelo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Cria a �rea de colis�o
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	
	//Permite que aconte�am eventos de sobreposi��o
	Root->bGenerateOverlapEvents = true;
	//Diz que pode sobrepor qualquer objeto
	Root->SetCollisionProfileName("OverlapAllDynamic");
	//Diz qual m�todo ser� chamado quando acontecer a sobreposi��o
	Root->OnComponentBeginOverlap.AddDynamic(this, &ACogumelo::OnOverlapBegin);
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));	
	//Nada vai colidir com a forma para n�o haver conflitos
	MeshComp->SetCollisionProfileName("NoCollision");
	//Liga a forma � �rea
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
	//Se o ator for diferente de um ponteiro nulo / se o ator n�o for ele mesmo / se o comp for difertente de nulo
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		//Converter objeto de um tipo generalizado para um mais espec�fico (cast)
		ARobson* Robson = Cast<ARobson>(OtherActor);
		
		//Acrescentar na vida
		Robson->SetLife(Robson->GetLife() + LifeAmount);

		//LOG
		//Par�metros: categoria, tipo, conte�do (%d -> indica que ali haver� um int, que deve ser indicado no pr�ximo par�metro)
		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), Robson->GetLife());

		//UE_LOG(LogTemp, Warning, TEXT("Posi��o = %d"), Robson->GetActorLocation());


		//Quando ocorrer a colis�o e acrescentar a vida, destr�i o objeto
		Destroy();




	}
}
