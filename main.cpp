#include "SDL.h"
#include <random>
#include <vector>
#include "Vec3.h"
#include "Sphere.h"
#include <math.h>

int WIDTH = 900,
    HEIGHT = 600,
    D = 1,
    REFLECT_DEPTH_LIMIT = 2;
double CLIPPING_DIST = 10000000.0;

Color BACKGROUND_COLOR = Color(0, 0, 0);//Color(29, 33, 36);
std::vector<Sphere> spheres;


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


bool intersectRaySphere(const Vec3 &O, const Vec3 &R, const Sphere &sphere, double &t0, double &t1) {
    Vec3 C = O - sphere.center;

    double k1 = dot(R, R),
            k2 = 2 * dot(C, R),
            k3 = dot(C, C) - sphere.radius * sphere.radius;

    double det = k2 * k2 - 4 * k1 * k3;
    if (det < 0) return false;

    t0 = (-k2 - sqrt(det)) / 2 / k1;
    t1 = (-k2 + sqrt(det)) / 2 / k1;
    return true;
}


bool findIntersection(const Vec3 &O, const Vec3 &R,
                      double &closest_t, int &closest_sphere) {
    double t0, t1;
    bool is_intersected;
    closest_t = CLIPPING_DIST;

    for(size_t i = 0; i < spheres.size(); i += 1) {
        is_intersected = intersectRaySphere(O, R, spheres[i], t0, t1);

        if (!is_intersected) continue;

        if (t0 < closest_t && t0 >= 0) {
            closest_t = t0;
            closest_sphere = i;
        }
        if (t1 < closest_t && t1 >= 0) {
            closest_t = t1;
            closest_sphere = i;
        }
    }

    return (closest_t != CLIPPING_DIST);
}


Color traceRay(const Vec3 &O, const Vec3 &R) {
    double t = 0;
    int sph_id;

    bool is_intersected = findIntersection(O, R, t, sph_id);

    if (!is_intersected) return BACKGROUND_COLOR;

    Color c;

    // if depth map
    double temp = 20.0;
    double comp = pow(max(0.0, temp - t) / temp, 3.0) * 255.0;
    c = Color(comp, comp, comp);

    // if normal render
    c = spheres[sph_id].color;
    return c;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Stupid Renderer", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderClear(renderer);

    spheres.push_back(Sphere(0, -1, 5, 1, Color(242, 76, 39), 10, 0.9));
    spheres.push_back(Sphere(-1, 1, 6, 1, Color(86, 185, 208), 500, 0.3));
    spheres.push_back(Sphere(2, 1, 5, 1, Color(242, 76, 39), 10, 0));
    spheres.push_back(Sphere(0, -5001, 0, 5000, Color(251, 186, 66), 1000, 0.1));

    Vec3 O = Vec3(0, 0, 0);
    double biggest_window_side = max(WIDTH, HEIGHT);

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; j++) {
            double Cx, Cy;
            StoW(i, j, Cx, Cy);
            Vec3 R = Vec3(Cx / biggest_window_side, Cy / biggest_window_side, 1) * D;

            Color c = traceRay(O, R);
            SDL_SetRenderDrawColor(renderer, c.r(), c.g(), c.b(), SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
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