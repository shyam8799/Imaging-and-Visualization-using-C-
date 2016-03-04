#ifndef FORMULA_H
#define FORMULA_H

#include <iostream>

class Formula
{
public:
    Formula();

    static float interpolation1D(float x, float x0, float x1, float y0, float y1);
    static float interpolation2D(float x, float y, float x0, float x1, float y0, float y1, float q0, float q1, float q2, float q3);
    static float interpolation3D(float x, float y, float z, float x_coords[2], float y_coords[2], float z_coords[2], float values[8]);
    static void testInterpolation();
};

#endif // FORMULA_H
