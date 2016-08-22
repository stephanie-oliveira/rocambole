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

	//Para criar um método que possa ser editado em BP / método que será chamado dinamicamente
	UFUNCTION()
	//Colisão sobreposta
	//Parâmetros: outro ator que será sobreposto, outro componente que será sobreposto	
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Permite que a variável que acrescenta na vida seja editável 
	UPROPERTY(EditAnywhere)
		int LifeAmount = 10;
	
};
