#pragma once

#include "MemmoryPool.hpp"


template<typename T>
struct BlockAllocator 
{
	static MemmoryPool<T> pool;

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
		using other = BlockAllocator<U>;
	};

	BlockAllocator() = default;
	BlockAllocator(const BlockAllocator&) = default;

	template<typename U>
	BlockAllocator(const BlockAllocator<U>&) {}

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


template<typename T>
MemmoryPool<T> BlockAllocator<T>::pool{};


template<typename T>
typename BlockAllocator<T>::size_type BlockAllocator<T>::max_size() const
{
	return std::numeric_limits<size_type>::max();
}


template<typename T>
typename BlockAllocator<T>::pointer BlockAllocator<T>::allocate(std::size_t n)
{
	//std::cout << __func__ << " [n = " << n << "]" << std::endl;

	auto p = pool.Allocate(n);

	if (!p)
	{
		throw std::bad_alloc();
	}

	return p;
}


template<typename T>
void BlockAllocator<T>::deallocate(pointer p, std::size_t /* n */)
{
	//std::cout << __func__ << " [n  = " << n << "] " << std::endl;

	pool.Deallocate(p);
}


template<typename T>
template<typename U, typename ...Args>
void BlockAllocator<T>::construct(U *p, Args &&...args)
{
	//std::cout << __func__ << std::endl;
	new(p) U(std::forward<Args>(args)...);
};


template<typename T>
template<typename U>
void BlockAllocator<T>::destroy(U *p)
{
	//std::cout << __func__ << std::endl;
	p->~U();
}