#include "DiamondSquareFractal.h"

#include "MathHelper.h"
#include "MaterialHelper.h"

#include <memory>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

DiamondSquareFractal::DiamondSquareFractal()
        : grid_size{129},
          grid{nullptr} {
    generateGrid();
}

DiamondSquareFractal::~DiamondSquareFractal() {
    cleanUpGrid();
}

FractalResult DiamondSquareFractal::generate() {
    auto vertices = std::make_shared<std::vector<Vertex>>();
    auto size_float = static_cast<float>(grid_size);
    for (int y = 0; y < grid_size; y++) {
        auto y_float = static_cast<float>(y);
        for (int x = 0; x < grid_size; x++) {
            auto x_float = static_cast<float>(x);
            vertices->emplace_back(Vertex(
                    glm::vec3(
                            (x_float - (size_float / 2.0f)) * 0.25f,
                            (grid[x][y] / 2.0f) * 1.0f,
                            (y_float - (size_float / 2.0f)) * 0.25f),
                    glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
        }
    }

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

    std::vector<int> asd;
    float min = INT_MAX;
    float max = INT_MIN;

    for (const auto &vertex : *vertices) {
        float y = vertex.coordinates.y;
        if (y < min) {
            min = y;
        }
        if (y > max) {
            max = y;
        }
    }

    for (auto &vertex: *vertices) {
        vertex.color = MaterialHelper::getTerrainColorForHeight(vertex.coordinates.y, min, max);
    }

    return {vertices, indices};
}

void DiamondSquareFractal::generateGrid(int seed, float random_min, float random_max, float noise) {
    int s = grid_size - 1;
    if (!MathHelper::isPowerOf2(s) || random_min >= random_max) {
        return;
    }

    grid = new float *[grid_size];
    for (int i = 0; i < grid_size; i++)
        grid[i] = new float[grid_size];

    grid[0][0] = 0;
    grid[s][0] = 0;
    grid[0][s] = 0;
    grid[s][s] = 0;

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

void DiamondSquareFractal::cleanUpGrid() {
    if (grid) {
        for (int i = 0; i < grid_size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
    grid = nullptr;
}


