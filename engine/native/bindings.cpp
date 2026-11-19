#include <emscripten/bind.h>
#include "Simulation.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(robotwars)
{
    class_<Simulation>("Simulation")
        .constructor<>()
        .function("init", &Simulation::init)
        .function("step", &Simulation::step)
        .function("snapshot", &Simulation::snapshot)
        .function("log", &Simulation::log)
        .function("error", &Simulation::error);
}
