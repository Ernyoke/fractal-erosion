#ifndef FRACTALS_DIAMONDSQUAREFRACTAL_H
#define FRACTALS_DIAMONDSQUAREFRACTAL_H


#include "FractalResult.h"

class DiamondSquareFractal {
public:
    DiamondSquareFractal();

    virtual ~DiamondSquareFractal();

    FractalResult generate();

private:
    int grid_size;
    float **grid;

    void generateGrid(int seed = 0, float random_min = 0.0f, float random_max = 40.0f, float noise = 0.7f);

    void cleanUpGrid();
};


#endif //FRACTALS_DIAMONDSQUAREFRACTAL_H
