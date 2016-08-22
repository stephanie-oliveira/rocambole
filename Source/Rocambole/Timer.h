// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Timer.generated.h"

UCLASS()
class ROCAMBOLE_API ATimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UBoxComponent* Root;
	UStaticMeshComponent * MeshComp;

	FTimerHandle CountdownTimerHandle;

	//de quanto em quanto vai descontar
	float TheFinalCountdown;
	//o método que vai ser chamado a cada tanto tempo
	void TimerManager();

	
	
};
