#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <array>
#include <bitset>

#include "../application/components/RayColliderComponent.h"
#include "ComponentStorage.h"
#include "EntityDescriptor.h"

namespace PathTracer
{

static size_t s_componentCounter = 0;

class Scene
{
 public:
    Scene() = default;

    Scene(Scene &&other) : m_entityCount(other.m_entityCount),
                                 m_componentStorages(other.m_componentStorages),
                                 m_entityDescriptors(other.m_entityDescriptors)
    {
        std::fill(std::begin(other.m_componentStorages), std::end(other.m_componentStorages), nullptr);
        other.m_componentStorages.fill(nullptr);
        other.~Scene();
    }


    ~Scene()
    {
        for(auto ptr : m_componentStorages)
        {
            delete ptr;
        }
    }

      //  Entity-Component Management Functions

    size_t addEntity()
    {
        return m_entityCount++;
    }

    const EntityDescriptor &getEntityDescriptor(size_t entityId) const
    {
        return m_entityDescriptors[entityId];
    }

    inline bool queryEntity(size_t entityId, ComponentMask queryMask)
    {
        return (getEntityDescriptor(entityId).mask & queryMask) == queryMask;
    }

    size_t entityCount() const { return m_entityCount; }

    template<class T>
    size_t getComponentId() const
    {
          //  A lambda function that runs only once (not thread safe)
        static const size_t componentId = [this]
        {
            auto *s = m_componentStorages.data() + s_componentCounter;
            auto *ss = const_cast<BaseComponentStorage**>(s);
            *ss = dynamic_cast<BaseComponentStorage*>(new ComponentStorage<T>());
            return s_componentCounter++;
        }();

        return componentId;
    }

    template<class T>
    ComponentStorage<T> *getComponentStorage() const
    {
        return dynamic_cast<ComponentStorage<T>*>(m_componentStorages[getComponentId<T>()]);
    }

    template<class T>
    void addComponent(size_t entityId, const T &component)
    {
        m_entityDescriptors[entityId].mask.set(getComponentId<T>());
        static_cast<ComponentStorage<T>*>(getComponentStorage<T>())->getElementAt(entityId) = component;
    }

    template<class T>
    void addComponent(size_t entityId, const T &&component)
    {
        m_entityDescriptors[entityId].mask.set(getComponentId<T>());
        ComponentStorage<T> *componentStorage = getComponentStorage<T>();
        componentStorage->getElementAt(entityId) = component;
    }

    template<class T>
    void removeComponent(size_t entityId)
    {
        m_entityDescriptors[entityId].mask.set(getComponentId<T>(), false);
    }

      //  Systems

 private:
    size_t m_entityCount = 0;

    std::array<EntityDescriptor, MAX_ENTITIES> m_entityDescriptors;
    std::array<BaseComponentStorage*, MAX_COMPONENTS> m_componentStorages{};
};

};

#endif  //  SCENE_H
