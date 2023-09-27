#pragma once

#include "GameObject.h"

class CubeGameObject : public GameObject
{
public:
	CubeGameObject();
    virtual void Move(float x, float t) override
    {
    }
private:
	
};
class JumpCubeGameObject final : public CubeGameObject
{
public:
    virtual void Move(float x, float t) override
    {
        //t = (float)sin(t);
        float v0 = 9.8f, a = -9.8f;
        while (t > 2) // very bad :( but dont know how do better
            t -= 2.0f;
        float s = v0 * t + a * t * t / 2;
        SetPosition(m_vPosition[0], s, m_vPosition[2]);
    }
};

class ControlCubeGameObject final : public CubeGameObject
{
public:
    virtual void Move(float x, float t) override
    {
        this->SetPosition(x+m_vPosition[0], m_vPosition[1], m_vPosition[2]);
    }
};

class RandomCubeGameObject final : public CubeGameObject
{
public:
    virtual void Move(float x, float t)
    {
        t = (float)cos(t)*2;
        this->SetPosition(t, m_vPosition[1], m_vPosition[2]);
    }
};

