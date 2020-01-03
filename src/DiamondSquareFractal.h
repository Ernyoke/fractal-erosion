#ifndef FRACTALS_DIAMONDSQUAREFRACTAL_H
#define FRACTALS_DIAMONDSQUAREFRACTAL_H

#include "Mesh.h"

#include<functional>

struct Peak {
    float value;
    int x;
    int y;

    Peak(float value, int x, int y) : value{value}, x{x}, y{y} {
    }
};

class DiamondSquareFractal {
public:
    explicit DiamondSquareFractal(int grid_size = 129);

    DiamondSquareFractal(const DiamondSquareFractal &display) = delete;

    DiamondSquareFractal &operator=(const DiamondSquareFractal &display) = delete;

    virtual ~DiamondSquareFractal();

    Mesh generateMesh();

    void generateGrid(int grid_size, int seed, float noise, float random_min = 0.0f, float random_max = 40.0f);

    void applyThermalErosion();

    void applyHydraulicErosion(float quantity, float sediment_factor);

private:
    int grid_size;
    float **grid;

    std::shared_ptr<std::vector<Vertex>> computeVertices();

    std::shared_ptr<std::vector<unsigned int>> computeIndices();

    static void computeNormals(std::shared_ptr<std::vector<Vertex>> &vertices,
                               const std::shared_ptr<std::vector<unsigned int>> &indices);

    static void computeTextureColors(std::shared_ptr<std::vector<Vertex>> &vertices);

    void applyThermalErosionTonNeighbour(float erosion_height);

    bool isPeak(float value, int x, int y, bool upper = true);

    void applyHydraulicErosionFromPeak(const Peak &peak, bool **grid_checked, float sediment_factor,
                                       float **water_quantity, float **sediment_quantity);

    static float moveWater(float height, float neighbour_height, float water_quantity, float water_quantity_neighbour);

    void removeExcessWaterFromMargins(float **water_quantity);

    int countNeighbours(const Peak &peak);

    bool isMargin(const Peak &peak, int i, int j);

    // utility methods
    template<typename T>
    T **createGrid(T default_value);

    template<typename T>
    void cleanUpGrid(T **grid);

    void traverseGrid(std::function<void(int, int)>);
};


#endif //FRACTALS_DIAMONDSQUAREFRACTAL_H
