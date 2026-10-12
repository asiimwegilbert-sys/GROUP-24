#pragma once
#include "satellite_trajectory/vector.hpp"
namespace sat::orbit {
struct OrbitalState { sat::num::Vector position; sat::num::Vector velocity; double time{0.0}; };
}
