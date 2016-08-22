// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Cogumelo.generated.h"

UCLASS()
class ROCAMBOLE_API ACogumelo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACogumelo();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	//Para criar um m�todo que possa ser editado em BP / m�todo que ser� chamado dinamicamente
	UFUNCTION()
	//Colis�o sobreposta
	//Par�metros: outro ator que ser� sobreposto, outro componente que ser� sobreposto	
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Permite que a vari�vel que acrescenta na vida seja edit�vel 
	UPROPERTY(EditAnywhere)
		int LifeAmount = 10;
	
};
