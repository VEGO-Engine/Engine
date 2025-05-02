# Configuring the game

By either adding your own configuration .json file and overwriting its path in setConfigFilePath() found in Chickengame.cpp or editing configs/mainConfig.json you can configure some aspects of the game. These are:
- **fullscreen**: bool to determine if you want your game to be displayed in fullscreen or not. Maintains the screen size set in screen_width and screen_height and stretches it out

- **screen_width**: int, in pixels 

- **screen_height**: int, in pixels

- **title**: string, the title of the game/the name displayed on the top left of the window

- **icon**: string, path to the bitmap (.btm) you want to use as the app icon of your game 