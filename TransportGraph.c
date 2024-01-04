#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MAX_SIZE 400	//Максимальное количество возможных вершин
#define FICTIVE_SIZE 500 //Максимально возможное число вершин вместе с фиктивными

void CreateGraph(int (*Graph)[MAX_SIZE], int cols, int rows);	//Функция создания транспортного графа
void AddFictiveVertex(int (*graph)[MAX_SIZE], int cols, int rows, int vertex);	//Функция добавления фиктивной фершины

int main() 
{
	srand(time(NULL));
	//Graph[][] - матрица смежности графа
	//vertex - номер вершины, от которой ищутся пути
	int Graph[MAX_SIZE][MAX_SIZE], cols = 5, rows = 5, vertex = 3;
	
	CreateGraph(Graph, cols, rows);	//Рандомное заполнение графа
	printf("\n");
	AddFictiveVertex(Graph, cols, rows, vertex);	//Добавление фиктивной вершины
	
	system("pause");	//Системная команда чтобы окно консоли не закрывалось
	
	return 0;
}

void CreateGraph(int Graph[][MAX_SIZE], int cols, int rows)
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			Graph[i][j] = rand() % 2;	//Генерируем числа 1 или 0
			if(i == j) Graph[i][j] = 0;	//Обнуляем главную диагональ
			printf("%d ", Graph[i][j]);	//Попутно выводим матрицу
		}
		printf("\n");
	}
}

void AddFictiveVertex(int graph[][MAX_SIZE], int cols, int rows, int vertex)
{
	int Graph[FICTIVE_SIZE][FICTIVE_SIZE];	//Граф с добавляемой фиктивной вершиной
	
	//Копируем все вершины из исходного графа в целевой 
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			Graph[i][j] = graph[i][j];
	
	//Копируем рёбра в фиктивную вершину
	for(int i = 0; i < rows; i++)
		Graph[i][cols] = graph[i][vertex];
	
	for(int i = 0; i < cols; i++)
		Graph[rows][i] = graph[vertex][i];


	for(int i = 0; i <= rows; i++)
	{
		for(int j = 0; j <= cols; j++)
		{
			printf("%d ", Graph[i][j]);
		}
		printf("\n");
	}
}
