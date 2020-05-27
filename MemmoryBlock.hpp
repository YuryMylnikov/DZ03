#pragma once

#include <string>
#include <iomanip>


#define InstanceCount 10


template<typename T, size_t N = InstanceCount>
class MemmoryBlock
{
	uint8_t* m_pRaw;
	uint8_t* m_pHead;

	size_t m_szBlock;
	size_t m_szInstance;
	size_t m_szInstances;

public:
	MemmoryBlock();
	MemmoryBlock(MemmoryBlock&& blc);
	MemmoryBlock(const MemmoryBlock& blc);

	~MemmoryBlock();

	T* GetHead() const;
	T* GetInstance();
	bool FreeInstance(T* ins);

	operator bool() const;
	MemmoryBlock& operator=(MemmoryBlock&& blc);
	MemmoryBlock& operator=(const MemmoryBlock&);
	

private:
	void MarkUpBlock();
};


template<typename T, size_t N>
MemmoryBlock<T, N>::MemmoryBlock() : m_pRaw{ nullptr }, m_pHead{ nullptr },  m_szInstances{ N }
{
	m_szInstance = sizeof(T);

	if (m_szInstance < sizeof(T*))
	{
		m_szInstance = sizeof(T*);
	}

	m_szBlock = m_szInstance * N;
	
	m_pHead = new uint8_t[m_szBlock];
	m_pRaw = m_pHead;

	MarkUpBlock();
}


template<typename T, size_t N>
MemmoryBlock<T, N>::MemmoryBlock(MemmoryBlock&& blc)
{
	m_pRaw = blc.m_pRaw;
	m_pHead = blc.m_pHead;
	m_szBlock = blc.m_szBlock;
	m_szInstance = blc.m_szInstance;
	m_szInstances = blc.m_szInstances;

	blc.m_szBlock = 0;
	blc.m_szInstance = 0;
	
	blc.m_pRaw = nullptr;
	blc.m_pHead = nullptr;
}


template<typename T, size_t N>
MemmoryBlock<T, N>::MemmoryBlock(const MemmoryBlock& blc)
{
	m_szBlock = blc.m_szBlock;
	m_szInstance = blc.m_szInstance;
	
	m_pHead = new uint8_t[m_szBlock];

	memmove(m_pHead, blc.m_pHead, m_szBlock);
}


template<typename T, size_t N>
MemmoryBlock<T, N>::~MemmoryBlock()
{
	delete[] m_pRaw;
}


template<typename T, size_t N>
void MemmoryBlock<T, N>::MarkUpBlock()
{
	uint8_t* tmp = m_pHead;

	for (size_t i = 0; i < N - 1; ++i)
	{
		*((uint8_t**)tmp) = tmp + m_szInstance;
		tmp = *((uint8_t**)tmp);
	}

	*((uint8_t**)tmp) = nullptr;
}


template<typename T, size_t N>
T* MemmoryBlock<T, N>::GetInstance()
{
	uint8_t* tmp = m_pHead;

	if (tmp != nullptr)
	{
		--m_szInstances;
		m_pHead = *((uint8_t**)m_pHead);

		//std::cout << __func__ << " " << typeid(T).name() << ": " << (void*)tmp << std::endl;

		return (T*)tmp;
	}

	return nullptr;
}


template<typename T, size_t N>
T* MemmoryBlock<T, N>::GetHead() const
{
	return (T*)m_pHead;
}


template<typename T, size_t N>
bool MemmoryBlock<T, N>::FreeInstance(T* pins)
{
	//std::cout << __func__ << ": " << pins << std::endl;

	if ((uint8_t*)pins >= m_pRaw && (uint8_t*)pins < m_pRaw + m_szBlock)
	{
		*((uint8_t**)pins) = m_pHead;
		m_pHead = (uint8_t*)pins;

		++m_szInstances;

		if (N == m_szInstances)
		{
			return true;
		}
	}

	return false;
}


template<typename T, size_t N>
MemmoryBlock<T, N>::operator bool() const
{
	return nullptr != *((uint8_t**)m_pHead);
}


template<typename T, size_t N>
MemmoryBlock<T, N>& MemmoryBlock<T, N>::operator=(MemmoryBlock&& blc)
{
	m_pRaw = blc.m_pRaw;
	m_pHead = blc.m_pHead;
	m_szBlock = blc.m_szBlock;
	m_szInstance = blc.m_szInstance;
	m_szInstances = blc.m_szInstances;

	blc.m_szBlock = 0;
	blc.m_szInstance = 0;

	blc.m_pRaw = nullptr;
	blc.m_pHead = nullptr;

	return *this;
}


template<typename T, size_t N>
MemmoryBlock<T, N>& MemmoryBlock<T, N>::operator=(const MemmoryBlock& blc)
{
	m_szBlock = blc.m_szBlock;
	m_szInstance = blc.m_szInstance;
	m_szInstances = blc.m_szInstances;

	m_pHead = new uint8_t[m_szBlock];
	m_pRaw = m_pHead;

	memmove(m_pHead, blc.m_pHead, m_szBlock);

	return *this;
}