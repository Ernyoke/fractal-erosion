#include "DiamondSquareFractal.h"

#include "MathHelper.h"
#include "MaterialHelper.h"
#include "Mesh.h"

#include <memory>
#include <vector>

DiamondSquareFractal::DiamondSquareFractal(int grid_size)
        : grid_size{grid_size},
          grid{nullptr} {
}

DiamondSquareFractal::~DiamondSquareFractal() {
    cleanUpGrid<float>(grid);
}

Mesh DiamondSquareFractal::generateMesh() {
    auto vertices = computeVertices();
    auto indices = computeIndices();
    computeNormals(vertices, indices);
    computeTextureColors(vertices);

    return {vertices, indices};
}

void DiamondSquareFractal::generateGrid(int grid_size, int seed, float noise, float random_min, float random_max) {
    this->grid_size = grid_size;
    int s = grid_size - 1;
    if (!MathHelper::isPowerOf2(s) || random_min >= random_max) {
        return;
    }

    grid = createGrid<float>(0);

    /*
     * Use temporary named variables to simplify equations
     *
     * s0 . d0. s1
     *  . . . . .
     * d1 . cn. d2
     *  . . . . .
     * s2 . d3. s3
     *
     * */
    float s0, s1, s2, s3, d0, d1, d2, d3, cn;

    float mod_noise = 0.0f;
    for (int i = s; i > 1; i /= 2) {
        // reduce the random range at each step
        mod_noise = (random_max - random_min) * noise * ((float) i / (float) s);

        // diamonds
        for (int y = 0; y < s; y += i) {
            for (int x = 0; x < s; x += i) {
                s0 = grid[x][y];
                s1 = grid[x + i][y];
                s2 = grid[x][y + i];
                s3 = grid[x + i][y + i];

                // cn
                grid[x + (i / 2)][y + (i / 2)] =
                        ((s0 + s1 + s2 + s3) / 4.0f) + MathHelper::randRange(-mod_noise, mod_noise, seed);
            }
        }

        // squares
        for (int y = 0; y < s; y += i) {
            for (int x = 0; x < s; x += i) {
                s0 = grid[x][y];
                s1 = grid[x + i][y];
                s2 = grid[x][y + i];
                s3 = grid[x + i][y + i];
                cn = grid[x + (i / 2)][y + (i / 2)];

                d0 = y <= 0 ? (s0 + s1 + cn) / 3.0f : (s0 + s1 + cn + grid[x + (i / 2)][y - (i / 2)]) / 4.0f;
                d1 = x <= 0 ? (s0 + cn + s2) / 3.0f : (s0 + cn + s2 + grid[x - (i / 2)][y + (i / 2)]) / 4.0f;
                d2 = x >= s - i ? (s1 + cn + s3) / 3.0f :
                     (s1 + cn + s3 + grid[x + i + (i / 2)][y + (i / 2)]) / 4.0f;
                d3 = y >= s - i ? (cn + s2 + s3) / 3.0f :
                     (cn + s2 + s3 + grid[x + (i / 2)][y + i + (i / 2)]) / 4.0f;

                grid[x + (i / 2)][y] = d0 + MathHelper::randRange(-mod_noise, mod_noise, seed);
                grid[x][y + (i / 2)] = d1 + MathHelper::randRange(-mod_noise, mod_noise, seed);
                grid[x + i][y + (i / 2)] = d2 + MathHelper::randRange(-mod_noise, mod_noise, seed);
                grid[x + (i / 2)][y + i] = d3 + MathHelper::randRange(-mod_noise, mod_noise, seed);
            }
        }
    }
}

void DiamondSquareFractal::applyThermalErosion() {
    if (grid == nullptr) {
        return;
    }

    bool **grid_checked = createGrid<bool>(false);

    float peak = grid[0][0];
    float low = grid[0][0];

    // look for the highest point
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid[i][j] > peak) {
                peak = grid[i][j];
            }
            if (grid[i][j] < low) {
                low = grid[i][j];
            }
        }
    }
    float erosion_height = (peak - low) / 1000.0f;
    applyThermalErosionTonNeighbour(erosion_height);

    cleanUpGrid<bool>(grid_checked);
}

void DiamondSquareFractal::applyHydraulicErosion(float quantity, float sediment_factor) {
    if (grid == nullptr) {
        return;
    }

    std::vector<Peak> peaks;
    bool **grid_checked = createGrid<bool>(false);

    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (isPeak(grid[x][y], x, y)) {
                peaks.emplace_back(Peak{grid[x][y], x, y});
            }
        }
    }

    float **water_quantity = createGrid<float>(quantity);
    float **sediment_quantity = createGrid<float>(quantity * sediment_factor);

    for (const auto &peak : peaks) {
        applyHydraulicErosionFromPeak(peak, grid_checked, sediment_factor, water_quantity, sediment_quantity);
    }
    removeExcessWaterFromMargins(water_quantity);

    cleanUpGrid<float>(sediment_quantity);
    cleanUpGrid<float>(water_quantity);
    cleanUpGrid<bool>(grid_checked);
}

