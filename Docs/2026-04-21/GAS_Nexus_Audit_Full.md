# 1. 프로젝트 내 GAS 구조 요약

이 문서는 C++ 소스, 설정 파일, 에셋 이름, 블루프린트/위젯/맵의 문자열 참조를 기준으로 정리했습니다. 에디터에서 노드 배선을 직접 본 것은 아니므로, 노드 분기까지는 `[추정]`으로 표시합니다.

`[확인됨]` GAS 시작점은 [NexusCharacterBase.h](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.h:21>), [NexusCharacterBase.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.cpp:35>)입니다. 여기서 캐릭터가 `UAbilitySystemComponent`와 `UBasicAttributeSet`를 직접 소유하고, `PossessedBy`/`OnRep_PlayerState`에서 `InitAbilityActorInfo(this, this)`를 호출합니다. 즉 이 프로젝트는 `PlayerState`가 아니라 `Character` 축에 ASC가 붙어 있습니다.

`[확인됨]` Attribute는 [BasicAttributeSet.h](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.h:21>), [BasicAttributeSet.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.cpp:14>)에 `Health`, `MaxHealth`, `Stamina`, `MaxStamina`만 있습니다. 현재 Nexus/GAS 파트는 아주 얇은 기본 스탯 구조입니다.

`[확인됨]` 프로젝트 기본 맵은 [DefaultEngine.ini](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Config/DefaultEngine.ini:1>) 기준 `Lvl_GAS_0402`입니다. 이 맵에는 `BP_Nexus_Enemy`, `BP_EffectArea_Base`, `BP_EffectArea_Base_Heal`, `PlayerStart`가 배치되어 있습니다. 그래서 이 맵은 “플레이어 스킬 + 적 피격 + 지속 데미지/지속 힐 + HUD”를 한 번에 검증하는 실습장으로 보입니다.

`[확인됨]` 게임 시작 흐름은 `Lvl_GAS_0402` → [BP_Nexus_GameMode](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_GameMode.uasset>) → [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>) + [BP_Nexus_PlayerController](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_PlayerController.uasset>)입니다. `BP_Nexus_PlayerController`는 `BeginPlay`에서 `IMC_Default`, `IMC_MouseLook`를 추가하고 `W_PlayerHUD`를 생성합니다.

`[확인됨]` 플레이어 입력은 혼합형입니다. 이동/시점/점프는 `IA_Move`, `IA_Look`, `IA_MouseLook`, `IA_Jump` 기반 Enhanced Input이고, GAS 스킬은 `LeftShift`, `Q`, `E` 키 이벤트가 [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>) 안에서 태그 기반 활성화로 연결되어 있습니다. 태그는 [DefaultGameplayTags.ini](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Config/DefaultGameplayTags.ini:13>)에 `GameplayAbility.Movement.Dash`, `GameplayAbility.Skill.Q`, `GameplayAbility.Skill.E`로 선언돼 있습니다.

`[확인됨]` [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>)는 `BeginPlay`에서 `GA_Dash`, `GA_Attack_Q`, `GA_Heal_E`를 `K2_GiveAbility`로 부여하고, `GE_Status_StaminaRegen`을 자신에게 적용하며, `WaitForAttributeChanged`로 `Stamina` 변화를 감시합니다. 즉 “어빌리티 부여”와 “스태미나 재생 상태 관리”가 현재는 플레이어 블루프린트에 들어 있습니다.

`[확인됨]` Dash는 [GA_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Dash.uasset>)가 [GE_Dash_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cost.uasset>)와 [GE_Dash_Cooldown](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cooldown.uasset>)를 참조하고, `ApplyRootMotionConstantForce`, `GetLastMovementInputVector`, `K2_AddGameplayCue`를 사용합니다. 큐 태그는 `GameplayCue.Dash.Active`, 실제 큐는 [GC_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Cues/GC_Dash.uasset>)입니다.

`[확인됨]` AttackQ는 [GA_Attack_Q](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Attack_Q.uasset>)가 [GE_AttackQ_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Cost.uasset>), [GE_AttackQ_Cooldown](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Cooldown.uasset>), [GE_AttackQ_Damage](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Damage.uasset>)를 분리 참조합니다. 실행 중 `SphereTraceSingle` 후 `BP_ApplyGameplayEffectToTarget`를 호출하고, `K2_ExecuteGameplayCueWithParams`로 `GameplayCue.AttackQ.Active`를 실행합니다.

