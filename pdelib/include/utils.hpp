#pragma once

#include "defines.hpp"
#include "vector.hpp"

namespace pde
{

/*
 * Linear interpolation
 */
real lerp(interval i, real t);

/*
 * Absolute value
 */
real abs(real x);

/*
 * Evaluates function f at domain with step delta
 */
vector eval(interval domain, function f, real delta);

/*
 * Creates vector filld with zeros
 */
vector zeros(size_t len);

/*
 * Creates vector with evenly spaced numbers
 */
vector linspace(interval domain, real delta);

} // namespace pde
