# GAS Nexus Audit Full

작성일: 2026-04-24

이 문서는 `Docs/2026-04-21` 이후 진행 상황을 다시 점검한 결과다.
목표는 두 가지다.

1. 실제로 무엇이 완료되었는지 확인한다.
2. 다음 계획을 세울 때 어디가 아직 “부분 완료” 상태인지 분리한다.

---

# 1. 총평

현재 구조는 분명히 전진했다.

- 학습용 단일 BP 의존 구조에서
- **기능 이름 기반 Ability 구조**
- **AbilitySet 기반 지급 구조**
- **Base Ability + UI DataTable 기반 구조**

까지는 올라왔다.

하지만 아직 완전히 수렴하지는 않았다.

현재 상태를 한 줄로 정리하면:

> 방향은 맞고 토대는 많이 올라왔지만, 입력 계층과 태그 계층이 아직 한 체계로 완전히 정리되지는 않았다.

즉,

- P0는 실질적으로 완료
- P1은 절반 이상 진행
- P2 이후는 아직 본격 시작 전

상태로 본다.

---

# 2. 이번 점검에서 확인된 완료 사항

## 2-1. Attribute replication 보강 완료

확인 파일:

- `Source/StepUp_Unreal/BasicAttributeSet.cpp`

현재 `GetLifetimeReplicatedProps`에는 다음이 모두 등록되어 있다.

- `Health`
- `MaxHealth`
- `Stamina`
- `MaxStamina`

이건 이전 점검 때 가장 먼저 위험하다고 본 지점이었고, 지금은 보강된 상태다.

## 2-2. Q/E 기반 이름에서 기능 이름 기반으로 이동 시작

확인 에셋:

- `Content/GameAbilitySystem/Ability/GA_EnergyBolt`
- `Content/GameAbilitySystem/Ability/GA_HealingBolt`
- `Content/GameAbilitySystem/Effects/GE_EnergyBolt_*`
- `Content/GameAbilitySystem/Effects/GE_HealingBolt_*`
- `Content/GameAbilitySystem/Cues/GC_EnergyBolt`
- `Content/GameAbilitySystem/Cues/GC_HealingBolt`

이전의 `AttackQ`, `HealE` 식 이름에서 벗어나
기능 이름 기준으로 Ability/Effect/Cue가 재정리되기 시작했다.

이건 매우 중요한 변화다.

이제 스킬 이름과 입력 슬롯을 분리할 수 있는 기반이 생겼다.

## 2-3. Cooldown 구조와 Instancing 이슈 정리

Todo 기록 기준으로 다음 사항이 정리되었다.

- `GA_EnergyBolt`
- `GA_HealingBolt`

가 `Instanced Per Actor` 기준으로 맞춰졌고,
`W_Ability`의 쿨다운 오버레이 동작도 정상화되었다.

문제의 원인을 “GE 누락”이 아니라
“Ability 인스턴싱 정책 차이 + UI 조회 구조”로 잡은 점이 좋다.

## 2-4. Ability 지급 로직이 BP 직접 GiveAbility에서 한 단계 회수됨

확인 파일:

- `Source/StepUp_Unreal/NexusCharacterBase.h`
- `Source/StepUp_Unreal/NexusCharacterBase.cpp`
- `Source/StepUp_Unreal/NexusAbilitySet.h`
- `Content/Blueprints/Nexus/DA_Player_DefaultAbilitySet`

현재는:

- `UNexusAbilitySet`
- `FNexusAbilitySetEntry`
- `GrantStartupAbilities()`
- `GrantAbilitiesFromSet()`

가 추가되어 있다.

즉 “플레이어 BP가 직접 Ability를 하나씩 GiveAbility 하던 구조”에서 벗어나,
적어도 지급 정책 자체는 C++ + DataAsset 축으로 올리기 시작했다.

이건 P1의 핵심 성과다.

