// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "ChangeColor.h"
#include "Robson.h"


// Sets default values
AChangeColor::AChangeColor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->bGenerateOverlapEvents = true;

	Root->SetCollisionProfileName("OverlapAllDynamic");
	//diz que esse elemento vai disparar os eventos no momento em que iniciar a sobreposi��o / quando encerrar a sobreposi��o
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->OnComponentBeginOverlap.AddDynamic(this, &AChangeColor::OnOverlapBegin);
	
	//Root->OnComponentEndOverlap.AddDynamic(this, &AChangeColor::OnOverlapEnd);
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	//classe est�tica que s� pode ser usada no construtor, n�o nos m�todos / encontra um objeto espec�fico e carrega o mesh via c�digo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Wedge_A.Shape_Wedge_A'"));

	//ver se conseguiu carregar o objeto / se for carregado o objeto, conseguiu encontrar o elemento, seta pro MeshComponent
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}

	//agora procura um objeto do tipo UMaterial
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/Amarelo.Amarelo'"));

	//se for encontrado, seta pro MeshComp (indice em que vai entrar e o objeto que ser� jogado nessa posi��o)
	if (Material.Succeeded()) {

		MeshComp->SetMaterial(0,Material.Object);
	}

	//ajuste via c�digo da posi��o do root e do mesh component
	MeshComp->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AChangeColor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChangeColor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//Mudar a cor quando estiver sobrepondo o objeto
void AChangeColor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		ARobson* Robson = Cast<ARobson>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("OverlapBegin"));
		if (MeshComp->GetMaterial(0)->GetName() == "Amarelo") {
			UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Materials/Azul.Azul'")));
			if (NewMaterial != nullptr) {
				MeshComp->SetMaterial(0, NewMaterial);

				Robson->SetCont(Robson->GetCont() + 1);
				UE_LOG(LogTemp, Warning, TEXT("Cont + 1"));
				UE_LOG(LogTemp, Warning, TEXT("Cont + 1 /=%d"), Robson->GetCont());


			}
		}
		else {
			UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Materials/Amarelo.Amarelo'")));
			if (NewMaterial != nullptr) {
				MeshComp->SetMaterial(0, NewMaterial);

				Robson->SetCont(Robson->GetCont() - 1);
				UE_LOG(LogTemp, Warning, TEXT("Cont - 1"));
				UE_LOG(LogTemp, Warning, TEXT("Cont + 1 /=%d"), Robson->GetCont());

			}
		}
		if (Robson->GetCont() == 4) {

			UE_LOG(LogTemp, Warning, TEXT("YOU WIN"));

			//pega o level atual e todo o mundo 
			UWorld* World = GetWorld();
			if (World != nullptr) {
				//para abrir um novo level / passa o mundo atual e o nome do pr�ximo level por parametro
				UGameplayStatics::OpenLevel(World, "OnHit");
			}

		}
	}

	

}

//void AChangeColor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

