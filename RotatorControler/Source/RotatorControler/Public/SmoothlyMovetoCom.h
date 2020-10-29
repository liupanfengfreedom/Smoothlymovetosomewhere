// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ECSPBlueprintFunctionLibrary.h"
#include "SmoothlyMovetoCom.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROTATORCONTROLER_API USmoothlyMovetoCom : public UActorComponent, public ECSinterface
{
	GENERATED_BODY()
	USceneComponent* targetcom;
	AActor* owner;
	FAttachmentTransformRules* atf;
public:
	// Sets default values for this component's properties
	USmoothlyMovetoCom();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void ECSBeginplay() override;
	virtual void ECSEndplay()  override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void settargetcom(USceneComponent* tg) { targetcom = tg;}
		
};
