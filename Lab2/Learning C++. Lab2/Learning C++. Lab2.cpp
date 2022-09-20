﻿#include <iostream>

#include "functions.h"

int main()
{
	int N;

	std::cout << "Input an array size: ";
	std::cin >> N;
	std::cout << "\n";

	int** arr = create_array(N, N);

	fill_array(arr, N, N);

	int ans = 0;
	while (true)
	{
		print_array(arr, N, N);

		std::cout << "Actions:\n"
			<< "1) Fill normal\n"
			<< "2) Fill backward\n"
			<< "3) Fill along main diagonal\n"
			<< "4) Fill along side diagonal\n"
			<< "5) Fill like round spiral (from 0,0)\n"
			<< "0) Exit\n";

		std::cout << "Input an action: ";
		std::cin >> ans;
		std::cout << "\n";

		switch (ans)
		{
		case 0:
			return 0;
		case 1:
			fill_array(arr, N, N);
			break;
		case 2:
			fill_array_backward(arr, N, N);
			break;
		case 3:
			fill_array_along_main_diag(arr, N, N);
			break;
		case 4:
			fill_array_along_side_diag(arr, N, N);
			break;
		case 5:
			fill_array_spiral(arr, N, N);
			break;
		default:
			break;
		}

		system("cls");
	}

	free_array(arr, N);

	return 0;
}