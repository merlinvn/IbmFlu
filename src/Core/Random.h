/* 
 * File:   Random.h
 * Author: merlin
 *
 * Created on May 7, 2012, 1:22 PM
 */

#ifndef RANDOM_H
#define	RANDOM_H

#include <gsl/gsl_rng.h> // random number generators from Gnu Scientific Library
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>

#include "PropertyMacro.h"

class Random {
    VIRTUAL_PROPERTY(unsigned int, seed);
    
public:
    gsl_rng* G_RNG;

    Random(gsl_rng* g_rng = NULL);

    virtual ~Random();

    void Initialize(const unsigned int& seed = -1);

    void Release();

    virtual int RandomPoisson(const double& poissonMeans);

    virtual int RandomUniform(const int& range);
    

    /*
     * This function will return a random number in [0,1)
     */
    virtual double RandomUniform();

    virtual double RandomNormal(const double& mean, const double& sd);

    virtual int RandomNormal(const int& mean, const int& sd);

    virtual double RandomBeta(const double& alpha, const double& beta);

    virtual double RandomGamma(const double& shape, const double& scale);

    virtual double CDFGammaDistribution(const double& x, const double& alpha, const double& beta);

    virtual double CDFGammaDsitributionInverse(const double& p, const double& alpha, const double& beta);

    virtual double RandFlat(const double& from, const double& to);

    virtual void RandomMultinomial(const int& K, const unsigned& N, double p[], unsigned n[]);

private:
    unsigned int GoodSeed();
};

#endif	/* RANDOM_H */

