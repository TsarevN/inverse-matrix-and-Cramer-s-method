#include <malloc.h>
#include <stdio.h>
#include <math.h>	

double det(int n, double** mat)
{
	double d = 0;
	int c, subi, i, j, subj;
	double** submat = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		submat[i] = (double*)malloc(n * sizeof(double));
	if (n == 2)
	{
		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	}
	else
	{
		for (c = 0; c < n; c++)
		{
			subi = 0;
			for (i = 1; i < n; i++)
			{
				subj = 0;
				for (j = 0; j < n; j++)
				{
					if (j == c)
					{
						continue;
					}
					submat[subi][subj] = mat[i][j];
					subj++;
				}
				subi++;
			}
			d = d + (pow(-1, c) * mat[0][c] * det(n - 1, submat));
		}
	}
	free(submat);
	return d;

}

void inversion(double** A, int N) 
{
	double DeterMatrix;
	DeterMatrix = det(N, A);
	if (DeterMatrix == 0)
	{
		printf("\nThe determinant is 0, the inverse matrix does not exist\n");
	}
	else
	{
		double temp;
		double** E = (double**)malloc(N * sizeof(double));

		for (int i = 0; i < N; i++)
			E[i] = (double*)malloc(N * sizeof(double));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				E[i][j] = 0.0;

				if (i == j)
					E[i][j] = 1.0;
			}
		}

		for (int k = 0; k < N; k++)
		{
			temp = A[k][k];

			for (int j = 0; j < N; j++)
			{
				A[k][j] /= temp;
				E[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				A[i][j] = E[i][j];

		printf("Inversion matrix:\n");
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				printf("%.3lf ", A[i][j]);
			}
			printf("\n");
		}

		free(E);
	}

}

void Kramer(int n, double** aMain, double* freeVar, double* answer)
{
	double* detArray = (double*)malloc(n * sizeof(double));
	double deterMain;
	double* temp = (double*)malloc(n * sizeof(double));
	deterMain = det(n, aMain);
	if (deterMain == 0)
	{
		printf("\nThe determinant is 0, the Cramer method cannot be solved\n");
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				temp[j] = aMain[j][i];
				aMain[j][i] = freeVar[j];
			}
	
			detArray[i] = det(n, aMain);
			
			for (int k = 0; k < n; k++)
				aMain[k][i] = temp[k];

		}

		printf("\nSearched roots:\n");
		for (int i = 0; i < n; i++)
		{
			answer[i] = detArray[i] / deterMain;
			printf("\nx%d = %.3lf\n", i + 1, answer[i]);
		}

		free(detArray);
		free(temp);
	}
}


int main()
{
	int n;
	double DeterMatrix;
	printf("Enter a number of variables ");
	scanf_s("%d", &n);
	double** aMain = (double**)malloc(n * sizeof(double));
	double** aMain1 = (double**)malloc(n * sizeof(double));
	double* freeVar = (double*)malloc(n * sizeof(double));
	double* answer = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		aMain[i] = (double*)malloc(n * sizeof(double));
		aMain1[i] = (double*)malloc(n * sizeof(double));
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			printf("A[%d][%d]=", i, j);
			scanf_s("%lf", &aMain[i][j]);
			aMain1[i][j] = aMain[i][j];
		}
	printf("\nEnter free variables\n");
	for (int i = 0; i < n; i++)
	{
		printf("b[%d]=", i);
		scanf_s("%lf", &freeVar[i]);
	}
	printf("\nOriginal Matrix:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.0lf ", aMain[i][j]);
		}
		printf("\n");
	}

	DeterMatrix = det(n, aMain);
	printf("\nDeterminant = %.3lf\n", DeterMatrix);
	printf("\n");

	inversion(aMain1, n);	//NumberOne

	Kramer(n, aMain, freeVar, answer);	//NumberTwo

	free(aMain);
	free(aMain1);
	free(freeVar);
	free(answer);

	return 0;
}