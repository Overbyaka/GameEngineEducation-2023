#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, ScriptProxy* scriptProxy)
{
    doc.LoadFile("../../../Assets/XML/entity.xml");
    //int i = doc.ErrorID();
    //std::cout << i;
    
    ecs.entity("scriptProxy")
        .set(ScriptProxyPtr{ scriptProxy });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    /*auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .add<CubeMesh>();

    auto cubeMoving = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 1.f })
        .add<CubeMesh>(); */

    tinyxml2::XMLElement* pRootElement = doc.RootElement();

    if (NULL != pRootElement)
    {
        tinyxml2::XMLElement* pEntity = pRootElement->FirstChildElement("Entity");
        while (pEntity)
        {
                auto entity = ecs.entity();

                tinyxml2::XMLElement* pPositionX = pEntity->FirstChildElement("PositionX");
                tinyxml2::XMLElement* pPositionY = pEntity->FirstChildElement("PositionY");
                tinyxml2::XMLElement* pPositionZ = pEntity->FirstChildElement("PositionZ");
                if (NULL != pPositionX && NULL != pPositionY && NULL != pPositionZ)
                {
                    float x, y, z;
                    pPositionX->QueryFloatText(&x);
                    pPositionY->QueryFloatText(&y);
                    pPositionZ->QueryFloatText(&z);
                    entity.set(Position{x, y, z});
                }
                tinyxml2::XMLElement* pVelocityX = pEntity->FirstChildElement("VelocityX");
                tinyxml2::XMLElement* pVelocityY = pEntity->FirstChildElement("VelocityY");
                tinyxml2::XMLElement* pVelocityZ = pEntity->FirstChildElement("VelocityZ");
                if (NULL != pVelocityX && NULL != pVelocityY && NULL != pVelocityZ)
                {
                    float x, y, z;
                    pVelocityX->QueryFloatText(&x);
                    pVelocityY->QueryFloatText(&y);
                    pVelocityZ->QueryFloatText(&z);
                    entity.set(Velocity{x, y, z});
                }
                tinyxml2::XMLElement* pSpeed = pEntity->FirstChildElement("Speed");
                if (NULL != pSpeed) {
                    float speed;
                    pSpeed->QueryFloatText(&speed);
                    entity.set(Speed{speed});
                }
                tinyxml2::XMLElement* pFrictionAmount = pEntity->FirstChildElement("FrictionAmount");
                if (NULL != pFrictionAmount) {
                    float frictionAmount;
                    pFrictionAmount->QueryFloatText(&frictionAmount);
                    entity.set(FrictionAmount{frictionAmount});
                }
                tinyxml2::XMLElement* pJumpSpeed = pEntity->FirstChildElement("JumpSpeed");
                if (NULL != pJumpSpeed) {
                    float jumpSpeed;
                    pJumpSpeed->QueryFloatText(&jumpSpeed);
                    entity.set(JumpSpeed{jumpSpeed});
                }
                tinyxml2::XMLElement* pGravityX = pEntity->FirstChildElement("GravityX");
                tinyxml2::XMLElement* pGravityY = pEntity->FirstChildElement("GravityY");
                tinyxml2::XMLElement* pGravityZ = pEntity->FirstChildElement("GravityZ");
                if (NULL != pGravityX && NULL != pGravityY && NULL != pGravityZ)
                {
                    float x, y, z;
                    pGravityX->QueryFloatText(&x);
                    pGravityY->QueryFloatText(&y);
                    pGravityZ->QueryFloatText(&z);
                    entity.set(Gravity{x, y, z});
                }
                tinyxml2::XMLElement* pBouncePlaneX = pEntity->FirstChildElement("BouncePlaneX");
                tinyxml2::XMLElement* pBouncePlaneY = pEntity->FirstChildElement("BouncePlaneY");
                tinyxml2::XMLElement* pBouncePlaneZ = pEntity->FirstChildElement("BouncePlaneZ");
                tinyxml2::XMLElement* pBouncePlaneW = pEntity->FirstChildElement("BouncePlaneW");
                if (NULL != pBouncePlaneX && NULL != pBouncePlaneY && NULL != pBouncePlaneZ && NULL != pBouncePlaneW)
                {
                    float x, y, z, w;
                    pBouncePlaneX->QueryFloatText(&x);
                    pBouncePlaneY->QueryFloatText(&y);
                    pBouncePlaneZ->QueryFloatText(&z);
                    pBouncePlaneW->QueryFloatText(&w);
                    entity.set(BouncePlane{x, y, z, w});
                }
                tinyxml2::XMLElement* pBounciness = pEntity->FirstChildElement("Bounciness");
                if (NULL != pBounciness) {
                    float bounciness;
                    pBounciness->QueryFloatText(&bounciness);
                    entity.set(Bounciness{bounciness });
                }
                tinyxml2::XMLElement* pControllable = pEntity->FirstChildElement("Controllable");
                if (NULL != pControllable) {
                    entity.add<Controllable>();
                }
                tinyxml2::XMLElement* pCubeMesh = pEntity->FirstChildElement("CubeMesh");
                if (NULL != pCubeMesh) {
                    entity.add<CubeMesh>();
                }

                pEntity = pEntity->NextSiblingElement("Entity");
        }
    }
     
}

void EntitySystem::Update()
{
    ecs.progress();
}