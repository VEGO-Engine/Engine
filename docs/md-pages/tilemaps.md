# Building a map using Tiled and tmx and loading it
In order to create a map for your game the library has .tmx format support. In order to get .tmx files you use the associated tile editor "Tiled" which gets automatically downloaded when executing the VEGO libraries setup file (the installer is provided the installation itself must be finalized by the user). This section will walk you step by step through the creation of your first map/background using Tiled.

see also: [the official Tiled documentation](https://doc.mapeditor.org/en/stable/manual/introduction/#getting-started)

### Getting started
After opening Tiled, select "New Map", a custom size measured in tiles and as tile size select 32x32 as this is 
the size the library currently supports. Also choose the size of your canvas, it is recommended you choose the same size as the one you defined in the [games config](@ref md_docs_2md-pages_2config) (default is 25w x 20h, measured in tiles, to get the pixel size just multiply by 32 as that is the tilesize the library uses)

![](@ref Tiled1.jpg){html: width=50%}
![](@ref Tiled2.jpg){html: width=50%}

### Create a New Tileset
1. In the editor, go to the lower-right corner and select "New Tileset".
2. Give your tileset a name.
3. Make sure to select "Embed in map".
4. Choose your tilesheet as the source.
5. Leave the rest of the settings on default
![](@ref Tiled3.jpg){html: width=50%}
![](@ref Tiled4.jpg){html: width=50%}
### Draw Your Environment
Once imported, you can select tiles from the tileset and use them to build your environment.

### Understand Layers in Tiled

Tiled allows you to use multiple layers for organizing your map.

You need to give your Layers seperate z-Indices to decide their rendering order, the lower the number the earlier it gets rendered.
In order to do this:
1. Select a layer.
1. Right-click "Custom Properties" and go to "Add Property".
1. Add a new int property named "zIndex" and give it a number starting with 0 to decide when to render it (the lower the number the more the layer is in the background i.e. tiles on layer 0 will be covered by tiles on layer 1 if they occupy the same space).

![](@ref Tiled5.jpg){html: width=50%}

**Important: Tiles that should have collision must be placed on a separate layer as custom properties are per layer not per tile.**

### Set Up Collision
To add collision to a layer:

1. Select the layer you want to have collision.
1. Right-click and go to "Custom Properties".
1. Add a new boolean property named "collision" and tick the checkbox.

![](@ref Tiled5.jpg){html: width=50%}

Any tile placed on this layer will now automatically have collision—meaning moving entities cannot pass through them.

### Saving your work

After completeing your map, save it in the asset folder of the library (or any place really the asset folder just exists as a recommendation to easily find all of your maps and textures)

![](@ref Tiled6.jpg){html: width=50%}

### Loading your work into the game
The map gets loaded into the game in `GameImplementation.cpp`, simply add the path of the map .tmx file to the [Map](@ref Map) constructor
