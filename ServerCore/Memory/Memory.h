#pragma once
#include "Allocator.h"

template<typename Type, typename... Args>
Type* inew(Args&&... args)
{
	Type* memory = static_cast<Type*>(ialloc(sizeof(Type)));
	new(memory)Type(forward<Args>(args)...); // placement new
	return memory;
}

template<typename Type>
void idelete(Type* obj)
{
	obj->~Type();
	irelease(obj);
}