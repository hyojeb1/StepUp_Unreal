# GAS Nexus QuickStart

작성일: 2026-04-24

이 문서는 `2026-04-24` 기준의 현재 상태와 다음 작업 순서를 짧게 보는 용도다.

깊은 근거는 `GAS_Nexus_Audit_Full.md`를 본다.

---

## 1. 지금 상태 한 줄 요약

지금 GAS 구조는:

- Ability 이름은 기능 이름 기준으로 정리되기 시작했고
- Ability 지급과 UI 메타데이터도 데이터 기반으로 옮기기 시작했지만
- 입력과 태그는 아직 구 체계와 신 체계가 섞여 있다

상태다.

---

## 2. 지금부터의 정답 기준

앞으로는 아래 이름 체계를 기준으로만 간다.

### Input Tag

- `Input.Ability.Dash`
- `Input.Ability.EnergyBolt`
- `Input.Ability.HealingBolt`

### Ability Tag

- `GameplayAbility.Movement.Dash`
- `GameplayAbility.Attack.EnergyBolt`
- `GameplayAbility.Support.HealingBolt`

### Cooldown Tag

- `Cooldown.Dash`
- `Cooldown.EnergyBolt`
- `Cooldown.HealingBolt`

### Cue Tag

- `GameplayCue.Dash.Active`
- `GameplayCue.EnergyBolt.Active`
- `GameplayCue.HealingBolt.Active`

---

## 3. 당분간 쓰지 말아야 할 과거 흔적

다음은 더 이상 기준 이름으로 쓰지 않는다.

- `Input.Ability.Q`
- `Input.Ability.E`
- `GameplayAbility.Skill.Q`
- `GameplayAbility.Skill.E`
- `AttackQ`
- `HealE`

이 흔적은 남아 있으면 제거 대상이다.

---

## 4. 지금 가장 중요한 다음 순서

### 1순위

입력/태그 수렴 끝내기

해야 할 것:

- `DA_Player_DefaultAbilitySet`의 입력 태그를 기능 이름 기준으로 통일
- `BP_Nexus_Player`에서 old tag / raw key 흔적 제거
- `Config`, `AbilitySet`, `DT_AbilityUI`, `BP`가 같은 태그 이름을 쓰게 만들기

### 2순위

Enhanced Input 실제 전환

해야 할 것:

- `IA_Ability_Dash`
- `IA_Ability_EnergyBolt`
- `IA_Ability_HealingBolt`

를 만들고 `IMC_Default`에 연결

### 3순위

BeginPlay에 남은 startup responsibility 정리

남아 있는 것:

- `GE_Status_StaminaRegen` 적용
- `WaitForAttributeChanged`
- regen 재시작/제거 정책

### 4순위

공통 타겟팅 패턴 추출

대상:

- `GA_EnergyBolt`
- `GA_HealingBolt`

공통 패턴:

- trace
- target 결정
- GE 적용
- cue 실행

---

## 5. 지금 당장 새 Ability를 추가해도 되나

권장하지 않는다.

이유:

- 입력 체계가 아직 미수렴 상태
- 태그 체계가 파일마다 조금씩 다름
- 새 Ability를 지금 넣으면 옛 구조와 새 구조가 더 섞일 가능성이 큼

권장:

- 먼저 입력/태그 수렴 완료
- 그 다음 새 Ability 추가

---

## 6. 다음 작업을 시작할 때 먼저 열 파일

- `Config/DefaultGameplayTags.ini`
- `Content/Blueprints/Nexus/DA_Player_DefaultAbilitySet`
- `Content/Blueprints/BP_Nexus_Player`
- `Content/Blueprints/BP_Nexus_PlayerController`
- `Content/Blueprints/Nexus/DT_AbilityUI`
- `Source/StepUp_Unreal/NexusCharacterBase.*`

---

## 7. 다음 검토 전에 완료되어야 할 것

- `Input.Ability.Q/E` 흔적 제거 여부 확인
- raw key `LeftShift/Q/E` 제거 여부 확인
- `IA_Ability_*` 생성 여부 확인
- `DA_Player_DefaultAbilitySet`와 `DT_AbilityUI` 태그 일치 여부 확인
- 1인/2인 PIE에서 Dash/EnergyBolt/HealingBolt 입력과 UI 동작 확인
