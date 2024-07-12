#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <array>
#include <bitset>

#include "components/SphericalRayColliderComponent.h"
#include "ComponentStorage.h"
#include "EntityDescriptor.h"

namespace PathTracer
{

static size_t s_componentCounter = 0;

class Scene
{
 public:
    Scene() = default;
    explicit Scene(const char *fileName)
    {
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

    template<class T>
    size_t getComponentId() const
    {
          //  A lambda function that runs only once (not thread safe)
        static const size_t componentId = [this]
        {
            auto *s = m_componentStorages.begin() + componentId;
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
        static_cast<ComponentStorage<T>*>(getComponentStorage<T>())->getElementAt(entityId) = component;
    }

    template<class T>
    void removeComponent(size_t entityId)
    {
        m_entityDescriptors[entityId].mask.set(getComponentId<T>(), false);
    }

      //  Ray Collision Detection
    std::optional<CollisionRecord> collideFirst(const Ray &ray, Interval interval) const
    {
        CollisionRecord cRec;
        const size_t componentId = getComponentId<SphericalRayColliderComponent>();

        auto *p_colliderStorage = getComponentStorage<SphericalRayColliderComponent>();
        for(size_t i = 0; i < m_entityCount; i++)
        {
            if(!m_entityDescriptors[i].mask.test(componentId)) continue;

            const auto &collider = p_colliderStorage->getElementAt(i);
            auto tempRec = collider.sphere.collide(ray, interval);
            if(tempRec)
            {
                cRec = (cRec.t < tempRec->t) ? cRec : tempRec.value();
            }
        }

        return (cRec.t < std::numeric_limits<double>::max()) ? cRec : std::optional<CollisionRecord>{} ;
    }



 private:
    size_t m_entityCount = 0;

    std::array<EntityDescriptor, MAX_ENTITIES> m_entityDescriptors;
    std::array<BaseComponentStorage*, MAX_COMPONENTS> m_componentStorages{};

};

};

#endif  //  SCENE_H
