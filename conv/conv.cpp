#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../baselib/baselib.h"

/*
 *x[n]:the longer sequence
 *w[n]:the short sequence
 *y[n]:results of linear convolution
*/
void overlap_save(double xn[], int len_xn, double wn[], int len_wn, double yn[])
{
	int seq_m, i;
	if (len_xn != len_wn*2) {
		printf("par error\n");
		return ;
	}

	double *wn_double=(double *)malloc(2*len_wn* sizeof(double));
	complex *X=(complex *)malloc(len_xn * sizeof(complex));
	complex *W=(complex *)malloc(len_xn * sizeof(complex));
	complex *Y=(complex *)malloc(len_xn * sizeof(complex));
	complex *Res=(complex *)malloc(len_xn * sizeof(complex));

	//fft(x[n])
	seq_m = (int) log2(len_xn);
	FFTR(xn, len_xn, seq_m, X);
	for(i=0; i <len_xn; i++) {
		printf("X[%d].real=%f, X[%d].img=%f\n", i, X[i].real, i, X[i].img);
	}
	printf("\n\n");

	//fft(w[n])
	for (i=0; i<2*len_wn; i++) {
		if(i<len_wn)
			wn_double[i]=wn[i];
		else
			wn_double[i]=0;
	}

	seq_m = (int) log2(len_wn*2);
	FFTR(wn_double, 2*len_wn, seq_m, W);
	for(i=0; i <len_xn; i++) {
		printf("W[%d].real=%f, W[%d].img=%f\n", i, W[i].real, i, W[i].img);
	}
	printf("\n\n");

	//time domain:conv<------>frequency domain:mul
	for (i=0; i<len_xn; i++) {
		complex_mul(X[i], W[i], &Y[i]);
	}

	for(i=0; i <len_xn; i++) {
		printf("Y[%d].real=%f, Y[%d].img=%f\n", i, Y[i].real, i, Y[i].img);
	}
	printf("\n\n");

	//ifft(Y[n])
	seq_m = (int) log2(len_xn);
	iFFT(Y, len_xn, seq_m, Res);
	for(i=0; i <len_xn; i++) {
		printf("Res[%d].real=%f, Res[%d].img=%f\n", i, Res[i].real, i, Res[i].img);
	}
	printf("\n\n");

	//get last N point
	//memcpy(yn, Res, len_xn);
	for (i=len_wn; i<len_xn; i++) {
		yn[i]=Res[i].real;
	}

	free(wn_double);
	free(X);
	free(W);
	free(Y);
	free(Res);
}

void conv(double *inputdata, long input_len, double *rir_dat, long rir_length, double *outputdata)
{

	printf("input_len:%ld\n", input_len);
	printf("rir_length=%d\n", rir_length);
	memcpy(outputdata, inputdata, input_len);
}

