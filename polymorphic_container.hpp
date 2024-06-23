#pragma once
#include "polymorphic_ptr.hpp"
#include "Vector.hpp"
//github terziev

template<typename T>
class polymorphic_container {
private:
	Vector<polymorphic_ptr<T>> ptrs;

public:
	void add(T* ptr);
	size_t getPtrsCount() const;
	T& operator[](size_t index) const;
	/*void execute(size_t index, void(*func)(T*));
	void execute(size_t index, void(*func)(const T*)) const;*/
};

template<typename T>

//see if this is the right way
void polymorphic_container<T>::add(T* ptr) {
	ptrs.push_back(polymorphic_ptr<T>(ptr);
}
template<typename T>
size_t polymorphic_container<T>::getPtrsCount() const {
	return ptrs.getSize();
}

template<typename T>
T& polymorphic_container<T>::operator[](size_t index) const{
	return *ptrs[index];
}

//template<typename T>
//void polymorphic_container<T>::execute(size_t index, void(*func)(T*)) {
//	func(ptrs[index].get());
//}
//
//
//template<typename T>
//void polymorphic_container<T>::execute(size_t index, void(*func)(const T*)) const {
//	func(ptrs[index].get());
//}