
여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?



이 영상은 Ali Elzoheiry 채널의 **"Unreal Engine's Gameplay Ability System — Part 7: Multiplayer — Tutorial"**로, 언리얼 엔진의 GAS(Gameplay Ability System)를 활용하여 멀티플레이어 환경을 구축하고 동기화하는 방법을 설명하는 튜토리얼입니다. 

영상의 주요 내용을 요약해 드립니다.

### 1. 언리얼 엔진의 멀티플레이어 네트워크 기초 [[00:38](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=38)]
* **권한(Authority)과 리플리케이션(Replication):** 언리얼 엔진의 멀티플레이어는 서버가 게임 상태를 결정하는 권한을 가지고 있으며, 변경된 상태를 연결된 클라이언트들에게 동기화(리플리케이션)하는 방식으로 작동합니다.
* **RPC와 클라이언트 측 예측(Client-Side Prediction):** 클라이언트가 서버에 행동을 요청하는 RPC 기능과, 네트워크 지연(Lag)을 숨기기 위해 서버 응답을 기다리지 않고 클라이언트가 먼저 행동을 실행하는 예측 기능에 대해 설명합니다. GAS는 이러한 복잡한 네트워크 처리를 기본적으로 제공합니다 [[03:27](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=207)].

### 2. 무기 매니저(Weapons Manager) 컴포넌트 멀티플레이어 적용 [[04:07](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=247)]
* 기존 싱글 플레이어 구조에서는 멀티플레이어 환경 시 서로의 무기 장착 상태나 애니메이션이 올바르게 보이지 않는 문제가 발생합니다.
* **서버 전용 실행:** 무기를 스폰(Spawn)하고 캐릭터에 부착하는 중요한 로직은 중복 생성을 막기 위해 오직 **서버에서만 실행**되도록 로직을 분리합니다 [[07:34](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=454)].
* **`RepNotify` 활용:** `EquippedWeapon`이라는 단일 변수에 `RepNotify`를 설정하여, 서버에서 무기를 변경하면 연결된 모든 클라이언트가 이를 감지하고 각자의 화면에서 무기의 속성과 애니메이션을 올바르게 업데이트하도록 최적화했습니다 [[10:46](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=646)].

