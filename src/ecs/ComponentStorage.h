#ifndef COMPONENT_STORAGE_H
#define COMPONENT_STORAGE_H


#include "../core/Constants.h"

namespace PathTracer
{

class BaseComponentStorage
{
 public:
    virtual ~BaseComponentStorage() = default;
};

template<class T>
class ComponentStorage : public BaseComponentStorage
{
 public:
    ComponentStorage() = default;
    ~ComponentStorage() override = default;

    inline T &getElementAt(size_t index)
    {
        return *(m_components.begin() + index);
    }

 private:
    std::array<T, MAX_ENTITIES> m_components;
};

}

#endif  //  COMPONENT_STORAGE_H
