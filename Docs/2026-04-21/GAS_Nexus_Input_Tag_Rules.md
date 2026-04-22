# GAS Nexus Input And Tag Rules

이 문서는 두 가지 결정을 확정하기 위한 문서다.

1. 스킬 입력을 Enhanced Input 기준으로 통일할지
2. Ability / Cooldown / Cue / Input 태그를 어떤 규칙으로 만들지

---

## 1. 결론

결론은 다음과 같다.

- `Shift / Q / E` 스킬 입력도 Enhanced Input 기준으로 통일한다.
- 입력용 태그와 Ability 식별 태그를 분리한다.
- 신규 스킬은 `입력 태그`, `어빌리티 태그`, `쿨다운 태그`, `큐 태그`를 각각 명시적으로 만든다.

즉 앞으로의 방향은:

`Input Action -> Input Tag -> Player/ASC 전달 -> Ability Tag 활성화 -> GE/Cue 처리`

구조로 간다.

---

## 2. 왜 Enhanced Input으로 통일하는가

현재 상태:

- 이동/시점/점프는 Enhanced Input
- Dash/Q/E는 raw key event

이 상태는 학습용으로는 가능하지만, 실전 구조로는 애매하다.

문제:

- 입력 관리 위치가 나뉜다
- 키 변경 대응이 어렵다
- 패드 입력 확장이 불편하다
- Ability 수가 늘수록 BP `InputKey` 노드가 급격히 늘어난다

따라서 P1 결정은:

- **입력 체계를 Enhanced Input으로 통일한다**

---

## 3. 입력 구조 결정안

### 권장 계층

입력은 다음처럼 4단계로 본다.

1. `IA_*`
- 실제 입력 액션 에셋

2. `IMC_*`
- 어떤 키가 어떤 액션을 누르는지 정의

3. `Input.Ability.*`
- 입력 바인딩용 Gameplay Tag

4. `GameplayAbility.*`
- 실제 Ability 식별 및 활성화용 Gameplay Tag

### 왜 입력 태그와 Ability 태그를 분리하는가

입력 태그와 Ability 태그는 역할이 다르다.

- `Input.Ability.*`
설명: 플레이어가 누른 버튼의 의미

- `GameplayAbility.*`
설명: 실제 GAS Ability의 식별 태그

예:

- `Input.Ability.Q`
- `GameplayAbility.Skill.Q`

이렇게 분리하면 나중에 다음이 쉬워진다.

- 같은 입력으로 여러 Ability 슬롯 교체
- 키 재바인딩
- 무기/직업별 다른 Ability 연결
- AI는 입력 없이 Ability 태그만 직접 사용

---

## 4. 현재 프로젝트 기준 최종 규칙

### 4-1. Input Action 네이밍

형식:

- `IA_동작명`

예:

- `IA_Move`
- `IA_Look`
- `IA_Jump`
- `IA_Ability_Dash`
- `IA_Ability_Q`
- `IA_Ability_E`

권장:

- 기존 raw key 기반 Dash/Q/E는 장기적으로 `IA_Ability_*`로 옮긴다

### 4-2. Input Tag 네이밍

형식:

- `Input.Ability.동작명`

현재/권장 예:

- `Input.Ability.Dash`
- `Input.Ability.Q`
- `Input.Ability.E`

확장 예:

- `Input.Ability.Primary`
- `Input.Ability.Secondary`
- `Input.Ability.Ultimate`

### 4-3. Ability Tag 네이밍

형식:

- `GameplayAbility.분류.이름`

현재 예:

- `GameplayAbility.Movement.Dash`
- `GameplayAbility.Skill.Q`
- `GameplayAbility.Skill.E`

권장:

- 기능 분류를 먼저 쓴다
- 이름이 아니라 역할을 반영한다

예:

- `GameplayAbility.Skill.Heal`
- `GameplayAbility.Skill.AttackQ`
- `GameplayAbility.Movement.Dash`

단, 현재 프로젝트는 이미 `Skill.Q`, `Skill.E`를 쓰고 있으므로
당장은 유지하고, 신규 스킬부터 더 의미 있는 이름 체계로 가는 것도 가능하다.

### 4-4. Cooldown Tag 네이밍

형식:

- `Cooldown.스킬명`

현재 예:

- `Cooldown.Dash`
- `Cooldown.AttackQ`
- `Cooldown.HealE`

규칙:

- 쿨다운은 반드시 Ability별 전용 태그를 둔다
- `Cooldown.*` 하위에 통일한다

### 4-5. Cue Tag 네이밍

형식:

- `GameplayCue.스킬명.상태`
- `GameplayCue.효과명.버스트`

현재 예:

- `GameplayCue.Dash.Active`
- `GameplayCue.AttackQ.Active`
- `GameplayCue.HealE.Active`
- `GameplayCue.Damage.Burst`
- `GameplayCue.Heal.Burst`

규칙:

- Ability 동작형 표현은 `.Active`
- 적용 순간형 표현은 `.Burst`

