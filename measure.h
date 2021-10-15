#ifndef MEASURE_H
#define MEASURE_H

#define NUMBER_OF_SAMPLES		2000

extern void voltageMeasurement_Init(void);

extern double getVoltage(uint16_t* maxim);
extern double getCurrent(uint16_t* maxim);


#endif /* MEASURE_H */
