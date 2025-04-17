# Quickstart guide for setting up the library

This guide's purpose is to get developers from 0 to being able to create their game in the quickest and most uncomplicated way possible. Therefore it will only go over the bare minimum to get everything up and running for implementation guides check out the other sections on the welcome page.

## Installations and tools

Go to the github repository and download the setup file for your OS (windows and linux supported). This file needs to be executed in the folder you want to start your project in which will start the initial setup. While you can also manually download all of the necessary tools, this setup file acts as a central automated executable to streamline and expedite the non-game development aspect of this process which is why it is highly recommended.
The tools downloaded are:
- mingw(win)/gcc(linux)
- CMake
- Tiled (Installer)
- Git

It will also automatically download the library and templates to start a project with.
The only manual step required of the user is to finalize the installation of Tiled in order to use it for the creation of maps. For this simply double click the downloaded setup file and go through the installation wizard. After it is installed the .msi file can be deleted.

After this is completed there should be a folder named vego, with everything necessary in it.
The optional templates will be under `vego/my_game/include` and `vego/my_game/src`. Even if you choose not to use them still place your .h files in include and your .cpp files in src. Once setup, open the project folder in the IDE of your choosing, building and compiling should work using the associated compilation script as it is “IDE Agnostic”. For actual development it is recommended to look into the preexisting files in the template. Within them inline short explanations and code snippets can be found that act as a guide for your own implementation of features.


