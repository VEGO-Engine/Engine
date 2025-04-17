# Building an environment using Tiled and tmx

see also: [the official Tiled documentation](https://doc.mapeditor.org/en/stable/manual/introduction/#getting-started)

After opening Tiled, select "New Map", a custom size measured in tiles and as tile size select 32x32 as this is the size the library currently supports.

### Create a New Tileset

    In the editor, go to the lower-right corner and select "New Tileset".

    Give your tileset a name.

    Make sure to select "Embed in map".

    Choose your tilesheet as the source.

### Draw Your Environment

    Once imported, you can select tiles from the tileset and use them to build your environment.

### Understand Layers in Tiled

    Tiled allows you to use multiple layers for organizing your map.

    You need to give your Layers seperate z-Indices to decide their rendering order, the lower the number the earlier it gets rendered.

    In order to do this select a layer.

    Add a new int property named "zIndex" and give it a number starting with 0 to decide when to render it (0 gets rendered first etc.).

    Important: Tiles that should have collision must be placed on a separate layer.

### Set Up Collision

    Select the layer you want to have collision.

    Right-click and go to "Custom Properties".

    Add a new boolean property named "collision" and tick the checkbox.

    Any tile placed on this layer will now automatically have collision—meaning moving entities cannot pass through them.