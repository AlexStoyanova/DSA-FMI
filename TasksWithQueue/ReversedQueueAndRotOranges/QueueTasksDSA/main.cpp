#include <iostream>
#include <queue>
#include <stack>

//Task 1. Reversing a queue.
void task1()
{
	std::queue<int> queue;
	int numOfElem = 0;
	for (int i = 1; i < 10; ++i)
	{
		queue.push(i);
	}
	std::stack<int> helper;
	while (!queue.empty())
	{
		helper.push(queue.front());
		queue.pop();
	}
	while (!helper.empty())
	{
		queue.push(helper.top());
		helper.pop();
		numOfElem++;
	}

}

//Task 2.  Minimum time required to rot all oranges.

bool isValidIndex(int x, int y)
{
	return (x >= 0 && x <= 2 && y >= 0 && y <= 4);
}

void task3()
{
	int arr[][50] =                                
	{ { 2, 1, 0, 2, 1 },
	  { 2, 0, 1, 2, 1 },
	  { 1, 0, 0, 2, 1 } };

	std::queue<std::pair<int,int>> queue;
	std::pair<int, int> help;
	std::pair<int, int> cell;
	std::pair<int, int> delimeter(-1, -1);
	int time = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (arr[i][j] == 2)
			{
				cell = std::make_pair(i, j);
				queue.push(cell);
			}
		}
	}

	queue.push(delimeter);

	while (!queue.empty())
	{
		cell = queue.front();
		queue.pop();
		
		if (isValidIndex(cell.first - 1, cell.second) && arr[cell.first - 1][cell.second] == 1)
		{
			help = std::make_pair(cell.first - 1, cell.second);
			queue.push(help);
			arr[cell.first - 1][cell.second] = 2;
		}
		if (isValidIndex(cell.first + 1, cell.second) && arr[cell.first + 1][cell.second] == 1)
		{
			help = std::make_pair(cell.first + 1, cell.second);
			queue.push(help);
			arr[cell.first + 1][cell.second] = 2;
		}
		if (isValidIndex(cell.first, cell.second - 1) && arr[cell.first][cell.second - 1] == 1)
		{
			help = std::make_pair(cell.first, cell.second - 1);
			queue.push(help);
			arr[cell.first][cell.second - 1] = 2;
		}
		if (isValidIndex(cell.first, cell.second + 1) && arr[cell.first][cell.second + 1] == 1)
		{
			help = std::make_pair(cell.first, cell.second + 1);
			queue.push(help);
			arr[cell.first][cell.second + 1] = 2;
		} 
		if (cell.first == -1 && cell.second == -1)
		{
			if (!queue.empty()) 
			{ 
				queue.push(delimeter); 
				++time;
			}
		}

	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (arr[i][j] == 1)
			{
				std::cout << "All oranges cannot be rotten!!!" << std::endl;
				return;
			}
		}
	}
	std::cout << "All oranges can become rotten in: " << time << std::endl;

}

int main()
{
	//task1();
	task3();



	return 0;
}