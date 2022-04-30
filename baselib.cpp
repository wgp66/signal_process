#include <stdio.h>
#include <math.h>
#include "baselib.h"

//�������еĳ��ȱ�����2����������
void Reader_Sort(complex *x, int len)
{
	complex temp;
	int cur_rev = 0; //��0��ʼ�����Ƴ�����ԭ��Ȼ��������Ӧ�ĵ�����
	int k = len / 2; //��ʼ��Ȩֵϵ��
	int i, j;
	for (j = 1; j <= len - 1; j++) {
		//��ǰ�����������λΪ0��
		if (cur_rev < k) {
			//��temp�����λ��0��Ϊ1(����Ȩϵ��)���ɵõ���һ��������
			cur_rev = cur_rev + k;
		} else {
			//��ǰ�����������λΪ1
			while (cur_rev >= k) {
				//�����λ��1��Ϊ0(��ȥȨϵ������)
				cur_rev = cur_rev - k;
				//û����ѭ����˵���θ�λΪ1�������Ȩϵ��������ǰλ��Ϊ0��......
				k = k / 2;
			}
			//��ǰλ(���λ)Ϊ0������while()����Ϊ1(����Ȩϵ��)�����õ�ǰ������
			cur_rev = cur_rev + k;
			//��ԭȨϵ��ֵ
			k = len / 2;
		}
		//printf("j=%d, cur_rev=%d\n", j, cur_rev);
		//����x[j]��x[cur_rev]
		if (j < cur_rev) {
			//ʵ�����ֻ���
			temp.real = x[j].real;
			x[j].real = x[cur_rev].real;
			x[cur_rev].real = temp.real;

			//�������ֻ���
			temp.img = x[j].img;
			x[j].img = x[cur_rev].img;
			x[cur_rev].img = temp.img;
		}
	}
}

void FFTR(double *dat_seq, int SEQ_N, int SEQ_M, complex res_seq[])
{
	int i, j, k, r;
	int B, P;
	complex Wn, Res;
	complex yn[SEQ_N/2], X1[SEQ_N/2], X2[SEQ_N/2], X[SEQ_N];

	//����y(n)
//	yn[0].real=0.0; yn[0].img=1.0;
//	yn[1].real=2.0; yn[1].img=3.0;
//	yn[2].real=4.0; yn[2].img=5.0;
//	yn[3].real=6.0; yn[3].img=7.0;
	for (i=0; i<SEQ_N/2; i++) {
		yn[i].real=dat_seq[2*i];
		yn[i].img=dat_seq[2*i+1];
	}

	//y(n)����N/2���FFT
	//FFT(yn, SEQ_N/2, 2);
	FFT(yn, SEQ_N/2, SEQ_M-1, NULL);

	//��X1(k)��X2(k)
	for (k=0; k < SEQ_N/2; k++) {
		if (k==0) {
			X1[k].real = yn[k].real;
			X1[k].img = yn[k].img;
			X2[k].real = yn[k].img;
			X2[k].img = (-1)*yn[k].real;
		} else {
			X1[k].real=(yn[k].real + yn[SEQ_N/2-k].real)/2;
			X1[k].img=(yn[k].img - yn[SEQ_N/2-k].img)/2;
			X2[k].real=(yn[k].img + yn[SEQ_N/2-k].img)/2;
			X2[k].img=(yn[SEQ_N/2-k].real - yn[k].real)/2;
		}
	}

	//��M��(���һ��)�ĵ�������
	B = 1;
	B = (int)pow(2, SEQ_M-1);
	for (j=0; j<=SEQ_N/2-1; j++) {
		P=1;
		P=j;
		r=1;
		r=j;
		Wn.real = cos((2*PI)/SEQ_N*P);
		Wn.img = -1*sin((2*PI)/SEQ_N*P);
		complex_mul(X2[r], Wn, &Res);
		X[r].real = X1[r].real + Res.real;
		X[r].img = X1[r].img + Res.img;
		if (r==0) {
			X[SEQ_N/2].real = X1[0].real-X2[0].real;
			X[SEQ_N/2].img = X1[0].img-X2[0].img;
		} else {
			X[SEQ_N-r].real = X[r].real;
			X[SEQ_N-r].img = (-1)*X[r].img;
		}
	}

	for (i=0; i < SEQ_N; i++) {
		res_seq[i].real=X[i].real;
		res_seq[i].img=X[i].img;
	}
}