`[확인됨]` HealE는 [GA_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Heal_E.uasset>)가 [GE_HealE_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_HealE_Cost.uasset>)와 [GE_HealE_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_HealE_Heal.uasset>)를 참조하고, AttackQ와 비슷하게 `SphereTraceSingle` + `BP_ApplyGameplayEffectToTarget` + `K2_ExecuteGameplayCueWithParams`를 씁니다. 현재 에셋 기준으로는 `GE_HealE_Cooldown`은 없습니다.

`[확인됨]` EffectActor 축은 [BP_EffectArea_Base](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base.uasset>)와 [BP_EffectArea_Base_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base_Heal.uasset>)입니다. 전자는 `GE_Damage_OverTime_Infinite` + `Data.Damage`, 후자는 `GE_Heal_OverTime_Infinite` + `Data.Heal`을 씁니다. 둘 다 오버랩 시작 시 적용, 끝날 때 제거하는 구조입니다.

`[확인됨]` Cue 연결 지점은 둘로 나뉩니다. 캐스팅/동작 큐는 GA에서 직접 붙습니다. `GA_Dash`는 `GameplayCue.Dash.Active`, `GA_Attack_Q`는 `GameplayCue.AttackQ.Active`, `GA_Heal_E`는 `GameplayCue.HealE.Active`를 씁니다. 피격/치유 버스트 큐는 GE에 붙습니다. `GE_Damage_OverTime_Infinite`는 `GameplayCue.Damage.Burst`, `GE_Heal_OverTime_Infinite`는 `GameplayCue.Heal.Burst`를 참조합니다.

`[확인됨]` UI는 [W_PlayerHUD](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerHUD.uasset>) 안에 [W_PlayerVitals](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerVitals.uasset>)와 [W_AbilitiesContainer](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_AbilitiesContainer.uasset>)가 들어가는 구조입니다. `W_PlayerVitals`는 ASC에서 `Health/MaxHealth/Stamina/MaxStamina`를 읽고 `WaitForAttributeChanged`를 사용합니다. `W_AbilitiesContainer`는 `Event.Abilities.Changed`를 기다렸다가 `GetAllAbilities`로 스펙 핸들을 가져와 [W_Ability](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_Ability.uasset>)를 생성합니다. `W_Ability`는 `GetCooldownTimeRemaining`과 `WaitGameplayTagCountChangedOnActor(Tag=Cooldown)`를 사용합니다.

`[추정]` 이 프로젝트는 강의 Part 1~4 중 “설정, 대시, 기본 속성/이펙트, Q/E 확장, 간단 HUD”까지만 현재 로컬 구조로 남아 있고, 강의 후반부의 `NexusGameplayAbility`, `NexusAbilitySystemComponent`, Talent Tree 류의 고급 공통화는 아직 프로젝트 본체에 들어오지 않았습니다.

# 2. 강의 순서 기준으로 재구성한 학습 지도

1. 1단계: Setup 이해. 먼저 볼 것: [NexusCharacterBase.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.cpp:35>), [BasicAttributeSet.h](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.h:21>), [BP_Nexus_GameMode](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_GameMode.uasset>), [BP_Nexus_PlayerController](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_PlayerController.uasset>). 왜 이 순서인가: ASC가 어디에 붙고, 맵 진입 시 어떤 Pawn/Controller가 뜨는지 먼저 고정해야 이후 설명이 안 꼬입니다. 핵심 개념: “ASC는 Character 소유”, “ActorInfo 초기화는 possession 시점”, “HUD는 Controller에서 생성”. 지금은 몰라도 되는 것: Cue 세부 VFX, DOT/HOT, 위젯 꾸밈. 체크리스트: `InitAbilityActorInfo(this, this)` 의미를 말할 수 있어야 합니다.

2. 2단계: Dash 이해. 먼저 볼 것: [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>), [GA_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Dash.uasset>), [GE_Dash_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cost.uasset>), [GE_Dash_Cooldown](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cooldown.uasset>), [GC_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Cues/GC_Dash.uasset>). 왜 이 순서인가: Dash가 가장 단순한 “입력 → Ability → Cost/Cooldown → Cue” 패턴입니다. 핵심 개념: 태그 활성화, Root Motion Force, 지속형 Active Cue. 지금은 몰라도 되는 것: 타겟 추적형 공격. 체크리스트: “Shift 입력이 어떤 태그를 타고 어떤 GE 2개를 커밋하는지”를 추적할 수 있어야 합니다.

