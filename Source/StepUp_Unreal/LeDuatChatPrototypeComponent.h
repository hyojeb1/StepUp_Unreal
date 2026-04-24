#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "TRB_ChatTrigger.h"
#include "TRB_ChatLine.h"
#include "LeDuatChatPrototypeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STEPUP_UNREAL_API ULeDuatChatPrototypeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULeDuatChatPrototypeComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LeDuat Chat")
    UDataTable* ChatTriggerTable = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LeDuat Chat")
    UDataTable* ChatLineTable = nullptr;

    UFUNCTION(BlueprintCallable, Category = "LeDuat Chat")
    void TestDamageTakenLowHP();

    UFUNCTION(BlueprintCallable, Category = "LeDuat Chat")
    bool TryPlayChatByTags(
        const FGameplayTagContainer& CurrentTags,
        float CurrentMainValue,
        float CurrentSubValue
    );

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

private:
    bool DoesTriggerMatch(
        const FTRB_ChatTrigger& Trigger,
        const FGameplayTagContainer& CurrentTags,
        float CurrentMainValue,
        float CurrentSubValue
    ) const;

    void DisplayChatLine(
        const FName& TriggerRowName,
        const FTRB_ChatTrigger& Trigger
    );
};