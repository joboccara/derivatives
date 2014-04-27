#pragma once
#include <cstddef>

/* Simple memory usage monitoring
This component monitors per-class memory usage if no class in the hierarchy overrides
operator new or operator delete. A class T to be monitored should inherit from
MemoryLogger<T>. To get the current size of memory allocated on the free store for
class T at a given time, one should use:
size_t currentAllocatedSize = MemoryLogger<T>::getCurrentAllocatedSize();
*/

template<typename T>
class MemoryLogger
{
public:
   static void* operator new(size_t size)
   {
      m_allocatedSize += size;
      return ::operator new(size);
   }
   static void operator delete(void *mem, size_t size)
   {
      m_allocatedSize -= size;
      ::operator delete(mem);
   }
   static size_t getCurrentAllocatedSize()
   {
      inheritanceCheck();
      return m_allocatedSize;
   }

private:
   static void inheritanceCheck()
   {
      T* p = 0;
      MemoryLogger<T>* pBase = p; // compile-time check to make sure T inherits from MemoryLogger<T>
   }

   static size_t m_allocatedSize;
};

template<typename T>
size_t MemoryLogger<T>::m_allocatedSize = 0;

