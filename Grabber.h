// Copyright Bidilă Timotei 2017.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_BUILDING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Distance reached in front of the player
	float Reach = 100.f;
		
	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UInputComponent *InputComponent = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();

	//Release what's been grabbed
	void Release();

	//Find attached Physics Handle
	void FindPhysicsHandleComponent();

	//Setup (assumed)attached Input Controller
	void SetupInputController();

	//Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Returns current start of reach line
	FVector GetReachLineStart() const;

	//Returns current end of reach line
	FVector GetReachLineEnd() const;
};
