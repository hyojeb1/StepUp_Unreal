# GAS Nexus Todo

작성일: 2026-04-24

이 문서는 `2026-04-24` 기준의 새 backlog다.
이전 Todo는 `Docs/2026-04-21/GAS_Nexus_Todo.md`에 있다.

이번 Todo는 “완료된 것”보다 “지금 당장 더 섞이면 위험한 지점”을 먼저 정리한다.

---

## 이미 완료된 기반 작업

- [x] `BasicAttributeSet` replication 보강
- [x] `AttackQ / HealE` 기능 이름 기반 리네이밍 시작
- [x] `EnergyBolt / HealingBolt` cooldown 및 UI 표시 안정화
- [x] `NexusAbilitySet` 도입
- [x] `GrantStartupAbilities()` 도입
- [x] `NexusGameplayAbilityBase` 도입
- [x] `DT_AbilityUI` 도입

---

## S0. 입력 / 태그 수렴 정리

이 구간은 새 기능 추가보다 먼저 해야 한다.

- [ ] `Config/DefaultGameplayTags.ini`를 canonical source로 확정
완료 기준: 입력/어빌리티/쿨다운/큐 태그의 최종 이름이 여기 기준으로 고정된다.

- [ ] `DA_Player_DefaultAbilitySet`의 입력 태그를 canonical 이름으로 교체
현재 확인된 혼선:
- `Input.Ability.Dash`
- `Input.Ability.Q`
- `Input.Ability.E`
완료 기준: AbilitySet이 `Input.Ability.Dash / EnergyBolt / HealingBolt`만 사용한다.

- [ ] `DT_AbilityUI`와 `DefaultAbilitySet`의 InputTag / AbilityTag / CooldownTag를 일치시킨다
완료 기준: Config, AbilitySet, DataTable이 같은 태그 묶음을 사용한다.

- [ ] `BP_Nexus_Player`에서 구 태그 흔적 제거
제거 대상:
- `GameplayAbility.Skill.Q`
- `GameplayAbility.Skill.E`
완료 기준: Player BP에 구 Ability 태그 문자열이 남지 않는다.

- [ ] old naming 흔적 제거 규칙 문서화
완료 기준: 앞으로 `Q/E` 이름을 에셋명이나 태그명에 다시 쓰지 않는다는 규칙이 문서로 남는다.

---

## S1. Enhanced Input 실제 전환

- [ ] `IA_Ability_Dash` 생성
- [ ] `IA_Ability_EnergyBolt` 생성
- [ ] `IA_Ability_HealingBolt` 생성

- [ ] `IMC_Default`에 Ability 입력 액션 연결
완료 기준: Dash/EnergyBolt/HealingBolt가 모두 Input Action을 통해 들어온다.

- [ ] `BP_Nexus_PlayerController` 또는 입력 전용 계층에서 Ability 입력 수신
완료 기준: 입력 계층이 raw key가 아니라 Input Action 이벤트를 쓴다.

- [ ] `BP_Nexus_Player`의 `LeftShift/Q/E` raw key 이벤트 제거
완료 기준: 능력 입력이 raw key 노드에 의존하지 않는다.

- [ ] 1인 PIE에서 Dash/EnergyBolt/HealingBolt 입력 테스트
- [ ] 2인 PIE에서 Dash/EnergyBolt/HealingBolt 입력 테스트

---

## S2. Startup initialization 추가 정리

- [ ] `GrantStartupAbilities()` 호출 위치를 최종 결정
선택지:
- 계속 BP가 호출
- `PossessedBy()`에서 호출
- 별도 공통 초기화 함수에서 호출
완료 기준: “왜 여기서 부르나”가 설명 가능하다.

- [ ] `GE_Status_StaminaRegen` 적용 책임 정리
현재 상태: 아직 BP BeginPlay에 남아 있음
완료 기준: startup effect 책임 위치가 정해진다.

- [ ] `WaitForAttributeChanged` 바인딩 책임 정리
현재 상태: 아직 BP BeginPlay에 남아 있음
완료 기준: callback binding이 player-specific init인지, 공통 init인지 분리된다.

- [ ] `BP_Nexus_Player BeginPlay`를 최종 3덩어리로 문서화
목표 덩어리:
- startup abilities
- startup effects
- callback binding

---

## S3. Ability framework 수렴

- [ ] `NexusGameplayAbilityBase`의 책임 확장 여부 결정
후보:
- `AbilityTag`
- `InputTag`
- `CooldownTag`
- UI row lookup key
완료 기준: Base Ability가 어디까지 메타데이터를 책임질지 결정된다.

- [ ] `W_Ability`의 DT 조회 키를 최종 확정
완료 기준: UI가 ability display/cooldown/input 정보를 어떤 태그 기준으로 찾는지 고정된다.

- [ ] `GA_EnergyBolt`와 `GA_HealingBolt`의 공통 trace/apply/cue helper 추출 여부 결정
완료 기준: 반복 패턴을 helper로 뺄지, base ability로 뺄지 방향이 정해진다.

---

## S4. 다음 전투 루프 준비

이 구간은 S0~S2가 정리된 뒤 들어간다.

- [ ] `BP_Nexus_Enemy` 피격 반응 추가
- [ ] `BP_Nexus_Enemy` 사망 처리 추가
- [ ] Enemy 대상 필터 규칙 정리
- [ ] EnergyBolt / HealingBolt의 적/아군/자기 자신 판정 규칙 정리

---

## 이번 스프린트에서 하지 않을 것

- [ ] 새 Ability 추가
- [ ] Talent Tree 확장
- [ ] Cue polish
- [ ] 아이콘 polish

위 항목은 지금 하면 구조가 더 섞일 가능성이 크므로 보류한다.

---

## 다음 검토 때 보여줘야 할 것

- `DefaultGameplayTags.ini`
- `DA_Player_DefaultAbilitySet`
- `DT_AbilityUI`
- `BP_Nexus_Player`
- `BP_Nexus_PlayerController`
- `IMC_Default`
- 새로 만든 `IA_Ability_*`

그리고 아래 3가지를 같이 알려주면 된다.

- 무엇을 canonical 이름으로 확정했는지
- raw key 제거가 끝났는지
- BeginPlay에 무엇이 아직 남아 있는지
