#include <AnalogSensor.h>


AnalogSensor::AnalogSensor() {}

AnalogSensor::AnalogSensor(int p) { this->setPin(p); }
AnalogSensor::~AnalogSensor() {}

void AnalogSensor::begin(void)
{
    ;
    ;
}

void AnalogSensor::setUpperThreshold(uint16_t threshold, CallBack_t cb)
{
    this->_upperThreshold = threshold;
    this->_CallBackOnUpperThreshold = cb;
}
void AnalogSensor::setLowerThreshold(uint16_t threshold, CallBack_t cb)
{
    this->_lowerThreshold = threshold;
    this->_CallBackOnLowerThreshold = cb;
}

void AnalogSensor::setTimeBetweenReads(uint32_t timeout) { this->_timeBetweenReads = timeout; }


void AnalogSensor::setPin(int p)
{
    this->_pin = p;
    pinMode(this->_pin, INPUT);
}


uint16_t AnalogSensor::read(void)
{
    this->_timeOfLastRead = millis();
    this->_raw = analogRead(this->_pin);
    return map(this->_raw, this->_fromLow, this->_fromHigh, this->_toLow, this->_toHigh);
}


void AnalogSensor::setBounds(uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh)
{
    this->_fromLow = fromLow;
    this->_fromHigh = fromHigh;
    this->_toLow = toLow;
    this->_toHigh = toHigh;
}
void AnalogSensor::setBounds(uint16_t toLow, uint16_t toHigh)
{
    this->_toLow = toLow;
    this->_toHigh = toHigh;
}


void AnalogSensor::tick(void)
{
    if (millis() - this->_timeOfLastRead > this->_timeBetweenReads)
    {
        uint16_t val = this->read();
        this->_checkThresholds(val);
    }
}


void AnalogSensor::_checkThresholds(uint16_t val)
{
    if (this->_CallBackOnLowerThreshold != nullptr)
    {
        if (val < this->_lowerThreshold) this->_CallBackOnLowerThreshold();
    }

    if (this->_CallBackOnUpperThreshold != nullptr)
    {
        if (val > this->_upperThreshold) this->_CallBackOnUpperThreshold();
    }
}