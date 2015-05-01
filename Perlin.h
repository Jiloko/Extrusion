/************************
Author : Gwenaël Larmet
Perlin.h
*************************/

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

