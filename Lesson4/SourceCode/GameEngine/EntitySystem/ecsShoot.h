#pragma once
#include "flecs.h"

struct Gun {};
struct Bullet {};
struct ShootCooldown { float v; };
struct CurrentShootCooldown { float v; };
struct Reload { float v; };
struct CurrentReload { float v; };
struct MaxBullet { int v; };
struct CurrentBullet { int v; };
struct MoreBullet { int v; };
struct BulletSpeed { float v; };
struct BulletLifeTime { float v; };
struct ToDestroy { };


void register_ecs_shoot_systems(flecs::world& ecs);