# GAS Nexus QuickStart

이 문서는 `GAS_Nexus_Audit_Full.md`의 실전 압축본이다.
목표는 3가지다.

1. 지금 프로젝트의 GAS 시작점과 실행 흐름을 빠르게 다시 잡는다.
2. 새 Ability를 추가할 때 어디를 건드려야 하는지 즉시 판단한다.
3. 게임 완성용 확장 전에 반드시 이해해야 할 구조만 남긴다.

## 1. 먼저 머리에 넣을 한 줄 구조

이 프로젝트의 GAS는 `Character 기반 ASC` 구조다.

- ASC 시작점: `Source/StepUp_Unreal/NexusCharacterBase.*`
- Attribute 시작점: `Source/StepUp_Unreal/BasicAttributeSet.*`
- 플레이어 GAS 진입점: `Content/Blueprints/BP_Nexus_Player`
- 입력/HUD 진입점: `Content/Blueprints/BP_Nexus_PlayerController`
- 테스트 맵: `Content/Maps/Lvl_GAS_0402`

즉 지금은:

`BP_Nexus_Player 입력/초기화 -> GA_* 실행 -> GE_* 적용 -> GC_* 재생 -> HUD 갱신`

순서로 보면 된다.

## 2. 가장 먼저 확인할 핵심 파일

### Setup

- `Source/StepUp_Unreal/NexusCharacterBase.h`
- `Source/StepUp_Unreal/NexusCharacterBase.cpp`
- `Source/StepUp_Unreal/BasicAttributeSet.h`
- `Source/StepUp_Unreal/BasicAttributeSet.cpp`
- `Config/DefaultGameplayTags.ini`

여기서 확인할 것:

- ASC가 `Character`에 직접 붙어 있는가
- `InitAbilityActorInfo(this, this)`를 언제 하는가
- 현재 Attribute가 `Health`, `MaxHealth`, `Stamina`, `MaxStamina`만 있는가
- 어떤 Ability/Cooldown/Cue 태그가 실제로 선언되어 있는가

### Runtime Entry

- `Content/Blueprints/BP_Nexus_GameMode`
- `Content/Blueprints/BP_Nexus_Player`
- `Content/Blueprints/BP_Nexus_PlayerController`
- `Content/Maps/Lvl_GAS_0402`

여기서 확인할 것:

- 어떤 Pawn/Controller가 뜨는가
- BeginPlay에서 어떤 Ability를 부여하는가
- 입력은 어디서 받고 어디로 넘기는가
- HUD는 어디서 생성하는가

## 3. 강의 순서로 보는 현재 프로젝트

### 1단계: Setup 이해

핵심만 보면 된다.

- `ANexusCharacterBase`가 ASC와 `BasicAttributeSet`를 생성한다.
- `PossessedBy`, `OnRep_PlayerState`에서 ActorInfo를 초기화한다.
- 이 프로젝트는 `PlayerState ASC`가 아니라 `Character ASC`다.

이 단계에서 꼭 이해할 것:

- 왜 `IAbilitySystemInterface`가 필요한가
- 왜 ASC getter가 필요한가
- 왜 ActorInfo 초기화 시점이 중요한가

지금은 몰라도 되는 것:

- Cue 내부 VFX 디테일
- UI 위젯 배치 디테일

### 2단계: Dash 이해

기준 에셋:

- `Content/GameAbilitySystem/Ability/GA_Dash`
- `Content/GameAbilitySystem/Effects/GE_Dash_Cost`
- `Content/GameAbilitySystem/Effects/GE_Dash_Cooldown`
- `Content/GameAbilitySystem/Cues/GC_Dash`

핵심 구조:

- 입력 태그: `GameplayAbility.Movement.Dash`
- 실행 본체: `GA_Dash`
- 자원 차감: `GE_Dash_Cost`
- 쿨다운: `GE_Dash_Cooldown`
- 시각 효과: `GameplayCue.Dash.Active` -> `GC_Dash`

이 단계에서 꼭 이해할 것:

- Dash는 이동 로직 자체를 Ability가 가진다
- Dash는 `ApplyRootMotionConstantForce`를 사용한다
- Cost와 Cooldown은 Ability 밖의 GE로 분리된다

### 3단계: Attributes & Effects 이해

기준 에셋:

- `Content/GameAbilitySystem/Effects/GE_Status_StaminaRegen`
- `Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base`
- `Content/GameAbilitySystem/EffectActor/BP_EffectArea_Base_Heal`
- `Content/GameAbilitySystem/Effects/GE_Damage_OverTime_Infinite`
- `Content/GameAbilitySystem/Effects/GE_Heal_OverTime_Infinite`

핵심 구조:

- Attribute 계산의 기준은 `BasicAttributeSet`
- 플레이어는 BeginPlay에서 `GE_Status_StaminaRegen`을 자기 자신에게 적용한다
- 장판형 테스트는 EffectActor가 오버랩으로 GE를 붙이고 뗀다
- `Data.Damage`, `Data.Heal` 태그로 SetByCaller 값을 넣는 흔적이 있다

이 단계에서 꼭 이해할 것:

- Attribute는 C++, 적용은 GE, 트리거는 BP/Ability다
- 지속 데미지와 지속 힐은 Ability가 아니라 EffectActor로도 검증 가능하다

### 4단계: AttackQ / HealE 확장 패턴 이해

기준 에셋:

