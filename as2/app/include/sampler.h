#ifndef _SAMPLER_H_
#define _SAMPLER_H_

void Sampler_init(void);
void Sampler_cleanup(void);

void Sampler_moveCurrentDataToHistory(void);

int Sampler_getHistorySize(void);

double* Sampler_getHistory(int *size);

double Sampler_getAverageReading(void);

long long Sampler_getNumSamplesTaken(void);


#endif 