/*
*   name: include/core/vector.hpp
*   origin: Citrus Engine
*   purpose: Provides a replacement for std::vector
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__
#define CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__

#include <cstdlib>
#include "include/core/extensions.hpp"
#include "include/core/mem.hpp"

namespace engine
{
    template <typename T>
    class Vector
    {
        private:
            T *data;
            int count;
        public:
            OPERATOR T &operator[](int index)
            {
                return (index < count) ? data[index] : getLast();
            }

            OPERATOR void push(T obj)
            {
                count++;
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
                data[count-1] = obj;
            }

            OPERATOR T pop()
            {
                if(!count)
                    return;
                count--;
                T obj = data[count];
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
                return obj;
            }

            OPERATOR void rm(int index)
            {
                if(!count)
                    return;
                for(int i = index; i < count - 1; i--)
                    data[i] = data[i+1];
                count--;
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
            }

            OPERATOR void insert(int index, T obj)
            {
                if(!count)
                    return;
                count++;
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
                for(int i = count - 2; i > index; i--)
                    data[i+1] = data[i];
                data[index] = obj;
            }

            OPERATOR int getCount()
            {
                return count;
            }

            OPERATOR T &getLast()
            {
                if(count)
                    return data[count-1];
            }
            OPERATOR T &getFirst()
            {
                if(count)
                    return data[0];
            }

            Vector()
            {
                data = memalloc(sizeof(T), MEM_FLAG_UNIT_BYTE);
                count = 0;
            }

            ~Vector()
            {
                memfree(data);
            }
    };
};

#endif