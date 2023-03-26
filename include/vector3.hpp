#pragma once

struct Vector3
{
    public: 
    static double getDistance(Vector3 from, Vector3 to);

    Vector3 operator+(const Vector3& b) const;

    double x,y,z;
};