// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


UCLASS()
class ROCAMBOLE_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private: 

	UPROPERTY(EditAnywhere)
		int LifeAmount = 10;

	UPROPERTY(EditAnywhere)
	UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnyWhere, Category = Tick)
	float RunningTime;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponen, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	
	
};