- `Content/GameAbilitySystem/Ability/GA_Attack_Q`
- `Content/GameAbilitySystem/Effects/GE_AttackQ_Cost`
- `Content/GameAbilitySystem/Effects/GE_AttackQ_Cooldown`
- `Content/GameAbilitySystem/Effects/GE_AttackQ_Damage`
- `Content/GameAbilitySystem/Cues/GC_Attack_Q`
- `Content/GameAbilitySystem/Ability/GA_Heal_E`
- `Content/GameAbilitySystem/Effects/GE_HealE_Cost`
- `Content/GameAbilitySystem/Effects/GE_HealE_Heal`
- `Content/GameAbilitySystem/Cues/GC_Heal_E`

핵심 패턴:

- `SphereTraceSingle`
- `TargetData 생성`
- `BP_ApplyGameplayEffectToTarget`
- `K2_ExecuteGameplayCueWithParams`

즉 Q와 E는 현재 거의 같은 틀이다.
바뀌는 것은:

- Ability 태그
- Cost/Cooldown/Effect GE
- Cue 태그와 Cue 에셋
- Trace 반경과 의도

### 5단계: UI 연동 이해

기준 에셋:

- `Content/Blueprints/BP_Nexus_PlayerController`
- `Content/Widget/W_PlayerHUD`
- `Content/Widget/W_PlayerVitals`
- `Content/Widget/W_AbilitiesContainer`
- `Content/Widget/W_Ability`

핵심 구조:

- Controller가 HUD를 만든다
- `W_PlayerVitals`는 ASC에서 Attribute를 직접 읽고 `WaitForAttributeChanged`를 쓴다
- `W_AbilitiesContainer`는 `Event.Abilities.Changed`를 기다렸다가 Ability Spec 목록을 다시 채운다
- `W_Ability`는 쿨다운 시간을 읽고 `Cooldown` 태그 카운트를 감시한다

### 6단계: 게임 완성용 확장

현재 프로젝트는 학습용 구현이 우선이다.
게임 완성 단계로 가려면 다음 축을 추가해야 한다.

- Enemy 전투 루프
- 피격/사망
- Ability 공통 베이스
- 입력 통합
- 데이터 기반 스케일링

## 4. Ability 추가 규칙

새 Ability 1개를 넣을 때 기본 체크리스트:

- `GA_NewSkill`
- `GE_NewSkill_Cost`
- `GE_NewSkill_Cooldown`
- `GE_NewSkill_Effect`
- `GC_NewSkill_Active` 또는 `GC_NewSkill_Burst`
- `DefaultGameplayTags.ini` 태그 추가
- `BP_Nexus_Player` 입력 또는 부여 로직 연결
- UI 노출 여부 점검

### 분리 규칙

- Cost는 리소스를 깎는 GE다
- Cooldown은 `Cooldown.*` 태그를 부여하는 GE다
- Actual Effect는 Damage/Heal/Buff/Debuff를 주는 GE다
- Cue는 Ability 동작 표현 또는 Effect 적용 표현이다

### Cue 붙이는 기준

- Ability가 진행되는 동안 보여야 하면 GA에 붙인다
- 적용 순간만 보여주면 GE에 붙인다

예시:

- Dash: GA Active Cue
- Damage Burst: GE Burst Cue
- Heal Burst: GE Burst Cue

### Player BP와 Ability의 책임 분리

`BP_Nexus_Player` 책임:

- 입력 받기
- 시작 Ability 부여
- 상태 이벤트 브리지

`GA_*` 책임:

- Commit
- 트레이스/타겟 확정
- 대상에 GE 적용
- Cue 실행
- 종료 처리

## 5. 지금 구조에서 특히 조심할 것

- `BasicAttributeSet.cpp`는 현재 `Health`만 복제 등록되어 있다
- `BP_Nexus_Player`에 Ability 부여와 상태 로직이 몰려 있다
- 입력이 Enhanced Input과 raw key event로 섞여 있다
- `GA_Heal_E`는 현재 별도 cooldown asset이 보이지 않는다
- `BP_Nexus_Enemy`는 아직 전투 AI라기보다 테스트 타겟에 가깝다

## 6. Lvl_GAS_0402에서 해야 하는 기본 검증

- Dash 사용 시 스태미나가 줄어드는가
- Dash 사용 후 쿨다운 UI가 도는가
- Q 사용 시 적에게 실제 GE가 적용되는가
- E 사용 시 Heal이 적용되는가
- Damage/Heal EffectArea에 들어갔다 나올 때 GE가 붙고 제거되는가
- HUD의 HP/Stamina/Cooldown이 실시간으로 반영되는가

## 7. 다음에 새 스킬을 만들 때 추천 기준 Ability

- 이동기면 `GA_Dash`를 복제
- 단일 타격기면 `GA_Attack_Q`를 복제
- 단일 치유기면 `GA_Heal_E`를 복제

가장 무난한 시작점은 `GA_Attack_Q`다.
이유는 “입력 -> Trace -> Target GE 적용 -> Cue” 패턴이 가장 일반적이기 때문이다.

## 8. 지금 이 문서를 어떻게 써야 하나

1. 새 세션을 시작하면 먼저 이 문서를 읽는다.
2. 그 다음 `GAS_Nexus_Audit_Full.md`에서 필요한 섹션만 깊게 본다.
3. 실제 작업 우선순위는 `GAS_Nexus_Todo.md`를 기준으로 진행한다.
