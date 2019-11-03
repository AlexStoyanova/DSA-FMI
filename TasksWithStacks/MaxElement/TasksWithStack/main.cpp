#include <iostream>
#include <stack>

int maxElementInStack(std::stack<int>& st)
{
	std::stack<int> temp;
	int maxEl = 0;
	int currEl = 0;
	while (!st.empty())
	{
		currEl = st.top();
		temp.push(currEl);
		if (currEl > maxEl)
		{
			maxEl = currEl;
		}
		st.pop();
	}
	while (!temp.empty())
	{
		currEl = temp.top();
		st.push(currEl);
		temp.pop();
	}
	return maxEl;
}

int main()
{
	std::stack<int> st;
	unsigned int n;
	int type;
	int x;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> type;
		if (type == 1)
		{
			std::cin >> x;
			st.push(x);
		}
		else if (type == 2)
		{
			st.pop();
		}
		else
		{
			std::cout << maxElementInStack(st) << std::endl;
		}
	}

	return 0;
}