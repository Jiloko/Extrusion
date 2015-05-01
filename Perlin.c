/**
 * \file Perlin.c
 * \brief Perlin
 * \author SCHIMCHOWITSCH Raphael
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

#include "Perlin.h"

//-----------------------------------------------------------

static Vector _vectorInterpolate(Vector v1, Vector v2, double blend)
{
	return V_add( V_multiply(1-blend,v1), V_multiply(blend,v2)); 
}

//-----------------------------------------------------------
// This is a polynomial function which :
// - for x=0 yields y=0
// - for x=1 yields y=1
// - for x=0 and x=1 has a zero first derivative.

static double _contrast(double x)
{
	return x*x*(3-2*x);
}

//-----------------------------------------------------------
// For alpha=0, the return value is x
// For alpha=1, the return value is y
// For intermediate values -> interpolation

//-----------------------------------------------------------

static double _scalarCubicInterpolate(Vector p, double *grid_values)
{
	double res, fx,fy,fz; // fractional part

	int nx = (int)(floor(p.x)); 
	int ny = (int)(floor(p.y));
	int nz = (int)(floor(p.z));

	fx = p.x - nx;
	fy = p.y - ny;
	fz = p.z - nz;

	fx = _contrast(fx);
	fy = _contrast(fy);
	fz = _contrast(fz);

	res=0.0;

	res += (1-fx)*(1-fy)*(1-fz)*grid_values[PRLN_000];
	res +=   fx  *(1-fy)*(1-fz)*grid_values[PRLN_100];
	res += (1-fx)*  fy  *(1-fz)*grid_values[PRLN_010];
	res +=   fx  *  fy  *(1-fz)*grid_values[PRLN_110];
	res += (1-fx)*(1-fy)*  fz  *grid_values[PRLN_001];
	res +=   fx  *(1-fy)*  fz  *grid_values[PRLN_101];
	res += (1-fx)*  fy  *  fz  *grid_values[PRLN_011];
	res +=   fx  *  fy  *  fz  *grid_values[PRLN_111];

	return res;
}

//-----------------------------------------------------------

static Vector _vectorLinearInterpolate(Vector p, Vector *grid_vectors)
{
	double fx,fy,fz; // fractional part

	int nx = (int)(floor(p.x));
	int ny = (int)(floor(p.y));
	int nz = (int)(floor(p.z));

	fx = p.x - nx; 
	fy = p.y - ny; 
	fz = p.z - nz; 

	fx = _contrast(fx);
	fy = _contrast(fy);
	fz = _contrast(fz);

	Vector interp_y0z0 = _vectorInterpolate(grid_vectors[PRLN_000],grid_vectors[PRLN_100],fx);
	Vector interp_y1z0 = _vectorInterpolate(grid_vectors[PRLN_010],grid_vectors[PRLN_110],fx);
	Vector interp_y0z1 = _vectorInterpolate(grid_vectors[PRLN_001],grid_vectors[PRLN_101],fx);
	Vector interp_y1z1 = _vectorInterpolate(grid_vectors[PRLN_011],grid_vectors[PRLN_111],fx);

	Vector interp_z0 = _vectorInterpolate(interp_y0z0,interp_y1z0,fy);
	Vector interp_z1 = _vectorInterpolate(interp_y0z1,interp_y1z1,fy);

	Vector interp_vector = _vectorInterpolate(interp_z0,interp_z1,fz);

	return interp_vector;
}


//-----------------------------------------------------------

static void _computeDotProducts(Vector p, Vector *random_vectors, double *dot_products)
{
	int nx = (int)(floor(p.x));
	int ny = (int)(floor(p.y));
	int nz = (int)(floor(p.z));

	int i;
	for(i=0;i<8;i++)
	{
		int nnx=nx,nny=ny,nnz=nz;
		if(i>=4) nnz++;
		if(i%4 > 1) nny++;
		if(i%2 > 0) nnx++;
		Vector A = V_new(nnx,nny,nnz);
		Vector Ap = V_substract(p,A);
		dot_products[i] = V_dot(random_vectors[i],Ap);
	}
}

//-----------------------------------------------------------

static void _computeCrossProducts(Vector p, Vector *random_vectors, Vector *cross_products)
{
	int nx = (int)(floor(p.x));
	int ny = (int)(floor(p.y));
	int nz = (int)(floor(p.z));

	int i;
	for(i=0;i<8;i++)
	{
		int nnx=nx,nny=ny,nnz=nz;
		if(i>=4) nnz++;
		if(i%4 > 1) nny++;
		if(i%2 > 0) nnx++;
		Vector A = V_new(nnx,nny,nnz);
		Vector Ap = V_substract(p,A);
		cross_products[i] = V_cross(random_vectors[i],Ap);
	}
}

//-----------------------------------------------------------

static double myRand(long int x)
{
	x = (x<<13) ^ x;
	return 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
}

//-----------------------------------------------------------
// 2^32 = (approximately) 2^11 * 2^11 * 2^10
// If we don't want to have the same seed for two different
// points in space we have to write :
// seed = 2^11*2^11*nx + 2^11*ny + nz
// Even better, instead of 2^11*2^11 and 2^10, we could find
// prime numbers in those vicinities.

static Vector _computeRandomVector(int nx, int ny, int nz)
{
	long seed = 2097013*nx+2039*ny+nz;
	double x = myRand(seed);
	double y = myRand(seed+1);
	double z = myRand(seed+2);
	Vector v_rand = V_new(x,y,z);
	return V_unit(v_rand);
}

//-----------------------------------------------------------

static void _computeRandomVertexVectors(Vector p, Vector *v_rand)
{
	int nx = (int)(floor(p.x));
	int ny = (int)(floor(p.y));
	int nz = (int)(floor(p.z));

	v_rand[PRLN_000] = _computeRandomVector(nx,  ny,  nz);
	v_rand[PRLN_100] = _computeRandomVector(nx+1,ny,  nz);
	v_rand[PRLN_010] = _computeRandomVector(nx,  ny+1,nz);
	v_rand[PRLN_110] = _computeRandomVector(nx+1,ny+1,nz);
	v_rand[PRLN_001] = _computeRandomVector(nx,  ny,  nz+1);
	v_rand[PRLN_101] = _computeRandomVector(nx+1,ny,  nz+1);
	v_rand[PRLN_011] = _computeRandomVector(nx,  ny+1,nz+1);
	v_rand[PRLN_111] = _computeRandomVector(nx+1,ny+1,nz+1);
}

//-----------------------------------------------------------

static double _scalarNoise(Vector p, double frequency, double amplitude)
{
	Vector random_vectors[8];
	double dot_products[8];

	Vector lp = V_multiply(frequency,p);

	_computeRandomVertexVectors(lp,random_vectors);
	_computeDotProducts(lp,random_vectors,dot_products);

	// double noise_value = amplitude*_scalarLinearInterpolate(lp,dot_products);
	double noise_value = amplitude*_scalarCubicInterpolate(lp,dot_products);

	return noise_value;
}

//-----------------------------------------------------------

static Vector _vectorNoise(Vector p, double frequency, double amplitude)
{
	Vector random_vectors[8];
	Vector cross_products[8];

	Vector lp = V_multiply(frequency,p);

	_computeRandomVertexVectors(lp,random_vectors);
	_computeCrossProducts(lp,random_vectors,cross_products);
	Vector noise_vector = _vectorLinearInterpolate(lp,cross_products);
	return V_multiply(amplitude,noise_vector);
}

//-----------------------------------------------------------

// double PRLN_scalarNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain)
double PRLN_scalarNoise(Vector p)
{
	double period = 0.25; 
	double amplitude = 1.0; 
	int nb_octaves = 1.0; 
	double lacunarity = 2.0; 
	double gain = 0.5; 

	double noise_value = 0.0;

	double frequency = 1.0/period;

	int noct;
	for(noct=0;noct<nb_octaves;noct++)
	{
		noise_value += _scalarNoise(p,frequency,amplitude);
		frequency *= lacunarity;
		amplitude *= gain;
	}
	return noise_value;
}

//-----------------------------------------------------------

// Vector PRLN_vectorNoise(Vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain)
Vector PRLN_vectorNoise(Vector p)
{
	double period = 2.0; 
	double amplitude = 0.35; 
	int nb_octaves = 1.0; 
	double lacunarity = 2.0; 
	double gain = 0.5; 

	Vector noise_vector = V_new(0,0,0);

	double frequency = 1.0/period;

	int noct;
	for(noct=0;noct<nb_octaves;noct++)
	{
		Vector tmp = V_add(noise_vector,_vectorNoise(p,frequency,amplitude));
		noise_vector = tmp;
		frequency *= lacunarity;
		amplitude *= gain;
	}
	return noise_vector;
}

