#pragma once


#include <map>
#include <algorithm>


#include "MemmoryBlock.hpp"


template<typename T, size_t N = InstanceCount>
class MemmoryPool
{
	std::map<T*, MemmoryBlock<T, N>> m_mMemoryBlocks;

public:
	MemmoryPool() = default;
	
	MemmoryPool(MemmoryPool&&) = delete;
	MemmoryPool(const MemmoryPool&) = delete;
	
	MemmoryPool& operator=(MemmoryPool&&) = delete; 
	MemmoryPool& operator=(const MemmoryPool&) = delete;

	T* Allocate(size_t szNum);
	void Deallocate(T* p);

private:
	T* AllocateBloc();
};


template<typename T, size_t N>
T* MemmoryPool<T, N>::Allocate(size_t /*szNum*/)
{
	//std::cout << __func__ << std::endl;

	for (auto& it : m_mMemoryBlocks)
	{
		//if (it.second)
		if (it.second.GetHead() != nullptr)
		{
			return it.second.GetInstance();
		}
	}

	return AllocateBloc();
}


template<typename T, size_t N>
T* MemmoryPool<T, N>::AllocateBloc()
{
	//std::cout << __func__ << " " << typeid(T).name() << std::endl;

	MemmoryBlock<T, N> tmp;
	T* head = tmp.GetHead();

	bool res{ false };
	auto it{ m_mMemoryBlocks.begin() };

	std::tie(it, res) = m_mMemoryBlocks.emplace(head, std::move(tmp));

	if (res)
	{
		return it->second.GetInstance();
	}

	return nullptr;
}


template<typename T, size_t N>
void MemmoryPool<T, N>::Deallocate(T* p)
{
	//std::cout << __func__ << std::endl;

	auto it = m_mMemoryBlocks.upper_bound(p);
	--it;

	if (it->second.FreeInstance(p))
	{
		m_mMemoryBlocks.erase(it);
	}

	//m_mMemoryBlocks.erase(it);
}