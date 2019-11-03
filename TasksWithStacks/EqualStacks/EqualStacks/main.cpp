#include <iostream>
#include <stack>
#include <vector>

size_t theSmallestOne(int sum1, int sum2, int sum3)
{
	if (sum1 <= sum2 && sum1 <= sum3)
	{
		return 1;
	}
	else if (sum2 <= sum1 && sum2 <= sum3)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

int equalStacks(std::vector<int> h1, std::vector<int> h2, std::vector<int> h3) 
{
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	std::stack<int> st1;
	std::stack<int> st2;
	std::stack<int> st3;


	for (size_t i = 0; i < h1.size; ++i)
	{
		sum1 += h1[i];
	}
	for (size_t i = 0; i < h2.size; ++i)
	{
		sum2 += h2[i];
	}
	for (size_t i = 0; i < h3.size; ++i)
	{
		sum3 += h3[i];
	}

	for (size_t i = 0; i < h1.size; ++i)
	{
		st1.push(h1[i]);
	}
	for (size_t i = 0; i < h2.size; ++i)
	{
		st2.push(h2[i]);
	}
	for (size_t i = 0; i < h3.size; ++i)
	{
		st3.push(h3[i]);
	}

	int type;
	int curr;

	while (sum1 != sum2 && sum2 != sum3)
	{
		type = theSmallestOne(sum1, sum2, sum3);
		if (type == 1)
		{
			while (sum1 < sum2)
			{
				curr = st2.top();
				sum2 -= curr;

				st2.pop();
			}

			while (sum1 < sum3)
			{
				curr = st3.top();
				sum3 -= curr;

				st3.pop();
			}
		}
		else if (type == 2)
		{
			while (sum2 < sum1)
			{
				curr = st1.top();
				sum1 -= curr;

				st1.pop();
			}

			while (sum2 < sum3)
			{
				curr = st3.top();
				sum3 -= curr;

				st3.pop();
			}
			
		}
		else
		{
			while (sum3 < sum2)
			{
				curr = st2.top();
				sum2 -= curr;

				st2.pop();
			}

			while (sum3 < sum1)
			{
				curr = st1.top();
				sum1 -= curr;

				st1.pop();
			}
			
		}

	}
	return sum1;
}


int main()
{

	return 0;
}