#include <iostream>
#include <string>
#include <stack>

std::string isBalanced(std::string s)
{
	std::stack<char> st;
	size_t length = s.length();
	for (size_t i = 0; i < length; ++i)
	{
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
		{
			st.push(s[i]);
		}
		else if (!st.empty())
		{
			if (s[i] == st.top() + 1 || s[i] == st.top() + 2)
			{
				st.pop();
			}
			else
			{
				return "NO";
			}
		}
		else
		{
			return "NO";
		}
	}
	return st.empty() ? "YES" : "NO";
}


int main()
{
	int n;
	std::cin >> n;
    std::cin.ignore();
	for (size_t i = 0; i < n; ++i)
	{
		std::string s;
		std::getline(std::cin, s);

		std::string result = isBalanced(s);
		std::cout << result << std::endl;
	}

	return 0;
}