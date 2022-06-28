#include <iostream>
#include <cmath>
#include <string>
using namespace std;
void matrix_store(double **Mat, int *R, int *C);
void matrix_print(double **Mat, int *R, int *C);
void matrix_add(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC);
void matrix_sub(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC);
void matrix_multi(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC);
double matrix_det(double **Mat, int n);
void matrix_trans(double **Mat, int *R, int *C);
void matrix_div(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC);
void matrix_inverse(double **a, int *R, int*C);
void menu(double **A, double **B, int *aR, int *aC, int *bR, int *bC);
int main(void)
{
	int Arow, Acolumn, Brow, Bcolumn;
	string choice;
	cout << "Welcome to the basic matrix operations performing application.\n";
	cout << "\nPlease Enter dimenstions of matrix (A): " << endl;
	cout << "rows: ";
	cin >> Arow;
	cout << "columns: ";
	cin >> Acolumn;
	cout << "Please Enter dimenstions of matrix (B): " << endl;
	cout << "rows: ";
	cin >> Brow;
	cout << "columns: ";
	cin >> Bcolumn;
	double **matA = new double*[Arow];
	for (int i = 0; i<Arow; i++) matA[i] = new double[Acolumn];
	double **matB = new double*[Brow];
	for (int i = 0; i<Brow; i++) matB[i] = new double[Bcolumn];
	cout << "\nWhich matrix would you like to store its data? (write down A or B)\n";
	cout << "Your response: "; cin >> choice;
	while (1)
	{
		if (choice == "A" || choice == "a")
		{
			matrix_store(matA, &Arow, &Acolumn);
			cout << "\nWould you like to store data of matrix B also ? (y/n)\n";
			cout << "Your response: "; cin >> choice;
			if (choice == "y")
			{
				matrix_store(matB, &Brow, &Bcolumn);
				break;
			}
			else break;
		}
		else if (choice == "B" || choice == "b")
		{
			matrix_store(matB, &Brow, &Bcolumn);
			cout << "\nWould you like to store data of matrix A also ? (y/n)\n";
			cout << "Your response: "; cin >> choice;
			if (choice == "y")
			{
				matrix_store(matA, &Arow, &Acolumn);
				break;
			}
			else break;
		}
		else cout << "Your entry " << choice << " is not recognized as it would be, please try again!\n";
	}
	menu(matA, matB, &Arow, &Acolumn, &Brow, &Bcolumn);
	for (int i = 0; i<Arow; i++) delete[] matA[i];
	delete[] matA;
	for (int i = 0; i<Brow; i++) delete[] matB[i];
	delete[] matB;
	return 0;
}
void menu(double **A, double **B, int *aR, int *aC, int *bR, int *bC)
{
	string choice;
	cout << "\n\nThe main menu of the application:\n";
	cout << "\nCommand line (write help to see the usage guide): "; cin >> choice;
	if (choice[1] == '+')
	{
		if (choice[0] == 'A') matrix_add(A, B, aR, aC, bR, bC);
		else if (choice[0] == 'B') matrix_add(B, A, aR, aC, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '-')
	{
		if (choice[0] == 'A') matrix_sub(A, B, aR, aC, bR, bC);
		else if (choice[0] == 'B') matrix_sub(B, A, aR, aC, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '*')
	{
		if (choice[0] == 'A') matrix_multi(A, B, aR, aC, bR, bC);
		else if (choice[0] == 'B') matrix_multi(B, A, aR, aC, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '`')
	{
		if (choice[0] == 'A') matrix_trans(A, aR, aC);
		else if (choice[0] == 'B') matrix_trans(B, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '/')
	{
		if (choice[0] == 'A')
		{
			if (matrix_det(B, *bR))
			{
				double **invS = new double*[*bR];
				for (int i = 0; i<*bR; i++) invS[i] = new double[*bC];
				for (int i = 0; i<*bR; i++)
				{
					for (int g = 0; g<*bC; g++)
					{
						invS[i][g] = B[i][g];
					}
				}
				matrix_inverse(invS, bR, bC);
				matrix_multi(A, invS, aR, aC, bR, bC);
				for (int i = 0; i<*bR; i++) delete[] invS[i];
				delete[] invS;
			}
			else cout << "Mathematical Error: The determinant of matrix B equals zero.\n";
		}
		else if (choice[0] == 'B')
		{
			if (matrix_det(A, *aR))
			{
				double **invS = new double*[*aR];
				for (int i = 0; i<*aR; i++) invS[i] = new double[*aC];
				for (int i = 0; i<*aR; i++)
				{
					for (int g = 0; g<*aC; g++)
					{
						invS[i][g] = A[i][g];
					}
				}
				matrix_inverse(invS, bR, bC);
				matrix_multi(B, invS, bR, bC, aR, aC);
				for (int i = 0; i<*aR; i++) delete[] invS[i];
				delete[] invS;
			}
			else cout << "Mathematical Error: The determinant of matrix B equals zero./n";
		}
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '!')
	{
		if (choice[0] == 'A') matrix_store(A, aR, aC);
		else if (choice[0] == 'B') matrix_store(B, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice[1] == '(')
	{
		if (choice[0] == 'd')
		{
			if (choice[2] == 'A' && choice[3] == ')')
			{
				int n = *aR;
				if (*aR == *aC) cout << "\n\nThe determinant of matrix A = " << matrix_det(A, n) << endl;
				else cout << "Mathematics Error: The matrix A is not a square matrix.";
				menu(A, B, aR, aC, bR, bC);
			}
			else if (choice[2] == 'B' && choice[3] == ')')
			{
				int n = *bR;
				if (*bR == *bC) cout << "\n\nThe determinant of matrix B = " << matrix_det(B, n) << endl;
				else cout << "Mathematics Error: The matrix A is not a square matrix.";
				menu(A, B, aR, aC, bR, bC);
			}
			else
			{
				cout << "Entry Error: Your entry may be wrong somehow, please try again.\n";
				menu(A, B, aR, aC, bR, bC);
			}
		}
	}
	else if (choice[1] == '\0')
	{
		if (choice[0] == 'A') matrix_print(A, aR, aC);
		else if (choice[0] == 'B') matrix_print(B, bR, bC);
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice == "help" || choice == "Help")
	{
		cout << "\n(write down A or B Printing matrix values)\n(write down A+B or B+A for Addition)\n(write down A-B or B-A for Subtraction)\n(write down A*B or B*A for Multiplication)\n(write down A` or B` for Transpose)\n(write down A/B or B/A for Division)\n(write down d(A) or d(B) to print the deteminant value of the matrix)\n(write down A! or B! to add/re-add matrix values)\n(write down exit to terminate the application)\n";
		menu(A, B, aR, aC, bR, bC);
	}
	else if (choice == "exit") return;
	else
	{
		cout << "Entry Error: Your entry may be wrong somehow, please try again.\n";
		menu(A, B, aR, aC, bR, bC);
	}
}
void matrix_store(double **Mat, int *R, int *C)
{
	int x = 1;
	for (int i = 0; i<*R; i++)
	{
		for (int j = 0; j<*C; j++)
		{
			cout << "x" << x << ": ";
			cin >> Mat[i][j];
			x++;
		}
	}
}
void matrix_print(double **Mat, int *R, int *C)
{
	cout << endl;
	int s = 0;
	for (int a = 0; a<*R; a++)
	{
		if (s == *C) cout << endl;
		for (s = 0; s<*C; s++)
		{
			if ((a == 0 && s == 0) || (a != 0 && s == 0)) cout << "| ";
			cout << Mat[a][s] << " ";
			if (s == (*C) - 1) cout << "|";
		}
	}
}
void matrix_add(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC)
{
	if (*fR == *sR && *fC == *sC)
	{
		double **matC = new double*[*fR];
		for (int i = 0; i<*fR; i++) matC[i] = new double[*sC];
		for (int i = 0; i<*fR; i++)
		{
			for (int g = 0; g<*sC; g++)
			{
				matC[i][g] = fMat[i][g] + sMat[i][g];
			}
		}
		matrix_print(matC, fR, sC);
		for (int i = 0; i<*fR; i++) delete[] matC[i];
		delete[] matC;
	}
	else cout << "Mathematical Error: The two matrix are not the same order.";
}
void matrix_sub(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC)
{
	if (*fR == *sR && *fC == *sC)
	{
		double **matC = new double*[*fR];
		for (int i = 0; i<*fR; i++) matC[i] = new double[*sC];
		for (int i = 0; i<*fR; i++)
		{
			for (int g = 0; g<*sC; g++)
			{
				matC[i][g] = fMat[i][g] - sMat[i][g];
			}
		}
		matrix_print(matC, fR, sC);
		for (int i = 0; i<*fR; i++) delete[] matC[i];
		delete[] matC;
	}
	else cout << "Mathematical Error: The two matrix are not the same order.";
}
void matrix_multi(double **fMat, double **sMat, int *fR, int *fC, int *sR, int *sC)
{
	if (*fC == *sR)
	{
		double **matC = new double*[*fR], sum = 0;
		for (int i = 0; i<*fR; i++) matC[i] = new double[*sC];
		for (int i = 0; i<*fR; i++)
		{
			for (int g = 0; g<*sC; g++)
			{
				sum = 0;
				for (int j = 0; j<*sC; j++)
				{
					sum += fMat[i][j] * sMat[j][g];
				}
				matC[i][g] = sum;
			}
		}
		matrix_print(matC, fR, sC);
		for (int i = 0; i<*fR; i++) delete[] matC[i];
		delete[] matC;
	}
	else cout << "Mathematical Error: The two matrix are not the same first column and second row.";
}
void matrix_trans(double **Mat, int *R, int *C)
{
	double **matC = new double*[*C];
	for (int i = 0; i<*C; i++) matC[i] = new double[*R];
	for (int i = 0; i<*C; i++)
	{
		for (int g = 0; g<*R; g++)
		{
			matC[i][g] = Mat[g][i];
		}
	}
	matrix_print(matC, C, R);
	for (int i = 0; i<*R; i++) delete[] matC[i];
	delete[] matC;
}
double matrix_det(double **Mat, int n)
{
	double det = 0;
	double **sMat = new double*[10];
	for (int i = 0; i<10; i++) sMat[i] = new double[10];
	if (n == 2) return ((Mat[0][0] * Mat[1][1]) - (Mat[1][0] * Mat[0][1]));
	else
	{
		for (int x = 0; x<n; x++)
		{
			int si = 0;
			for (int i = 1; i<n; i++)
			{
				int sj = 0;
				for (int j = 0; j<n; j++)
				{
					if (j != x)
					{
						sMat[si][sj] = Mat[i][j];
						sj++;
					}
				}
				si++;
			}
			det += (pow(-1, x)*Mat[0][x] * matrix_det(sMat, n - 1));
		}
	}
	for (int i = 0; i<n; i++) delete[] sMat[i];
	delete[] sMat;
	return det;
}
void matrix_inverse(double **Mat, int *R, int*C)
{
	int i, j, k, n = *R;
	double a[10][10] = { 0 }, d;
	for (i = 1; i <= *R; i++)
	{
		for (int g = 1; g <= *C; g++) a[i][g] = Mat[i - 1][g - 1];
	}
	for (i = 1; i <= n; i++) for (j = 1; j <= 2 * n; j++) if (j == (i + n)) a[i][j] = 1;
	for (i = n; i>1; i--)
	{
		if (a[i - 1][1]<a[i][1])
		{
			for (j = 1; j <= n * 2; j++)
			{
				d = a[i][j];
				a[i][j] = a[i - 1][j];
				a[i - 1][j] = d;
			}
		}
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n * 2; j++)
		{
			if (j != i)
			{
				d = a[j][i] / a[i][i];
				for (k = 1; k <= n * 2; k++) a[j][k] -= a[i][k] * d;
			}
		}
	}
	for (i = 1; i <= n; i++)
	{
		d = a[i][i];
		for (j = 1; j <= n * 2; j++) a[i][j] /= d;
	}
	int row = 0, col = 0;
	for (i = 1; i <= n; i++)
	{
		col = 0;
		for (j = n + 1; j <= n * 2; j++)
		{
			Mat[i - 1][col] = a[i][j];
			col++;
		}
	}
}
