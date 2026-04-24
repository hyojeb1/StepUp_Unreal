// Fill out your copyright notice in the Description page of Project Settings.


#include "LeDuatChatPrototypeComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
ULeDuatChatPrototypeComponent::ULeDuatChatPrototypeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULeDuatChatPrototypeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULeDuatChatPrototypeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULeDuatChatPrototypeComponent::TestDamageTakenLowHP()
{
    FGameplayTagContainer Tags;

    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Chat.Event.DamageTaken")));

    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Actor.Type.Player")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Actor.Heru")));

    // TargetType / TargetID 조건도 T10001에 들어 있으므로 추가
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Actor.Type.Player")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Actor.Heru")));

    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Chat.Action.EnemyAttack")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Chat.Attack.Melee")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Map.Group.Surface")));

    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Combat.Normal")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Party.AllAlive")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Character.LowHP")));

    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Value.Main.Damage")));
    Tags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Value.Sub.HPPercent")));

    TryPlayChatByTags(Tags, 30.f, 25.f);
}

bool ULeDuatChatPrototypeComponent::TryPlayChatByTags(
    const FGameplayTagContainer& CurrentTags,
    float CurrentMainValue,
    float CurrentSubValue
)
{
    if (!ChatTriggerTable || !ChatLineTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("ChatTriggerTable or ChatLineTable is missing."));
        return false;
    }

    TArray<FName> RowNames = ChatTriggerTable->GetRowNames();

    for (const FName& RowName : RowNames)
    {
        const FTRB_ChatTrigger* Trigger =
            ChatTriggerTable->FindRow<FTRB_ChatTrigger>(
                RowName,
                TEXT("LeDuatChatTrigger")
            );

        if (!Trigger)
        {
            continue;
        }

        if (DoesTriggerMatch(*Trigger, CurrentTags, CurrentMainValue, CurrentSubValue))
        {
            DisplayChatLine(RowName, *Trigger);
            return true;
        }
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            3.f,
            FColor::Red,
            TEXT("[LeDuatChat] No matching trigger.")
        );
    }

    return false;
}

bool ULeDuatChatPrototypeComponent::DoesTriggerMatch(
    const FTRB_ChatTrigger& Trigger,
    const FGameplayTagContainer& CurrentTags,
    float CurrentMainValue,
    float CurrentSubValue
) const
{
    auto HasTagOrEmpty = [&CurrentTags](const TCHAR* FieldName, const FGameplayTag& Tag)
        {
            if (!Tag.IsValid())
            {
                return true;
            }

            const bool bHasTag = CurrentTags.HasTagExact(Tag);

            if (!bHasTag)
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("[LeDuatChat] Missing tag. Field=%s Tag=%s"),
                    FieldName,
                    *Tag.ToString()
                );
            }
            else 
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("[LeDuatChat] Finding tag. Field=%s Tag=%s"),
                    FieldName,
                    *Tag.ToString()
                );
            }

            return bHasTag;
        };

    if (!HasTagOrEmpty(TEXT("EventType"), Trigger.EventType)) return false;
    if (!HasTagOrEmpty(TEXT("SubjectType"), Trigger.SubjectType)) return false;
    if (!HasTagOrEmpty(TEXT("SubjectID"), Trigger.SubjectID)) return false;
    if (!HasTagOrEmpty(TEXT("TargetType"), Trigger.TargetType)) return false;
    if (!HasTagOrEmpty(TEXT("TargetID"), Trigger.TargetID)) return false;
    if (!HasTagOrEmpty(TEXT("ActionType"), Trigger.ActionType)) return false;
    if (!HasTagOrEmpty(TEXT("AttackType"), Trigger.AttackType)) return false;
    if (!HasTagOrEmpty(TEXT("MapGroup"), Trigger.MapGroup)) return false;
    if (!HasTagOrEmpty(TEXT("CombatState"), Trigger.CombatState)) return false;
    if (!HasTagOrEmpty(TEXT("PartyState"), Trigger.PartyState)) return false;
    if (!HasTagOrEmpty(TEXT("CharacterState"), Trigger.CharacterState)) return false;
    if (!HasTagOrEmpty(TEXT("ValueMainType"), Trigger.ValueMainType)) return false;
    if (!HasTagOrEmpty(TEXT("ValueSubType"), Trigger.ValueSubType)) return false;

    // 오늘 프로토타입용 임시 규칙:
    // ValueMain > 0이면 CurrentMainValue가 그 이상이어야 함.
    if (Trigger.ValueMain > 0.f && CurrentMainValue < Trigger.ValueMain)
    {
        return false;
    }

    // ValueSub > 0이면 CurrentSubValue가 그 이하이어야 함.
    // HPPercent 30 이하 같은 조건을 빠르게 검증하기 위한 임시 규칙.
    if (Trigger.ValueSub > 0.f && CurrentSubValue > Trigger.ValueSub)
    {
        return false;
    }

    return true;
}

void ULeDuatChatPrototypeComponent::DisplayChatLine(
    const FName& TriggerRowName,
    const FTRB_ChatTrigger& Trigger
)
{
    const FTRB_ChatLine* Line =
        ChatLineTable->FindRow<FTRB_ChatLine>(
            TriggerRowName,
            TEXT("LeDuatChatLine")
        );

    if (!Line)
    {
        UE_LOG(LogTemp, Warning, TEXT("No chat line for TriggerID: %s"), *TriggerRowName.ToString());

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                3.f,
                FColor::Red,
                FString::Printf(TEXT("[LeDuatChat] Missing line: %s"), *TriggerRowName.ToString())
            );
        }

        return;
    }

    const FGameplayTag SpeakerTag = Line->Speaker.IsValid()
        ? Line->Speaker
        : Trigger.Speaker;

    const FString SpeakerName = SpeakerTag.IsValid()
        ? SpeakerTag.GetTagName().ToString()
        : TEXT("Unknown");

    const FString Message = FString::Printf(
        TEXT("[%s] %s"),
        *SpeakerName,
        *Line->LineText.ToString()
    );

    UE_LOG(LogTemp, Log, TEXT("%s"), *Message);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Yellow,
            Message
        );
    }
}