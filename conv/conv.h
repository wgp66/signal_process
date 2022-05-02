#ifndef __CONV_H__
#define __CONV_H__
void overlap_save(double xn[], int len_xn, double wn[], int len_wn, double yn[]);
void conv(double *inputdata, long input_len, double *rir_dat, long rir_length, double *outputdata);

#endif
