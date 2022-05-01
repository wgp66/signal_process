#ifndef __BASELIB_H__
#define __BASELIB_H__
#include <stdio.h>
#define PI 3.14159

typedef struct {
	double real;
	double img;
}complex;

/*
������
��1��N=2^M
��2��L=1~M����L��
��3����ת���ӵ�ָ��p��k��p��������p=p*k
��4��B�� Ԫ�س�ȡ��� = ���������(��ת���ӵ�����)
*/
//const int M=3, N=8;
//int L, B, P, K;
//complex A[N], Wn, Temp, Res;

void complex_add(complex a, complex b, complex *c);
void complex_sub(complex a, complex b, complex *c);
void complex_mul(complex a, complex b, complex *c);
void complex_div(complex   a, complex b, complex*c);

void Reader_Sort(complex *x, int len);
void FFT(complex *input_seq, int SEQ_N, int SEQ_M, complex res_seq[]);
void iFFT(complex *input_seq, int SEQ_N, int SEQ_M, complex res_seq[]);
void FFTR(double *dat_seq, int SEQ_N, int SEQ_M, complex res_seq[]);
void iFFTR(double *dat_seq, int SEQ_N, int SEQ_M, complex res_seq[]);

#endif