## 2-5. Base Ability와 UI DataTable 기반 준비가 시작됨

확인 파일:

- `Source/StepUp_Unreal/NexusGameplayAbilityBase.h`
- `Source/StepUp_Unreal/NexusUIDataTableRow.h`
- `Content/Blueprints/Nexus/DT_AbilityUI`
- `Content/Widget/W_Ability`

현재 확인된 구조:

- `UNexusGameplayAbilityBase`에 `AbilityTag`가 있다
- `DT_AbilityUI`는 `AbilityTag`, `CooldownTag`, `InputTag`, `DisplayName`, `Icon`을 가진다
- `W_Ability`는 `NexusGameplayAbilityBase:AbilityTag`와 `DT_AbilityUI`를 참조한다

즉 UI가 “Ability 이름 하드코딩”에서 벗어나
태그 기반 메타데이터 조회 구조로 갈 준비가 시작된 상태다.

---

# 3. 이번 점검에서 확인된 부분 완료 / 미완료 사항

## 3-1. 입력 체계 통일은 아직 “결정 완료, 구현 미완료” 상태

확인 사항:

- `Content/Input/Actions` 안에 `IA_Ability_Dash`, `IA_Ability_EnergyBolt`, `IA_Ability_HealingBolt`가 없다
- `BP_Nexus_PlayerController`는 여전히 `IMC_Default`, `IMC_MouseLook`만 추가한다
- `BP_Nexus_Player`에는 여전히 `LeftShift`, `Q`, `E` raw key 이벤트 문자열이 남아 있다

즉 현재 상태는:

- Enhanced Input으로 가겠다는 방향은 맞음
- 그러나 실제 입력 전환은 아직 끝나지 않음

으로 판단한다.

## 3-2. 입력 태그 체계가 아직 서로 안 맞는다

확인 결과:

- `Config/DefaultGameplayTags.ini`에는
  - `Input.Ability.Dash`
  - `Input.Ability.EnergyBolt`
  - `Input.Ability.HealingBolt`
  가 있다

- 그런데 `DA_Player_DefaultAbilitySet`에는
  - `Input.Ability.Dash`
  - `Input.Ability.Q`
  - `Input.Ability.E`
  가 보인다

- `DT_AbilityUI`에는
  - `Input.Ability.Dash`
  - `Input.Ability.EnergyBolt`
  - `Input.Ability.HealingBolt`
  가 보인다

즉 Config / AbilitySet / UI DataTable이 한 체계로 통일되지 않았다.

이건 현재 가장 먼저 정리해야 할 혼선이다.

## 3-3. Ability 태그도 과거 흔적이 남아 있다

확인 결과:

- `GA_EnergyBolt`, `GA_HealingBolt`는 각각
  - `GameplayAbility.Attack.EnergyBolt`
  - `GameplayAbility.Support.HealingBolt`
  를 사용한다

- 하지만 `BP_Nexus_Player` 문자열에는 여전히
  - `GameplayAbility.Skill.Q`
  - `GameplayAbility.Skill.E`
  도 남아 있다

즉 실행 경로 어딘가에는 구 태그 체계가 아직 섞여 있을 가능성이 높다.

## 3-4. Ability 지급은 회수됐지만, 시작점은 아직 BP가 쥐고 있다

확인 결과:

- `GrantStartupAbilities()`는 C++에 있다
- 하지만 그 함수를 호출하는 흔적은 `BP_Nexus_Player` 안에 남아 있다

즉 구조는 다음 중간 단계다.

- Ability 지급 정책: C++
- 지급 시작 트리거: BP

이건 나쁜 상태는 아니지만, “완전 회수”라고 부르긴 이르다.

## 3-5. Startup effects / attribute callback binding은 아직 BP BeginPlay에 남아 있다

`BP_Nexus_Player`에는 여전히 다음 흔적이 보인다.

