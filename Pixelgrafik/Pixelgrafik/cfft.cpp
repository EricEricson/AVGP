#include "pch.h"
#include "cfft.h"


CFFT::CFFT() {
	width = height = 0;
	for (int i = 0; i < 3; i++)
		real[i] = imag[i] = 0;
}

CFFT::~CFFT() {
	for (int i = 0; i < 3; i++) {
		delete[] real[i];
		delete[] imag[i];
	}
}


//2-dimensionale fft, dir=1:vorwärts, dir=-1:rückwärts, COLOR:Farbkanal
//******************************************************************

int CFFT::FFT2D(int dir, int COLOR)
{
	int i, j;
	int m;
	double* real_temp, * imag_temp;

	/* Transform the rows */
	real_temp = new double[width + 1];
	imag_temp = new double[width + 1];
	if (real_temp == NULL || imag_temp == NULL)
		return(FALSE);
	if (!PowerOf2(width, &m))
		return(FALSE);
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			real_temp[i] = real[COLOR][j * width + i];
			imag_temp[i] = imag[COLOR][j * width + i];
		}
		FFT(dir, m, real_temp, imag_temp);
		for (i = 0; i < width; i++)
		{
			real[COLOR][j * width + i] = real_temp[i];
			imag[COLOR][j * width + i] = imag_temp[i];
		}
	}
	delete[]real_temp;
	delete[]imag_temp;

	/* Transform the columns */
	real_temp = new double[height + 1];
	imag_temp = new double[height + 1];
	if (real_temp == NULL || imag_temp == NULL)
		return(FALSE);
	if (!PowerOf2(height, &m))
		return(FALSE);
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			real_temp[j] = real[COLOR][j * width + i];
			imag_temp[j] = imag[COLOR][j * width + i];
		}
		FFT(dir, m, real_temp, imag_temp);
		for (j = 0; j < height; j++)
		{
			real[COLOR][j * width + i] = real_temp[j];
			imag[COLOR][j * width + i] = imag_temp[j];
		}
	}
	delete[]real_temp;
	delete[]imag_temp;
	return(TRUE);
}

/*-------------------------------------------------------------------------
   This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform

	 Formula: forward
				  N-1
				  ---
			  1   \          - j k 2 pi n / N
	  X(n) = ---   >   x(k) e                    = forward transform
			  N   /                                n=0..N-1
				  ---
				  k=0

	  Formula: reverse
				  N-1
				  ---
				  \          j k 2 pi n / N
	  X(n) =       >   x(k) e                    = forward transform
				  /                                n=0..N-1
				  ---
				  k=0
*/


int CFFT::FFT(int dir, int m, double* x, double* y)
{
	long nn, i, i1, j, k, i2, l, l1, l2;
	double c1, c2, tx, ty, t1, t2, u1, u2, z;

	/* Calculate the number of points */
	nn = 1;
	for (i = 0; i < m; i++)
		nn *= 2;

	/* Do the bit reversal */
	i2 = nn >> 1;
	j = 0;
	for (i = 0; i < nn - 1; i++)
	{
		if (i < j)
		{
			tx = x[i];
			ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;
		}
		k = i2;
		while (k <= j)
		{
			j -= k;
			k >>= 1;
		}
		j += k;
	}

	/* Compute the FFT */
	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;
	for (l = 0; l < m; l++)
	{
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;
		for (j = 0; j < l1; j++)
		{
			for (i = j; i < nn; i += l2)
			{
				i1 = i + l1;
				t1 = u1 * x[i1] - u2 * y[i1];
				t2 = u1 * y[i1] + u2 * x[i1];
				x[i1] = x[i] - t1;
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			}
			z = u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}
		c2 = sqrt((1.0 - c1) / 2.0);
		if (dir == 1)
			c2 = -c2;
		c1 = sqrt((1.0 + c1) / 2.0);
	}

	/* Scaling for forward transform */
	if (dir == 1) {
		for (i = 0; i < nn; i++) {
			x[i] /= (double)nn;
			y[i] /= (double)nn;
		}
	}

	return(TRUE);
}

