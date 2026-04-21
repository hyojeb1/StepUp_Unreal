# GAS Nexus Todo

이 문서는 현재 프로젝트를 "학습용 GAS 실습"에서 "완성 가능한 게임 구조"로 옮기기 위한 작업 backlog다.
우선순위는 현재 코드 상태와 학습 흐름을 같이 반영했다.

---

## P0. 지금 바로 확인하고 고칠 것

- [ ] `BasicAttributeSet` 복제 누락 확인
설명: 현재 `GetLifetimeReplicatedProps`에는 `Health`만 보이고 `MaxHealth`, `Stamina`, `MaxStamina`는 등록 흔적이 없다.
완료 기준: 2인 PIE에서 클라이언트 HP/Stamina UI가 안정적으로 갱신된다.

- [ ] `BP_Nexus_Player` BeginPlay 초기화 흐름 문서화
설명: 지금 Ability 부여, 스태미나 재생 적용, 입력 연결의 실제 시작점이 플레이어 BP에 몰려 있다.
완료 기준: BeginPlay 그래프를 “무엇을 왜 하는지” 한글 주석 또는 별도 노트로 재정리했다.

- [ ] `GA_Heal_E` 쿨다운 의도 결정
설명: 현재 에셋 기준으로 `GE_HealE_Cooldown`이 보이지 않는다.
완료 기준: “쿨다운 없음”인지 “빠진 것”인지 결론을 내고 구조를 맞춘다.

- [ ] `Lvl_GAS_0402` 1인/2인 PIE 체크리스트 실행
설명: 로컬 구조 분석만으로는 복제 문제가 숨어 있을 수 있다.
완료 기준: Dash, Q, E, Damage Area, Heal Area, HUD를 1인과 2인 PIE에서 각각 검증했다.

---

## P1. 학습을 끝내고 확장 가능한 구조로 바꾸기

- [ ] Ability 부여 로직을 `BP_Nexus_Player` 밖으로 빼는 기준 세우기
설명: 지금은 BeginPlay에서 직접 `K2_GiveAbility`를 호출한다.
후보 방향:
- Character 공통 함수
- C++ 공통 함수
- Ability Set 구조
완료 기준: 새 Ability 추가 시 Player BP를 최소 수정하는 흐름이 정해진다.

- [ ] Q/E 공통 타겟팅 패턴 추출
설명: 현재 `SphereTraceSingle -> TargetData -> ApplyGEToTarget -> ExecuteCue`가 반복된다.
완료 기준: 공통 BP 함수나 C++ helper 후보를 정했다.

- [ ] 입력 체계를 Enhanced Input 기준으로 통일할지 결정
설명: 현재 이동은 Enhanced Input, 스킬은 raw key event다.
완료 기준: Shift/Q/E도 입력 액션 기반으로 갈지 여부를 정하고, 가면 전환 계획을 적는다.

- [ ] Ability 네이밍/태그 규칙 문서화
설명: 지금은 `GameplayAbility.Skill.Q`, `Cooldown.AttackQ` 식이다.
완료 기준: 신규 스킬 추가 시 어떤 태그를 어떻게 만들지 팀 규칙이 정리된다.

---

## P2. 실제 전투 게임으로 가기 위한 최소 기능

- [ ] Enemy 피격 반응 추가
설명: 지금 `BP_Nexus_Enemy`는 주로 맞아주는 대상이다.
완료 기준: 데미지를 받을 때 최소한 피격 애니메이션, 넉백, 상태 변화 중 하나가 반영된다.

- [ ] Enemy 사망 처리 추가
설명: 체력이 0이 되었을 때 제거/비활성화/리스폰 정책이 필요하다.
완료 기준: 적이 죽었을 때 전투 루프가 끝까지 이어진다.

- [ ] Enemy AI 1종 완성
설명: 게임 완성 기준이면 적도 공격 루프를 가져야 한다.
완료 기준: 플레이어를 추적하고 최소 1개 공격 Ability 또는 공격 로직을 쓴다.

