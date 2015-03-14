#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

int segmentation_branch(int n, double time, double delta_t) {
	int a = 0;
	int b = 101;
	double r;
	double p;
	double B, E, S, Tay, T;
	double c;
	B = 17.38;
	E = 0.39;
	S = 0;
	Tay = 0.2927;
	T = 14;
	c = rand() % (61 - 40) + 40;
	p = ((1 / pow(n, E))*B*(1 / exp(time / T))*(exp(delta_t / T) - 1)*pow(2, n - 1)) / c;

	p = round(p * 1000);//10000

	r = rand()%(b-a)+a;
	printf("p = %lf r = %lf\n", p,r);
	if (p > r) {
		return(1);
	}
	else {
		return(0);
	}
}

double length_branch(double tcr, double L) { //tcl - шаг
	const double a = 0.1;
	const double b = 1.1;
	const double C = 14;
	const double tay = 0.2927;
	const double Vat = 1;
	double k1, k2, k3, k4;
	double length_1;

	if (L >= 0) {
		k1 = a * C * exp(-tay * L / Vat) - b;
		k2 = a * C * exp(-tay * (L + tcr * k1 / 2) / Vat) - b;
		k3 = a * C * exp(-tay * (L + tcr * k2 / 2) / Vat) - b;
		k4 = a * C * exp(-tay * (L + tcr * k3 / 2) / Vat) - b;
		L = L + tcr / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
		if (L >= 0) {
			length_1 = L;
		}
		else {
		length_1 = 0;
		}
	}
	printf("Length = %lf\n", length_1);
	return(length_1);
}

void main() {
	setlocale(LC_ALL,"Rus");
	//srand(10000);
	srand((unsigned int)time(0));

	int i, j, n, vertex_number,k, delta_n, vertex, x;
	//int flag[4] = { 0, 1, 0, 1 };
	int segmentation;
	double time, time_max;
	double *p_time = &time;
	double delta_time;

	const int MAX = 1000;
	const int LINE = 100;
	const int BRANCH = 200;
	int tree[25];
	int length[25] = { 0 };
	double real_length[25] = { 0 };
	int ways[25][2] = {0};
	int division[25] = {0};
	int protein = MAX;
	double B, E, S, Tay, T;
	double length_count = 0;
	int vertrex_count=1;
	B = 17.38;
	E = 0.39;
	S = 0;
	Tay = 0.2927;
	T = 14;

	time_max = 100;
	delta_time = 0.1;
	time = delta_time;
	k = 0;
	vertex_number = 0;
	j = 1;
	n = 1; // n - сегмент деления
	vertex = 1;
	tree[0] = -1; //-1 вершина не связана
	while (time < time_max) {
		segmentation = segmentation_branch(n, time, delta_time);
		if (segmentation == 0) {	 //1 ветвь
			if ((protein - LINE) > 0) {
				protein -= LINE;
				tree[j] = vertex_number;
				real_length[vertrex_count] = length_branch(time, real_length[tree[vertex_number+1]]);
				vertrex_count++;
				vertex_number++;
				vertex++;
			}
			else {
				protein = -1;
			}
		}
		else {				//2 ветви
			if ((protein - BRANCH) > 0) {
				protein -= BRANCH;
				vertex += 2;
				tree[j] = vertex_number;
				real_length[vertrex_count] = length_branch(time, real_length[tree[vertex_number+1]]);
				vertrex_count++;
				tree[j + 1] = vertex_number;
				real_length[vertrex_count] = length_branch(time, real_length[tree[vertex_number+1]]);
				vertrex_count++;
				vertex_number++;
				length_count++;
				j++;
			}
			else {
				protein = -1;
			}
		}
		j++;
		k++;
		n++;
		time = time + delta_time;
		if (protein <= 0) {
			break;
		}
	}
	printf("\nTime = %lf\nСегмент = %d\n", time,n);
	printf_s("Общий вид графа:\n");
	for (i = 0; i < vertex; i++) {
		printf_s("%2d ", i+1);
	}
	printf_s("\n");
	for (i = 0; i < vertex; i++) {
		printf_s("%2d ",tree[i]+1);
	}
	printf_s("\n");
	for (i = 0; i < vertex - 1;i++) {
		if (tree[i] == tree[i + 1]) {
			division[tree[i]] = 1;
		}
	}

	for (i = vertex - 1; i > 1; i--) {
		int isLeafOrFork = 1;
		for (j = 0; j < vertex; j++) {
			if (i == tree[j]) {
				isLeafOrFork = 0;
			}
			if (division[i]==1) {
				isLeafOrFork = 1;
			}
		}
		if (isLeafOrFork) {
			int parentNode;
			int isBranch = 1;
			int nodeIndex = i;
			int branchLength = 0;
			ways[i][1] = i;
			while (isBranch) {
				branchLength++;
				parentNode = tree[nodeIndex];
				if ((division[parentNode] == 1) || (parentNode == 0)) {
					isBranch = 0;
				}
				else {
					nodeIndex = parentNode;
				}
			}
			length[i] = branchLength;
			ways[i][0] = tree[nodeIndex];
		}
	}
	printf_s("\nДлина отростков(путь - число веток - общая длина): \n");

	for (i = 0; i < vertex; i++) {
		int flag;
		if (!length[i]==0) {
			length_count = real_length[i];
			flag = 1;
			j = tree[i];
			while (flag == 1) {
				if (!(j == ways[i][0])) {
					length_count += real_length[j];
					j = tree[j];
				}
				else {
					flag = 0;
				}
			}
			printf_s("(%d-%d) %d %lf\n", ways[i][0] + 1, ways[i][1] + 1, length[i], length_count);
		}
	}

	//printf_s("Товарищ! Проверь первую точку! Потерять длину одного отрезка можешь ты!\n");
	system("PAUSE");
}
