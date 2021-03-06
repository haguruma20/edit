#ifndef SPHERE_FUNCTIONS_H_
#define SPHERE_FUNCTIONS_H_

// Copyright 2015 haguruma20

// This function computes the maximum edge length from std::vector<Sphere>,
// which is defined in Sphere.h
#include "Sphere.h"
#include <iostream>
#include <algorithm>
#include <vector>

double spheres_max_edge_size(const std::vector<Sphere>& Sphere_vector) {
  double max_edge_length = 0;
  int system_number = Sphere_vector.size();
  for (auto i = 0; i < system_number; ++i) {
    for (auto j = i + 1; j < system_number; ++j) {
      max_edge_length = std::max(max_edge_length,
                                 distance(Sphere_vector.at(i).center(),
                                          Sphere_vector.at(j).center()));
    }
  }
  return max_edge_length;
}

double tetrahedral_spheres_max_edge_size(
    const std::vector<Sphere>& Sphere_vector) {
  double max_edge_length = 0;
  int system_number = Sphere_vector.size();

  if (system_number != 4) {
    std::cout << "Input data is not tetrahedral." << std::endl;
    throw;
  }

  for (auto i = 0; i < system_number; ++i) {
    for (auto j = i + 1; j < system_number; ++j) {
      max_edge_length = std::max(max_edge_length,
                                 distance(Sphere_vector.at(i).center(),
                                          Sphere_vector.at(j).center()));
    }
  }
  return max_edge_length;
}

double octahedral_spheres_max_edge_size(
    const std::vector<Sphere>& Sphere_vector) {
  double max_edge_length = 0;
  double second_max_edge_length = 0;
  int system_number = Sphere_vector.size();

  if (system_number != 6) {
    std::cout << "Input data is not tetrahedral." << std::endl;
    throw;
  }

  for (auto i = 0; i < system_number; ++i) {
    for (auto j = i + 1; j < system_number; ++j) {
      double dist = distance(Sphere_vector.at(i).center(),
                             Sphere_vector.at(j).center());
      if (max_edge_length < dist) {
        second_max_edge_length = max_edge_length;
        max_edge_length = dist;
      }
    }
  }
  return second_max_edge_length;
}

#endif  // SPHERE_FUNCTIONS_H_
