// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorControlActor.generated.h"

UCLASS()
class ROTATORCONTROLER_API ARotatorControlActor : public AActor
{
	GENERATED_BODY()
	TArray<AActor*>actors;
	AActor* currentaddactor;
	bool blerp=false;
	FAttachmentTransformRules* atf;
	int mangle = 0;
	FVector maxis;
	int mradius;

public:
	// Sets default values for this actor's properties
	ARotatorControlActor();
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class USceneComponent* rootcom;
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
	class USceneComponent* temptarget;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "UHInsmeshcom")
	void addactor(AActor* ap, int radius, FVector axis = FVector(0, 0, 1));
	UFUNCTION(BlueprintCallable, Category = "UHInsmeshcom")
	void setangle(int anglep);
};