- `GE_Status_StaminaRegen`
- `BP_ApplyGameplayEffectToSelf`
- `WaitForAttributeChanged`
- `RemoveActiveEffectsWithGrantedTags`

즉 BeginPlay에서 빠져야 할 것 중 절반은 아직 남아 있다.

현재 상태는:

- Ability 지급은 일부 회수
- Startup effect / attribute binding은 BP 유지

로 보는 게 정확하다.

## 3-6. Q/E 공통 타겟팅 패턴은 아직 추출되지 않았다

확인 결과:

- `GA_EnergyBolt`
- `GA_HealingBolt`

둘 다 여전히 다음 패턴을 직접 들고 있다.

- `SphereTraceSingle`
- `BP_ApplyGameplayEffectToTarget`
- `K2_CommitAbilityCost`
- `K2_CommitAbilityCooldown`
- `K2_ExecuteGameplayCueWithParams`

즉 이름은 정리됐지만,
공통 타겟팅/적용 패턴은 아직 별도 helper나 base로 추출되지 않았다.

## 3-7. 근본 구조 부채는 그대로다

다음 문제들은 여전히 남아 있다.

- ASC owner/avatar가 여전히 `Character -> Character`
- `ASCReplicationMode` 적용 시점이 여전히 생성자
- `OnRep_PlayerState()`를 쓰지만 PlayerState owner 구조는 아님

즉 지금은 P1 정리 단계이고,
PlayerState ownership 같은 실전형 구조 전환은 아직 착수 전이다.

---

# 4. 현재 구조를 한 눈에 보는 실행 흐름

현재 확인 가능한 구조를 단순화하면 아래와 같다.

## Ability 지급

`BP_Nexus_Player BeginPlay -> GrantStartupAbilities() 호출 -> DefaultAbilitySet 순회 -> GiveAbility`

## Ability UI

`AbilitySpec -> NexusGameplayAbilityBase.AbilityTag -> DT_AbilityUI 조회 -> 이름/아이콘/쿨다운 표시`

## 입력

현재는 아직:

`LeftShift/Q/E raw key -> BP_Nexus_Player -> TryActivateAbilitiesByTag`

흐름이 남아 있다.

## Startup effect / callback

현재는 아직:

`BP_Nexus_Player BeginPlay -> GE_Status_StaminaRegen 적용 -> WaitForAttributeChanged 바인딩`

흐름이 남아 있다.

---

# 5. 지금 시점의 평가

## 잘된 점

- 이름 체계를 기능 기준으로 바꾸기 시작했다
- Ability 지급 구조를 데이터 기반으로 옮기기 시작했다
- UI 메타데이터 구조를 만들기 시작했다
- 쿨다운 표시 문제를 구조적으로 해결했다

## 아직 위험한 점

- 입력 태그가 한 체계로 안 맞는다
- BP에 옛 태그와 raw key 이벤트가 남아 있다
- BeginPlay 책임이 아직 완전히 정리되지 않았다
- 공통 타겟팅 패턴 중복이 계속된다

## 결론

지금은 “새 기능을 더 추가하기 좋은 상태”가 아니라
“리팩터링 방향은 맞으니, 수렴 정리를 한 번 끝내고 가야 하는 상태”다.

즉 다음 스프린트는:

- 새 Ability 추가보다
- 태그/입력/초기화 계층 수렴

에 집중하는 것이 맞다.

---

# 6. 다음 계획의 핵심 목표

다음 계획은 아래 세 줄로 요약된다.

1. 입력 체계를 진짜로 Enhanced Input 기준으로 끝낸다
2. 태그 체계를 Config / AbilitySet / UI / BP 전부 한 규칙으로 통일한다
3. BeginPlay에 남은 startup effect / binding 책임을 더 걷어낸다

이 세 가지가 끝나면,
그 다음부터는 공통 타겟팅 추출과 Enemy 전투 루프로 넘어가는 것이 가장 자연스럽다.
