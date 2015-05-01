/**
 * \file Perlin.h
 * \brief Perlin
 * \author HABIBI Arash
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#ifndef _PERLIN_H_
#define _PERLIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vector.h"

#define PRLN_000 0
#define PRLN_100 1
#define PRLN_010 2
#define PRLN_110 3
#define PRLN_001 4
#define PRLN_101 5
#define PRLN_011 6
#define PRLN_111 7


//double PRLN_scalarNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain);
//Vector PRLN_vectorNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain);
double PRLN_scalarNoise(Vector p);
Vector PRLN_vectorNoise(Vector p);

#endif

