// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_TPS_HUD.h"
#include "Engine/Canvas.h"
#include "SU_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASU_TPS_HUD::DrawHUD()
{
	Super::DrawHUD();

	ASU_Player* Player = Cast<ASU_Player>(GetOwningPawn());

	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;

	int32 UniX = Canvas->SizeX / 100;
	int32 DrawSize = UniX * 2;
	float GrabRatio = 0.f;
	int Gap = UniX * 2;
	if (Player)
	{
		int32 MaxSpeed = Player->GetCharacterMovement()->GetMaxSpeed();
		int32 Speed = Player->GetCharacterMovement()->Velocity.Size2D();
		GrabRatio = (float)Speed / (float)MaxSpeed;
	}

	Gap *= GrabRatio;

	int32 DrawSizeWithGap = DrawSize + Gap;
	//int32 DrawSizeWithoutGap = DrawSize - Gap;

	//Draw2DLine(CenterX - DrawSizeWithGap, CenterY, CenterX + DrawSizeWithGap, CenterY, FColor::Green);
	//Draw2DLine(CenterX, CenterY - DrawSizeWithGap, CenterX, CenterY + DrawSizeWithGap, FColor::Green);

	//X�� 2�� 
	Draw2DLine(CenterX - DrawSizeWithGap, CenterY, CenterX - Gap, CenterY, FColor::Green);
	Draw2DLine(CenterX + DrawSizeWithGap, CenterY, CenterX + Gap, CenterY, FColor::Green);

	//y�� 2��
	Draw2DLine(CenterX, CenterY - DrawSizeWithGap, CenterX, CenterY - Gap, FColor::Green);
	Draw2DLine(CenterX, CenterY + DrawSizeWithGap, CenterX, CenterY + Gap, FColor::Green);
}
