#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MAX_SIZE 400	//Максимальное количество возможных вершин

void CreateGraph(int (*Graph)[MAX_SIZE], int size);	//Функция создания транспортного графа
int VertexNumber(int (*Graph)[MAX_SIZE], int size, int vertex);	//Функция подсчёта числа инцидентных рёбер
int AddFictiveVertex(int (*graph)[MAX_SIZE], int size, int vertex, int count);	//Функция добавления фиктивной фершины
void ReducedMatrix(int (*Graph)[MAX_SIZE], int size);	//Функция приведения матрицы по столбцам истрокам

int main() 
{
	srand(time(NULL));
	//Graph[][] - матрица смежности графа
	//vertex - номер вершины, от которой ищутся пути
	int Graph[MAX_SIZE][MAX_SIZE], size = 5, vertex = 1, VertexNum = 0;
	
	CreateGraph(Graph, size);	//Рандомное заполнение графа
	
	//Вывод сгенерированной матрицы
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%3d ", Graph[i][j]);
		printf("\n");
	}
	printf("\n");
	
	VertexNum = VertexNumber(Graph, size, vertex);	//Число добавляемых фиктивных узлов 
	printf("Vertex number = %d\n", VertexNum);
	size = AddFictiveVertex(Graph, size, vertex, VertexNum);	//Добавление фиктивной вершины
	
	//Вывод нового графа с фиктивными вершинами
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			printf("%3d ", Graph[i][j]);
		}
		printf("\n");
	}
	printf("New size = %d\n", size);
	
	ReducedMatrix(Graph, size);	//Приведение матрицы по строкам и столбцам
	
	//Вывод приведённой матрицы
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			printf("%3d ", Graph[i][j]);
		}
		printf("\n");
	}
	
	system("pause");	//Системная команда чтобы окно консоли не закрывалось
	
	return 0;
}

void CreateGraph(int Graph[][MAX_SIZE], int size)
{
	for(int i = 0; i < size; i++)
		for(int j = i; j < size; j++)
		{
			Graph[i][j] = rand() % 50;	//Генерируем числа
			Graph[j][i] = Graph[i][j];
			if(i == j) Graph[i][j] = 0;	//Обнуляем главную диагональ
		}
}

int VertexNumber(int Graph[][MAX_SIZE], int size, int vertex)
{
	int count = 0;	//Счётчик числа рёбер
	
	for(int i = 0; i < size; i++)
		if(Graph[vertex][i] > 0) count++;
	
	return count;
}

int AddFictiveVertex(int Graph[][MAX_SIZE], int size, int vertex, int count)
{
	count--;	//Число фиктивных вершин = число инцидентных рёбер - 1
	
	//Копируем рёбра в фиктивную вершину
	for(int k = 0; k < count; k++)
	{
		for(int i = 0; i < size; i++)
			Graph[i][size] = Graph[i][vertex];
		
		for(int i = 0; i < size; i++)
			Graph[size][i] = Graph[vertex][i];
		
		size++;	//Определяем новый размер матрицы
	}
	
	//Заполняем все пропасти отрицательными хначениями
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(Graph[i][j] == 0) Graph[i][j] = -1;
	
	return size;
}

void ReducedMatrix(int Graph[][MAX_SIZE], int size)
{
	int min_number = 50000;	//Устанавливаем недостижимое значение
	
	//Приведение по строкам
	for(int i = 0; i < size; i++)
	{
		//Поиск минимального значения в строке
		for(int j = 0; j < size; j++)
			if((min_number > Graph[i][j]) && (Graph[i][j] > 0)) min_number = Graph[i][j];
		//Вычитание миничального значения из каждого элемента строки
		for(int j = 0; j < size; j++)
			Graph[i][j] = Graph[i][j] - min_number;
		
		min_number = 50000;
	}
	
	//Приведение по столбцам
	for(int i = 0; i < size; i++)
	{
		//Поиск минимального значения в столбце отличного от нуля
		for(int j = 0; j < size; j++)
		{
			if(Graph[j][i] == 0) goto label;	//Если найден 0, завершить обработку столбца
			if((min_number > Graph[j][i]) && (Graph[j][i] > 0)) min_number = Graph[j][i];
		}
		//Вычитание миничального значения из каждого элемента столбца
		for(int j = 0; j < size; j++)
			Graph[j][i] = Graph[j][i] - min_number;
		
		label:	//Переход, если в столбце найден 0
		min_number = 50000;
	}
}
