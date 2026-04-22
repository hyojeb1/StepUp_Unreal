https://www.youtube.com/watch?v=DkGEQt7whTI&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=6

영상 요약 해줘




이 영상은 언리얼 엔진(Unreal Engine)의 **게임플레이 어빌리티 시스템(GAS)**을 활용하여 액션 RPG의 기초가 되는 **무기 시스템(Weapon System)**을 구축하는 방법을 설명하는 튜토리얼입니다.

영상에서 다루는 주요 내용은 다음과 같습니다.

* **무기 클래스 및 데이터 구조 설계 [[01:48](http://www.youtube.com/watch?v=DkGEQt7whTI&t=108)]**: 모든 무기의 부모 클래스가 될 `BP_Weapon_Base`를 생성하고, 지팡이(Staff)와 도끼(Axe) 자식 클래스를 만듭니다. 각 무기마다 장착할 소켓 이름, 적용할 애니메이션, 부여할 능력(Ability) 등의 속성을 한곳에서 관리하기 위해 `RS_Weapon_Config`라는 구조체(Struct)를 세팅합니다.
* **소켓 및 애니메이션 블루프린트 설정 [[04:24](http://www.youtube.com/watch?v=DkGEQt7whTI&t=264)]**: 무기가 캐릭터의 손에 올바르게 쥐어지도록 캐릭터 메시에 소켓을 추가합니다. 또한 무기마다 달라지는 대기(Idle) 모션과 이동(Locomotion) 모션을 동적으로 변경하기 위해 무기별 애니메이션 블루프린트를 구성합니다.
* **무기 관리자 컴포넌트(Weapons Manager Component) 제작 [[12:26](http://www.youtube.com/watch?v=DkGEQt7whTI&t=746)]**: 실제 무기를 스폰(Spawn)하고 장착 및 해제하는 기능은 GAS 외부에서 처리하는 것이 일반적이므로, 이를 전담할 액터 컴포넌트를 만듭니다. 무기를 장착할 때 캐릭터의 이동 속도나 회전 방식(스트레이핑 등)을 무기에 맞게 변경하는 로직도 함께 구현합니다. [[22:42](http://www.youtube.com/watch?v=DkGEQt7whTI&t=1362)]
* **GAS 어빌리티 시스템 연동 [[27:03](http://www.youtube.com/watch?v=DkGEQt7whTI&t=1623)]**: 앞에서 만든 장착/해제 로직을 GAS 어빌리티(`GA_EquipWeapon`)로 변환합니다. 키 입력 시 게임플레이 이벤트 태그를 통해 '어떤 무기를 장착할 것인지' 데이터를 전달하여 무기를 스왑하는 방법을 배웁니다.
* **향상된 입력(Enhanced Input) 적용 [[35:50](http://www.youtube.com/watch?v=DkGEQt7whTI&t=2150)]**: 무기 스왑 단축키(1번, 2번 키)를 언리얼 엔진의 향상된 입력 액션에 연결하여 시스템을 더 깔끔하게 정리합니다.

튜토리얼의 마지막 부분에서는 이 무기 시스템을 **멀티플레이어 환경**에 적용하는 방법과 무기를 들었을 때 **새로운 어빌리티를 부여받는 기능**은 다음 영상에서 다룰 것임을 예고합니다. [[39:05](http://www.youtube.com/watch?v=DkGEQt7whTI&t=2345)]


http://googleusercontent.com/youtube_content/0



여기서  필요한 에셋을 정리해줘. 

매쉬
무기 - 도끼와 지팡이

----

어떤 코드가 더 생기고,어떤 ?




영상 내용을 바탕으로 프로젝트에 필요한 **에셋(Asset)**과 새로 추가되거나 변경되는 **코드/블루프린트(Blueprint) 구조**를 정리해 드립니다.

---

### 1. 필요한 에셋 (Assets)

* **3D 메시 (Meshes)**
    * 지팡이(Staff) 스태틱 또는 스켈레탈 메시
    * 도끼(Axe) 스태틱 또는 스켈레탈 메시
* **애니메이션 (Animations)**
    * **대기(Idle) 애니메이션**: 무기를 들고 서 있는 기본 자세 (도끼용, 지팡이용)
    * **이동(Locomotion) 애니메이션**: 무기를 든 상태에서의 전후좌우 걷기 및 달리기 애니메이션 (Mixamo 등 활용)
* **블렌드 스페이스 (Blend Spaces)**
    * 도끼용 이동 블렌드 스페이스 (Axe Blend Space)
    * 지팡이용 이동 블렌드 스페이스 (Staff Blend Space)

---

### 2. 새로 추가되는 블루프린트 및 시스템 구조

영상의 튜토리얼을 따라가면 크게 **무기 시스템, 애니메이션 처리, 장착 관리자, GAS 어빌리티** 파트로 나뉘어 여러 파일과 로직이 생성됩니다.

#### ① 데이터 구조체 (Structs)
무기의 정보와 무기를 들었을 때 변하는 캐릭터의 상태를 저장하기 위해 생성합니다.
* **`RS_Movement_Properties` (이동 속성 구조체)**
    * `Max Walk Speed` (플로트): 무기 장착 시 이동 속도
    * `Orient Rotation to Movement` (부울): 이동 방향으로 캐릭터 회전 여부 (스트레이핑 구현용)
    * `Use Controller Desired Rotation` (부울): 카메라 방향 기준 회전 여부
* **`RS_Weapon_Config` (무기 설정 구조체)**
    * `Abilities to Grant`: 무기 장착 시 부여할 어빌리티 목록 (배열)
    * `Equipped Socket Name`: 무기가 부착될 뼈(Bone)의 소켓 이름
    * `Anim Class`: 무기에 맞는 애니메이션 블루프린트 클래스
    * `Movement Properties`: 위에서 만든 이동 속성 구조체 포함

#### ② 무기 블루프린트 클래스 (Weapon Actor Classes)
* **`BP_Weapon_Base`**: 모든 무기의 부모가 되는 기본 액터 클래스입니다.
    * 메시 컴포넌트를 가지며, 충돌(Collision)은 끕니다.
    * 멀티플레이어를 대비해 `Replicates`를 활성화합니다.
    * `RS_Weapon_Config` 구조체 변수를 가집니다.
* **`BP_Weapon_Staff` & `BP_Weapon_Axe`**: 기본 무기 클래스를 상속받은 자식 클래스입니다.
    * 각각 지팡이와 도끼 메시를 할당하고, 구조체(Config)의 기본값(소켓 이름, 애니메이션, 이동 속도 등)을 각각의 무기에 맞게 세팅합니다.

#### ③ 애니메이션 블루프린트 (Animation Blueprints)
* **기존 `ABP_Unarmed` 수정**: 기존의 맨손 애니메이션 블루프린트에서 대기(Idle) 모션과 이동 블렌드 스페이스를 변수화(Promote to variable)하여 외부에서 덮어쓸 수 있게 만듭니다.
* **`ABP_Staff` & `ABP_Axe` (자식 애님 블루프린트)**: 맨손 애니메이션 블루프린트를 상속받아 생성한 뒤, 대기 및 이동 애니메이션 변수만 도끼/지팡이용으로 교체합니다.

#### ④ 무기 관리자 컴포넌트 (Actor Component)
* **`Weapons_Manager_Component`**: 캐릭터에 부착되어 실제 무기 장착/해제 물리적 로직을 담당합니다.
    * `Equip Weapon` 함수: 무기 클래스를 받아와 스폰(Spawn)하고, 지정된 소켓에 부착(Attach)하며, 애니메이션 클래스와 이동 속도를 무기 설정(Config)에 맞게 변경합니다.
    * `Unequip Weapon` 함수: 장착된 무기 액터를 파괴(Destroy)하고, 애니메이션과 이동 속도를 기본 상태(맨손)로 되돌립니다.

#### ⑤ 게임플레이 어빌리티 시스템 (GAS)
* **`GA_EquipWeapon` (장착 어빌리티)**: 캐릭터가 무기를 장착하는 행위 자체를 GAS 어빌리티로 만듭니다.
    * `Activate Ability From Event` 노드를 사용하여 외부에서 **이벤트 태그**와 **페이로드(Payload) 데이터**를 받아 실행됩니다.
    * 전달받은 타겟 태그(예: `weapon.range.staff` 등)에 따라 Switch 문을 거쳐 무기 관리자 컴포넌트의 `Equip Weapon` 함수를 호출해 알맞은 무기를 장착시킵니다.

#### ⑥ 기타 추가/수정 사항
* **캐릭터 스켈레톤 소켓**: 손뼈(`hand_r`)에 `staff_equipped_socket`, `axe_equipped_socket`을 추가하여 무기가 붙을 위치를 잡습니다.
* **향상된 입력 (Enhanced Input)**: 숫자키 1, 2번을 눌렀을 때 발동하는 인풋 액션(`IA_EquipWeapon_Slot1`, `IA_EquipWeapon_Slot2`)을 생성하고, 입력 시 `Send Gameplay Event to Actor` 노드를 통해 장착 어빌리티를 호출합니다.