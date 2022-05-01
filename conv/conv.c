#include <stdio.h>

/*
 *x[n]:the longer sequence
 *w[n]:the short sequence
 *y[n]:results of linear convolution
*/
void overlap_save(int xn[], int len_xn, int wn[], int len_wn, int yn[])
{
#if 0  /* 实现 overlap_save的伪代码*/
	int seq_m;
	complex X[], W[], Res[];

	seq_m = (int) log2(len_xn);
	FFTR(xn, len_xn, seq_m, X);

	seq_m = (int) log2(len_wn);
	FFTR(xn, len_xn, seq_m, W);

	complex_mul(X, W, Res);

	iFFT(Res);

	//取后面N个点
	yn=get last N point ;
#endif
}












