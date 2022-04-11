#ifndef _FROM_FILE_H_IS_INCLUDED_
#define _FROM_FILE_H_IS_INCLUDED_

void read_dimensions(char* input, int* x, int* y);

void from_file(char* input, int x, int y, double arr[x * y][x * y], int ps);

#endif
