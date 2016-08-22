// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Robson.generated.h"

UCLASS()
class ROCAMBOLE_API ARobson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobson();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//get e set do Life
	void SetLife(int NewLife);
	int GetLife();

	//get e set do contador
	void SetCont(int NewCont);
	int GetCont();

	//Voltar pro início
	void GameOver();


private:

	int cont = 0;

	//Forma do personagem
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
		//movimentação / angulo da câmera
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		//setinha
		UArrowComponent* ArrowComp;

	//movimentação com WASD
	void MoveForward(float Value);
	void MoveSides(float Value);
	//Correr
	void StartRun();
	void StopRun();

	//Vida
	UPROPERTY(EditAnywhere)
	int Life = 100;

	UPROPERTY(EditAnywhere)
	int Cont = 0;

	void DropSphere();

	void Turn(float Value);
	

	
};
