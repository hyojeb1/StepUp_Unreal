[효제 (사용자)]


https://www.youtube.com/watch?v=yDKRRFBWX28&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=10

영상 요약해줘


[LLM(AI)]

요청하신 영상의 요약입니다. 이 영상은 언리얼 엔진(Unreal Engine)의 **Gameplay Ability System(GAS) 파트 10 튜토리얼**로, 구성 및 재사용이 가능한 모듈식 근접 공격(Modular Base Melee Attack)을 설계하고, 이를 기반으로 3단 콤보 공격을 구현하는 방법을 설명합니다.

**주요 내용 요약:**

* **모듈식 기본 공격(Base Ability) 제작:** 기존의 도끼 공격 능력을 복제하여 모든 근접 공격이 상속받을 수 있는 `Melee Attack Base` 클래스를 생성합니다. 애니메이션 몽타주, 히트 스캔 대기, 데미지 적용 등 모든 근접 타격의 공통적인 기능들을 한 곳에 모아 재사용성을 높입니다. [[01:30](http://www.youtube.com/watch?v=yDKRRFBWX28&t=90)]
* **변수화 및 이벤트 확장(Overriding):** 공격 애니메이션 몽타주나 데미지 수치, 적용될 이펙트 등을 하위(자식) 클래스에서 쉽게 설정할 수 있도록 변수로 승격시킵니다. 또한 하위 클래스에서 기본 기능을 확장하거나 추가 로직을 덧붙일 수 있도록 `Montage Started`, `Handle Hit Scan Start`와 같은 커스텀 이벤트를 구축합니다. [[04:00](http://www.youtube.com/watch?v=yDKRRFBWX28&t=240)]
* **3단 콤보 공격 구현:** `Melee Attack Base`를 상속받는 새로운 콤보 능력을 만듭니다. 콤보 애니메이션 몽타주 안에 '콤보 윈도우(Combo Window)'라는 새로운 Anim Notify State를 추가하여, 타격 애니메이션 도중 특정 타이밍(윈도우) 내에 플레이어가 클릭 입력을 해야만 다음 콤보로 이어지는 시스템을 구현합니다. [[13:09](http://www.youtube.com/watch?v=yDKRRFBWX28&t=789)]
* **멀티플레이어 서버 동기화(RPC):** 클라이언트가 콤보를 누를 때 보내는 입력 이벤트가 서버로 전달되지 않아 콤보가 이어지지 않는 문제를 해결합니다. 클라이언트의 입력을 서버로 보내는 서버 RPC(Server Send Gameplay Event)를 생성하여 클라이언트와 서버 양쪽에서 콤보 공격이 정상적으로 실행되도록 처리합니다. [[21:31](http://www.youtube.com/watch?v=yDKRRFBWX28&t=1291)]
* **연속 타격에 따른 데미지 증가:** 앞서 만든 `Handle Hit Scan Start` 이벤트를 자식 클래스에서 오버라이드(Override)하여 데미지 로직을 확장합니다. 콤보가 이어질 때마다 카운트를 곱하여 1타(25), 2타(50), 3타(75)와 같이 데미지가 점진적으로 강해지게 만드는 응용 방법을 보여줍니다. [[26:17](http://www.youtube.com/watch?v=yDKRRFBWX28&t=1577)]

모듈식 구조를 통해 중복 코드를 줄이고 새로운 능력을 얼마나 빠르고 효율적으로 확장할 수 있는지 보여주는 매우 실용적인 튜토리얼입니다. 

자세한 코딩 과정과 시연 영상은 다음 링크를 통해 확인해 보세요!
[https://www.youtube.com/watch?v=yDKRRFBWX28](https://www.youtube.com/watch?v=yDKRRFBWX28)


http://googleusercontent.com/youtube_content/0


[효제 (사용자)]

여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?


[LLM(AI)]


영상의 내용을 바탕으로 3단 콤보 공격을 구현하기 위해 **필요한 에셋**과 **새롭게 추가/변경되는 코드 및 블루프린트**를 정리해 드립니다.

---

### 🎨 1. 필요한 에셋 (Assets)
이 튜토리얼을 따라하기 위해 물리적으로 준비해야 하는 에셋들입니다.

* **3단 콤보 애니메이션 몽타주 (Animation Montage):** * 연속으로 3번 공격하는 애니메이션이 필요합니다. (영상에서는 Mixamo에서 가져온 루트 모션이 포함된 도끼 공격 콤보 애니메이션을 사용했습니다.)
    * 이 몽타주에는 무기 궤적(Trail Effect)과 타격 판정(Hit Scan Window) 노티파이가 세팅되어 있어야 합니다.
* **어빌리티 UI 아이콘 (UI Icon):** * 게임 화면 하단의 스킬 바에 표시될 콤보 공격용 2D 이미지 아이콘이 필요합니다.

---

### 💻 2. 새로 생성되는 블루프린트 및 코드 (New Code & Blueprints)
시스템을 모듈화하고 콤보 로직을 구현하기 위해 여러 클래스가 새로 만들어집니다.

* **`GA_MeleeAttackBase` (Gameplay Ability 블루프린트):**
    * **역할:** 모든 근접 공격의 뼈대가 되는 부모(Base) 클래스입니다.
    * **내용:** 기존의 단일 도끼 공격(Axe Swing) 블루프린트를 복제해 만듭니다. 애니메이션 몽타주, 데미지 이펙트, 데미지 수치 등을 하위 클래스에서 마음대로 바꿀 수 있도록 **변수화**합니다.
* **`GA_MeleeAttack_AxeCombo` (Gameplay Ability 블루프린트):**
    * **역할:** 실제로 3단 콤보를 작동시키는 자식 클래스입니다. (`GA_MeleeAttackBase`를 상속받음)
    * **내용:** 플레이어가 올바른 타이밍에 클릭했는지 확인하고, 콤보 횟수(Combo Count)를 추적하여 타격마다 데미지를 증가(1타 25, 2타 50, 3타 75)시키는 핵심 로직이 들어갑니다.
* **`ANS_ComboWindow` (Anim Notify State 블루프린트):**
    * **역할:** 애니메이션 몽타주 타임라인 위에서 "지금 다음 공격 버튼을 누르면 콤보가 이어집니다"라는 타이밍(구간)을 알려주는 역할입니다.
    * **내용:** 해당 구간이 시작될 때와 끝날 때 게임플레이 이벤트를 발생시킵니다.
* **`IA_AxeCombo` (Input Action):**
    * 콤보 공격을 발생시키기 위한 새로운 입력 액션 에셋입니다.
* **C++ 함수 추가 (`ServerSendGameplayEventToSelf`):**
    * **역할:** 클라이언트(플레이어)가 마우스를 클릭했을 때, 그 입력 신호를 서버로 보내 콤보가 멀티플레이 환경에서도 끊기지 않게 합니다. (Server RPC)

---

### ⚙️ 3. 수정되는 기존 시스템 (Modifications)

* **무기 세팅:** 도끼를 장착했을 때 기존 단일 공격 외에 새로운 `AxeCombo` 능력을 부여하도록 배열(Array)에 추가합니다.
* **입력 매핑 컨텍스트 (IMC_Default):** 새로 만든 `IA_AxeCombo`를 마우스 왼쪽 버튼(LMB)에 할당합니다.
* **플레이어 블루프린트 (Nexus Player):** 마우스 왼쪽 버튼 클릭 시 콤보 어빌리티를 활성화(Activate)하고, 이미 활성화된 상태라면 방금 만든 C++ Server RPC 함수를 호출해 '콤보 계속 진행' 이벤트를 서버로 쏩니다.
