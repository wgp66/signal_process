#include <stdio.h>
#include <math.h>
#include "baselib/baselib.h"
#include "conv/conv.h"

int main(void)
{
	int i;
	double xn[2*N], wn[N], res[2*N];
	complex result[2*N];

	/* 初始化输入序列 */
	for (i=0; i<2*N; i++) {
		xn[i]=i;
	}

	for (i=0; i<N; i++) {
		wn[i]=i;
	}

	overlap_save(xn, 2*N, wn, N, res);

	for (i=N; i<N*2; i++) {
		printf("res[%d].img=%f\n", i, res[i]);
	}

}

