#include "formula.h"

Formula::Formula()
{

}

float Formula::interpolation1D(float x, float x0, float x1, float y0, float y1) {
    return (y0 + (y1-y0) * ((x-x0) / (x1-x0)));
}

float Formula::interpolation2D(float x, float y, float x0, float x1, float y0, float y1, float q0, float q1, float q2, float q3) {
    float value1 = Formula::interpolation1D(x, x0, x1, q0, q1);
    float value2 = Formula::interpolation1D(x, x0, x1, q2, q3);
    return Formula::interpolation1D(y, y0, y1, value1, value2);
}

float Formula::interpolation3D(float x, float y, float z, float x_coords[2], float y_coords[2], float z_coords[2], float values[8]) {
    float value1 = Formula::interpolation2D(x, y, x_coords[0], x_coords[1], y_coords[0], y_coords[1], values[0], values[1], values[2], values[3]);
    float value2 = Formula::interpolation2D(x, y, x_coords[0], x_coords[1], y_coords[0], y_coords[1], values[4], values[5], values[6], values[7]);
    return Formula::interpolation1D(z, z_coords[0], z_coords[1], value1, value2);
}

void Formula::testInterpolation() {
    std::cout << "Test Interpolation1D: " << Formula::interpolation1D(8,5,10,0,255) << std::endl;
    std::cout << "Test Interpolation1D: " << Formula::interpolation2D((float)7.5,(float)7.5,(float)5,(float)10,(float)5,(float)10,(float)10,(float)20,(float)10,(float)20) << std::endl;

    float x_coords[2];
    float y_coords[2];
    float z_coords[2];
    float values[8];

    x_coords[0] = (float)0;
    y_coords[0] = (float)10;
    z_coords[0] = (float)0;
    x_coords[1] = (float)10;
    y_coords[1] = (float)0;
    z_coords[1] = (float)10;


    values[0] = (float)5;
    values[1] = (float)5;
    values[2] = (float)5;
    values[3] = (float)5;
    values[4] = (float)10;
    values[5] = (float)10;
    values[6] = (float)10;
    values[7] = (float)10;

    float x = (float)7.5;
    float y = (float)7.5;
    float z = (float)7.5;

    std::cout << "Test Interpolation1D: " << Formula::interpolation3D((float)5,(float)5,(float)5,x_coords,y_coords,z_coords,values) << std::endl;



}
