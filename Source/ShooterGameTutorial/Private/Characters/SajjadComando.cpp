// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SajjadComando.h"

#include "Actors/Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Public/ShooterGameMode.h"

// Sets default values
ASajjadComando::ASajjadComando()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Set Team Id
	TeamId = FGenericTeamId(2);
}

// Called when the game starts or when spawned
void ASajjadComando::BeginPlay()
{
	Super::BeginPlay();

	// Hide the bone which has a gun
	GetMesh()->HideBoneByName(FName("gun"),EPhysBodyOp::PBO_None);

	//  spawn a gun and attach it to character
	Guns.SetNum(GunClasses.Num());
	for (int i = 0; i < GunClasses.Num();i++) {
		auto GunClass = GunClasses[i];
		if (GunClass)
		{
			Guns[i] = GetWorld()->SpawnActor<AGun>(GunClass);
			Guns[i]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));
			Guns[i]->SetOwner(this);
		}
	}
	ManageGuns();

	Health = MaxHealth;
}

void ASajjadComando::ManageGuns() {
	for (int i = 0; i < Guns.Num(); i++) {
		if (i == ActiveGunIndex)
		{
			Guns[i]->SetActorHiddenInGame(false);
		}
		else {
			Guns[i]->SetActorHiddenInGame(true);
		}
	}
}

// Called to bind functionality to input
void ASajjadComando::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASajjadComando::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASajjadComando::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&ASajjadComando::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnUp",this,&ASajjadComando::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate",this,&ASajjadComando::Turn);
	PlayerInputComponent->BindAxis("TurnUpRate",this,&ASajjadComando::TurnUp);
	PlayerInputComponent->BindAxis("ChangeWeapon", this, &ASajjadComando::ChangeWeapon);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASajjadComando::Jump);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ASajjadComando::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&ASajjadComando::StopFire);
	
}

float ASajjadComando::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	Health -= FMath::Min(Health,Damage);; // Health = Health - FMath::Min(Health,Damage)
	if(IsDead())
	{
		//Get Game Mode
		AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
		if (GameMode) {
			//Call Handle Kills
			GameMode->HandleKills(this);

			HandleDeath();
		}
	}
	
	return Damage;
}

void ASajjadComando::HandleDeath() {
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ASajjadComando::DestroyCharacter, DestroyDelay, false);
}

FGenericTeamId ASajjadComando::GetGenericTeamId() const
{
	return TeamId;
}

void ASajjadComando::Shoot()
{
	Guns[ActiveGunIndex]->Fire();
}

float ASajjadComando::GetHealth()
{
	// Return Health Normalized
	return Health / MaxHealth;
}

void ASajjadComando::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASajjadComando::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASajjadComando::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotateSensitivity * GetWorld()->GetDeltaSeconds());
}

void ASajjadComando::TurnUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotateSensitivity * GetWorld()->GetDeltaSeconds());
}

void ASajjadComando::StartFire()
{
	Guns[ActiveGunIndex]->StartShoot();
}

void ASajjadComando::StopFire()
{
	Guns[ActiveGunIndex]->EndShoot();
}

bool ASajjadComando::IsDead()
{
	return Health <= 0;
}

void ASajjadComando::DestroyCharacter()
{
	Guns[ActiveGunIndex]->Destroy();
	Destroy();
}

void ASajjadComando::ChangeWeapon(float AxisValue) {
	ActiveGunIndex += AxisValue;

	if (ActiveGunIndex < 0)
		ActiveGunIndex = Guns.Num() - 1;
	if (ActiveGunIndex >= Guns.Num())
		ActiveGunIndex = 0;

	ManageGuns();
}