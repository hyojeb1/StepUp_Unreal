[효제 (사용자)]

영상 요약해줘

https://www.youtube.com/watch?v=Exp7q-KmSsY&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=19

[LLM(AI)]

이 영상은 언리얼 엔진의 **GAS(Gameplay Ability System)** 시리즈 18부로, 공격자의 **'힘(Strength)'**과 방어자의 **'방어력(Armor)'** 속성을 활용하여 데미지를 계산하는 복합적인 방법을 다룹니다.

### **주요 요약 내용**

* **새로운 속성 세트(CombatAttributeSet) 생성 [[01:39](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=99)]**
    * 기본 속성(체력, 스태미나 등) 외에 전투 전용 속성인 **방어력(Armor)**과 **힘(Strength)**, 그리고 각각의 최대치를 관리하는 `CombatAttributeSet` 클래스를 C++로 생성하고 기본 캐릭터에 추가합니다.

* **속성 기반 데미지 계산 로직 [[10:04](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=604)]**
    * `RelevantAttributesToCapture` 배열을 사용하여 공격자(Source)의 힘과 대상(Target)의 방어력 속성을 캡처합니다.
    * **수학적 공식 적용**: 캡처된 속성 값을 기반으로 "힘 1포인트당 데미지 5% 증가, 방어력 1포인트당 데미지 5% 감소"와 같은 커스텀 계산 공식을 `Math Expression` 노드를 통해 구현합니다. [[15:22](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=922)]

* **Source와 Target의 명확한 구분 및 적용 [[24:01](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=1441)]**
    * `ApplyGameplayEffectSpecToSelf`와 `ApplyGameplayEffectSpecToTarget`의 차이점을 설명합니다.
    * 공격 주체(Instigator)를 명확히 설정해야 데미지 계산 시 공격자의 '힘' 속성을 올바르게 참조할 수 있음을 강조하며, 근접 공격, 투사체, 범위 공격(AoE) 등 다양한 상황에서의 적용법을 수정합니다. [[26:16](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=1576)]

* **속성 값 제한(Clamping) 구현 [[34:21](http://www.youtube.com/watch?v=Exp7q-KmSsY&t=2061)]**
    * 힘이나 방어력이 설정된 최대치(Max Value)를 초과하지 않도록 `PreAttributeChange`와 `PostGameplayEffectExecute` 함수 내에서 `Clamp` 로직을 추가하여 속성 시스템의 안정성을 높입니다.

이 튜토리얼은 GAS 프레임워크에서 속성 간의 상호작용을 통해 복잡한 전투 메커니즘을 구축하는 핵심적인 방법을 제시하며, 기초 단계를 마무리하고 심화 주제로 넘어가기 위한 중요한 가이드 역할을 합니다.

관련 영상 URL: [https://www.youtube.com/watch?v=Exp7q-KmSsY](https://www.youtube.com/watch?v=Exp7q-KmSsY)


http://googleusercontent.com/youtube_content/0

[효제 (사용자)]
여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?

[LLM(AI)]

영상에서 다루는 **언리얼 엔진 GAS(Gameplay Ability System) 전투 속성 시스템**을 구현하기 위해 필요한 에셋과 추가되는 코드를 정리해 드립니다.

### 1. C++ 코드 에셋 (프로그래밍 파트)

새로운 속성을 정의하고 관리하기 위해 가장 먼저 C++ 클래스 수정 및 생성이 필요합니다.

* **`CombatAttributeSet` 클래스 (신규 생성)**
    * `UAttributeSet`을 상속받아 생성합니다.
    * **추가되는 속성**: `Strength`(힘), `MaxStrength`, `Armor`(방어력), `MaxArmor`.
    * **주요 기능**:
        * 속성 복제(Replication)를 위한 `GetLifetimeReplicatedProps`.
        * 속성 값이 범위를 벗어나지 않게 제한하는 `PreAttributeChange` 및 `PostGameplayEffectExecute` (Clamping 로직).
* **`BaseCharacter` 클래스 (기존 코드 수정)**
    * 새로 만든 `CombatAttributeSet`을 캐릭터 클래스의 멤버 변수로 선언하고, 생성자에서 `CreateDefaultSubobject`를 통해 초기화합니다. 이로써 플레이어와 적군 모두 전투 속성을 갖게 됩니다.

### 2. 블루프린트 에셋 (데이터 및 로직 파트)

기능을 시각적으로 구현하고 조절하기 위해 필요한 에셋들입니다.

* **`DamageCalculation` (Execution Calculation 클래스)**
    * 데미지 계산의 핵심 로직이 들어가는 에셋입니다.
    * **Capture 설정**: 공격자(Source)의 `Strength`와 대상(Target)의 `Armor`를 캡처하도록 설정합니다.
    * **로직 구현**: `CalculateBaseMagnitude` 함수 내에서 `GetCapturedAttributeMagnitude`를 사용해 값을 가져온 후, 수학 공식(Math Expression)을 적용합니다.
* **Gameplay Effect (GE) 에셋**
    * **`GE_Strength_Buff`**: 캐릭터의 '힘' 속성을 영구적 또는 일시적으로 올려주는 효과.
    * **`GE_Armor_Buff`**: 캐릭터의 '방어력' 속성을 올려주는 효과.
    * **`GE_Damage` (수정)**: 기존의 단순 데미지 방식에서 위에서 만든 `DamageCalculation`을 사용하도록 설정을 변경합니다.
* **Effect Actor (테스트용 월드 에셋)**
    * 바닥에 배치되어 캐릭터가 올라서면 힘이나 방어력을 지속적으로 올려주는 '버프 존' 액터입니다.



### 3. 논리적 구성 요소 (개념적 변화)

코드나 에셋 파일은 아니지만, 시스템 구현을 위해 반드시 설정해야 하는 부분입니다.

* **수학 공식 (Math Expression)**:
    * 영상에서는 `Base Damage * (1 + 0.05 * Strength) / (1 + 0.05 * Armor)`와 같은 공식을 사용하여 힘이 높으면 데미지가 세지고, 방어력이 높으면 데미지가 줄어들게 설계했습니다.
* **Source vs Target 판정 수정**:
    * 기존의 `ApplyGameplayEffectSpecToSelf` 대신, 공격 주체와 대상을 명확히 구분하는 `ApplyGameplayEffectSpecToTarget` 함수를 사용하도록 모든 공격 로직(무기, 발사체, 범위 공격)을 업데이트해야 합니다.

### 요약하자면:
이 시스템을 완성하려면 **1개의 신규 C++ 클래스(`AttributeSet`)**, **기존 캐릭터 코드 수정**, **1개의 계산용 블루프린트 클래스**, 그리고 이를 적용할 **다수의 Gameplay Effect 데이터 에셋**이 필요합니다. 이를 통해 단순 수치 차감이 아닌, 캐릭터의 능력치에 따라 유동적으로 변하는 복합 전투 시스템을 구축할 수 있습니다.
