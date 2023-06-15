#include "MdWBGTMonitor.h"
#include "DrTHSensor.h"
#include <Arduino.h>

DrTHSensor dthsen;

void MdWBGTMonitor::init(){
    dthsen.init();
}

void MdWBGTMonitor::getWBGT(double* temperature, double* humidity, WbgtIndex* index){
    dthsen.getTempHumi(temperature, humidity);
    int calc_index = 0.68 * (*temperature) + 0.12 * (*humidity);

    if(calc_index <= 15){
        *index = DANGER;
    } else if(calc_index <= 24) {
        *index = ATTENTION;
    } else if(calc_index <= 27) {
        *index = ALERT;
    } else if(calc_index <=  30) {
        *index = HIGH_ALERT;
    } else {
        *index = DANGER;
    }
}