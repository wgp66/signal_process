 /***************************************************************************
  *
  * Homework for chapter 3 -- "overlap-save method"
  *
  * In the main function, we have finished data preparation for you. The
  * add-reverb function "conv" is called here. All you have to do is to
  * finish the add-reverb function in conv.cpp. Run the project to check
  * if the processed audio is right or not.
  *
  * The format of input/output audio is pcm ".raw". You can use Audition
  * or Cooledit to see the waveform or spectrogram of pcm audio files.
  *
  **************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "conv.h"
#include "rir.h"
#include "typedefs.h"
#include "baselib.h"

#define N 8

int main(int argc, char* argv[])
{
#if 1
    // open input and output file
    FILE *fpin, *fpout;
    fpin = fopen("audio.raw", "rb");
    if(NULL == fpin) {
        printf("open file %s error.\n", argv[1]);
        return -1;
    }

    fpout = fopen("audio_out.raw", "wb");
    if(NULL == fpout) {
        printf("open file %s error.\n", argv[2]);
        fclose(fpin);
        return -1;
    }

    // get date length of input audio
    fseek(fpin, 0, SEEK_END);
    long rir_length = 4096;
    long inputdata_length = ftell(fpin);
    inputdata_length /= 2;
    rewind(fpin);
    short* inputdata = new short[inputdata_length];
    short* outputdata = new short[inputdata_length];
    fread(inputdata, sizeof(short), inputdata_length, fpin);

    // add rir
    conv(inputdata, inputdata_length, rir, rir_length, outputdata);

    // save output
    fwrite(outputdata, sizeof(short), inputdata_length, fpout);

    printf("Add rir to %s, OK.\n", argv[1]);
    delete [] inputdata;
    delete [] outputdata;
    fclose(fpin);
    fclose(fpout);
    return 0;
#else
	int i;
	COMPLEX INPUT_SEQ[N], RES_SEQ[N], OUTPUT_SEQ[N];
	double SEQ_DAT[N];
	int M = (int)log2(N);
	//构造实数序列
	for (i = 0; i < N; i++) {
		SEQ_DAT[i] = i;
	}

	//构造虚数序列
	for (i = 0; i < N; i++) {
		INPUT_SEQ[i].real = SEQ_DAT[i];
		INPUT_SEQ[i].image = 0;
	}

	fft(INPUT_SEQ, M);

	for (i = 0; i < N; i++) {
		printf("fft: INPUT_SEQ[%d].real=%f, INPUT_SEQ[%d].img=%f\n", i, INPUT_SEQ[i].real, i, INPUT_SEQ[i].image);
	}
	printf("\n\n");
#endif
}

