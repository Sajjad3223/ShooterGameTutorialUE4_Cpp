// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/Tasks/BTTask_Shoot.h"

#include "AIController.h"
#include "Characters/SajjadComando.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get AI Controller
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller == nullptr) return EBTNodeResult::Failed;

	// Get Controlled Pawn
	APawn* ControlledPawn = Controller->GetPawn();
	if (ControlledPawn == nullptr) return EBTNodeResult::Failed;

	// Cast to SajjadComando
	ASajjadComando* Character = Cast<ASajjadComando>(ControlledPawn);
	if (Character == nullptr) return EBTNodeResult::Failed;

	//Call Shoot Function
	Character->Shoot();

	return EBTNodeResult::Succeeded;
}