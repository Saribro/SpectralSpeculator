#pragma once

#include "ap.h"

class Spectrum
{
public:
    static double TemperatureToRadiance(double temperature, double lStart, double lEnd);
    static double RadianceToTemperature(double temperature, double lStart, double lEnd);

private:
    static const double c;
    static const double h;
    static const double kb;

    static void PlanckCurve(double x, double xminusa, double bminusx, double & y, void * ptr);
    static void InverseKernel(alglib::real_1d_array const & x, alglib::real_1d_array & fi, void * arguments);
};
