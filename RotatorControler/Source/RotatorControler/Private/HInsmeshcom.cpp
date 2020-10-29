// Fill out your copyright notice in the Description page of Project Settings.


#include "HInsmeshcom.h"
#include "Kismet/KismetMathLibrary.h"
UHInsmeshcom::UHInsmeshcom()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHInsmeshcom::BeginPlay()
{

}

void UHInsmeshcom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	AddLocalRotation(FRotator(0,1,0));
}

void UHInsmeshcom::addcircleinstances(int number, int radius, FVector axis)
{
	FVector v1 = GetForwardVector();
	float angle = (float)360 / number;
	int currentnumber = GetInstanceCount();
	if (number > currentnumber)
	{
		for (int i = 0; i < number - currentnumber; i++)
		{
			FTransform trs;
			trs.SetLocation(FVector(0XFFFFFF));
			AddInstance(trs);
		}
	}
	for (int i = 0; i < number; i++)
	{
		FVector temv = UKismetMathLibrary::RotateAngleAxis(v1, angle*i,axis);
		temv *= radius;
		FTransform trs;
		trs.SetLocation(temv); 
		UpdateInstanceTransform(i, trs,false);
	}
}
