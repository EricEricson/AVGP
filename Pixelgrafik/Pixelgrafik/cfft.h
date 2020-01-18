#include <math.h>
#include <stdlib.h>
#include <complex>
#define PI 3.141592653589793


#ifndef __FFT__
#define __FFT__


class CFFT {

public:
	CFFT();
	~CFFT();
	static int MakePowerOf2(int i);
	int FFT2D(int dir, int COLOR);
	int FFT(int dir, int m, double* x, double* y);
	int PowerOf2(int i, int* m);
	void lowpass(int factor);
	void highpass(int factor);

	// Hilfsarrays für fft
	double* real[3], * imag[3];
	//Größe des fft-vektors
	int width, height;
};

#endif