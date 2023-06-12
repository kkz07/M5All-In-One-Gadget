#include "MdMeasureDistance.h"
#include "DrUltraSonic.h"
#include "M5All-In-One-Gadget.h"

#define METERS 340.0
#define SECONDS 1000000

DrUltraSonic drul = DrUltraSonic(ECHO_PIN, TRIG_PIN);

double MdMeasureDistance::getDistance(){
    double distance;

    distance = (METERS / SECONDS) * drul.measureReturnTime() * 0.5 * 100;

    return distance;
}