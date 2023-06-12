#include "DrUltraSonic.h"
#include "M5All-In-One-Gadget.h"

DrUltraSonic::DrUltraSonic(int echo_pin, int inttrig_pin) {
    m_echo_pin = echo_pin;
    m_trig_pin = inttrig_pin;
}

double measureReturnTime(){
    double t;

    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);

    t = pulseIn(m_echo_pin, HIGH);

    return t;
}