void iFFTR(double *dat_seq, int SEQ_N, int SEQ_M, complex res_seq[])
{
	int i, j, k, r;
	int B, P;
	complex Wn, Res;
	complex yn[SEQ_N/2], X1[SEQ_N/2], X2[SEQ_N/2], X[SEQ_N];

	//����y(n)
//	yn[0].real=0.0; yn[0].img=1.0;
//	yn[1].real=2.0; yn[1].img=3.0;
//	yn[2].real=4.0; yn[2].img=5.0;
//	yn[3].real=6.0; yn[3].img=7.0;
	for (i=0; i<SEQ_N/2; i++) {
		yn[i].real=dat_seq[2*i];
		yn[i].img=dat_seq[2*i+1];
	}

	//y(n)����N/2���FFT
	//FFT(yn, SEQ_N/2, 2);
	iFFT(yn, SEQ_N/2, SEQ_M-1, NULL);

	//��X1(k)��X2(k)
	for (k=0; k < SEQ_N/2; k++) {
		if (k==0) {
			X1[k].real = yn[k].real;
			X1[k].img = yn[k].img;
			X2[k].real = yn[k].img;
			X2[k].img = (-1)*yn[k].real;
		} else {
			X1[k].real=(yn[k].real + yn[SEQ_N/2-k].real)/2;
			X1[k].img=(yn[k].img - yn[SEQ_N/2-k].img)/2;
			X2[k].real=(yn[k].img + yn[SEQ_N/2-k].img)/2;
			X2[k].img=(yn[SEQ_N/2-k].real - yn[k].real)/2;
		}
	}

	//��M��(���һ��)�ĵ�������
	B = 1;
	B = (int)pow(2, SEQ_M-1);
	for (j=0; j<=SEQ_N/2-1; j++) {
		P=j;
		r=j;
		Wn.real = cos((2.0*PI)/SEQ_N*P);
		Wn.img = sin((2.0*PI)/SEQ_N*P);
		complex_mul(X2[r], Wn, &Res);
		X[r].real = X1[r].real + Res.real;
		X[r].real = X[r].real/2;
		X[r].img = X1[r].img + Res.img;
		X[r].img = X[r].img/2;
		if (r==0) {
			X[SEQ_N/2].real = X1[0].real-X2[0].real;
			X[SEQ_N/2].real = X[SEQ_N/2].real/2;
			X[SEQ_N/2].img = X1[0].img-X2[0].img;
			X[SEQ_N/2].img = X[SEQ_N/2].img/2;
		} else {
			X[SEQ_N-r].real = X[r].real;
			X[SEQ_N-r].img = (-1)*X[r].img;
		}
	}

	for (i=0; i < SEQ_N; i++) {
		res_seq[i].real = X[i].real;
		res_seq[i].img = X[i].img;
	}
}

void FFT(complex *input_seq, int SEQ_N, int SEQ_M, complex res_seq[])
{
	int i, j, r;
	int L, B, K, P;
	complex Temp, Wn, Res;
	if (!input_seq) {
		printf("input sequence can be NULL\n");
		return ;
	}

	Reader_Sort(input_seq, SEQ_N);

	for (L=1; L <= SEQ_M; L++) {
		B=1;
		B=(int)pow(2, L-1);
		for (j=0; j<=B-1; j++) {
			K=(int)pow(2, SEQ_M-L);
			P=1;
			P=K*j;
			for (i=0; i<=K-1; i++) {
				r=j;
				r=j+2*B*i;
				Temp = input_seq[r];
				Wn.real = cos((2*PI)/SEQ_N*P);
				Wn.img = -1*sin((2*PI)/SEQ_N*P);
				complex_mul(input_seq[r+B], Wn, &Res);
				input_seq[r].real=input_seq[r].real + Res.real;
				input_seq[r].img=input_seq[r].img + Res.img;
				input_seq[r+B].real=Temp.real - Res.real;
				input_seq[r+B].img=Temp.img - Res.img;
			}
		}
	}

	if (!res_seq) {
		printf("result sequence is NULL\n");
		return ;
	} else {
		for(i=0; i<SEQ_N; i++){
			res_seq[i].real = input_seq[i].real;
			res_seq[i].img = input_seq[i].img;
		}
	}
}

void iFFT(complex *input_seq, int SEQ_N, int SEQ_M, complex res_seq[])
{
	int i, j, r;
	int L, B, K, P;
	complex Temp, Wn, Res;
	if (!input_seq) {
		printf("input sequence can be NULL\n");
		return ;
	}

	Reader_Sort(input_seq, SEQ_N);

	for (L=1; L <= SEQ_M; L++) {
		B=1;
		B=(int)pow(2, L-1);
		for (j=0; j<=B-1; j++) {
			K=(int)pow(2, SEQ_M-L);
			P=1;
			P=K*j;
			for (i=0; i<=K-1; i++) {
				r=j;
				r=j+2*B*i;
				Temp = input_seq[r];
				Wn.real = cos((2.0*PI)/SEQ_N*P);
				Wn.img = sin((2.0*PI)/SEQ_N*P);
				complex_mul(input_seq[r+B], Wn, &Res);
				input_seq[r].real=input_seq[r].real + Res.real;
				input_seq[r].real=(1.0/2) * input_seq[r].real;
				input_seq[r].img=input_seq[r].img + Res.img;
				input_seq[r].img=(1.0/2) * input_seq[r].img;
				input_seq[r+B].real=Temp.real - Res.real;
				input_seq[r+B].real=(1.0/2) * input_seq[r+B].real;
				input_seq[r+B].img=Temp.img - Res.img;
				input_seq[r+B].img=(1.0/2) * input_seq[r+B].img;
			}
		}
	}

	if (!res_seq) {
		printf("result sequence is NULL\n");
		return ;
	} else {
		for(i=0; i<SEQ_N; i++){
			res_seq[i].real = input_seq[i].real;
			res_seq[i].img = input_seq[i].img;
		}
	}
}

void complex_add(complex a, complex b, complex *c)
{
	c->real = a.real + b.real;
	c->img = a.img + b.img;
}

void complex_sub(complex a, complex b, complex *c)
{
	c->real = a.real - b.real;
	c->img = a.img - b.img;
}

void complex_mul(complex a, complex b, complex *c)
{
	c->real = a.real*b.real - a.img*b.img;
	c->img = a.real*b.img + a.img*b.real;
}

void complex_div(complex   a, complex b, complex*c)
{
	c->real = (a.real*b.real + a.img*b.img)/(b.real*b.real + b.img*b.img);
	c->img = (a.img*b.real - a.real*b.img)/(b.real*b.real + b.img*b.img);
}

