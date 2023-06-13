#include "MdWBGTMonitor.h"
#include "DrTHSensor.h"
#include <Arduino.h>

DrTHSensor dthsen;

void MdWBGTMonitor::init(){
    dthsen.init();
}

void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index){
    dthsen.getTempHumi(temperature, humidity);
    double state = 0.68 * (*temperature) + 0.12 * (*humidity);

    if(state <= 15){
        *index = DANGER;
    } else if(state <= 24) {
        *index = ATTENTION;
    } else if(state <= 27) {
        *index = ALERT;
    } else if(state <=  30) {
        *index = HIGH_ALERT;
    } else {
        *index = DANGER;
    }
}