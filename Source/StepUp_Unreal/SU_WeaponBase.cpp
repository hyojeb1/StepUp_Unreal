// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_WeaponBase.h"

ASU_WeaponBase::ASU_WeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}
