// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Walker.generated.h"

UCLASS()
class ROCAMBOLE_API AWalker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	int Cont = 0;
	bool Right = true;
	bool Down = false;
	bool Left = false;
	bool Up = false;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnyWhere, Category = Tick)
		float RunningTime;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponen, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit);

	
	
};