### 3. 대시(Dash) 스킬의 네트워크 버그 수정
* **쿨다운 동기화 문제:** 클라이언트에서 대시를 사용할 때 쿨다운이 적용되지 않는 문제를 해결하기 위해, 비동기 작업이 아닌 스킬이 확실히 종료되는 시점(`End Ability`)에서 쿨다운이 동기화되도록 수정했습니다 [[21:00](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=1260)].
* **이동 방향 불일치(Jittering) 해결:** 클라이언트는 뒤로 대시하려고 하는데 서버는 앞으로 대시하는 것으로 인식하여 캐릭터가 버벅거리는 현상을 다룹니다. 이를 해결하기 위해, 플레이어의 이동 입력 방향 벡터를 **스킬 활성화 이벤트 데이터(Target Data의 Hit Result 내부)**에 담아 서버와 클라이언트가 동일한 이동 방향 값을 가지도록 구조를 변경했습니다 [[23:27](http://www.youtube.com/watch?v=jDKR5nsFmvU&t=1407)].

🔗 **관련 영상 링크:** [https://www.youtube.com/watch?v=jDKR5nsFmvU](https://www.youtube.com/watch?v=jDKR5nsFmvU)


http://googleusercontent.com/youtube_content/0








여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?






영상 내용을 바탕으로 멀티플레이어 환경(네트워크 동기화)을 구축하기 위해 **필요한 에셋**과 **추가 및 변경되는 주요 코드(블루프린트 로직)**를 정리해 드립니다.

---

### 1. 📂 필요한 주요 에셋 (Assets)

이번 튜토리얼에서 수정되거나 활용되는 주요 에셋들은 다음과 같습니다.

* **무기 매니저 컴포넌트 (Weapons Manager Component):** 플레이어의 무기 장착 상태와 속성을 관리하는 액터 컴포넌트
* **기본 무기 액터 (Base Weapon Blueprint):** 실제 스폰되는 무기. (반드시 세부 정보에서 `Replicates`가 체크되어 있어야 합니다.)
* **플레이어 캐릭터 (Nexus Player / Avatar Actor):** 입력(Input)을 받고 어빌리티를 실행하는 주체
* **게임플레이 어빌리티 (Gameplay Abilities):**
    * `GA_EquipWeapon` (무기 장착 스킬)
    * `GA_Dash` (대시 스킬)
* **게임플레이 태그 (Gameplay Tags):** 어빌리티를 트리거하기 위한 이벤트 태그
    * `Event.ActivateAbility.EquipWeapon`
    * `Event.ActivateAbility.Dash`

---

### 2. ⚙️ 추가 및 변경되는 코드 / 로직 (Blueprints)

멀티플레이어 동기화를 위해 각 에셋에서 다음과 같은 로직들이 추가되거나 변경됩니다.

#### ① 무기 매니저 컴포넌트 (Weapons Manager Component)
* **`Switch Has Authority` 노드 추가:** 클라이언트가 자체적으로 무기를 스폰하여 무기가 2개가 되는 버그를 막기 위해, 무기를 스폰(Spawn)하고 캐릭터에 붙이는(Attach) 핵심 로직은 **서버(Authority)에서만 실행**되도록 제한합니다.
* **클라이언트/서버 로직 분리:** * `SetEquippedWeaponProperties` (무기 장착 속성 설정)
    * `SetUnarmedWeaponProperties` (맨손 속성 설정)
    * 위 두 개의 커스텀 이벤트를 생성하여, 애니메이션 클래스나 이동 속성을 덮어씌우는 코드를 따로 분리합니다.
* **`RepNotify` 적용:** 현재 들고 있는 무기를 저장하는 `EquippedWeapon` 변수의 리플리케이션 설정을 `RepNotify`로 변경합니다.
    * 이렇게 하면 서버에서 무기 변수가 바뀔 때 클라이언트에서 자동으로 **`OnRep_EquippedWeapon`** 함수가 실행됩니다. 이 함수 안에서 분리해 둔 `SetEquippedWeaponProperties`를 호출하여 클라이언트 화면에서도 애니메이션과 무기가 정상적으로 보이게 만듭니다.
* **컴포넌트 리플리케이션 활성화:** 컴포넌트 자체의 Class Defaults 설정에서 `Component Replicates`를 True로 켜야 정상 작동합니다.

#### ② 대시 어빌리티 (GA_Dash)
* **쿨다운 노드(`CommitAbilityCooldown`) 위치 변경:** * 기존에는 비동기 처리인 이동이 끝났을 때(`OnFinish`) 쿨다운을 적용하여 클라이언트에서 쿨다운이 돌지 않는 버그가 있었습니다.
    * 이를 스킬이 종료되는 동기적 시점인 **`EndAbility`** 직전에 호출하도록 코드를 옮겨 서버/클라이언트 모두 정상 작동하게 만듭니다.
* **입력 방향 수신 (`ActivateAbilityFromEvent` 오버라이드):**
    * 클라이언트와 서버 간의 이동 방향 예측 불일치(Jittering)를 해결하기 위해, 클라이언트가 보낸 방향 데이터를 스킬 안에서 받아옵니다.
    * 이벤트 데이터(Event Data)에서 `Target Data` ➔ `Hit Result` ➔ `Location` 값을 추출하여 클라이언트가 바라보던 방향 벡터를 확보합니다.
    * 만약 받아온 값이 (0,0,0)이라면 캐릭터의 앞쪽 방향(`ActorForwardVector`)을 쓰도록 **Fallback(대체) 로직**을 추가합니다.

#### ③ 플레이어 캐릭터 (Nexus Player)
* **스킬 활성화 방식 변경 (`ActivateAbilityByClass` ➔ `SendGameplayEventToActor`):**
    * 단순히 클래스로 스킬을 켜는 것이 아니라, 이벤트 태그를 보내 스킬을 활성화하는 방식으로 코드를 바꿉니다.
* **클라이언트 데이터를 서버로 전송 (대시 방향 인코딩):**
    * 클라이언트 기기에서만 알 수 있는 플레이어의 이동 입력 방향(`Get Last Movement Input Vector`)을 가져옵니다.
    * 이 벡터 값을 `Make Hit Result` 노드의 **Location(위치)** 핀에 억지로 끼워 넣은 뒤(인코딩), `Ability Target Data From Hit Result`로 변환합니다.
    * 변환된 데이터를 `SendGameplayEventToActor`의 페이로드(Payload)에 담아 서버로 쏘아 보냅니다. 이를 통해 서버도 클라이언트가 어느 방향으로 대시하려는지 알게 됩니다.



