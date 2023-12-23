#include "./sandbox.h"

SandBox::SandBox()
    : gravity(0.0, 0.0) {

  // width and height for window
  WIDTH = 1000;
  HEIGHT = 800;

  // width and height for simulation box
  SIMWIDTH = WIDTH - 50; // border right 50 pixel between simwall and window screen
  SIMHEIGHT = HEIGHT - 50; // border at the bottom 50 pixel between simwall and winodw screen

  dt = 1.0 / 60.0; // simulation speed
  restitution = 1.0; // ratio of the relative velocity of seperation after collision

  // load relevant fonts
  if (!font.loadFromFile("fonts/monitorica.ttf"))
    printf("Error loading font\n");

  numberOfParticles = 1000;
  for (size_t particle_i = 0; particle_i < numberOfParticles; particle_i++) {
    double particleRadius = 10;
    double particleMass = M_PI * particleRadius * particleRadius; // mass in kg
    Vector2 particlePosition = getRandomVector(SIMWIDTH, SIMHEIGHT);   // create ball position vector
    Vector2 particleVelocity = getRandomVelocity(); // create ball velocity vector
    sf::Color particleColor = sf::Color::Blue;     // create ball color
    Particle particle(particleRadius, particleMass, particlePosition, particleVelocity, particleColor);  // create ball
    particles.push_back(particle); // add ball to the ball list
  }
}

void SandBox::draw(sf::RenderWindow &window) {
  // create simulation box lines
  sf::Vertex lines[] = {
      sf::Vertex(sf::Vector2f(50, 100)),  // Line 1 start (top)
      sf::Vertex(sf::Vector2f(950, 100)), // Line 1 end

      sf::Vertex(sf::Vector2f(50, 750)),  // Line 2 start (bottom)
      sf::Vertex(sf::Vector2f(950, 750)), // Line 2 end

      sf::Vertex(sf::Vector2f(50, 100)), // Line 3 start (left)
      sf::Vertex(sf::Vector2f(50, 750)), // Line 3 end

      sf::Vertex(sf::Vector2f(950, 100)),  // Line 4 start (right)
      sf::Vertex(sf::Vector2f(950, 750))}; // Line 4 end

  // draw balls
  for (size_t particle_i = 0; particle_i < particles.size(); particle_i++) {
    Particle particle = particles[particle_i];
    sf::CircleShape particle_shape(particle.radius);
    particle_shape.setFillColor(particle.color);
    particle_shape.setPosition(particle.position.x - particle.radius, particle.position.y - particle.radius);
    window.draw(particle_shape);
  }
  // draw lines
  window.draw(lines, 8, sf::Lines);
}

void SandBox::simulate() {
  for (size_t particle_i = 0; particle_i < particles.size(); particle_i++) {
    particles[particle_i].simulate(gravity, dt);

    for (size_t particle2_i = particle_i + 1; particle2_i < particles.size(); particle2_i++) {
      collisionBallToBall(particles[particle_i], particles[particle2_i], restitution);
    }
    collisionToWall(particles[particle_i]);
  }
}

void SandBox::collisionToWall(Particle &particle) {
  // Check collision with top wall
  if (particle.position.x < particle.radius + 50) {
    particle.position.x = particle.radius + 50;
    particle.velocity.x = -particle.velocity.x;
  }
  // Check collision with bottom wall
  if (particle.position.x > SIMWIDTH - 1 * particle.radius) {
    particle.position.x = SIMWIDTH - 1 * particle.radius;
    particle.velocity.x = -particle.velocity.x;
  }
  // Ceck collision with left wall
  if (particle.position.y <  particle.radius + 100) {
    particle.position.y = particle.radius + 100;
    particle.velocity.y = -particle.velocity.y;
  }
  // Check collision with right wall
  if (particle.position.y > SIMHEIGHT - 1 * particle.radius) {
    particle.position.y = SIMHEIGHT - 1 * particle.radius;
    particle.velocity.y = -particle.velocity.y;
  }
}

void SandBox::collisionBallToBall(Particle& particle_1, Particle& particle_2, double restitution) {
  
  // Physics
  Vector2 direction(0.0, 0.0);
  direction.subVectors(particle_2.position, particle_1.position); // new direction after collision
  double direction_length = direction.length(); // length of direction

  if (direction_length == 0.0 || direction_length > particle_1.radius + particle_2.radius) {
    return; // no collision
  }
  
  direction.scaleVector(1.0 / direction_length); // normalize direction vector
  
  double corr = (particle_1.radius + particle_2.radius - direction_length) / 2.0;
  particle_1.position.add(direction, -corr);
  particle_2.position.add(direction, corr);

  double v1 = particle_1.velocity.dot(direction);
  double v2 = particle_2.velocity.dot(direction);

  double m1 = particle_1.mass;
  double m2 = particle_2.mass;

  double newV1 = (m1 * v1 + m2 * v2 - m2 * (v1 - v2) * restitution) / (m1 + m2);
  double newV2 = (m1 * v1 + m2 * v2 - m1 * (v2 - v1) * restitution) / (m1 + m2);

  particle_1.velocity.add(direction, newV1 - v1);
  particle_2.velocity.add(direction, newV2 - v2);
}

void SandBox::update(sf::RenderWindow &window) {
  window.clear();
  simulate();
  draw(window);
  user_input(window);
  window.display();
}

void SandBox::user_input(sf::RenderWindow &window) {

}

void SandBox::run() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ideal gas law - physics simulation");
  // standard sfml window loop 
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    update(window);
  }
}

void SandBox::reset() {
  gravity = Vector2(0.0, 0.0);
  restitution = 1.0;

  particles.clear(); // delete every ball in balls
  numberOfParticles = 1000; // number of balls in simulation
  
  // create new balls
  for (size_t particle_i = 0; particle_i < numberOfParticles; particle_i++) {
    double particleRadius = getRandomRadius(); // create ball radius
    Vector2 particlePosition = getRandomVector(SIMWIDTH, SIMHEIGHT);   // create ball position vector
    Vector2 particleVelocity = getRandomVelocity(); // create ball velocity vector
    sf::Color particleColor = sf::Color::Blue;     // create ball color
    Particle particle(particleRadius, 1.0, particlePosition, particleVelocity, particleColor);  // create ball
    particles.push_back(particle); // add ball to balls vector
  }
}
