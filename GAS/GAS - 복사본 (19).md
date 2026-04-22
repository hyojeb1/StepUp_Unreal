[효제 (사용자)]

https://www.youtube.com/watch?v=DRCTOtQmziw&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=20

영상 요약해줘

[LLM(AI)]

제공해주신 영상 **"Unreal Engine's Gameplay Ability System — Part 19: Input Handling — Tutorial"**의 주요 내용을 요약해 드립니다.

이 영상은 언리얼 엔진의 **Gameplay Ability System(GAS)** 시리즈 중 19번째 파트로, 개별 어빌리티마다 별도의 입력 액션을 할당하는 기존 방식 대신, 어빌리티 유형별로 입력을 처리하는 더욱 효율적인 **입력 핸들링 시스템**을 구축하는 방법을 다룹니다.

### 1. 시스템 설계 및 Enum 생성
기존의 복잡한 입력 방식을 개선하기 위해 어빌리티를 카테고리화하고 이를 식별할 Enum을 생성합니다.
* **어빌리티 카테고리화**: 모든 무기가 공통적으로 가지는 '기본 공격', '보조 공격', '방어 기술', '이동 기술' 등의 카테고리를 정의합니다. [[02:00](http://www.youtube.com/watch?v=DRCTOtQmziw&t=120)]
* **C++ Enum 생성**: `EAbilityInputID`라는 Enum을 만들어 `Primary`, `Secondary`, `Defensive`, `Movement` 등을 정의합니다. [[04:02](http://www.youtube.com/watch?v=DRCTOtQmziw&t=242)]
* **어빌리티 클래스 확장**: 베이스 어빌리티 클래스(`UNexusGameplayAbility`)에 이 Enum 변수를 추가하여, 블루프린트에서 각 어빌리티가 어떤 입력 ID를 가질지 설정할 수 있게 합니다. [[06:45](http://www.youtube.com/watch?v=DRCTOtQmziw&t=405)]

### 2. 어빌리티 부여 및 입력 매핑
설정한 입력 ID를 실제 시스템에 연결하는 과정입니다.
* **자동 입력 ID 할당**: 어빌리티를 부여할 때(Grant Abilities), 해당 어빌리티 클래스에 설정된 입력 ID를 자동으로 읽어와 시스템에 등록하도록 C++ 코드를 수정합니다. [[11:18](http://www.youtube.com/watch?v=DRCTOtQmziw&t=678)]
* **Enhanced Input 설정**: 각 카테고리별로 `IA_PrimaryAbility` 등의 입력 액션을 만들고, 이를 마우스 왼쪽/오른쪽 버튼, R키, Shift키 등에 매핑합니다. [[18:27](http://www.youtube.com/watch?v=DRCTOtQmziw&t=1107)]
* **입력 처리 함수**: 입력이 발생했을 때 해당 입력 ID에 매핑된 어빌리티를 실행하는 공통 함수(`PressAbilityInputID`)를 구현합니다. [[16:27](http://www.youtube.com/watch?v=DRCTOtQmziw&t=987)]

### 3. Ability Task를 활용한 응용 (Wait Input Press)
입력 ID 시스템의 가장 큰 장점 중 하나인 `WaitInputPress` 태스크를 활용해 복잡한 로직을 단순화합니다.
* **대시(Dash) 기능 개선**: 복제(Replication) 문제가 있던 기존 방식을 대신하여, 캐릭터의 `CurrentAcceleration`을 활용해 방향을 결정하도록 수정합니다. [[27:42](http://www.youtube.com/watch?v=DRCTOtQmziw&t=1662)]
* **콤보 시스템**: RPC나 복잡한 이벤트 없이 `WaitInputPress` 태스크만으로 서버와 클라이언트 모두에서 다음 콤보 입력을 대기하고 처리할 수 있게 됩니다. [[30:21](http://www.youtube.com/watch?v=DRCTOtQmziw&t=1821)]
* **어빌리티 취소**: 광역 공격(AoE) 중 같은 입력 키를 다시 누르면 어빌리티가 취소되도록 `WaitInputPress`를 활용해 간단히 구현합니다. [[33:33](http://www.youtube.com/watch?v=DRCTOtQmziw&t=2013)]

### 4. 기타 방식 및 마무리
* 사용자가 직접 키를 지정하는 '슬롯 방식'이나, 더욱 확장성 있는 Lyra 샘플 프로젝트의 데이터 기반 입력 시스템에 대해서도 간략히 언급하며 마무리합니다. [[37:54](http://www.youtube.com/watch?v=DRCTOtQmziw&t=2274)]

**관련 영상 URL:** [https://www.youtube.com/watch?v=DRCTOtQmziw](https://www.youtube.com/watch?v=DRCTOtQmziw)



http://googleusercontent.com/youtube_content/0

[효제 (사용자)]
여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?

[LLM(AI)]


영상에서 설명한 시스템을 구축하기 위해 필요한 **에셋**과 **코드 변경 사항**을 정리해 드립니다.

### 1. 필요한 에셋 (Assets)
블루프린트와 입력 시스템 설정을 위해 다음 에셋들이 필요합니다.

* **Input Action (입력 액션):** 카테고리별로 4개를 생성합니다.
    * `IA_PrimaryAbility`: 기본 공격용
    * `IA_SecondaryAbility`: 보조 공격용
    * `IA_DefensiveAbility`: 방어 기술용
    * `IA_MovementAbility`: 이동 기술(대시 등)용
* **Input Mapping Context (입력 매핑 컨텍스트):**
    * `IMC_AbilityInput`: 위에서 만든 4개의 `IA`를 실제 키(마우스 왼쪽, 오른쪽, R, Shift 등)에 할당합니다. 기존의 기본 이동 매핑과 분리하여 관리하는 것이 깔끔합니다.
* **Enum (열거형):**
    * `EAbilityInputID`: C++에서 정의하지만 블루프린트에서 각 어빌리티의 속성을 지정할 때 사용됩니다. (`None`, `Primary`, `Secondary`, `Defensive`, `Movement` 포함)



---

### 2. 추가 및 수정되는 코드 (Code & Logic)

#### **C++ 부분**
기존의 하드코딩된 입력 방식을 자동화하기 위해 베이스 클래스들을 수정합니다.

1.  **`UNexusGameplayAbility` (베이스 어빌리티 클래스):**
    * `EAbilityInputID` 변수를 추가합니다. 이를 통해 각 어빌리티 블루프린트의 `Class Defaults`에서 이 어빌리티가 어떤 입력(예: Primary)에 반응할지 선택할 수 있게 됩니다.
2.  **`GrantAbilities` 함수 (어빌리티 부여 로직):**
    * 어빌리티를 캐릭터에게 줄 때, 클래스 기본 객체(CDO)로부터 설정된 `AbilityInputID`를 읽어와서 `GiveAbility` 함수의 인자로 전달하도록 수정합니다.
3.  **`ANexusPlayer` (캐릭터/플레이어 클래스):**
    * `PressAbilityInputID` 함수를 추가합니다. 블루프린트에서 호출 가능하며, 입력 액션이 트리거될 때 해당 Enum 값을 정수로 변환하여 ASC(Ability System Component)의 `PressInputID`를 호출하는 래퍼 함수입니다.

#### **블루프린트 로직 부분**
각 어빌리티 내부의 복잡한 네트워크 로직을 GAS 전용 태스크로 교체합니다.

* **`WaitInputPress` 태스크 활용:**
    * **콤보 공격:** 기존의 RPC나 수동 이벤트를 삭제하고, `WaitInputPress` 태스크를 사용하여 다음 공격 입력을 대기합니다.
    * **어빌리티 취소:** 어빌리티 실행 중 다시 입력을 누르면 `CancelAbility`가 호출되도록 설정합니다. (예: AoE 공격 취소)
* **대시(Dash) 방향 처리:**
    * 복제되지 않는 `LastMovementInputVector` 대신, 서버와 클라이언트 모두에서 사용 가능한 `GetCurrentAcceleration`을 사용하여 대시 방향을 결정하는 함수(`GetDashDirection`)를 새로 만듭니다.



### 3. 요약: 무엇이 달라지나요?
이 과정을 거치면 **"왼쪽 마우스를 클릭하면 어떤 코드를 실행하라"**는 방식이 아니라, **"왼쪽 마우스는 'Primary' 입력이다 -> 'Primary'로 설정된 어빌리티를 실행하라"**는 데이터 주도형 방식으로 바뀝니다. 덕분에 새로운 무기나 어빌리티를 만들 때 입력 코드를 매번 새로 짤 필요 없이, 에셋 설정만으로 해결이 가능해집니다.

**관련 영상 URL:** [https://www.youtube.com/watch?v=DRCTOtQmziw](https://www.youtube.com/watch?v=DRCTOtQmziw)
