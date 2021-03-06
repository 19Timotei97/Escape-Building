// Copyright Bidilă Timotei 2017.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "Open_Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_BUILDING_API UOpen_Door : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpen_Door();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	UPROPERTY(EditAnywhere) /// OpenAngle is editable anywhere
	ATriggerVolume *PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float MinMassToOpen = 30.f;

	///The owning door
	AActor *Owner = nullptr; 
	
   /// In kg
	float GetTotalMassOfActorsOnPlate();
	
};
