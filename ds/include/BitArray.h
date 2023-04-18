#ifndef __BITARRAY_H__
#define __BITARRAY_H__


typedef size_t bitarr_t;

#define TURN_ON (size_t)(0xFFFFFFFFFFFFFFFF)
#define TRUE (size_t)1
#define FALSE (size_t)0
#define SIZE_ARR (size_t)(64)
#define SIZE_LUT (256)
#define UNUSED(a) ((void)a)
#define NIBBLE (4)

bitarr_t BitArrSetOn(bitarr_t arr, size_t pos);

bitarr_t BitArrSetOff(bitarr_t arr, size_t pos);

bitarr_t BitArrSet(bitarr_t arr, size_t pos, int bool_val);

size_t BitArrGetVal(bitarr_t arr, size_t pos);

bitarr_t BitArrSetAll(bitarr_t arr);

bitarr_t BitArrResetAll(bitarr_t arr);

size_t BitArrCountOn(bitarr_t arr);

size_t BitArrCountOff(bitarr_t arr);

size_t BitArrCountOnLUT(bitarr_t arr);

bitarr_t BitArrFlip(bitarr_t arr, size_t pos);

bitarr_t BitArrMirror(bitarr_t arr);

bitarr_t BitArrRotateLeft(bitarr_t arr, size_t shift);

bitarr_t BitArrRotateRight(bitarr_t arr, size_t shift);

char *BitArrToString(bitarr_t arr, char *dest);

size_t BitArrMirrorLUT(bitarr_t arr);

#endif
