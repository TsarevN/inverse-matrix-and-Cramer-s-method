#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void DeleteElements(float** matrix, int n, float** TempMatrix, int row, int col)
{
	int k = 0;
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		if (i != row)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != col)
					TempMatrix[k][m] = matrix[i][j];
				else continue;
				m++;
			}
			m = 0;
			k++;
		}
		else continue;
	}
}

float Determinant(float** matrix, int n)
{
	float temp = 0;
	int k = 1;
	if (n == 1)
		temp = matrix[0][0];
	else
		if (n == 2)
			temp = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		else
		{
			for (int i = 0; i < n; i++)
			{
				int m = n - 1;
				int** temp_matr = malloc(m * sizeof(int));
				for (int j = 0; j < m; j++)
					temp_matr[j] = malloc(m * sizeof(int));

				DeleteElements(matrix, n, temp_matr, 0, i);
				temp = temp + k * matrix[0][i] * Determinant(temp_matr, m);
				k = -k;	
				free(temp_matr);
			}
		}
	return temp;
}

void MatrixTransponse(float** InvMatrix, float** TranspInvMatrix, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			TranspInvMatrix[j][i] = InvMatrix[i][j];
}

void NumberOne()
{
	int n, m;
	printf("Enter the size matrix:\n");
	printf("number of lines: ");
	scanf_s("%d", &n);
	printf("number of columns: ");
	scanf_s("%d", &m);
	if ((n != m) || (n < 1))
	{
		printf("Only a square matrix can have an inverse");
		exit(1);
	}
	float** matrix = (float**)malloc(n * (sizeof(float)));
	float** InvMatrix = (float**)malloc(n * (sizeof(float)));
	float** TranspInvMatrix = (float**)malloc(n * (sizeof(float)));
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = (float*)malloc(n * sizeof(float));
		InvMatrix[i] = (float*)malloc(n * (sizeof(float)));
		TranspInvMatrix[i] = (float*)malloc(n * (sizeof(float)));
	}
	printf("Enter matrix:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			printf("Matrix[%d][%d] = ", i, j);
			scanf_s("%f", &matrix[i][j]);
		}

	int Deter = Determinant(matrix, n);
	printf("\nDeterminant = %d\n", Deter);
	if (Deter == 0)
	{
		printf("The determinant is 0, the inverse matrix does not exist");
		exit(1);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			float** TempMatrix = (float*)malloc(n * sizeof(float));
			for (int k = 0; k < n-1; k++)
				TempMatrix[k] = ((float*)malloc(n * sizeof(float)));
			DeleteElements(matrix, n, TempMatrix, i, j);
			InvMatrix[i][j] = pow(-1, i + j + 2) * Determinant(TempMatrix, n-1) / Deter;
		}
	MatrixTransponse(InvMatrix, TranspInvMatrix, n);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.3f ", TranspInvMatrix[i][j]);
		}
		printf("\n");
	}
}

void NumberTwo()
{
	int n;
	int m;
	int DeterMatrix;
	printf("Enter the size matrix:\n");
	printf("number of lines: ");
	scanf_s("%d", &n);
	printf("number of columns: ");
	scanf_s("%d", &m);
	if ((n != m) || (n < 1))
	{
		printf("Incorrect size of matrix");
		exit(1);
	}
	float** matrix = (float**)malloc(n * (sizeof(float)));
	float* freeVar = (float*)malloc(n * (sizeof(float)));
	float* answer = (float*)malloc(n * (sizeof(float)));
	for (int i = 0; i < n; i++)
		matrix[i] = (float*)malloc(n * (sizeof(float)));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			printf("A[%d][%d]=", i, j);
			scanf_s("%f", &matrix[i][j]);
		}
	printf("\nEnter free variables\n");
	for (int i = 0; i < n; i++)
	{
		printf("b[%d]=", i);
		scanf_s("%f", &freeVar[i]);
	}
	DeterMatrix = Determinant(matrix, n);
	printf("\nDeterminant = %d\n", DeterMatrix);

	if (DeterMatrix == 0)
	{
		printf("\nThe determinant is 0, the Cramer method cannot be solved\n");
		exit(1);
	}

	float* detMatrix = (float*)malloc(n * (sizeof(float)));
	float* temp = (float*)malloc(n * (sizeof(float)));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[j] = matrix[j][i];
			matrix[j][i] = freeVar[j];
		}

		detMatrix[i] = Determinant(matrix, n);

		for (int k = 0; k < n; k++)
			matrix[k][i] = temp[k];

	}

	printf("\nSearched roots:\n");
	for (int i = 0; i < n; i++)
	{
		answer[i] = detMatrix[i] / DeterMatrix;
		printf("\nx%d = %.3f\n", i + 1, answer[i]);
	}

	free(detMatrix);
	free(temp);
}

int main()
{
	NumberOne();
	NumberTwo();
	return 0;
}
