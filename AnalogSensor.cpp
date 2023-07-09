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

void AnalogSensor::setUpperThreshold(uint16_t threshold) { this->_upperThreshold = threshold; }

void AnalogSensor::setLowerThreshold(uint16_t threshold, CallBack_t cb)
{
    this->_lowerThreshold = threshold;
    this->_CallBackOnLowerThreshold = cb;
}

void AnalogSensor::setLowerThreshold(uint16_t threshold) { this->_lowerThreshold = threshold; }

void AnalogSensor::setTimeBetweenReads(uint32_t timeout) { this->_timeBetweenReads = timeout; }

void AnalogSensor::setPin(int p)
{
    this->_pin = p;
    pinMode(this->_pin, INPUT);
}


int16_t AnalogSensor::read(void)
{
    this->_timeOfLastRead = millis();
    this->_raw = analogRead(this->_pin);
    int16_t val = map(this->_raw, this->_fromLow, this->_fromHigh, this->_toLow, this->_toHigh);
    return constrain(val, (int16_t) this->_toLow, (int16_t) this->_toHigh);
    // return val;
}

float AnalogSensor::readFloat(void)
{
    this->_timeOfLastRead = millis();
    this->_raw = analogRead(this->_pin);
    float val = mapFloat((float) this->_raw, (float) this->_fromLow, (float) this->_fromHigh, (float) this->_toLow, (float) this->_toHigh);
    return constrain(val, (float) this->_toLow, (float) this->_toHigh);
    // return val;
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
        if (val < this->_lowerThreshold)
        {
            if ((this->_lowerThresholdCallBackFired == false))
            {
                this->_CallBackOnLowerThreshold();
                this->_lowerThresholdCallBackFired = true;
            }
        }
        else
        {
            this->_lowerThresholdCallBackFired = false;
        }
    }

    if (this->_CallBackOnUpperThreshold != nullptr)
    {
        if (val > this->_upperThreshold)
        {
            if ((this->_upperThresholdCallBackFired == false))
            {
                this->_CallBackOnUpperThreshold();
                this->_upperThresholdCallBackFired = true;
            }
        }
        else
        {
            this->_upperThresholdCallBackFired = false;
        }
    }
}


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}