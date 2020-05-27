#include "BlockAllocator.hpp"
#include "SortedList.hpp"

#include <iostream>
#include <map>


int factorial(int num)
{
	if (num <= 1)
	{
		return 1;
	}

	return num * factorial(num - 1);
}


int main()
{
	try
	{
		{
			std::map<int, int> mFact{};

			for (int i = 0; i < 10; ++i)
			{
				mFact[i] = factorial(i);
			}

			for (const auto& it : mFact)
			{
				std::cout << it.first << " " << it.second << std::endl;
			}

			std::cout << std::endl;
		}

		{
			std::map<int, int, std::less<int>, BlockAllocator<int>> mFact{};

			for (int i = 0; i < 10; ++i)
			{
				mFact[i] = factorial(i);
			}

			for (const auto& it : mFact)
			{
				std::cout << it.first << " " << it.second << std::endl;
			}

			std::cout << std::endl;
		}

		{
			SortedList<int> slCont{};

			for (int i = 0; i < 10; ++i)
			{
				slCont.Add(factorial(i));
			}

			int i{ 0 };

			for (const int& it : slCont)
			{
				std::cout << i++ << " " << it << std::endl;
			}

			std::cout << std::endl;
		}

		{
			SortedList<int, BlockAllocator<int>> slCont{};

			for (int i = 0; i < 10; ++i)
			{
				slCont.Add(factorial(i));
			}

			int i{ 0 };

			for (const int& it : slCont)
			{
				std::cout << i++ << " " << it << std::endl;
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}