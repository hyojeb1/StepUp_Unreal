// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "SU_Player.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "SU_BulletDamageType.h"


ASU_WeaponBase::ASU_WeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void ASU_WeaponBase::Fire()
{
	
	ASU_Player* Player = Cast<ASU_Player>(GetOwner());

	if (!Player)
	{
		return;
	}

	FVector StartTrace = Player->FollowCam->GetComponentLocation();
	FVector EndTrace;

	APlayerController* PC = Cast<APlayerController>(Player->GetController());
	if (PC) {
		int32 ScreenSizeX = 0;
		int32 ScreenSizeY = 0;
		FVector WorldLocation;
		FVector WorldDirection;

		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
		PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2, ScreenSizeY / 2, WorldLocation, WorldDirection);

		EndTrace = StartTrace + (WorldDirection * 100000.f);

		TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);

		FHitResult OutHit;

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			StartTrace,
			EndTrace,
			Objects,
			true,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			OutHit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			5.0f);
		if (Result) {
			UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
				DecalTemplate,
				FVector(5.f, 5.f, 5.f),
				OutHit.ImpactPoint,
				OutHit.ImpactNormal.Rotation(),
				5.f);

			if (Decal) {
				Decal->SetFadeScreenSize(0.005f);
			}

			UGameplayStatics::ApplyDamage(
				OutHit.GetActor(),
				10.0f,
				Player->GetController(),
				this,
				USU_BulletDamageType::StaticClass()
			);
		}

		//Muzzle Flash
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MuzzleFlashEffect,
			Mesh->GetSocketLocation(TEXT("Muzzle")),
			Mesh->GetSocketRotation(TEXT("Muzzle"))
		);

		//Hit Effect
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitEffect,
			OutHit.ImpactPoint,
			OutHit.ImpactNormal.Rotation()
		);

		//UGameplayStatics::SpawnSoundAtLocation(
		//	GetWorld(),
		//	FireSound,
		//	Weapon->GetSocketLocation(TEXT("Muzzle")),
		//	Weapon->GetSocketRotation(TEXT("Muzzle"))
		//);
		 
	}
	

	
}