### 4-6. Data / Status / Event Tag 네이밍

형식:

- `Data.*`
- `Status.*`
- `Event.*`

현재 예:

- `Data.Damage`
- `Data.Heal`
- `Status.HP.Heal`
- `Status.Stamina.Regen`
- `Event.Abilities.Changed`

규칙:

- `Data.*`: SetByCaller나 계산용 값 전달
- `Status.*`: 캐릭터 상태
- `Event.*`: UI/시스템 갱신 이벤트

---

## 5. 이 프로젝트에서의 입력 통일 최종 결정

### 결정

- **진행한다**

### 이유

- 현재 이동은 이미 Enhanced Input이라 같은 체계로 묶는 것이 자연스럽다
- `Input.Ability.Dash/Q/E` 태그가 이미 태그 파일에 들어가 있다
- P1 목표가 “확장 가능한 구조”이므로, 지금 정리하는 편이 맞다

### 당장 전환할 범위

1. Dash
2. Attack Q
3. Heal E

### 지금은 유지해도 되는 것

- Ability 내부 활성화는 여전히 `GameplayAbility.*` 태그 기반으로 유지 가능
- 즉 입력만 바꾸고, GAS 능력 식별 태그는 유지해도 된다

---

## 6. 권장 전환 구조

### 단계 1

`IA_Ability_Dash`, `IA_Ability_Q`, `IA_Ability_E` 생성

### 단계 2

`IMC_Default` 또는 별도 Ability IMC에 연결

### 단계 3

Player 또는 Controller에서:

- `IA_Ability_Dash` -> `Input.Ability.Dash`
- `IA_Ability_Q` -> `Input.Ability.Q`
- `IA_Ability_E` -> `Input.Ability.E`

를 보내는 함수로 연결

### 단계 4

입력 태그를 실제 Ability 태그로 매핑

예:

- `Input.Ability.Dash` -> `GameplayAbility.Movement.Dash`
- `Input.Ability.Q` -> `GameplayAbility.Skill.Q`
- `Input.Ability.E` -> `GameplayAbility.Skill.E`

### 단계 5

기존 `InputKey Q/E/LeftShift` 노드를 제거

---

## 7. 추천 구현 방식

현재 프로젝트 기준 가장 무난한 방식:

- 입력 수신은 `BP_Nexus_PlayerController` 또는 Player 입력 전용 영역에서 처리
- 실제 GAS 활성화 요청은 `BP_Nexus_Player` 또는 공통 함수로 전달

최소 구현 예시 개념:

- `HandleAbilityInputTagPressed(InputTag)`
- 내부에서 대응 Ability 태그로 변환
- `TryActivateAbilitiesByTag(AbilityTag)` 호출

즉 지금은 완전한 ASC 확장형 입력 시스템까지는 안 가더라도,
적어도 raw key 이벤트를 Input Action 기반으로 바꾸는 것부터 한다.

---

## 8. 신규 스킬 추가 시 태그 작성 규칙

신규 스킬 하나를 추가할 때는 아래를 같이 만든다.

- 입력 태그 1개
- Ability 태그 1개
- Cooldown 태그 1개
- Cue 태그 1개 이상

예시: 신규 화염구 스킬

- `Input.Ability.Fireball`
- `GameplayAbility.Skill.Fireball`
- `Cooldown.Fireball`
- `GameplayCue.Fireball.Active`
- `GameplayCue.Fireball.Burst`

---

## 9. 이 규칙으로 기존 스킬 다시 보기

### Dash

- Input Tag: `Input.Ability.Dash`
- Ability Tag: `GameplayAbility.Movement.Dash`
- Cooldown Tag: `Cooldown.Dash`
- Cue Tag: `GameplayCue.Dash.Active`

### Attack Q

- Input Tag: `Input.Ability.Q`
- Ability Tag: `GameplayAbility.Skill.Q`
- Cooldown Tag: `Cooldown.AttackQ`
- Cue Tag: `GameplayCue.AttackQ.Active`

### Heal E

- Input Tag: `Input.Ability.E`
- Ability Tag: `GameplayAbility.Skill.E`
- Cooldown Tag: `Cooldown.HealE`
- Cue Tag: `GameplayCue.HealE.Active`

---

## 10. 완료 기준

이 문서 기준으로 아래가 되면 P1의 두 항목은 완료다.

- `Shift/Q/E도 Enhanced Input 기준으로 간다`는 결정이 문서화됐다
- `Input.Ability.*`와 `GameplayAbility.*`를 분리해 쓰기로 정했다
- 신규 스킬 추가 시 태그 생성 규칙이 문서화됐다
- 실제 전환 순서가 문서에 적혀 있다

---

## 11. 다음 실행 항목

1. `IA_Ability_Dash`, `IA_Ability_Q`, `IA_Ability_E` 생성 여부 확인
2. `IMC_Default`에 위 액션 연결
3. 기존 raw key 입력과 병행 테스트
4. 정상 동작 확인 후 raw key 노드 제거
