// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorControlActor.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "ECSPBlueprintFunctionLibrary.h"
#include "SmoothlyMovetoCom.h"
#include "KeyMap.h"
#include "MessageManager.h"
#include "MessageMiddlewareLibrary.h"

// Sets default values
ARotatorControlActor::ARotatorControlActor()//(EAttachmentRule::KeepRelative, false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootcom = CreateDefaultSubobject<USceneComponent>(TEXT("rootcom"));
	rootcom->SetupAttachment(GetRootComponent());
	rootcom->SetRelativeLocation(FVector(0));
	rootcom->SetRelativeRotation(FRotator(0));

	temptarget = CreateDefaultSubobject<USceneComponent>(TEXT("temptarget"));
	temptarget->SetupAttachment(rootcom);
	temptarget->SetRelativeLocation(FVector(0));
	temptarget->SetRelativeRotation(FRotator(0));
}

// Called when the game starts or when spawned
void ARotatorControlActor::BeginPlay()
{
	Super::BeginPlay();
	atf = new FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ADDMESSAGELISTEN(this, key_onaddrotatorleaf+mnumber, [=](const void* const p) {
		//float addr;
		//UMessageMiddlewareLibrary::getfloatfromjsonstring(*(FString*)p,"", addr);
		int64 i = (int64)p;
		int32 ih = i;
		int32 il = i<<8;
		//FPlatformMisc::LowLevelOutputDebugStringf(*FString("addactor: ").Append(FString::FromInt(ih)).Append(FString::FromInt(il)));

		addactor((AActor*)p);
	})
}
void ARotatorControlActor::setradius(int radius)
{
	mradius = radius;
}
void ARotatorControlActor::addactor(AActor* ap, FVector axis)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString("add sth"));
	maxis = axis;
	GetAttachedActors(actors);
	int currentnumber = actors.Num();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(currentnumber));
	int totalnumber = currentnumber + 1;
	float angle = (float)360 / totalnumber;
	FVector v1 = GetActorForwardVector();
	int i = 0;
	for (; i < currentnumber; i++)
	{
		FVector temv = UKismetMathLibrary::RotateAngleAxis(v1, angle * i, axis);
		temv *= mradius;
		actors[i]->SetActorRelativeLocation(temv);
		FVector tv = actors[i]->GetActorLocation() - GetActorLocation();
		FVector tv1 = UKismetMathLibrary::RotateAngleAxis(tv, mangle, axis);
		actors[i]->SetActorRotation(tv1.Rotation());
	}
	//ap->AttachToActor(this, *atf);
	FVector temv = UKismetMathLibrary::RotateAngleAxis(v1, angle * i, axis);
	temv *= mradius;
	temptarget->SetRelativeLocation(temv);
	FVector tv = temptarget->GetComponentLocation() - GetActorLocation();
	FVector tv1 = UKismetMathLibrary::RotateAngleAxis(tv, mangle, axis);
	temptarget->SetWorldRotation(tv1.Rotation());
	UECSPBlueprintFunctionLibrary::AddComponent <USmoothlyMovetoCom>(ap)->settargetcom(temptarget);
}

// Called every frame
void ARotatorControlActor::setangle(int anglep)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString("setangle"));
	mangle = anglep;
	GetAttachedActors(actors);
	int currentnumber = actors.Num();
	int totalnumber = currentnumber ;
	int i = 0;
	for (; i < currentnumber; i++)
	{
		FVector tv = actors[i]->GetActorLocation() - GetActorLocation();
		FVector tv1 = UKismetMathLibrary::RotateAngleAxis(tv, mangle, maxis);
		actors[i]->SetActorRotation(tv1.Rotation());
	}
	FVector tv = temptarget->GetComponentLocation() - GetActorLocation();
	FVector tv1 = UKismetMathLibrary::RotateAngleAxis(tv, mangle, maxis);
	temptarget->SetWorldRotation(tv1.Rotation());


	//float angle = (float)360 / totalnumber;
	//FVector v1 = GetActorForwardVector();
	//for (; i < currentnumber; i++)
	//{
	//	FVector temv = UKismetMathLibrary::RotateAngleAxis(v1, angle * i, maxis);
	//	temv *= mradius;
	//	actors[i]->SetActorRelativeLocation(temv);
	//	FVector tv = actors[i]->GetActorLocation() - GetActorLocation();
	//	FVector tv1 = UKismetMathLibrary::RotateAngleAxis(tv, mangle, maxis);
	//	actors[i]->SetActorRotation(tv1.Rotation());
	//}
}
void ARotatorControlActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0,1,0));

}

