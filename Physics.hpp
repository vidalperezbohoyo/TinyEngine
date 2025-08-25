#pragma once

namespace console
{

struct Vector3
{
    float x;
    float y;
    float z;
};

class Physics
{
    void check();

    void setParticlePosition(const Vector3& position);

    void setParticleVelocity(const Vector3& velocity);

private:

    Vector3 particle_position_;
    Vector3 particle_velocity_;

    Vector3 gravity_;
};
}