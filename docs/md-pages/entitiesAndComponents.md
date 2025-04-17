# Entities and Components

## Entities
In the scope of this library entities essentially function like empty containers that you can add components or properties to. So an entity can be whatever you want it to be, give it a texture, make it pickupable, give it collision or all of the above and more.
Here is a quick overview over relevant classes containing functions pertaining to the creation and editing of entities:
- Manager
- Entity

## Components
The following components are currently available to you to use in your entities:
- Collider Component

Adds collision functionality to an Entity meaning functionality can be assigned to happen when two Entities collision boxes intersect --> this is used by the library, the developer themselves cannot (yet) add custom functionality to happen on collision. It is used to stop entities from running through tiles given the "collision" tag (see [Tiled](@ref md_docs_2md-pages_2tilemaps) section) and to enable picking up other entities.
- Data Component

Custom Data such as Stats can be added to an Entity and accessed using this Component. If an Entity is supposed to have movement the stat "speed" **has to be added**! 
- Interaction Component

Adding this component to an entity tells it to react to triggered Interactions e.g. by button press. For this a custom lambda or function pointer is passed to determine what exactly should happen once an entities ineraction was triggered.
- Pickup Component

Entities with pickup components will disappear once another collision having entity with the [Group Label](@ref Entity#GroupLabel) "Player" intersects with it and executes the custom functionality given to it via constructor.
- Sprite Component

Textures and Animations can be added via this component
- Stateffects Component

Temporary stateffects can be added using this component. Using the time and function passed it will execute whatever is in the function after the given time. It is used to e.g. reset stats after raising them in order to allow for temporary stat raises
- Transform Component

The Transform Component manages the position and movement of an Entity. Multiple overloaded constructors exist depending on whether or not the entity is stationary