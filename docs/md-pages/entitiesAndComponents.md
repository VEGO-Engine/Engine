# Entities and Components
## Entities
In the scope of this library entities essentially function like empty containers that you can add components or properties to. So an entity can be whatever you want it to be, give it a texture, make it pickupable, give it collision or all of the above and more.
[Manager](@ref Manager) contains functions responsible for the creation and editing of entities:

**If you are ever lost when looking for related functionality via search or side bar remember it is all neatly organized on this page for better readability and a better overview**

## Components
The following components are currently available for you to use in your entities (the associated managers/handlers are also linked):

---
### [Transform Component](@ref TransformComponent)
The Transform Component manages the position and movement of an Entity. Multiple overloaded constructors exist depending on whether or not the entity is stationary

---
### [Sprite Component](@ref SpriteComponent)
Textures and Animations can be added via this component. 

> [!important]
> A [Transform Component](@ref TransformComponent) is first needed before adding a Texture as the coordinates from the transform component are needed to tell the game where to render the texture

---
### [Data Component](@ref DataComponent)
Custom Data such as Stats can be added to an Entity and accessed using this Component.

> [!important]
> If an Entity is supposed to be able to move the stat "speed" has to be added and set to a positive int!

---
### [Collider Component](@ref ColliderComponent)
see also [Collision Handler](@ref CollisionHandler)

Adds collision functionality to an Entity. It is used to stop entities with a PLAYER group label from running through tiles that were given the "collision" tag in the Tiled editor (see [Tiled](@ref md_docs_2md-pages_2tilemaps) section) or the COLLIDERS group label in the code.

Also enables "picking up" other entities via [Pickup Component](@ref PickupComponent).

---
### [Interaction Component](@ref InteractionComponent)
see also [InteractionEventdataStruct](@ref InteractionEventdataStruct)

Adding this component to an entity tells it to react to triggered Interactions e.g. by button press. For this a custom lambda or function pointer is passed to determine what exactly should happen once an entities ineraction was triggered. 

> [!note]
> This component is only used to assign a functionality to an entity to be triggered when it is interacted with, to actually map a button to do something such as trigger an interaction refer to [Input Management](@ref md_docs_2md-pages_2inputhandling) and [Eventhandling](@ref md_docs_2md-pages_2eventhandling)

---
### [Pickup Component](@ref PickupComponent)
see also [Pickup Manager](@ref PickupManager)

Entities with pickup components will disappear once another collision having entity with the [Group Label](@ref Entity#GroupLabel) "Player" intersects with it and executes the custom functionality given to it via constructor.

---
### [Stat Effects Component](@ref StatEffectsComponent)
Temporary stateffects can be added using this component. Using the time and function passed it will execute whatever is in the function after the given time. It is used to e.g. reset stats after raising them in order to allow for temporary stat raises