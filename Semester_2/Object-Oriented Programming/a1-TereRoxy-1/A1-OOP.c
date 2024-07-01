#include <stdio.h>

void print_menu();
void read_array(int* nr, int vector[]);
int gcd(int a, int b);
int prime(int x);
int same_digits(int x, int y);
void print_req_b(int start, int lmax, int size, int arr[]);


void req_a()
{
	printf("The numbers are: ");
	int x = 3, cnt = 0;
	int ok;
	while (cnt < 8)
	{
		ok = 1;
		for (int i = x - 1; i > 1; i--)
		{
			if ((gcd(x, i) == 1) && !(prime(i)))
				ok = 0;
		}
		if (ok)
		{
			printf("%d ", x);
			cnt++;
		}
		x++;
	}
	printf("\n");
}

void req_b(int size, int arr[])
{
	int lc = 1, lmax = 1, start = 0;
	int x = arr[0], y = 0;
	for (int i = 1; i < size; i++)
	{
		y = arr[i];
		if (same_digits(x, y))
			lc++;
		else
			lc = 1;
		if (lc > lmax)
		{
			lmax = lc;
			start = i - lmax + 1;
		}
		x = y;
	}
	print_req_b(start, lmax, size, arr);
}

void print_req_b(int start, int lmax, int size, int arr[])
{
	for (int i = start; i <= start + lmax - 1; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{

	int size = 0, arr[25], ok = 0;
	int run = 1;
	while (run)
	{
		int option = 0;
		print_menu();
		scanf("%d", &option);
		if (option == 1)
		{
			read_array(&size, arr);
			ok = 1;
		}
		else if (option == 2)
			req_a();
		else if (option == 3)
		{
			if (!ok)
				printf("There is no array of numbers. Please enter an array of numbers first and try again!\n");
			else
				req_b(size, arr);
		}
		else if (option == 0)
		{
			run = 0;
		}
		else
			printf("Invalid option. Please try again! \n");

	}
	return 0;
}

void print_menu()
{
	printf("Please enter an option:\n");
	printf("1. Read an array of elements\n");
	printf("2. Determine the first (and only) 8 natural numbers (x1, x2, . . .,  x8) \n");
	printf("	xi > 2 with the following property: all the natural numbers smaller than xi and \n");
	printf("	that are relatively prime with xi(except for the number 1) are prime.\n");
	printf("3. Find the longest contiguous subsequence (of the given array) \n such that any consecutive elements contain the same digits\n");
	printf("0. Exit\n");
}

void read_array(int* nr, int vector[])
{
	int size;
	printf("Please enter the number of elements: ");
	// 12
	scanf("%d", &size);

	printf("Please enter the elements: ");
	// 1 2 3 4 5 6 11 12 21 12 211 30
	int elem = 0;
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &elem);
		vector[i] = elem;
	}
	*nr = size;
}

int gcd(int a, int b)
{
	int r;
	while (b)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int prime(int x)
{
	if (x == 2) return 1;
	if (x < 2) return 0;
	if (x % 2 == 0) return 0;
	int d = 3;

	while (d * d <= x)
	{
		if (x % d == 0)
			return 0;
		d += 2;
	}
	return 1;
}

int same_digits(int x, int y)
{
	int digits_x[10] = { 0 };
	int digits_y[10] = { 0 };

	while (x)
	{
		digits_x[x % 10]++;
		x /= 10;
	}
	while (y)
	{
		digits_y[y % 10]++;
		y /= 10;
	}
	for (int i = 0; i < 10; i++)
	{
		if (digits_x[i] != digits_y[i])
			return 0;
	}
	return 1;
}