3. 3단계: Attributes & Effects 이해. 먼저 볼 것: [BasicAttributeSet.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.cpp:14>), [GE_Status_StaminaRegen](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Status_StaminaRegen.uasset>), [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>), [BP_EffectArea_Base](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base.uasset>), [BP_EffectArea_Base_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base_Heal.uasset>). 왜 이 순서인가: 이 단계에서 “속성은 C++, 효과는 GE, 적용 타이밍은 BP/Ability”라는 경계가 보입니다. 핵심 개념: Clamp, SetByCaller용 `Data.Damage/Data.Heal`, 태그 기반 상태 유지. 지금은 몰라도 되는 것: 리팩터링용 글로벌 GE 템플릿. 체크리스트: Cost/Effect/Status용 GE가 서로 다른 책임이라는 걸 설명할 수 있어야 합니다.

4. 4단계: AttackQ / HealE 확장 패턴 이해. 먼저 볼 것: [GA_Attack_Q](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Attack_Q.uasset>), [GE_AttackQ_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Cost.uasset>), [GE_AttackQ_Cooldown](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Cooldown.uasset>), [GE_AttackQ_Damage](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Damage.uasset>), [GA_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Heal_E.uasset>), [GE_HealE_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_HealE_Cost.uasset>), [GE_HealE_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_HealE_Heal.uasset>). 왜 이 순서인가: Dash 뒤에 보면 “이동형 Ability”와 “타격/치유형 Ability”의 차이가 분명해집니다. 핵심 개념: `SphereTraceSingle` 후 `BP_ApplyGameplayEffectToTarget`, 공격/치유가 GE만 바꾸고 틀은 비슷하다는 점. 지금은 몰라도 되는 것: 고급 타겟 액터, 프로젝트ाइल화. 체크리스트: Q를 복제해서 새 스킬 1개를 추가할 때 건드릴 에셋 목록을 말할 수 있어야 합니다.

5. 5단계: UI 연동 이해. 먼저 볼 것: [BP_Nexus_PlayerController](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_PlayerController.uasset>), [W_PlayerHUD](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerHUD.uasset>), [W_PlayerVitals](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerVitals.uasset>), [W_AbilitiesContainer](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_AbilitiesContainer.uasset>), [W_Ability](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_Ability.uasset>). 왜 이 순서인가: 현재 UI는 ASC/Attribute를 직접 읽는 구조라 게임 확장 전 꼭 이해해야 합니다. 핵심 개념: HUD 생성 책임은 Controller, 스탯 갱신은 Attribute Wait, 스킬 바 갱신은 `Event.Abilities.Changed` + Ability Spec Handle. 지금은 몰라도 되는 것: 고급 아이콘 데이터 에셋. 체크리스트: “쿨다운 숫자가 어디서 계산되는지”를 추적할 수 있어야 합니다.

6. 6단계: 게임 완성용 확장 단계. 먼저 볼 것: [Lvl_GAS_0402](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Maps/Lvl_GAS_0402.umap>), [BP_Nexus_Enemy](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Enemy.uasset>), [GE_refactoring.txt](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_refactoring.txt>). 왜 이 순서인가: 지금 구조는 “학습용 단발 구현”과 “실제 게임용 반복 가능한 구조”가 아직 분리되지 않았기 때문입니다. 핵심 개념: 반복 패턴 추출, 입력 통합, Enemy 전투 루프, 사망/피격/레벨링. 지금은 몰라도 되는 것: Talent Tree 전체. 체크리스트: 새 Ability를 추가할 때 Player BP를 덜 건드리는 방향으로 설계를 바꿀 수 있어야 합니다.

# 3. 단계별로 먼저 읽을 파일/에셋

1. Setup: [NexusCharacterBase.h](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.h:21>) → [NexusCharacterBase.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.cpp:35>) → [BasicAttributeSet.h](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.h:21>) → [DefaultGameplayTags.ini](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Config/DefaultGameplayTags.ini:13>).

2. Dash: [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>) → [GA_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Dash.uasset>) → [GE_Dash_Cost](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cost.uasset>) → [GE_Dash_Cooldown](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Dash_Cooldown.uasset>) → [GC_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Cues/GC_Dash.uasset>).

3. Attributes / Effects: [BP_EffectArea_Base](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base.uasset>) → [BP_EffectArea_Base_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base_Heal.uasset>) → [GE_Damage_OverTime_Infinite](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Damage_OverTime_Infinite.uasset>) → [GE_Heal_OverTime_Infinite](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Heal_OverTime_Infinite.uasset>) → [GE_Status_StaminaRegen](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_Status_StaminaRegen.uasset>).

4. AttackQ / HealE: [GA_Attack_Q](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Attack_Q.uasset>) → [GE_AttackQ_Damage](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_AttackQ_Damage.uasset>) → [GC_Attack_Q](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Cues/GC_Attack_Q.uasset>) → [GA_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Heal_E.uasset>) → [GE_HealE_Heal](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Effects/GE_HealE_Heal.uasset>) → [GC_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Cues/GC_Heal_E.uasset>).

