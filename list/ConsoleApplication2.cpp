#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <stack>

using namespace std;
vector<bool> vis;
int swt = 0;


vector<vector<int>> cmej_mat(int num_vertices, double veroj) {
	vector<vector<int>> cmej_mat(num_vertices + 1, vector<int>(num_vertices + 1, 0));
	int cont = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = i + 1; j <= num_vertices; ++j) {
			if (static_cast<double>(rand()) / RAND_MAX < veroj) {
				cmej_mat[i][j] = 1;
				cmej_mat[j][i] = 1;
				cont++;
			}
		}
	}

	if (cont == 0) {
		swt = 1;
	}
	printf("Матрица смежности:\n");
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			printf("%d ", cmej_mat[i][j]);
		}
		printf("\n");
	}
	return cmej_mat;
}

vector<vector<int>> matrixToList(const vector<vector<int>>& matrix) {
	int num_vertices = matrix.size() - 1;
	vector<vector<int>> adjacency_list(num_vertices + 1);
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			if (matrix[i][j] == 1) {
				adjacency_list[i].push_back(j);
			}
		}
	}
	return adjacency_list;
}



void DFS_List(int v, const vector < vector < int>>& adjacency_list) {
	if (adjacency_list[v].empty())
		return; 

	vis[v] = 1;
	printf("%d ", v);
	

	for (int neighbor : adjacency_list[v]) {
		if (!vis[neighbor]) {
			DFS_List(neighbor, adjacency_list);
		}
	}
}

void printList(const vector<vector<int>>& list) {
	printf("Список смежности:\n");
	for (int i = 1; i < list.size(); ++i) {
		printf("%d: ", i);
		for (int j : list[i]) {
			printf("%d ", j);
		}
		printf("\n");
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	int num_vertices;
	double veroj = 0.5;
	printf("Введите количество вершин: ");
	scanf("%d", &num_vertices);
	srand(static_cast<unsigned int>(time(0)));
	auto matrix = cmej_mat(num_vertices, veroj);
	auto adjacency_list = matrixToList(matrix);
	if (swt == 1) {
		printf("\nОбход произвести нельзя! Первая вершина изолированна\n");
	}
	else {
		printList(adjacency_list);
		vis = vector<bool>(num_vertices + 1, false);
		printf("Обход в глубину для списка: ");
		for (int i = 1; i <= num_vertices; ++i) {
			if (!vis[i]) {
				DFS_List(i, adjacency_list);
			}
		}
		printf("\n");
	}
	return 0;
}