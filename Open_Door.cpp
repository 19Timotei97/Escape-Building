// Copyright Bidilă Timotei 2017.

#include "Open_Door.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#define OUT

// Sets default values for this component's properties
UOpen_Door::UOpen_Door()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpen_Door::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PressurePlate"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpen_Door::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the TriggerVolume
	//If ATO is in the volume
	if (GetTotalMassOfActorsOnPlate() > MinMassToOpen)//if the player is standing on the trigger volume
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpen_Door::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	///Find the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	///Iterate and add their masses
	for (const auto *Actors : OverlappingActors)
	{
		TotalMass += Actors->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("The actor on the pressure plate is %s"), *Actors->GetName())
	}
	return TotalMass;
}
