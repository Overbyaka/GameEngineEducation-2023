#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsShoot.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
    register_ecs_shoot_systems(ecs);

    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .set(MaxBullet{ 6 })
        .set(CurrentBullet{ 6 })
        .set(BulletSpeed{ 10.f })
        .set(Reload{ 1.0f })
        .set(CurrentReload{ 1.0f })
        .set(ShootCooldown{ 0.1f })
        .set(CurrentShootCooldown{ 0.1f })
        .add<Gun>()
        .add<CubeMesh>();

    for (int i = -3; i < 5; i+=3)
    {
        auto cubeDestroyable = ecs.entity()
            .set(Position{ 5.f, 0.f, i + 0.f })
            .set(MoreBullet{ 3 })
            .add<Destroyable>()
            .add<CubeMesh>();
    }

    /*auto cubeMoving = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 1.f })
        .add<CubeMesh>();*/
}

void EntitySystem::Update()
{
    ecs.progress();
}