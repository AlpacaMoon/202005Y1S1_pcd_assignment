#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

float roundOff(float f, int dec) {
	int decimalPlace = pow(10, dec);
	float value = (int)(f * decimalPlace + 0.5);

	float result = (float)value / decimalPlace;
	return result;
}

int main() {
	// 4.347826087
	float x = (5.0 / 115.0) * 100.0;
	printf("%f\n", x);
	printf("%f\n", roundOff(x, 1));
	printf("%f\n", roundOff(x, 2));
	printf("%f\n", roundOff(x, 3));
	printf("%f\n", roundOff(x, 4));
	printf("%f\n", roundOff(x, 5));
	printf("%f\n", roundOff(x, 6));

	/*
	char str[72] = "[ Gathering Supplies... / ]";

	float f = ((float)72 - strlen(str)) / 2;
	printf("String length: %d\n", strlen(str));
	printf("Indent length: %.2f\n", f);
	printf("Number of Tab: %d\n", (int)f / 8);
	printf("Number of space: %d\n", (int)f % 8);
	*/
}