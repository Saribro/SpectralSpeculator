#include "Spectrum.h"

#include "integration.h"
#include "optimization.h"

const double Spectrum::c = 299792458.0;
const double Spectrum::h = 6.6260695729e-34;
const double Spectrum::kb = 1.380648813e-23;

double Spectrum::TemperatureToRadiance(double temperature, double lStart, double lEnd)
{
    alglib::autogkstate state;

    alglib::autogksmooth(lStart, lEnd, state);
    alglib::autogkintegrate(state, Spectrum::PlanckCurve, &temperature);

    double radiance = 0.0f;
    alglib::autogkreport report;

    alglib::autogkresults(state, radiance, report);

    return radiance;
}

double Spectrum::RadianceToTemperature(double radiance, double lStart, double lEnd)
{
    double arguments[3] = { radiance, lStart, lEnd };

    alglib::real_1d_array x = "[300]";   // initial guess

    double epsg = 1e-10;
    double epsf = 0;
    double epsx = 0;
    double diffstep = 1e-4;

    alglib::ae_int_t iterations = 0;
    alglib::minlmstate state;
    alglib::minlmreport report;

    alglib::minlmcreatev(1, x, diffstep, state);
    alglib::minlmsetcond(state, epsg, epsf, epsx, iterations);

    alglib::minlmoptimize(state, Spectrum::InverseKernel, 0, reinterpret_cast<void *>(arguments));
    alglib::minlmresults(state, x, report);

    return x[0];
}

void Spectrum::PlanckCurve(double x, double xminusa, double bminusx, double & y, void * arguments)
{
    auto arg = reinterpret_cast<double *>(arguments);
    y  = expm1(h * c / (kb * x * arg[0]));  // equivalent of 'exp() - 1'
    y *= pow(x, 5.0f);
    y  = 2 * h * c * c / y;
}

void Spectrum::InverseKernel(alglib::real_1d_array const & x, alglib::real_1d_array & fi, void * arguments)
{
    auto arg = reinterpret_cast<double *>(arguments);
    fi[0] = Spectrum::TemperatureToRadiance(x[0], arg[1], arg[2]) - arg[0];
}
