#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "../ScriptSystem/ScriptProxy.h"

void init_script(flecs::world& ecs, sol::state& lua, Velocity vel, Speed spd, Position pos, BouncePlane plane, JumpSpeed jumpconst, float dt)
{
    lua = NULL;
    lua["vel_x"] = vel.x;
    lua["vel_y"] = vel.y;
    lua["speed"] = spd;
    lua["pos_x"] = pos.x;
    lua["pos_y"] = pos.y;
    lua["pos_z"] = pos.z;
    lua["plane_x"] = plane.x;
    lua["plane_y"] = plane.y;
    lua["plane_z"] = plane.z;
    lua["plane_w"] = plane.w;
    lua["jump_speed"] = jumpconst.val;
    lua["delta_time"] = dt;
}
void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<ScriptProxyPtr>();
  ecs.system<Velocity, const Speed, const Position, const BouncePlane, const JumpSpeed, const Controllable>()
    .each([&](flecs::entity e, Velocity& vel, const Speed& spd, const Position& pos, const BouncePlane& plane, const JumpSpeed& jumpconst, const Controllable &)
    {
      inputQuery.each([&](ScriptProxyPtr input)
      {
              init_script(ecs, input.ptr->GetLua(), vel, spd, pos, plane, jumpconst, e.delta_time());
              input.ptr->ScriptMove();
              input.ptr->Init("../../../Assets/scripts/movable.lua");
              sol::state &lua = input.ptr->GetLua();
              vel.x = lua["vel_x"];
              vel.y = lua["vel_y"];
      });
    });
}


