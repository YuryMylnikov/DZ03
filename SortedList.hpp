#pragma once

#include "SortedListIterator.hpp"

#include <iostream>
#include <memory>


template<typename T, typename A = std::allocator<T>>
class SortedList
{
	struct Node
	{
		T val;
		Node* next;

		using value_type = T;
		using ref_type = T&;

		Node(T val, bool isEnd) :val{ val }, isEnd{ isEnd }, next{ nullptr } {};

		bool isEnd;
	};

	using iterator = SortedListIterator<Node>;
	using const_iterator = SortedListIterator<const Node>;

	using NodeAllocator = typename std::allocator_traits<A>::template rebind_alloc<Node>;

	A m_valAllocator;
	NodeAllocator m_nodeAllocator;

	Node* m_pHead;
	Node* m_pTail;

public:
	SortedList();
	~SortedList();

	iterator begin() const;
	iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	void Add(T val);
	void print();
};


template<typename T, typename A>
SortedList<T, A>::SortedList() : m_pHead{ nullptr } 
{
	Node* pNode = std::allocator_traits<NodeAllocator>::allocate(m_nodeAllocator, 1);
	std::allocator_traits<NodeAllocator>::construct(m_nodeAllocator, pNode, -1, true);

	m_pHead = pNode;
	m_pTail = pNode;
}


template<typename T, typename A>
SortedList<T, A>::~SortedList()
{
	while (m_pHead != nullptr)
	{
		Node* pNode = m_pHead->next;

		std::allocator_traits<NodeAllocator>::destroy(m_nodeAllocator, m_pHead);
		std::allocator_traits<NodeAllocator>::deallocate(m_nodeAllocator, m_pHead, 1);

		m_pHead = pNode;
	}
}


template<typename T, typename A>
typename SortedList<T, A>::iterator SortedList<T, A>::begin() const
{
	return SortedListIterator<Node>(m_pHead);
}


template<typename T, typename A>
typename SortedList<T, A>::iterator SortedList<T, A>::end() const
{
	return SortedListIterator<Node>(m_pTail);
}


template<typename T, typename A>
typename SortedList<T, A>::const_iterator SortedList<T, A>::cbegin() const
{
	return SortedListIterator<const Node>(m_pHead);
}


template<typename T, typename A>
typename SortedList<T, A>::const_iterator SortedList<T, A>::cend() const
{
	return SortedListIterator<const Node>(m_pTail);
}


template<typename T, typename A>
void SortedList<T, A>::Add(T val)
{
	Node* pNode = std::allocator_traits<NodeAllocator>::allocate(m_nodeAllocator, 1);
	std::allocator_traits<NodeAllocator>::construct(m_nodeAllocator, pNode, val, false);

	if (m_pHead->isEnd || m_pHead->val > val)
	{
		pNode->next = m_pHead;
		m_pHead = pNode;

		return;
	}

	auto prv = m_pHead;
	auto cur = m_pHead;

	for (; !cur->isEnd && cur->val <= val; prv = cur, cur = cur->next);

	prv->next = pNode;
	pNode->next = cur;
}


template<typename T, typename A>
void SortedList<T, A>::print()
{
	for (auto it = m_pHead; !it->isEnd; it = it->next)
	{
		std::cout << it->val << std::endl;
	}
}