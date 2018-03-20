#include "SDL.h"
#include <random>
#include <vector>
#include "Vec3.h"
#include "primitives/Sphere.h"
#include "primitives/Triangle.h"
#include "primitives/BasePrimitive.h"
#include <math.h>
#include "PointLight.h"
#include "Material.h"

#include <cstdlib>
#include <iostream>

int WIDTH = 1366,
    HEIGHT = 740,
    D = 1,
    REFLECT_DEPTH_LIMIT = 2;

Color BACKGROUND_COLOR = Color(0, 0, 0);//Color(29, 33, 36);
Color AMBIENT = Color(0, 5, 10);
std::vector<Triangle> spheres;
std::vector<PointLight> lightSources;


inline double max(const double &a, const double &b) {
    if (a > b) return a;
    return b;
}

inline double min(const double &a, const double &b) {
    if (a < b) return a;
    return b;
}

void StoW(const int &Sx, const int &Sy, double &Cx, double &Cy) {
    Cx = Sx;
    Cy = Sy;

    Cx = Cx - double(WIDTH) / 2.0;
    Cy = -(Cy - double(HEIGHT) / 2.0);

    return;
}


bool findIntersection(const Vec3 &O, const Vec3 &R,
                      double &closest_t, int &closest_sphere) {
    double t;
    bool is_intersected;
    closest_t = CLIPPING_DIST;

    for(size_t i = 0; i < spheres.size(); i += 1) {
        is_intersected = spheres[i].intersect(O, R, t);

        if (!is_intersected) continue;

        if (t < closest_t && t > FLOAT_PRECISION) {
            closest_t = t;
            closest_sphere = i;
        }
    }

    return closest_t < CLIPPING_DIST - FLOAT_PRECISION;
}


Color calculateLighting(const Vec3 &P, const Vec3 &V, Triangle sph) {
    Vec3 R = lightSources[0].position - P;
    Vec3 N = sph.normal(P);

    Color I = AMBIENT;

    double t;
    int sph_id;
    bool is_in_shadow = findIntersection(P, R, t, sph_id);
    if (!is_in_shadow) {
        Material mat = sph.mat;
        I = AMBIENT;
        I += mat.diffuseColor * pcos(N, R);
        I += Color(255, 255, 255) * pow(pcos(R, V), mat.specular);
    }

    return I;
}


Color traceRay(const Vec3 &O, const Vec3 &R) {
    double t = 0;
    int sph_id;

    bool is_intersected = findIntersection(O, R, t, sph_id);
    if (!is_intersected) return BACKGROUND_COLOR;

    Color c = calculateLighting(O + t * R, R, spheres[sph_id]);
    return c;
}


void loadGeometry() {
    Vec3 A = Vec3(1.135053, -0.131832, 6.269258);
    Vec3 B = Vec3(-0.420450, -0.418204, 6.162949);
    Vec3 C = Vec3(-0.065169, 1.113089, 6.367437);
    Vec3 D = Vec3(0.191465, 0.273355, 4.874459);

    Vec3 P = Vec3(100, -2, 100);
    Vec3 Q = Vec3(-100, -2, 100);
    Vec3 R = Vec3(-100, -2, -100);
    Vec3 S = Vec3(100, -2, -100);

    Material mat = Material(Color(242, 76, 39), 10, 0);

    spheres.push_back(Triangle(P, Q, R, Vec3(0, 1, 0), mat));
    spheres.push_back(Triangle(P, S, R, Vec3(0, 1, 0), mat));
    spheres.push_back(Triangle(C, B, D, Vec3(-0.919400, 0.253500, 0.300600), mat));
    spheres.push_back(Triangle(A, B, C, Vec3(-0.045300, -0.121900, -0.991500), mat));
    spheres.push_back(Triangle(D, B, A, Vec3(0.192400, -0.899800, 0.391600), mat));
    spheres.push_back(Triangle(A, C, D, Vec3(0.683700, 0.680000, 0.265000), mat));

    lightSources.push_back(PointLight(Vec3(2, 3, 6), Color(255, 255, 255)));
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Stupid Renderer", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderClear(renderer);

    loadGeometry();

    Vec3 O = Vec3(0, 0, 0);
    double biggest_window_side = max(WIDTH, HEIGHT);

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; j++) {
            double Cx, Cy;
            StoW(i, j, Cx, Cy);
            Vec3 R = Vec3(Cx / biggest_window_side, Cy / biggest_window_side, 1) * D;

            Color c = traceRay(O, normalize(R));
            SDL_SetRenderDrawColor(renderer, c.r(), c.g(), c.b(), SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event) >= 0) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
