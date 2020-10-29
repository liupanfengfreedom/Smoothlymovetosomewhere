// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothlyMovetoCom.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
USmoothlyMovetoCom::USmoothlyMovetoCom()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void USmoothlyMovetoCom::ECSBeginplay()
{
	owner = GetOwner();
	//SetComponentTickEnabled(true);
}
void USmoothlyMovetoCom::ECSEndplay()
{
	//SetComponentTickEnabled(false);
}

// Called when the game starts
void USmoothlyMovetoCom::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
	atf = new FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	// ...
	
}
#define keepdis 300
// Called every frame
void USmoothlyMovetoCom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
			FTransform tt = targetcom->GetComponentTransform();
			FTransform tc = owner->GetActorTransform();
			float dis = FVector::Dist(tt.GetLocation(), tc.GetLocation());
			float factor;// = UKismetMathLibrary::FClamp(1 / FMath::Square(dis - keepdis) + 0.5, 0.5, 50);
			if (dis > keepdis * 2)
			{
				factor = 20;
				owner->SetActorTransform(UKismetMathLibrary::TLerp(tc, tt, DeltaTime * factor));
			}
			else if (keepdis / 2 < dis && dis < keepdis * 2)
			{
				factor = 8;
				owner->SetActorTransform(UKismetMathLibrary::TLerp(tc, tt, DeltaTime * factor));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString("AttachToActor"));
				owner->AttachToActor(targetcom->GetOwner(), *atf);
				owner->SetActorTransform(tt);
				UECSPBlueprintFunctionLibrary::RemoveComponent<USmoothlyMovetoCom>(owner);
			}

	// ...
}

