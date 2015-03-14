#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

void main() {
	setlocale(LC_ALL, "Rus");
	const double a = 0.1;
	const double b = 1.1;
	const double C = 14;
	const double tay = 0.2927;
	const double Vat = 1;
	double L, tcr, tc, k1, k2, k3, k4, s, dl;
	double length_1;
	int i, n;

	dl = 100; //время
	tcr = 2;	//шаг
	L = 0;
	n = round(dl / tcr);
	printf("n = %d\n",n);
	for (i = 0; i < n; i++) {
		if (L >= 0) {
			k1 = a * C * exp(-tay * L / Vat) - b;
			k2 = a * C * exp(-tay * (L + tcr * k1 / 2) / Vat) - b;
			k3 = a * C * exp(-tay * (L + tcr * k2 / 2) / Vat) - b;
			k4 = a * C * exp(-tay * (L + tcr * k3 / 2) / Vat) - b;
			L = L + tcr / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
			tc = i * tcr;
			if (L >= 0) {
				length_1 = L;
			}
			printf("%lf\n", length_1);
		}
		else {
			length_1 = 0;
		}
	}
	printf("%lf\n",length_1);
	system("PAUSE");
}
