#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "model.h"

void initializeHairSimulation(const std::vector<Vertex>& vertices);
void updateHairSimulation(); // should update this later, right now no idea what all will be needed in this.

#endif