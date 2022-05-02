#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "baselib/baselib.h"
#include "conv/conv.h"
#include "rir.h"

int main(void)
{
	//open input and output file
	FILE *fpin, *fpout;
	fpin=fopen("audio.raw", "rb");
	if (NULL == fpin) {
		printf("open source file error!\n");
		fclose(fpin);
		return -1;
	}

	fpout=fopen("audio_out.raw", "wb");
	if (NULL == fpin) {
		printf("open output file error!\n");
		fclose(fpin);
		fclose(fpout);
		return -1;
	}

	//get date length of input audio file
	fseek(fpin, 0, SEEK_END);
	int inputdata_length=ftell(fpin);
	int rir_length = sizeof(rir)/sizeof(double);//4096
	rewind(fpin);

	double *inputdata = (double *)malloc(inputdata_length * sizeof(double));
	double *outputdata = (double *)malloc(inputdata_length * sizeof(double));
	fread(inputdata, 1, inputdata_length, fpin);

	//printf("inputdata_length:%ld\n", inputdata_length);
	//printf("rir_len=%d\n", sizeof(rir)/sizeof(double));

	// add rir
	conv(inputdata, inputdata_length, rir, rir_length, outputdata);

	// save output
	fwrite(outputdata, 1, inputdata_length, fpout);
	free(inputdata);
	free(outputdata);
	fclose(fpin);
	fclose(fpout);
	return 0;
}