- [ ] 팀 판정 또는 대상 필터링 추가
설명: Q/E가 앞으로 자기 자신, 적, 아군을 어떻게 구분할지 기준이 필요하다.
완료 기준: 공격형/치유형 스킬의 대상 필터 규칙이 정해진다.

---

## P3. GAS 구조 개선

- [ ] 공통 Ability Base 도입 검토
설명: 강의 후반형 구조처럼 `NexusGameplayAbility` 역할을 하는 베이스가 있으면 확장성이 좋아진다.
후보 책임:
- UI 노출 여부
- 기본 태그
- 공통 Commit 정책
- 공통 Targeting helper
완료 기준: 새 Ability가 바로 이 베이스를 상속받도록 설계가 정리된다.

- [ ] 공통 AbilitySystemComponent 도입 검토
설명: Ability 목록 변화 이벤트, UI 갱신, 공통 질의를 ASC 쪽으로 옮길 수 있다.
완료 기준: `Event.Abilities.Changed`를 어디서 책임질지 명확해진다.

- [ ] GE 템플릿화 대상 선별
설명: 지금은 학습용 전용 GE가 많아도 괜찮지만, 게임 규모가 커지면 정리가 필요하다.
공용화 후보:
- Cooldown Base
- Cost Base
- Damage Base
- Heal Base
전용 유지 후보:
- 상태 이상 의미가 강한 GE
- 특정 태그/정책이 강한 GE
완료 기준: “공용화할 것 / 그대로 둘 것” 목록이 생긴다.

---

## P4. UI 개선

- [ ] `W_PlayerVitals` 갱신 안정성 점검
설명: Wait 기반 갱신이 멀티플레이에서 얼마나 안정적인지 확인해야 한다.
완료 기준: 체력/스태미나가 누락 없이 갱신된다.

- [ ] `W_AbilitiesContainer` 갱신 흐름 문서화
설명: 현재는 `Event.Abilities.Changed` 태그 이벤트 기반이다.
완료 기준: 새 Ability 추가 시 UI가 언제 다시 그려지는지 추적 가능하다.

- [ ] `W_Ability`에 아이콘/툴팁 규칙 추가
설명: 지금은 쿨다운 수치 중심으로 보인다.
완료 기준: 실제 게임 HUD 수준의 최소 표시 규칙이 생긴다.

---

## P5. 나중에 다듬어도 되는 것

- [ ] Cue VFX/SFX 교체
- [ ] 카메라 쉐이크 정리
- [ ] 히트 숫자/플로팅 텍스트
- [ ] 더 다양한 테스트 맵 구성
- [ ] Ability 아이콘 리소스 정리

---

## 새 Ability 추가용 작업 템플릿

아래 순서대로 진행한다.

- [ ] 기준 Ability 선택
- [ ] `GA_*` 복제
- [ ] `GE_*_Cost` 생성 또는 연결
- [ ] `GE_*_Cooldown` 생성 또는 연결
- [ ] `GE_*_Effect` 생성 또는 연결
- [ ] `GC_*` 필요 여부 결정
- [ ] `DefaultGameplayTags.ini` 태그 추가
- [ ] `BP_Nexus_Player` 입력/부여 연결
- [ ] `W_Ability` UI 노출 여부 점검
- [ ] `Lvl_GAS_0402`에서 실제 테스트

추천 기준 Ability:

- 이동기: `GA_Dash`
- 공격기: `GA_Attack_Q`
- 치유기: `GA_Heal_E`

---

## 내가 다음 작업으로 잡아야 할 추천 순서

1. `BasicAttributeSet` 복제 보완 여부 확인
2. `BP_Nexus_Player` BeginPlay와 입력 흐름 정리
3. `GA_Attack_Q`를 기준으로 새 Ability 1개 복제 실습
4. Enemy 피격/사망 루프 추가
5. Ability 공통 베이스 도입 여부 결정
