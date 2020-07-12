#pragma once


template<typename T>
class SortedListIterator : public std::iterator<std::input_iterator_tag, T>
{
	using pointer = typename std::iterator_traits<SortedListIterator>::pointer;

	pointer p;

public:
	SortedListIterator(pointer p);
	SortedListIterator(const SortedListIterator& it);

	bool operator!=(const SortedListIterator& other) const;
	bool operator==(const SortedListIterator& other) const;
	
	typename T::ref_type operator*() const;

	SortedListIterator& operator++();
};


template<typename T>
SortedListIterator<T>::SortedListIterator(pointer p) : p{ p } {}


template<typename T>
SortedListIterator<T>::SortedListIterator(const SortedListIterator &it) : p{ it.p } {}


template<typename T>
bool SortedListIterator<T>::operator==(const SortedListIterator& other) const
{
	return p == other.p;
}


template<typename T>
bool SortedListIterator<T>::operator!=(const SortedListIterator& other) const
{
	return !(*this == other);
}


template<typename T>
typename T::ref_type SortedListIterator<T>::operator*() const
{
	return p->val;
}


template<typename T>
SortedListIterator<T>& SortedListIterator<T>::operator++()
{
	p = p->next;

	return *this;
}


template<typename T>
class SortedListIterator<const T> : public SortedListIterator<T>
{
public:
	typename T::value_type operator*() const;
};


template<typename T>
typename T::value_type SortedListIterator<const T>::operator*() const
{
	return SortedListIterator<T>::p->val;
}