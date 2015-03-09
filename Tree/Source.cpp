#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

int random_numbers() {
	int a = 0;
	int b = 2;
	return(rand()%(b-a)+a);
}

void main() {
	setlocale(LC_ALL,"Rus");
	srand((unsigned int)time(0));
	int i, j, n, k, delta_n, vertex;
	//int flag[4] = { 0, 1, 0, 1 };
	int flag;

	const int MAX = 1000;
	const int LINE = 100;
	const int BRANCH = 200;
	int tree[25];
	int length[25] = { 0 };
	int ways[25][2] = {0};
	int division[25] = {0};
	int protein = MAX;
	k = 0;
	n = 0;
	j = 1;
	vertex = 1;
	tree[0] = -1; //-1 вершина не связана
	while (protein>0) {
		flag = random_numbers();
		if (flag == 0) {	 //1 ветвь
			if ((protein - LINE) > 0) {
				protein -= LINE;
				tree[j] = n;
				n++;
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
				tree[j] = n;
				tree[j+1] = n;
				n++;
				j++;
			}
			else {
				protein = -1;
			}
		}
		j++;
		k++;
	}
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

	for (i = vertex-1; i > 1; i--) {
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
			ways[i][0] = i;
			while (isBranch) {
				branchLength++;
				parentNode = tree[nodeIndex];
				if (division[parentNode] == 1 || parentNode == 0) {
					isBranch = 0;
				}
				else {
					nodeIndex = parentNode;
				}
			}
			length[i] = branchLength;
			ways[i][1] = tree[nodeIndex];
		}
	}

	printf_s("\nДлина отростков: \n");
	for (i = 0; i < vertex; i++) {
		printf_s("(%d-%d) %d\n", ways[i][1]+1, ways[i][0]+1, length[i]);
	}
	system("PAUSE");
}
