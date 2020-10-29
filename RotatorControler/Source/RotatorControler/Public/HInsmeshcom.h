// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "HInsmeshcom.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent))
class ROTATORCONTROLER_API UHInsmeshcom : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	UHInsmeshcom();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "UHInsmeshcom")
	void addcircleinstances(int number,int radius,FVector axis=FVector(0,0,1));
};
