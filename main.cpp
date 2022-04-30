#include <stdio.h>
#include <math.h>
#include "baselib.h"

//int N=8;
//int M=3;
int N=8;
int M=log2(N);

#if 1
/* 验证FFT和iFFT*/
int main(void)
{

	int i;
	complex INPUT_SEQ[N], RES_SEQ[N], OUTPUT_SEQ[N];
	double SEQ_DAT[N], dataR[N], dataI[N];

	//构造实数序列
	for (i=0; i < N; i++) {
		SEQ_DAT[i]=i;
	}

	//构造虚数序列
	for (i=0; i<N; i++) {
		INPUT_SEQ[i].real=SEQ_DAT[i];
		INPUT_SEQ[i].img=0;
	}
	for (i=0; i <N; i++) {
		printf("before fft: INPUT_SEQ[%d].real=%f, INPUT_SEQ[%d].img=%f\n", i, INPUT_SEQ[i].real, i, INPUT_SEQ[i].img);
	}
	printf("\n\n");

	FFT(INPUT_SEQ, N, M, RES_SEQ);
	for (i=0; i <N; i++) {
		printf("fft: RES_SEQ[%d].real=%f, RES_SEQ[%d].img=%f\n", i, RES_SEQ[i].real, i, RES_SEQ[i].img);
	}
	printf("\n\n");

	iFFT(RES_SEQ, N, M, OUTPUT_SEQ);
	for (i=0; i <N; i++) {
		printf("ifft: OUTPUT_SEQ[%d].real=%f, OUTPUT_SEQ[%d].img=%f\n", i, OUTPUT_SEQ[i].real, i, OUTPUT_SEQ[i].img);
	}
	printf("\n\n");
}
#else
int main(void)
{
	int i;
	complex INPUT_SEQ[N], OUTPUT_SEQ[N];
	double SEQ_DAT[N];

	//初始化输入序列
	for (i=0; i <N; i++) {
		SEQ_DAT[i]=i;
		INPUT_SEQ[i].real=i;
		INPUT_SEQ[i].img=0;
	}

	iFFTR(SEQ_DAT, N, M, OUTPUT_SEQ);
	for (i=0; i <N; i++) {
		printf("ifftr: OUTPUT_SEQ[%d].real=%f, OUTPUT_SEQ[%d].img=%f\n", i, OUTPUT_SEQ[i].real, i, OUTPUT_SEQ[i].img);
	}
	printf("\n\n");

	iFFT(INPUT_SEQ, N, M, OUTPUT_SEQ);
	for (i=0; i <N; i++) {
		printf("ifft: OUTPUT_SEQ[%d].real=%f, OUTPUT_SEQ[%d].img=%f\n", i, OUTPUT_SEQ[i].real, i, OUTPUT_SEQ[i].img);
	}
	printf("\n\n");

	return 0;
}
#endif

