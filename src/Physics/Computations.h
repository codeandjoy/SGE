#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include <SFML/Graphics.hpp>
#include <functional>
struct ContinuousComputation;
class PhysicalObject;


std::function<void(PhysicalObject*, float)> updatePositionBasedOnVelocity();

std::function<void(PhysicalObject*, float)> updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit=sf::Vector2f(9999, 9999));


#endif