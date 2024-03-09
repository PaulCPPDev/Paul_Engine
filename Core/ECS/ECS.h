#ifndef CORE_ECS_ECS_H_
#define CORE_ECS_ECS_H_

#include <bitset>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>


namespace ecs {

// Component signature
const int kMaxComponents = 32;
typedef std::bitset<kMaxComponents> Signature;


////////////////////////////////////////////////////////////
/////////////////   Component       ////////////////////////
////////////////////////////////////////////////////////////

class IComponent {
  protected:
    static int next_id_;
};

template <typename TStruct>
class Component : public IComponent {
  public:
    static int GetId() {
      int id = next_id_++;
      return id;
    }
};



////////////////////////////////////////////////////////////
/////////////////   Entity       ///////////////////////////
////////////////////////////////////////////////////////////

class Entity {
  public:
    explicit Entity(const int& id): id_(id) {} // have to understand
    Entity(const Entity& entity) = default;  // creates a Copy constructor

    int GetId();
    template <typename TComponent> IComponent GetComponent() const;
    template <typename TComponent, typename ...Targs> void AddComponent(Targs&& ... args) const; // because you wan't to move it
    template <typename TComponent> void RemoveComponent();
    template <typename TComponent> bool HasComponent() const;
    
    // creates a default copy operator for this class
    Entity& operator =(const Entity& entity) = default;
    bool operator ==(const Entity& entity) const {
      return (this->id_ == entity.id_); }
    bool operator !=(const Entity& entity) const {
      return (this->id_ != entity.id_); }
    bool operator >(const Entity& entity) const {
      return (this->id_ > entity.id_); }
    bool operator <(const Entity& entity) const {
      return (this->id_ < entity.id_); }

  private:
    int id_;
};



////////////////////////////////////////////////////////////
/////////////////   System       ///////////////////////////
////////////////////////////////////////////////////////////

class System {
  public:
    virtual void Update() {}
    virtual ~System(){}
    
    const Signature& GetComponentSignature() const;
    std::vector<Entity> GetEntities() const;
    void AddEntityToSystem(const Entity& entity);
    void RemoveEntityFromSystem(const Entity& entity);
    template <typename TComponent> void RequireComponent();
  
  private:
    Signature component_signature_;
    std::vector<Entity> entities;
};





////////////////////////////////////////////////////////////
/////////////////   IPOOL       ///////////////////////////
////////////////////////////////////////////////////////////

class IPool {
  public:
        virtual ~IPool() {}
};

template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) {
            data.resize(size);
        }

        virtual ~Pool() = default;

        bool isEmpty() const {
            return data.empty();
        }

        int GetSize() const {
            return data.size();
        }

        void Resize(int n) {
            data.resize(n);
        }

        void Clear() {
            data.clear();
        }

        void Add(T object) {
            data.push_back(object);
        }

        void Set(int index, T object) {
            data[index] = object;
        }

        T& Get(int index) {
            return static_cast<T&>(data[index]);
        }

        T& operator [](unsigned int index) {
            return data[index];
        }
};





////////////////////////////////////////////////////////////
/////////////////   Registry       ///////////////////////////
////////////////////////////////////////////////////////////

class Registry {
  public:
    Registry() = default;
    ~Registry() = default;

    void Update();
    // entities
    void AddEntityToSystem(const Entity&& entity);
    void RemoveEntityFromSystem(const Entity&& entity);
    Entity& CreateEntity();

    // components
    template <typename TComponent>
    TComponent GetComponent(const Entity& entity) const;
    template <typename TComponent, typename ...Targs>
    void AddComponent(Targs... args);
    template <typename TComponent>
    void RemoveComponent();
    template <typename TComponent>
    bool HasComponent();
    
    // systems
    template <typename TSystem>
    TSystem& GetSystem() const;
    template <typename TSystem, typename ...Targs>
    void AddSystem(Targs&& ... args);
    template <typename TSystem>
    void RemoveSystem();
    template <typename TSystem>
    bool HasSystem() const;
    

  private:
    int num_entities_ = 0;
    std::vector<std::shared_ptr<IPool>> componentPools;
    std::vector<Signature> entityComponentSignatures;
    std::unordered_map<int, System> systems;
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;
};




////////////////////////////////////////////////////////////
/////////////////   ENTITY       ///////////////////////////
////////////////////////////////////////////////////////////


template <typename TComponent>
IComponent Entity::GetComponent() const {
  // registry->GetComponentFromEntity<TComponent>(this);
}

template <typename TComponent, typename ... Targs>
void Entity::AddComponent(Targs&& ... args) const {
  // registry->AddComponentToEntity<TComponent>(this);
}

template <typename TComponent>
void Entity::RemoveComponent() {
  // registry->RemoveComponentFromEntity<TComponent>(this);
}

template <typename TComponent>
bool Entity::HasComponent() const {
  // registry->HasComponent<TComponent>(this);
}





}  // namespace ecs

#endif // CORE_ECS_ECS_H_
