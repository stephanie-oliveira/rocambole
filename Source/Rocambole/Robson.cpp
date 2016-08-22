// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocambole.h"
#include "Robson.h"
#include "Spawn.h"

// Sets default values
ARobson::ARobson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Permite que haja sobreposição
	GetCapsuleComponent()->bGenerateOverlapEvents = true;


	//Cria forma do personagem
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(GetCapsuleComponent());


	//Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	//distancia entre o player e a camera / ligação entre o player e a camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	PlayerCamera->AttachTo(CameraBoom);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->AttachTo(MeshComp);

	//Seta velocidade do personagem
	GetCharacterMovement()->MaxWalkSpeed = 400;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


}

// Called when the game starts or when spawned
void ARobson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobson::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ARobson::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//mapeamento de entrada criado no editor, qual elemento que ele vai movimentar, qual método será utilizado quando chamar isso(endereço de memória onde foi armazenado)
	InputComponent->BindAxis("MoveForward", this, &ARobson::MoveForward);
	InputComponent->BindAxis("MoveSides", this, &ARobson::MoveSides);
	InputComponent->BindAxis("Turn", this, &ARobson::Turn);


	//mapeamento de entrada criado no editor, estado da tecla(pressionada), qual elemento que ele vai movimentar, qual método será utilizado quando chamar isso(endereço de memória onde foi armazenado)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//quando solta a tecla
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Run", IE_Pressed, this, &ARobson::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &ARobson::StopRun);

	//dropa esfera
	InputComponent->BindAction("Drop", IE_Pressed, this, &ARobson::DropSphere);




}

//Movimentação frente/trás
void ARobson::MoveForward(float Value) {
	//(x,y,z)
	FVector Forward(1, 0, 0);
	//forward, value do parametro
	AddMovementInput(Forward, Value);


}

//Movimentação lados
void ARobson::MoveSides(float Value) {
	//(x,y,z)
	FVector Forward(0, 1, 0);
	//forward, value do parametro
	AddMovementInput(Forward, Value);

}

void ARobson::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800;

}
void ARobson::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 400;

}

//Encapsulamento da variável Life
void ARobson::SetLife(int NewLife) {
	Life = NewLife;
}

int ARobson::GetLife() {
	return Life;

}

void ARobson::SetCont(int NewCont) {
	Cont = NewCont;
}

int ARobson::GetCont() {
	return Cont;

}

void ARobson::GameOver() {

	if (Life <= 0) {
		//Pega a posição inicial
		FVector InitialLocation(-660.0f, 320.0f, 2320.0f);
		//Seta a vida de volta a 100 pra não morrer infinitamente
		Life = 100;
		//Seta a posição do ator para a inicial
		SetActorLocation(InitialLocation);
	}

}

void ARobson::DropSphere() {

	//para fazer o spawn do objeto. manda parametros específicos de colisão, movimentação, etc
	FActorSpawnParameters SpawnParameters;

	//para saber em que level vai adicionar o objeto
	UWorld* World = GetWorld();

	if (World != nullptr) {

		//pega a rotação do mesh pra dropar o projétil virado pro lado da seta
		FRotator Rotation = MeshComp->GetComponentRotation();

		//parametros: localização do spawn, rotação do objeto, spawn parameters
		ASpawn* Proj = World->SpawnActor<ASpawn>(GetActorLocation(), Rotation, SpawnParameters);

		if (Proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("SPAUNO KRAI"));
		}

	}


}

void ARobson:: Turn(float Value) {

	//girar sobre o eixo z
	//AddControllerYawInput(Value);

	FRotator NewRotation = MeshComp->GetComponentRotation();
	NewRotation.Yaw += Value;
	MeshComp->SetWorldRotation(NewRotation);
}




