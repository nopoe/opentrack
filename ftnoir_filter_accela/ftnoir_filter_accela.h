#pragma once
#include "opentrack/plugin-api.hpp"
#include <atomic>
#include <QMutex>
#include <QTimer>

#include "opentrack/options.hpp"
using namespace options;
#include "opentrack/timer.hpp"

struct settings_accela : opts {
    value<int> rot_threshold, trans_threshold, ewma, rot_deadzone, trans_deadzone;
    settings_accela() :
        opts("Accela"),
        rot_threshold(b, "rotation-threshold", 30),
        trans_threshold(b, "translation-threshold", 50),
        ewma(b, "ewma", 2),
        rot_deadzone(b, "rotation-deadzone", 0),
        trans_deadzone(b, "translation-deadzone", 0)
    {}
};

class FTNoIR_Filter : public IFilter
{
public:
    FTNoIR_Filter();
    void filter(const double* input, double *output);
private:
    settings_accela s;
    bool first_run;
    double last_output[6];
    double smoothed_input[6];
    Timer t;
    
    double f(double val, const double gains[][2]);
};
