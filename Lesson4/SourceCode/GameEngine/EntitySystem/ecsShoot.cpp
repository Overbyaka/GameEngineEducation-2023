#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "ecsShoot.h"
#include "flecs.h"
#include "../InputHandler.h"


void register_ecs_shoot_systems(flecs::world& ecs)
{
	static auto inputQuery = ecs.query<InputHandlerPtr>();

	ecs.system <const Position, const Gun, const BulletSpeed, CurrentBullet, const ShootCooldown, CurrentShootCooldown>() // create bullet
		.each([&](flecs::entity e, const Position& pos, const Gun& gun, const BulletSpeed& speed, CurrentBullet& curAmmo, const ShootCooldown& cd, CurrentShootCooldown& currentCd)
			{
				inputQuery.each([&](InputHandlerPtr input)
					{
						if (input.ptr->GetInputState().test(eIC_Shoot))
						{
							currentCd.v -= e.delta_time();
							if (currentCd.v <= 0.f && curAmmo.v > 0)
							{
								currentCd.v = cd.v;
								e.world().entity()
									.set(Position{ pos.x + 0.5f, pos.y, pos.z })
									.set(Velocity{ speed.v, 0.f, 0.f })
									.set(FrictionAmount{ 0.001f })
									.set(Gravity{ 0.f, -9.8065f, 0.f })
									.set(BulletLifeTime{ 5.0f })
									.add<Bullet>()
									.add<CubeMesh>();
								curAmmo.v -= 1;
							}
						}
					});
			});

	ecs.system<const Gun, const Reload, CurrentReload, const MaxBullet, CurrentBullet>()
		.each([&](flecs::entity e, const Gun& gun, const Reload& reload, CurrentReload& curReload, const MaxBullet& maxAmmo, CurrentBullet& curAmmo) // reload
			{
				if (curAmmo.v <= 0)
				{
					curReload.v -= e.delta_time();
					if (curReload.v <= 0.f)
					{
						curReload.v = reload.v;
						curAmmo.v = maxAmmo.v;
					}
				}
			});


	ecs.system<Velocity, Position, const Bullet, Gravity>()
		.each([&](flecs::entity e, Velocity& vel, Position& bulletPos, const Bullet& bullet, Gravity& grav) // hold and add to remove bullet
			{
				if (bulletPos.y < -10.f)
				{
					vel.x = 0;
					vel.y = 0;
					vel.z = 0;
					grav.y = 0;
					if (!e.has<ToDestroy>())
					{
						e.add<ToDestroy>();
					};
				}

			});

	ecs.system<const Bullet, BulletLifeTime, RenderProxyPtr, const ToDestroy>()
		.each([&](flecs::entity e, const Bullet& bullet, BulletLifeTime& lifeTime, RenderProxyPtr& renderProxy, const ToDestroy& destroy) // remove bullet after time
			{
				lifeTime.v -= e.delta_time();

				if (lifeTime.v <= 0.f)
				{
					delete renderProxy.ptr;
					e.destruct();
				}
			});


	static auto BulletQuery = ecs.query<const Position, const Bullet>();

	ecs.system<const Position, const Destroyable>()
		.each([&](flecs::entity e, const Position& pos, const Destroyable& destroyable) // add to remove destroyable objects
			{
				BulletQuery.each([&](const Position& bulletPos, const Bullet& bullet)
					{
						if (abs(bulletPos.y - pos.y) < 2.f && (abs(bulletPos.x - pos.x) < 2.f) && (abs(bulletPos.z - pos.z) < 2.f))
						{
							if (!e.has<ToDestroy>())
							{
								e.add<ToDestroy>();
							};
						}
					});
			});

	static auto ShouldBeDestroyedQuery = ecs.query <const Destroyable, const ToDestroy, const MoreBullet>();

	ecs.system<const Gun, CurrentBullet>()
		.each([&](const Gun& gun, CurrentBullet& curAmmo) // add ammonation after destroying
			{
				ShouldBeDestroyedQuery.each([&](const Destroyable& destroyable, const ToDestroy& destroy, const MoreBullet& more)
					{
						curAmmo.v += more.v;
					});
			});


	ecs.system<const Destroyable, const ToDestroy, RenderProxyPtr>() // remove destroyable objects
		.each([&](flecs::entity e, const Destroyable& destroyable, const ToDestroy& destroy, RenderProxyPtr& renderProxy)
			{
				delete renderProxy.ptr;
				e.destruct();
			});

}