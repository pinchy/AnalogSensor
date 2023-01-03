#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>

class AnalogSensor
{
        typedef void (*CallBack_t)();

    private:
        int _pin;
        uint16_t _raw;
        uint32_t _timeBetweenReads = 1000;
        uint32_t _timeOfLastRead = 0;

        uint16_t _upperThreshold;
        uint16_t _lowerThreshold;

        uint16_t _fromLow = 0;
        uint16_t _fromHigh = 1024;
        uint16_t _toLow = 0;
        uint16_t _toHigh = 1024;

        CallBack_t _CallBackOnUpperThreshold = nullptr;
        CallBack_t _CallBackOnLowerThreshold = nullptr;

        void _checkThresholds(uint16_t val);

    public:
        AnalogSensor();
        AnalogSensor(int p);
        ~AnalogSensor();
        void begin(void);

        void setUpperThreshold(uint16_t threshold, CallBack_t cb);
        void setLowerThreshold(uint16_t threshold, CallBack_t cb);

        void setBounds(uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh);
        void setBounds(uint16_t toLow, uint16_t toHigh);

        void setTimeBetweenReads(uint32_t timeout);
        void setPin(int p);
        uint16_t read(void);
        uint16_t getRaw(void) { return analogRead(this->_pin); };
        void tick(void);
};

#endif