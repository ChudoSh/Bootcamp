#ifndef __BITWISE_H__
#define __BITWISE_H__

long Pow2(unsigned int x, unsigned int y);
unsigned int IsPow2_Lp(unsigned int);
unsigned int IsPow2_No_Lp(unsigned int);
unsigned int AddOne(unsigned int n);
void ThreeBit(unsigned int *n, size_t size);
unsigned int CountBit(unsigned int n);
unsigned char ByteMirrors_LP(unsigned char n);
unsigned char ByteMirrors_No_LP(unsigned char n);
unsigned int BothTwoSix(unsigned char n);
unsigned int EitherTwoSix(unsigned char n);
unsigned int SwapThreeFive(unsigned char n);
unsigned int HexaDec(unsigned char n);
void SwapValues(unsigned int *p,unsigned int *q);
unsigned int CountNumBits_LP(unsigned int n);
unsigned int CountNumBits_No_Lp(unsigned int n);
void BitFloat(float num);


#endif

