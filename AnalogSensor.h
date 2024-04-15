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

        bool _upperThresholdCallBackFired = false;
        bool _lowerThresholdCallBackFired = false;


        /*
            Checks if the value is above or below the thresholds.
            If the value is above the upper threshold and the callback has not been fired, the callback is fired.
            If the value is below the lower threshold and the callback has not been fired, the callback is fired.
        */
        void _checkThresholds(uint16_t val);

    public:
        AnalogSensor();
        AnalogSensor(int p);
        ~AnalogSensor();
        void begin(void);

        void setUpperThreshold(uint16_t threshold, CallBack_t cb);
        void setUpperThreshold(uint16_t threshold) { this->_upperThreshold = threshold; }
        void setLowerThreshold(uint16_t threshold, CallBack_t cb);
        void setLowerThreshold(uint16_t threshold) { this->_lowerThreshold = threshold; };

        uint16_t getUpperThreshold(void) { return this->_upperThreshold; };
        uint16_t getLowerThreshold(void) { return this->_lowerThreshold; };

        /*
            Sets the bounds for the sensor.
            The sensor will map the raw value to the range specified by the bounds.
            The bounds are inclusive.
        */
        void setBounds(uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh);
        void setBounds(uint16_t toLow, uint16_t toHigh);

        void setTimeBetweenReads(uint32_t timeout);
        void setPin(int p);

        uint16_t read(void);
        float readFloat(void);

        uint16_t getRaw(void) { return analogRead(this->_pin); };

        // reset the threshold checks so callbacks fire again
        void reset(void);

        // check thresholds and fire callbacks
        void check(void);

        // automode, check thresholds and fire callbacks every x seconds
        void tick(void);
};

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);


#endif