5. UI: [BP_Nexus_PlayerController](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_PlayerController.uasset>) → [W_PlayerHUD](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerHUD.uasset>) → [W_PlayerVitals](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_PlayerVitals.uasset>) → [W_AbilitiesContainer](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_AbilitiesContainer.uasset>) → [W_Ability](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Widget/W_Ability.uasset>).

6. 검증 맵: [Lvl_GAS_0402](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Maps/Lvl_GAS_0402.umap>) → [BP_Nexus_Enemy](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Enemy.uasset>) → 두 EffectArea 액터 배치 확인.

# 4. Ability/Effect/Cue/입력/UI 연결 규칙

- Ability 1개 추가 시 기본 목록은 `GA_새스킬`, `GE_새스킬_Cost`, `GE_새스킬_Cooldown(필요시)`, `GE_새스킬_ActualEffect`, `GC_새스킬_Active 또는 GC_새스킬_Burst`, Player 입력 연결, UI 노출 여부 확인입니다.
- Cost / Cooldown / 실제 효과는 반드시 분리하세요. 이 프로젝트도 Dash와 AttackQ는 그 규칙을 따릅니다. Cost는 Attribute 차감, Cooldown은 `Cooldown.*` 태그 부여, ActualEffect는 Health/Stamina 변경입니다.
- Cue 기준은 “동작 중 보여줄 것인가, 적용 순간 보여줄 것인가”입니다. Dash처럼 이동 지속형은 GA에서 Active Cue, Damage/Heal 틱처럼 적용 순간은 GE에서 Burst Cue가 맞습니다.
- Player 블루프린트 책임은 입력 수신, 초기 Ability 부여, 상태 이벤트 브리지입니다. Ability 에셋 책임은 실제 발동 절차, 트레이스, 커밋, 대상 GE 적용입니다.
- Enemy 상호작용 체크포인트는 `SphereTraceSingle` 적중 여부, 타겟이 ASC를 갖는지, `BP_ApplyGameplayEffectToTarget`가 맞는 GE를 쓰는지, 오버랩 종료 시 지속 GE 제거가 되는지입니다.
- 블루프린트로 끝내도 되는 부분은 몽타주/큐/이펙트 조합, 단순 트레이스 스킬, HUD 배치입니다. C++로 옮겨야 할 부분은 공통 Ability 베이스, 공통 타겟팅 함수, Ability 부여/제거, 복제 민감 Attribute 처리입니다.
- 중복 로직이 보이면 “같은 순서의 노드가 2번 이상 반복되는가”를 기준으로 뽑으세요. 지금은 `SphereTraceSingle → TargetData → ApplyGEToTarget → ExecuteCue`가 Q/E 둘 다 반복됩니다.

# 5. 지금 구조에서 리팩터링이 필요한 지점

- 가장 먼저 고칠 후보는 [BasicAttributeSet.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.cpp:22>)입니다. 현재 `GetLifetimeReplicatedProps`가 `Health`만 등록하고 `MaxHealth`, `Stamina`, `MaxStamina`는 복제 등록이 없습니다. 지금 UI가 Stamina를 적극적으로 보는데, 멀티플레이 기준으론 위험합니다.
- [NexusCharacterBase.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.cpp:41>)에서 `ASCReplicationMode`를 생성자 시점에 바로 `SetReplicationMode`에 넣습니다. 그런데 [BP_Nexus_Enemy](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Enemy.uasset>)는 `Minimal`을 들고 있어도, 이 값이 실제 컴포넌트에 재적용되는 코드가 보이지 않습니다. `[추정]` Enemy의 복제 정책 의도가 런타임에 안 먹을 가능성이 있습니다.
- 현재 프로젝트엔 `NexusGameplayAbility` / `NexusAbilitySystemComponent` 같은 공용 GAS 베이스가 없습니다. 강의 메모에는 후반부에 나오는 구조지만, 실제 프로젝트는 아직 `BP_Nexus_Player`와 위젯이 직접 GAS를 만집니다. 새 스킬이 늘수록 Player BP가 비대해질 가능성이 큽니다.
- 입력이 혼합형입니다. 이동은 Enhanced Input, 스킬은 raw key event라서 스케일링에 약합니다. 나중에 키 변경, 패드 입력, 스킬 슬롯 재바인딩을 하려면 Ability 입력도 Enhanced Input으로 통합하는 편이 낫습니다.
- [GA_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Heal_E.uasset>)는 현재 `GE_HealE_Cost`와 `GE_HealE_Heal`만 연결되어 있고 별도 cooldown asset이 보이지 않습니다. 의도라면 괜찮지만, 실전 게임 스킬이면 설계 결정을 명확히 해야 합니다.
- [BP_Nexus_Enemy](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Enemy.uasset>)는 현재 “맞아주는 표적”에 가깝습니다. 실제 게임 완성을 보려면 Enemy도 Ability, 피격, 사망, AI 의사결정 축으로 확장해야 합니다.

