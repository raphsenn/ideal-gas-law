#ifndef PARTICLE_H
#define PARTICLE_H
#include "./vector2.h"
#include "./SFML/Graphics.hpp"
#include "./random.h"

class Particle {
  private:
    // no private methods or attributes

  public:
    Particle(double rad, double m, Vector2 pos, Vector2 vel, sf::Color col); // Constructor
    double radius; // radius of particle
    double mass; // mass of particle
    Vector2 position; // 2d vector for current position
    Vector2 velocity; // 2d vector for current velocity and direction
    sf::Color color; // color of ball
    void simulate(Vector2 gravity, double dt); // simulate particle movement
};
#endif // PARTICLE_H
