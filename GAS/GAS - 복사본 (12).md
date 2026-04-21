[효제 (사용자)]

https://www.youtube.com/watch?v=LuaqBhXP32k&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=13

영상 요약해줘

[LLM(AI)]
이 영상은 언리얼 엔진의 **Gameplay Ability System(GAS)** 시리즈 중 12번째 파트로, **어빌리티 태그(Ability Tags)**를 사용하여 어빌리티 간의 상호작용(취소, 차단, 우선순위 설정)을 관리하는 방법을 설명합니다.

주요 내용은 다음과 같습니다.

### 1. 어빌리티 태그의 핵심 기능 [[00:14](http://www.youtube.com/watch?v=LuaqBhXP32k&t=14)]
* **Asset Tags**: 각 어빌리티의 고유한 ID 역할을 합니다. [[01:18](http://www.youtube.com/watch?v=LuaqBhXP32k&t=78)]
* **Cancel Abilities with Tag**: 이 어빌리티가 활성화될 때, 특정 태그를 가진 실행 중인 다른 어빌리티를 취소시킵니다. [[01:42](http://www.youtube.com/watch?v=LuaqBhXP32k&t=102)]
* **Block Abilities with Tag**: 이 어빌리티가 활성화되어 있는 동안, 특정 태그를 가진 다른 어빌리티의 실행을 막습니다. [[02:21](http://www.youtube.com/watch?v=LuaqBhXP32k&t=141)]

### 2. 어빌리티 상호작용 및 우선순위 설정
* **계층 구조 활용**: `gameplay.ability`와 같은 상위 태그를 차단/취소 대상으로 설정하면 그 하위의 모든 어빌리티에 적용됩니다. [[02:43](http://www.youtube.com/watch?v=LuaqBhXP32k&t=163)]
* **대시(Dash) 예시**: 대시 어빌리티가 모든 다른 어빌리티를 취소하고 차단하도록 설정하여 최우선 순위를 부여하는 실습을 진행합니다. [[03:44](http://www.youtube.com/watch?v=LuaqBhXP32k&t=224)]
* **Melee Attack 우선순위**: 일반 공격이 콤보 공격을 취소할 수 있도록 설정하는 등 게임 디자인에 따른 우선순위 제어 방법을 보여줍니다. [[10:03](http://www.youtube.com/watch?v=LuaqBhXP32k&t=603)]

### 3. 소유자 관련 태그 관리 [[06:01](http://www.youtube.com/watch?v=LuaqBhXP32k&t=361)]
* **Activation Owned Tags**: 어빌리티가 활성화된 동안 캐릭터(소유자)에게 부여되는 태그입니다. 이를 통해 현재 어떤 어빌리티가 활성 상태인지 쿼리하거나 UI에 표시할 수 있습니다. [[06:48](http://www.youtube.com/watch?v=LuaqBhXP32k&t=408)]
* **Activation Required/Blocked Tags**: 캐릭터가 특정 태그를 가지고 있어야만 어빌리티를 쓸 수 있거나(Required), 특정 태그가 있으면 어빌리티 사용을 막는(Blocked) 조건 설정입니다. [[09:02](http://www.youtube.com/watch?v=LuaqBhXP32k&t=542)]

### 4. C++ 및 실전 응용
* **기초 클래스 구현**: C++에서 모든 어빌리티의 기본이 되는 `NexusGameplayAbility` 클래스에 기본적으로 `active` 태그가 붙도록 생성자를 수정합니다. [[13:23](http://www.youtube.com/watch?v=LuaqBhXP32k&t=803)]
* **무기 장착/해제 제한**: 어떤 어빌리티라도 실행 중일 때는 무기를 바꾸지 못하도록 `Activation Blocked Tags`를 활용해 효율적으로 로직을 구성합니다. [[16:12](http://www.youtube.com/watch?v=LuaqBhXP32k&t=972)]

이 튜토리얼을 통해 어빌리티들이 서로 충돌하지 않게 설계하고, 복잡한 전투 시스템에서 어빌리티의 질서를 잡는 방법을 배울 수 있습니다.

**관련 영상:** [Unreal Engine's Gameplay Ability System — Part 12: Ability Tags — Tutorial](https://www.youtube.com/watch?v=LuaqBhXP32k)



http://googleusercontent.com/youtube_content/0


[효제 (사용자)]
여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?

[LLM(AI)]

영상에서 설명하는 **Gameplay Ability System(GAS)**의 상호작용 시스템을 구현하기 위해 필요한 에셋, 태그, 그리고 코드 변경 사항을 정리해 드립니다.



### 1. 필요한 에셋 및 게임플레이 태그 (Assets & Tags)

이 시스템을 구축하려면 먼저 **Gameplay Tags**를 정의해야 합니다.

* **기본 상태 태그:**
    * `gameplayability.active`: 모든 어빌리티가 실행 중일 때 공통으로 가질 태그.
* **어빌리티별 자산 태그 (Asset Tags):**
    * `gameplayability.dash`: 대시 어빌리티 식별용.
    * `gameplayability.meleeattack.axswing`: 도끼 휘두르기 식별용.
    * `gameplayability.meleeattack.combo`: 콤보 공격 식별용.
    * `gameplayability.equipweapon`: 무기 장착/해제 어빌리티 식별용.
* **상태 세부 태그 (Owned Tags):**
    * `gameplayability.dash.active`: 대시 중임을 나타냄.
    * `gameplayability.meleeattack.active`: 근접 공격 중임을 나타냄.

---

### 2. 어빌리티 블루프린트 설정 (Settings)

각 어빌리티 블루프린트의 **Class Defaults**에서 다음 설정을 변경해야 합니다.

#### **GA_Dash (대시)**
* **Cancel Abilities with Tag**: `gameplayability` (대시 시작 시 모든 어빌리티 취소)
* **Block Abilities with Tag**: `gameplayability` (대시 중 모든 어빌리티 실행 차단)
* **Activation Owned Tags**: `gameplayability.dash.active` 추가

#### **GA_AxSwing (도끼 휘두르기)**
* **Cancel Abilities with Tag**: `gameplayability.meleeattack` (다른 근접 공격 취소)
* **Block Abilities with Tag**: `gameplayability.meleeattack` (다른 근접 공격 차단)

#### **GA_EquipWeapon (무기 장착/해제)**
* **Activation Blocked Tags**: `gameplayability.active`
    * **설명**: 어떤 어빌리티라도 실행 중(`active` 태그 보유)이라면 무기 교체를 못 하게 막습니다.

---

### 3. 추가/변경되는 코드 (C++)

모든 어빌리티에 일일이 태그를 넣는 것은 비효율적이므로, 프로젝트의 커스텀 베이스 클래스(`UNexusGameplayAbility`)를 수정하여 **자동화**합니다.

#### **NexusGameplayAbility.h**
기존 클래스에 생성자를 선언합니다.
```cpp
public:
    UNexusGameplayAbility();
```

#### **NexusGameplayAbility.cpp**
생성자에서 모든 어빌리티가 실행될 때 자동으로 캐릭터에게 부여될 태그를 설정합니다.
```cpp
UNexusGameplayAbility::UNexusGameplayAbility()
{
    // 어빌리티가 활성화되었을 때 소유자(캐릭터)에게 부여될 태그 컨테이너에 추가
    ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("gameplayability.active")));
}
```

### 요약하자면
1.  **태그**: 계층 구조(`active`, `dash.active` 등)를 먼저 설계합니다.
2.  **코드**: 베이스 C++ 클래스에서 공통 `active` 태그를 자동 부여하도록 수정합니다.
3.  **에셋(BP)**: 개별 어빌리티에서 어떤 태그를 취소(`Cancel`)하거나 차단(`Block`)할지 설정하여 우선순위를 완성합니다.