# 6. 게임 완성까지의 backlog

**이미 구현된 것**
- 캐릭터 기반 ASC/AttributeSet 연결.
- Dash / AttackQ / HealE 3개 Ability.
- Cost / Cooldown / Effect 분리 패턴.
- Damage/Heal EffectArea로 DOT/HOT 검증.
- Player HUD, 스탯 바, 스킬 바, 쿨다운 표시.

**학습용으로만 존재하는 것**
- Player BeginPlay에서 직접 `GiveAbility`.
- raw key 기반 Q/E/Shift 발동.
- 단일 Enemy 더미 1개 중심 검증.
- 맵 안 EffectArea로 수동 테스트하는 구조.

**실제 게임화하려면 더 필요한 것**
- Enemy AI 행동 루프, 피격/사망/리스폰.
- 스킬 대상 필터링과 팀 판정.
- Ability 공통 베이스와 데이터화.
- 레벨링/스케일링/밸런싱 구조.
- 저장, 라운드 규칙, 전투 상태 흐름.

**가장 먼저 해야 할 것**
- Attribute replication 문제 정리.
- Ability 입력/부여 공통화.
- Q/E 공통 타겟팅 로직 추출.
- Enemy 전투 루프 최소 1종 완성.
- HealE의 의도 정의: 자기치유, 대상치유, HoT, 비용, 쿨다운.

**나중에 polish 해도 되는 것**
- Cue 교체, Niagara/SFX 개선.
- 스킬 아이콘/툴팁 정교화.
- 카메라 흔들림, 히트플래시, 숫자 피드백.
- 다중 Enemy 배치와 더 예쁜 테스트 맵.

# 7. 내가 다음으로 바로 해야 할 일 5개

1. [NexusCharacterBase.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/NexusCharacterBase.cpp:35>)와 [BasicAttributeSet.cpp](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Source/StepUp_Unreal/BasicAttributeSet.cpp:22>)를 먼저 열고, “ASC는 Character 소유”, “ActorInfo는 possession 때 초기화”, “현재 복제되는 Attribute가 무엇인지”를 직접 체크하세요.

2. [BP_Nexus_Player](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Blueprints/BP_Nexus_Player.uasset>)를 열고 `BeginPlay` 노드부터 끝까지 따라가세요. `GA_Dash`, `GA_Attack_Q`, `GA_Heal_E`를 어디서 부여하는지, `GE_Status_StaminaRegen`을 언제 적용하는지, `Q/E/Shift`가 어떤 태그를 활성화하는지 노트로 적으세요.

3. [GA_Dash](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Dash.uasset>)를 기준 Ability로 삼아, `Cost GE`, `Cooldown GE`, `Cue`, `입력 태그`, `실행 노드`를 1페이지에 정리하세요. 그런 다음 `Lvl_GAS_0402`에서 “정지 상태 Dash”와 “이동 입력 중 Dash”를 각각 테스트해서 `GetLastMovementInputVector` 체감을 확인하세요.

4. [GA_Attack_Q](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Attack_Q.uasset>)와 [GA_Heal_E](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/GameAbilitySystem/Ability/GA_Heal_E.uasset>)를 나란히 열고, 공통 패턴인 `SphereTraceSingle → TargetData → ApplyGameplayEffectToTarget → ExecuteCue`를 표시해두세요. 다음 새 스킬은 Q를 복제해서 만들고, 바꾸는 것은 `태그`, `GE 3종`, `Cue`, `트레이스 반경/범위`만 바꾸는 식으로 시작하세요.

5. [Lvl_GAS_0402](</C:/Dev/30UrealSpecialClass/StepUp_Unreal/Content/Maps/Lvl_GAS_0402.umap>)에서 `BP_Nexus_Enemy`, `BP_EffectArea_Base`, `BP_EffectArea_Base_Heal` 위치를 확인한 뒤, 실제로 “Q로 적 타격”, “E로 치유”, “데미지 장판/힐 장판 진입”, “HUD 스태미나/체력/쿨다운 변화”를 한 번에 기록하세요. 가능하면 2인 PIE로도 돌려서 Stamina UI가 클라이언트에서 제대로 복제되는지 꼭 확인하세요.