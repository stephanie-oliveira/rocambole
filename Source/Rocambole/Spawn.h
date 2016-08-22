// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawn.generated.h"

UCLASS()
class ROCAMBOLE_API ASpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	//cria como esfera
	UBoxComponent* Root;
	UStaticMeshComponent * MeshComp;

	//movimenta��o do proj�til
	UProjectileMovementComponent* ProjectileMovement;

	float DefaultZ;

	
	
};
