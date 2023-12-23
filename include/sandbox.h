#ifndef SANDBOX_H
#define SANDBOX_H
#include <vector>
#include <cstdio>
#include <cmath>
#include "./SFML/Graphics.hpp"
#include "./particle.h"
#include "./random.h"
#include "./slider.h"
#include "./button.h"

class SandBox {
  private:
    // application
    int WIDTH; // width of window
    int HEIGHT; // height of window
    int SIMWIDTH; // width for simulation box
    int SIMHEIGHT; // height for simulation box
    sf::Font font; // font for text
   
    // simulation 
    std::vector<Particle> particles; // list (array) of all particles
    Vector2 gravity; // gravity vector
    double restitution; // 0 < restitiution <= 1
    double dt; // simulation speed
    size_t numberOfParticles; // number of balls

  public:
    SandBox(); // Constructor
    void simulate(); // simulates the particles
    void collisionToWall(Particle& particles); // physics logic for ball to wall collision
    void collisionBallToBall(Particle& particle_1, Particle& particle_2, double restitution); // physics logic for ball to ball collision
    void run(); // main window loop, standard sfml
    void update(sf::RenderWindow& window); // update method
    void draw(sf::RenderWindow& window); // draw method
    void user_input(sf::RenderWindow& window); // checks user input, sliders, and buttons
    void reset(); // restarts the simulation
};
#endif // SANDBOX_H
