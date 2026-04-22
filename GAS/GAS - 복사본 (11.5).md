[효제 (사용자)]
https://www.youtube.com/watch?v=gcSi_VoE_Fk&list=PLNwKK6OwH7eVaq19HBUEL3UnPAfbpcUSL&index=12

영상 요약해줘
[LLM(AI)]
이 영상은 언리얼 엔진의 **Gameplay Ability System(GAS)**을 사용하여 투사체(Projectile) 시스템을 구축하는 방법을 다루는 튜토리얼입니다. 주요 내용을 단계별로 요약해 드립니다.

### **1. 투사체 액터 제작 (Projectile Actor)**
* **컴포넌트 구성:** `Sphere Collision`을 루트로 설정하고, `Arrow`와 `Projectile Movement` 컴포넌트를 추가합니다. [[01:45](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=105)]
* **설정:** 중력을 0으로 설정하고, 회전이 속도를 따르도록(`Rotation Follows Velocity`) 설정합니다. 자동 활성화는 끄고 수동으로 제어합니다. [[02:22](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=142)]
* **복제(Replication):** 멀티플레이어를 위해 `Replicates`와 `Replicate Movement`를 활성화합니다. 투사체는 서버에서만 생성되어 클라이언트로 복제됩니다. [[03:41](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=221)]

### **2. 투사체 발사 어빌리티 (GA_ShootProjectileBase)**
* **애니메이션 재생:** 어빌리티가 시작되면 몽타주를 재생합니다. [[09:55](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=595)]
* **타겟팅:** GAS의 `Wait for Target Data` 노드를 사용하여 화면 중앙(카메라 방향)의 타겟 위치를 가져옵니다. [[13:20](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=800)]
* **스폰 시점 제어:** 애니메이션의 특정 시점에 투사체를 생성하기 위해 커스텀 `Anim Notify`를 만들어 게임플레이 이벤트를 보냅니다. [[17:21](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=1041)]

### **3. 데미지 및 효과 적용**
* **게임플레이 이펙트:** 투사체가 타겟에 오버랩될 때 `Gameplay Effect Spec`을 적용하여 데미지를 입힙니다. 이때 데미지 적용은 반드시 서버(Authority)에서만 수행되도록 체크해야 합니다. [[06:56](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=416)], [[34:21](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=2061)]
* **게임플레이 큐(Gameplay Cues):** 투사체 생성 시의 효과음과 충돌 시의 시각 효과/사운드를 위해 `Gameplay Cue`를 사용합니다. [[23:01](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=1381)]

### **4. 무기별 스폰 위치 설정**
* **스폰 포인트:** 무기 베이스 클래스에 `Scene Component`를 추가하여 투사체가 발사될 정확한 위치(예: 지팡이 끝)를 정의합니다. [[30:44](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=1844)]
* **로직 구현:** 어빌리티에서 장착된 무기의 스폰 포인트 위치를 동적으로 가져와 투사체를 생성합니다. [[32:18](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=1938)]

### **5. 멀티플레이어 최적화**
* 투사체의 속도와 타겟 위치 변수를 **Replicated**로 설정하여 클라이언트에서 움직임이 끊기거나 어색하게 보이는 현상을 수정합니다. [[29:14](http://www.youtube.com/watch?v=gcSi_VoE_Fk&t=1754)]

이 영상은 GAS를 활용해 데이터 기반의 확장 가능하고 멀티플레이어 환경에 적합한 투사체 시스템을 만드는 핵심 원리를 잘 설명하고 있습니다.

관련 영상 URL: [https://www.youtube.com/watch?v=gcSi_VoE_Fk](https://www.youtube.com/watch?v=gcSi_VoE_Fk)


http://googleusercontent.com/youtube_content/0
[효제 (사용자)]
여기서 필요한 에셋을 정리해줘.
어떤 코드가 더 생기고,어떤 ?
[LLM(AI)]
영상 내용(Unreal Engine GAS Part 11: Projectiles)을 바탕으로, 시스템 구현에 필요한 **에셋**과 **추가/수정되는 코드(블루프린트 로직)**를 정리해 드립니다.

---

### **1. 필요한 에셋 목록**

투사체 시스템을 시각적, 청각적으로 완성하기 위해 다음 에셋들이 준비되어야 합니다.

* **애니메이션 (Animation):**
    * 투사체를 발사하는 동작이 포함된 **애니메이션 몽타주(Montage)**.
* **시각 효과 (VFX - Niagara):**
    * 투사체 자체의 외형(예: 날아가는 불꽃).
    * 투사체가 벽이나 적에게 부딪혔을 때 터지는 **임팩트 효과**.
* **사운드 (SFX):**
    * 투사체 발사 시 출력되는 사운드.
    * 충돌 시 출력되는 임팩트 사운드.
* **3D 에셋 및 컴포넌트:**
    * **투사체용 콜리전:** `Sphere Collision` (루트 컴포넌트로 사용).
    * **무기 메시:** 지팡이 등 투사체가 나갈 무기 모델과 스폰 위치를 지정할 `Scene Component`.

---

### **2. 새로 생성하거나 수정해야 할 코드 (블루프린트)**

GAS를 기반으로 투사체를 구현하기 위해 다음과 같은 로직들이 추가됩니다.

#### **① 투사체 액터 (BP_ProjectileBase)**
* **Projectile Movement Component:** 속도, 중력(0), 회전 방향 설정 로직.
* **속도 계산 로직:** 스폰 시 `Target Location`을 받아 방향을 계산하고 속도를 할당하는 코드.
* **데미지 처리 로직:** `OnComponentBeginOverlap` 시 서버 권한(`Has Authority`)을 체크하고 타겟의 ASC에 `Gameplay Effect`를 적용하는 코드.
* **복제(Replication):** 멀티플레이어를 위해 속도와 타겟 위치 변수를 `Replicated`로 설정.

#### **② 게임플레이 어빌리티 (GA_ShootProjectileBase)**
* **이벤트 대기 로직:** `Wait for Gameplay Event`를 통해 애니메이션의 특정 시점(Notify)까지 대기.
* **타겟 데이터 획득:** `Wait for Target Data`를 사용하여 카메라 정면의 타겟 좌표를 가져오는 로직.
* **액터 스폰:** `SpawnActorFromClass` (Ability Task)를 사용하여 서버에서 투사체를 생성.



#### **③ 애니메이션 노티파이 (AnimNotify_SendGameplayEvent)**
* **커스텀 노티파이:** 애니메이션 도중 특정 프레임에서 GAS 어빌리티에 "이제 발사해라"라는 태그(예: `Event.ShootProjectile`)를 보내는 범용 노티파이 코드.

#### **④ 무기 시스템 수정 (BP_WeaponBase)**
* **Get Spawn Point Location:** 무기별로 투사체가 나갈 위치(`Scene Component`)를 반환하는 함수 추가.

#### **⑤ 게임플레이 큐 (Gameplay Cues)**
* **GC_ProjectileSpawn:** 발사 시 사운드/이펙트 실행 로직.
* **GC_ProjectileImpact:** 충돌 및 파괴 시 사운드/이펙트 실행 로직.

---

### **정리하자면**
이 시스템은 **[애니메이션 실행] → [노티파이 발생] → [어빌리티에서 타겟팅 및 스폰] → [투사체가 날아가서 충돌] → [서버에서 데미지 계산 및 큐 실행]** 순서로 작동하게 됩니다.

관련 영상 URL: [https://www.youtube.com/watch?v=gcSi_VoE_Fk](https://www.youtube.com/watch?v=gcSi_VoE_Fk)