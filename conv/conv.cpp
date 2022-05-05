/***************************************************************************
  *
  * Homework for chapter 3 -- "overlap-save method"
  *
  * Here is the realization of add rir function.
  * You have to finish "conv" function by yourself. It is called in main
  * function. Also, you may want to use FFT, which is ready for you too.
  *
  * NOTICE: There is no IFFT function. So you have to realize IFFT using FFT.
  * Take some time to think about how to do this please.
  *
  **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "conv.h"
#include "baselib.h"

/**
 * @brief add rir using overlap-save method.
 *
 * @param inputdata         input clean audio data buffer
 * @param inputdata_length  length of inputdata(samples)
 * @param rir               room impulse response buffer
 * @param rir_length        length of rir, 4096 by default
 * @param outputdata        processed data, same length as inputdata
 * @return
 *     @retval 0            successfully
 */
#if 1
int conv(short* inputdata, long inputdata_length, double* rir, long rir_length, short* outputdata)
{
	// finish overlap-save method here
	int i, j, k, h;
	long N1=rir_length;
	long N2=2*N1;
	int fftorder = (int)log2(N2);

	COMPLEX *temp = (COMPLEX *)malloc(N1 * sizeof(COMPLEX));
	COMPLEX *xn = (COMPLEX *)malloc(N2 * sizeof(COMPLEX));//X(k)
	COMPLEX *wn = (COMPLEX *)malloc(N2 * sizeof(COMPLEX));//W(k)
	COMPLEX *yn = (COMPLEX *)malloc(N2 * sizeof(COMPLEX));//Y(k)

	//初始化滤波器权值向量
	for (i=0; i<N2; i++) {
		if(i<N1){
			wn[i].real=(float)rir[i];
			xn[i].real=0.f; //第一个old block,N个0
			xn[i].image=0.f;
		} else {
			wn[i].real=0.f;
		}
		wn[i].image=0.f;
	}

	fft(wn, fftorder);
	long pack_cnt = inputdata_length/rir_length;
	printf("pack_cnt:%d\n", pack_cnt);//17

	//处理整包
	for (i=0; i<pack_cnt; i++) {
		for (j=0; j<N1; j++) {
			k=j+i*N1;
			xn[j+N1].real = (float)inputdata[k] / 32767.f;
			xn[j+N1].image = 0.f;
			temp[j].real = xn[j+N1].real;
			temp[j].image = xn[j+N1].image;
		}

		fft(xn, fftorder);
		for (j=0; j<N2; j++) {
			yn[j].real = wn[j].real*xn[j].real - wn[j].image*xn[j].image;
			yn[j].image = wn[j].real*xn[j].image + wn[j].image*xn[j].real;
		}

		ifft(yn, fftorder);

		//更新输出指针(取iFFT后面的N个点)
		for (j = N1, h=0;  j < N2; j++, h++) {
			k = h + i*N1;
			outputdata[k] = (short)yn[j].real;
		}

		//更新xn的old block
		for (k=0; k<N1; k++) {
			xn[k].real = temp[k].real;
			xn[k].image = temp[k].image;
		}

		//printf("i=%d\n", i);
	}
	//最后一个包

	return 0;
}
#else
int conv(short* inputdata, long inputdata_length, double* rir, long rir_length, short* outputdata)
{
	// finish overlap-save method here
	long N = rir_length;
	long N2 = 2*N;
	int fftorder = (int)log2(N2);
	printf("N2:%ld, log2(2N):%d\n", N2, fftorder);
	short* ptr_outputdata=outputdata;

	COMPLEX *fftwk = new COMPLEX[N2]; // W(k)
	COMPLEX *fftxk = new COMPLEX[N2]; // X(k)
	COMPLEX *ifftyk = new COMPLEX[N2];// Y(k)
	// init W(k)
	for (int i=0; i<N2; ++i) {
		if (i<N) {
			fftwk[i].real=(float)rir[i];
		} else {
			fftwk[i].real=0.f;
		}
		fftwk[i].image=0.f;
	}
	fft(fftwk, fftorder);

	/*for (int i=N; i<N2; i++) {
			printf("fftwk[%d].real:%f, fftwk[%d].img:%f\n", i, fftwk[i].real, i, fftwk[i].image);
	}
	while(1);*/

	long package = ceil((float) inputdata_length /(float) N);
	printf("inputdata_length: %ld,package:%ld\n", inputdata_length, package);
	for(int i=0; i < package; ++i) {
		for (int j=0; j<N2; ++j) {
			int k=j+(i-1)*N;
			//int k=j+i*N;
			//初始化第一个oldblock为N个0，大于信号长度的部分数据补0
			if ((i == 0 && j<N)|| k>=inputdata_length) {
				fftxk[j].real=0.f;
			} else {
				fftxk[j].real=(float)inputdata[k] /32767.f;
			}
			fftxk[j].image=0.f;
		}
		fft(fftxk, fftorder);

		//Y(k)=X(k)W(k)
		for (int j=0; j<N2; ++j) {
			ifftyk[j].real = fftxk[j].real*fftwk[j].real - fftxk[j].image * fftwk[j].image;
			ifftyk[j].image = fftxk[j].image*fftwk[j].real + fftxk[j].real *fftwk[j].image;
		}
		ifft(ifftyk, fftorder);
		/*for (int i=N; i<N2; i++) {
			printf("ifftyk[%d].real:%f, ifftyk[%d].img:%f\n", i, ifftyk[i].real, i, ifftyk[i].image);
		}
		while(1);*/
		int k=0;
		//write outputdata
		for(int j=N; j<N2; ++j) {
			k = j+(i-1)*N;
			if (k < inputdata_length) {
				ptr_outputdata[k] = (short)(ifftyk[j].real);
				//ptr_outputdata[k] = (short)(ifftyk[j].real * 32767.f);
				//printf("ifftyk:%f\n", ifftyk[j].real);
				//printf("ifftyk:%f\n", (short)ifftyk[j].real);//大转小，%d打印
				//printf("%f\n", (ifftyk[j].real * 32767.f)/32767.f);
				//ptr_outputdata[k] = (short)((ifftyk[j].real * 32767.f)/32767.f);
				//printf("%f\n", ifftyk[j].real);
				//printf("ptr_outputdata[%d]:%hd\n", k, ptr_outputdata[k]);
			} else {
				break;
			}
		}

		//for (int i=0; i<N; i++) {
			//printf("outputdata[%d]:%d\n", i, outputdata[i]);
		//}
		//while(1);
	}
	return 0;
}
#endif
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