std::shared_ptr<std::vector<Vertex>> DiamondSquareFractal::computeVertices() {
    auto vertices = std::make_shared<std::vector<Vertex>>();
    auto size_float = static_cast<float>(grid_size);
    traverseGrid([this, &vertices, size_float](int y, int x) {
        auto y_float = static_cast<float>(y);
        auto x_float = static_cast<float>(x);
        vertices->emplace_back(Vertex{
                glm::vec3{
                        (x_float - (size_float / 2.0f)) * 0.25f,
                        (grid[x][y] / 2.0f) * 1.0f,
                        (y_float - (size_float / 2.0f)) * 0.25f
                },
                glm::vec4{0.0f, 0.0f, 0.0f, 0.0f},
                glm::vec3{0.0f, 1.0f, 0.0f}
        });
    });
    return vertices;
}

std::shared_ptr<std::vector<unsigned int>> DiamondSquareFractal::computeIndices() {
    auto indices = std::make_shared<std::vector<unsigned int>>();

    for (int y = 0; y < grid_size - 1; y++) {
        for (int x = 0; x < grid_size - 1; x++) {
            // tl - - tr
            //  | \   |
            //  |   \ |
            // bl - - br

            unsigned int tl = x + (y) * grid_size;
            unsigned int tr = (x + 1) + (y) * grid_size;
            unsigned int bl = x + (y + 1) * grid_size;
            unsigned int br = (x + 1) + (y + 1) * grid_size;

            // indices for first triangle
            indices->push_back(tl);
            indices->push_back(br);
            indices->push_back(bl);

            // indices for 2nd triangle
            indices->push_back(tl);
            indices->push_back(tr);
            indices->push_back(br);
        }
    }

    return indices;
}

void DiamondSquareFractal::computeNormals(std::shared_ptr<std::vector<Vertex>> &vertices,
                                          const std::shared_ptr<std::vector<unsigned int>> &indices) {
    for (int i = 0; i < indices->size(); i += 3) {
        int index0 = (*indices)[i];
        int index1 = (*indices)[i + 1];
        int index2 = (*indices)[i + 2];

        auto &vertex0 = (*vertices)[index0];
        auto &vertex1 = (*vertices)[index1];
        auto &vertex2 = (*vertices)[index2];

        auto v0 = vertex0.coordinates - vertex1.coordinates;
        auto v1 = vertex0.coordinates - vertex2.coordinates;

        auto normal = glm::normalize(glm::cross(v0, v1));

        vertex0.normal += normal;
        vertex1.normal += normal;
        vertex2.normal += normal;
    }

    for (Vertex &vertex: *vertices) {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

void DiamondSquareFractal::computeTextureColors(std::shared_ptr<std::vector<Vertex>> &vertices) {
    auto minmax = std::minmax_element(vertices->begin(), vertices->end(), [](const Vertex &a, const Vertex &b) {
        return a.coordinates.y < b.coordinates.y;
    });

    for (auto &vertex: *vertices) {
        vertex.color = MaterialHelper::getTerrainColorForHeight(vertex.coordinates.y,
                                                                minmax.first->coordinates.y,
                                                                minmax.second->coordinates.y);
    }
}

void DiamondSquareFractal::applyThermalErosionTonNeighbour(float erosion_height) {
    traverseGrid([this, erosion_height](int x, int y) {
        for (int i = -1; i <= 1; i++) {
            int position_x = x;
            int position_y = y;
            for (int j = -1; j <= 1; j++) {
                // check if neighbour is inside the matrix
                if (position_x + i >= 0 &&
                    position_x + i < grid_size &&
                    position_y + j >= 0 &&
                    position_y + j < grid_size) {
                    // check if material needs to be moved to the neighbour
                    if (grid[position_x + i][position_y + j] < grid[position_x][position_y]) {
                        grid[position_x + i][position_y + j] += erosion_height;
                        grid[position_x][position_y] -= erosion_height;
                    }
                }
            }
        }
    });
}

bool DiamondSquareFractal::isPeak(float value, int x, int y, bool upper) {
    bool isPeak = true;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // check if neighbour is inside the matrix
            if (x + i >= 0 &&
                x + i < grid_size &&
                y + j >= 0 &&
                y + j < grid_size) {
                if (upper) {
                    if (grid[x + i][y + j] > value) {
                        isPeak = false;
                        continue;
                    }
                } else {
                    if (grid[x + i][y + j] < value) {
                        isPeak = false;
                        continue;
                    }
                }
            }
        }
        if (!isPeak) {
            continue;
        }
    }
    return isPeak;
}

