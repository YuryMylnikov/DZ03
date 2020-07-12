#pragma once

#include "MemmoryPool.hpp"


template<typename T, size_t N = InstanceCount>
struct BlockAllocator 
{
	static MemmoryPool<T, N> pool;

	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T& ;
	using const_reference = const T&;

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	template<typename U>
	struct rebind 
	{
		using other = BlockAllocator<U, N>;
	};

	BlockAllocator() = default;
	BlockAllocator(const BlockAllocator&) = default;

	template<typename U, size_t S>
	BlockAllocator(const BlockAllocator<U, S>&) {}

	~BlockAllocator() = default; 

	BlockAllocator& operator=(const BlockAllocator& other) = default;

	size_type max_size() const;

	pointer allocate(std::size_t /*n*/);
	void deallocate(pointer p, size_t /*n*/);

	template<typename U, typename ...Args> 
	void construct(U* p, Args &&...args);

	template<typename U> 
	void destroy(U* p);
};


template<typename T, size_t N>
MemmoryPool<T, N> BlockAllocator<T, N>::pool{};


template<typename T, size_t N>
typename BlockAllocator<T, N>::size_type BlockAllocator<T, N>::max_size() const
{
	return std::numeric_limits<size_type>::max();
}


template<typename T, size_t N>
typename BlockAllocator<T, N>::pointer BlockAllocator<T, N>::allocate(std::size_t n)
{
	//std::cout << __func__ << " [n = " << n << "]" << std::endl;

	auto p = pool.Allocate(n);

	if (!p)
	{
		throw std::bad_alloc();
	}

	return p;
}


template<typename T, size_t N>
void BlockAllocator<T, N>::deallocate(pointer p, std::size_t /* n */)
{
	//std::cout << __func__ << " [n  = " << n << "] " << std::endl;

	pool.Deallocate(p);
}


template<typename T, size_t N>
template<typename U, typename ...Args>
void BlockAllocator<T, N>::construct(U *p, Args &&...args)
{
	//std::cout << __func__ << std::endl;
	new(p) U(std::forward<Args>(args)...);
}


template<typename T, size_t N>
template<typename U>
void BlockAllocator<T, N>::destroy(U *p)
{
	//std::cout << __func__ << std::endl;
	p->~U();
}