int CFFT::MakePowerOf2(int i) {
	/*
	 * Returns i if "i" is a power of 2 (has only one bit on).
	 * else returns next powerof2
	 * return 0 if i==0
	*/
	int x;
	if (i != 0) {
		if (((i - 1) & i) == 0)
			return i;
		else {
			for (x = 1; x < i; x *= 2);
			return x;
		}
	}
	else
		return 0;

}

int CFFT::PowerOf2(int i, int* m)
{
	/*
	 * Returns TRUE if "i" is a power of 2 (has only one bit on).
	 * Doesn't work for i == 0 (returns TRUE).
	 */

	int x;

	if (i == 0)
		return 0;

	if (((i - 1) & i) == 0)
	{
		for (x = 2, (*m) = 1; x != i; x *= 2, (*m)++);
		return 1;
	}
	else
		return 0;

}

void CFFT::lowpass(int factor)
{
	if (factor < 0 || factor > 100)
	{
		AfxMessageBox(L"Unzulässiger Faktor.");
		return;
	}

	if (factor == 0)
		factor = 1; //alles wegschneiden


	int i, j;

	int xborder = (width / 2) / (100 / factor);
	int yborder = (height / 2) / (100 / factor);

	for (j = 0; j < yborder; j++)
	{
		for (i = xborder; i < width / 2; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}

		for (i = width - xborder - 1; i >= width / 2; i--)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}
	}

	for (j = yborder; j < height - yborder; j++)
	{
		for (i = 0; i < width; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}
	}

	for (j = height - yborder; j < height; j++)
	{
		for (i = xborder; i < width / 2; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}

		for (i = width - xborder - 1; i >= width / 2; i--)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}
	}

}


void CFFT::highpass(int factor)
{
	if (factor < 0 || factor > 100)
	{
		AfxMessageBox(L"Unzulässiger Faktor.");
		return;
	}

	if (factor == 0)
		factor = 1; //alles wegschneiden


	int i, j;
	int xborder = (width / 2) / (100 / factor);
	int yborder = (height / 2) / (100 / factor);

	for (i = 1; i < xborder; i++)
	{
		real[0][i] = real[1][i] = real[2][i] = 0;
		imag[0][i] = imag[1][i] = imag[2][i] = 0;
	}

	for (i = width - xborder - 1; i < width - 1; i++)
	{
		real[0][i] = real[1][i] = real[2][i] = 0;
		imag[0][i] = imag[1][i] = imag[2][i] = 0;
	}

	for (j = 1; j < yborder; j++)
	{
		for (i = 0; i < xborder; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}

		for (i = width - xborder - 1; i < width; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}
	}

	for (j = height - yborder; j < height - 1; j++)
	{
		for (i = 0; i < xborder; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}

		for (i = width - xborder; i < width; i++)
		{
			real[0][j * width + i] = real[1][j * width + i] = real[2][j * width + i] = 0;
			imag[0][j * width + i] = imag[1][j * width + i] = imag[2][j * width + i] = 0;
		}

	}

	for (i = 1; i < xborder; i++)
	{
		real[0][(height - 1) * width + i] = real[1][(height - 1) * width + i] = real[2][(height - 1) * width + i] = 0;
		imag[0][(height - 1) * width + i] = imag[1][(height - 1) * width + i] = imag[2][(height - 1) * width + i] = 0;
	}

	for (i = width - xborder; i < width - 1; i++)
	{
		real[0][(height - 1) * width + i] = real[1][(height - 1) * width + i] = real[2][(height - 1) * width + i] = 0;
		imag[0][(height - 1) * width + i] = imag[1][(height - 1) * width + i] = imag[2][(height - 1) * width + i] = 0;
	}
}