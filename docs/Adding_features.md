<h2 align="center">Adding feature to the project</h2>

---

## 📝 Table of Contents

- [Getting Started](#loader)
- [Entity](#entity)
- [Usage](#usage)
- [Architecture](#architecture)
- [Authors](#authors)

## Getting started <a name = "loader"></a>

### Ressource Loader

The rtype global variable provides you an automatic resource loader which dynamically load all the textures and fonts added respectively in the `resources/textures` and `resources/fonts` folders. You can get your assets like this:

```c++
// Reference is important !
sf::Texture &texture = rtype.textures.get("MyTexture");
sf::Font &font = rtype.fonts.get("MyFont");
```

Do NOT include the file extension in the name of your resource or it will not find it

### Adding new resources

If you want to add a new kind of resource to the resource loader, you must add it to the RType class in the `rtype.h` file like this:

```c++
struct RType {
    explicit RType(const std::string &basePath) : textures(basePath + "/textures"), fonts(basePath + "/fonts"), newRessource(basepath + "/yourFolder") {}

    {...}

    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::Font> fonts;
    ResourceManager<newResource> newResource;
};
```

Your newResource class MUST have a `loadFromFile` method to load the corresponding resource e.g: 
```c++
newResource loadFromFile(std::string filename);
```

## Entity <a name = "entity"></a>

To add an Entity, your new Entity class must have the following:

```c++
// Must inherit from the Entity class (to be an Entity)
class MyEntity : public Entity {
public:
    explicit MyEntity();

// This makes the class polymorphic
// (or else you can't cast it to Entity)
    void cast() const override {};
};
```

In the MyEntity constructor, you can then add your components and define their default behaviour (you can still overwrite it later if needed).

```c++
MyEntity::MyEntity() {
    addComponent<PositionComponent>(0, 0);
    addComponent<RenderComponent>(rtype.textures.get("YourTexture"));
}
```

When it is done, you can construct your entity like this:

```c++
std::shared_ptr<MyEntity> myEntity = rtype.world.createEntity<MyEntity>(Args);
```

## 🏁 Component <a name = "component"></a>

To add a Component, your new Component class must have the following:

```c++
// Must inherit from the Component class (to be a Component)
class MyComponent : public Component {
public:
explicit MyComponent();

// This makes the class polymorphic
// (or else you can't cast it to Component)
void cast() const override {};
};
```

You can then add variables to your component.

```c++
class MyComponent : public Component {
private:
    // Variables here
public:
    explicit MyComponent();
    
    // Getters and setters here
    
    void cast() const override {};
};
```

When it is done, you can construct your Component like this:

```c++
std::shared_ptr<MyComponent> myComponent = entity->addComponent<MyComponent>(Args);
```

## System <a name = "system"></a>

To add a System, your new System class must have the following:

```c++
// Must inherit from the System class (to be a System)
class MySystem : public System {
public:
    explicit MySystem();

    // Update function called each frame
    // Where window is the render window,
    // world the World class contained in the rtype global variable,
    // delta the time (in seconds) elapsed since the last call of the function
    void update(sf::RenderWindow &window, World &world, float delta);
    
    // This makes the class polymorphic
    // (or else you can't cast it to System)
    void cast() const override {};
};
```

You must then add your component to the `world.h` for it to be called

```c++
std::vector<std::shared_ptr<System>> _systems = {
        std::make_shared<BackgroundSystem>(),
        std::make_shared<AnimationSystem>(),
        std::make_shared<HealthSystem>(),
        std::make_shared<HitboxSystem>(),
        std::make_shared<MovementSystem>(),
        std::make_shared<RenderSystem>()
};
```

Each system is called in the order it is defined here, so pay attention if your system includes getting / setting data from components used in another system.
