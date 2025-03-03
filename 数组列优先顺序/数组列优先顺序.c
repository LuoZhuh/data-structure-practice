#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<assert.h>

#define OK 1
#define ERROR -1

#define MAX_DIM 8

typedef int ElemType;

typedef struct {
	ElemType* base;
	int dim;
	int* bounds;
	int* constants;
}Array;

int InitArray(Array* pArr, int nDim, ...);
void DestroyArray(Array* pArr);
int Locate(Array* pArr, int nDim, va_list ap);
int Assign(Array* pArr, ElemType* elm, ...);
int Value(Array* pArr, ElemType* elm, ...);

int InitArray(Array* pArr, int nDim, ...) {
	if (nDim<1 || nDim>MAX_DIM)
		return ERROR;

	pArr->dim = nDim;

	pArr->bounds = (int*)malloc(nDim * sizeof(int));
	if (!pArr->bounds)
		return ERROR;

	int nElemCount = 1;
	va_list ap;
	va_start(ap, nDim);

	for (int i = nDim - 1; i >= 0; i--) {
		pArr->bounds[i] = va_arg(ap, int);
		if (pArr->bounds[i] < 0)
			return ERROR;

		nElemCount *= pArr->bounds[i];
	}
	va_end(ap);

	pArr->base = (ElemType*)malloc(nElemCount * sizeof(ElemType));
	if (!pArr->base)
		return ERROR;

	pArr->constants = (int*)malloc(nDim * sizeof(int));
	pArr->constants[nDim - 1] = 1;
	for (int i = nDim - 2; i >= 0; i--) {
		pArr->constants[i] = pArr->constants[i + 1] * pArr->bounds[i + 1];
	}

	return OK;
}

void DestroyArray(Array* pArr) {
	if (pArr->base)
		free(pArr->base);

	if (pArr->bounds)
		free(pArr->bounds);

	if (pArr->constants)
		free(pArr->constants);
}

int Locate(Array* pArr, int nDim, va_list ap) {
	int nPos = 0, ind = 0;

	for (int i = nDim - 1; i >= 0; i--) {
		ind = va_arg(ap, int);

		assert(ind >= 0 && ind < pArr->bounds[i]);

		nPos += pArr->constants[i] * ind;
	}
	va_end(ap);

	return nPos;
}

int Assign(Array* pArr, ElemType* elm, ...) {
	int nPos;
	va_list ap;
	va_start(ap, elm);
	nPos = Locate(pArr, pArr->dim, ap);
	pArr->base[nPos] = *elm;

	return OK;
}

int Value(Array* pArr, ElemType* elm, ...) {
	int nPos;
	va_list ap;
	va_start(ap, elm);
	nPos = Locate(pArr, pArr->dim, ap);
	*elm = pArr->base[nPos];

	return OK;
}

int main() {
	Array arr;

	InitArray(&arr, 3, 2, 3, 5);

	int a;
	int i = 0, m = 0, n = 0;
	for (i = 0; i < 2; ++i)
		for (m = 0; m < 3; ++m)
			for (n = 0; n < 5; ++n)
			{
				a = i + m + n;
				Assign(&arr, &a, i, m, n);
			}

	int b = 0;
	for (i = 0; i < 2; ++i)
		for (m = 0; m < 3; ++m)
			for (n = 0; n < 5; ++n)
			{
				Value(&arr, &b, i, m, n);
				printf("[%d][%d][%d]=%d\n", i, m, n, b);
			}

	DestroyArray(&arr);

	return 0;
}