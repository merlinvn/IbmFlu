/* 
 * File:   Random.cpp
 * Author: merlin
 * 
 * Created on May 7, 2012, 1:22 PM
 */

#include "Random.h"
#include <iostream>
//#include <cstdlib>
#include <fstream>
#include <ctime>
#include <math.h>

Random::Random(gsl_rng* g_rng): G_RNG(g_rng){    
    
}

Random::~Random()
{
    Release();
}

void Random::Initialize(const unsigned int& seed) {
    // get random number seed from current time
//    int seed = time(0);

    const gsl_rng_type *TT = gsl_rng_mt19937;
    G_RNG = gsl_rng_alloc(TT);

    // seed the RNG
    if(seed==-1){
        seed_ = GoodSeed();
        gsl_rng_set(G_RNG, seed_);        
    }
    else {
        seed_ = seed;
        gsl_rng_set(G_RNG, seed_);        
    }
    
}

unsigned int Random::GoodSeed()
{
    unsigned int random_seed, random_seed_a = 0, random_seed_b;
//    std::ifstream file ("/dev/urandom", std::ios::binary);
//    if (file.is_open())
//    {
//        char * memblock;
//        const int size = sizeof(int);
//        memblock = new char [size];
//        file.read (memblock, size);
//        file.close();
//        random_seed_a = *reinterpret_cast<int*>(memblock);
//        delete[] memblock;
//    }// end if
//    else {
//        random_seed_a = 0;
//    }
    random_seed_b = std::time(0);
    random_seed = random_seed_a ^ random_seed_b;

    return random_seed;
}

void Random::Release() {
    gsl_rng_free(G_RNG);
}

int Random::RandomPoisson(const double& poisson_mean) {
    return gsl_ran_poisson(G_RNG, poisson_mean);
}

int Random::RandomUniform(const int& range) {
    return gsl_rng_uniform_int(G_RNG, range);
}

double Random::RandomUniform() {
    return gsl_rng_uniform(G_RNG);
}

double Random::RandomNormal(const double& mean, const double& sd) {
    return mean + gsl_ran_gaussian(G_RNG, sd);
}

int Random::RandomNormal(const int& mean, const int& sd) {
    return mean + round(gsl_ran_gaussian(G_RNG, sd));
}

double Random::RandomBeta(const double& alpha, const double& beta) {
    //if beta =0, alpha = means
    if (beta == 0)
        return alpha;
    return gsl_ran_beta(G_RNG, alpha, beta);
}

//
// the parameterization below is done so alpha*beta = mean
// and alpha*beta^2 = variance
//

double Random::RandomGamma(const double& shape, const double& scale) {
    //if beta =0, alpha = means
    if (scale == 0)
        return shape;
    return gsl_ran_gamma(G_RNG, shape, scale);
}

double Random::CDFGammaDistribution(const double& x, const double& alpha, const double& beta) {
    //if beta =0, alpha = means
    if (beta == 0)
        return 1.0;
    return gsl_cdf_gamma_P(x, alpha, beta);
}

double Random::CDFGammaDsitributionInverse(const double& P, const double& alpha, const double& beta) {
    return gsl_cdf_gamma_Pinv(P, alpha, beta);
}

double Random::RandFlat(const double& from, const double& to) {
    return gsl_ran_flat(G_RNG, from, to);
}

void Random::RandomMultinomial(const int& K, const unsigned& N, double p[], unsigned n[]) {
    gsl_ran_multinomial(G_RNG, K, N, p, n);
}