void DiamondSquareFractal::applyHydraulicErosionFromPeak(const Peak &peak, bool **grid_checked, float sediment_factor,
                                                         float **water_quantity, float **sediment_quantity) {
    grid_checked[peak.x][peak.y] = true;

    int neighbour_count = countNeighbours(peak);
    if (neighbour_count == 0) {
        return;
    }

    float kd = 0.1f;
    float kc = 5.0f;
    float ks = 0.3f;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (peak.x + i >= 0 &&
                peak.x + i < grid_size &&
                peak.y + j >= 0 &&
                peak.y + j < grid_size) {
                if (!(i == 0 || j == 0)) {
                    continue;
                }
                // we do this only if the peak is higher
                if (grid[peak.x][peak.y] > grid[peak.x + i][peak.y + j]) {
                    if (!isMargin(peak, i, j)) {
                        // 1. Move water from the peak to the neighbours
                        float height = grid[peak.x][peak.y];
                        float neighbour_height = grid[peak.x + i][peak.y + j];
                        float wt = moveWater(height, neighbour_height, water_quantity[peak.x][peak.y],
                                             water_quantity[peak.x + i][peak.y + j]);

                        if (wt > 0) {
                            water_quantity[peak.x][peak.y] -= wt;
                            water_quantity[peak.x + i][peak.y + j] += wt;

                            // 2. Move sediment to the neighbours
                            grid[peak.x][peak.y] -= wt * sediment_factor;
                            grid[peak.x + i][peak.y + j] += wt * sediment_factor;

                            float cs = kc * wt;

                            if (sediment_quantity[peak.x][peak.y] >= cs) {
                                sediment_quantity[peak.x + i][peak.y + j] += cs;
                                grid[peak.x][peak.y] += kd * (sediment_quantity[peak.x][peak.y] - cs);
                                sediment_quantity[peak.x][peak.y] = (1 - kd) * (sediment_quantity[peak.x][peak.y] - cs);
                            } else {
                                sediment_quantity[peak.x + i][peak.y + j] +=
                                        sediment_quantity[peak.x][peak.y] +
                                        ks * (cs - sediment_quantity[peak.x][peak.y]);
                                grid[peak.x][peak.y] += -ks * (cs - sediment_quantity[peak.x][peak.y]);
                                sediment_quantity[peak.x][peak.y] = 0;
                            }
                        } else {
                            grid[peak.x][peak.y] += ks * sediment_quantity[peak.x][peak.y];
                        }
                    } else {
                        water_quantity[peak.x + i][peak.y + j] = 0;
                        sediment_quantity[peak.x + i][peak.y + j] = 0;
                    }
                    if (!grid_checked[peak.x + i][peak.y + j]) {
                        applyHydraulicErosionFromPeak(Peak{
                                                              grid[peak.x + i][peak.y + j],
                                                              peak.x + i,
                                                              peak.y + j},
                                                      grid_checked,
                                                      sediment_factor,
                                                      water_quantity,
                                                      sediment_quantity);
                    }
                }
            }
        }
    }
}

float DiamondSquareFractal::moveWater(float height, float neighbour_height, float water_quantity,
                                      float water_quantity_neighbour) {
    return std::min(water_quantity, (water_quantity + height) - (water_quantity_neighbour + neighbour_height));
}

void DiamondSquareFractal::removeExcessWaterFromMargins(float **water_quantity) {
    std::vector<Peak> low_peaks;
    traverseGrid([this, &low_peaks](int x, int y) {
        if (isPeak(grid[x][y], x, y, false)) {
            low_peaks.emplace_back(Peak(grid[x][y], x, y));
        }
    });
    for (const auto &peak : low_peaks) {
        water_quantity[peak.x][peak.y] = 0.0f;
    }
}

int DiamondSquareFractal::countNeighbours(const Peak &peak) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (peak.x + i >= 0 &&
                peak.x + i < grid_size &&
                peak.y + j >= 0 &&
                peak.y + j < grid_size) {
                if (grid[peak.x + i][peak.y + j] < grid[peak.x][peak.y])
                    count++;
            }
        }
    }
    return count;
}

bool DiamondSquareFractal::isMargin(const Peak &peak, int i, int j) {
    return peak.x + i == 0 ||
           peak.x + i == grid_size ||
           peak.y + j == 0 ||
           peak.y + j == grid_size;
}

// Returns a pointer to a 2D grid of type T with every value initialized to `default_value`.
template<typename T>
T **DiamondSquareFractal::createGrid(T default_value) {
    auto **grid = new T *[grid_size];
    for (int i = 0; i < grid_size; i++) {
        grid[i] = new T[grid_size];
        for (int j = 0; j < grid_size; j++) {
            grid[i][j] = default_value;
        }
    }
    return grid;
}

// Cleans up the memory for a 2D grid. The size of the grid is expected to be `grid_size`.
template<typename T>
void DiamondSquareFractal::cleanUpGrid(T **grid) {
    if (grid) {
        for (int i = 0; i < grid_size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}

// Traverses a 2D grid with the size of `grid_size`. Applies the input function to every element of the grid.
void DiamondSquareFractal::traverseGrid(std::function<void(int, int)> func) {
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            func(x, y);
        }
    }
}


