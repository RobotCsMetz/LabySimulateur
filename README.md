# Code du simulateur de labyrinthe

Compiler avec CMAKE 3.0, C11

# Organisation
```
LabySimulateur/
|   main.c : code pour lancer sur machine
|   api.h : déclaration des fonctions apis du simulateur
|
|___algorithm/ : implementation de la resolution
|
|___gui/ : interface graphique avec OpenGL/SDL
|
|___sdl2-lib/ : dossier pour la SDL2 sous windows

```

# Librairies

Le partie graphique est géré par SDL2 (version **2.24.0**). Pour l'installer voir si dessous :

### Linux

```bash
sudo apt install libsdl2-dev
```

### Windows

Il faut télecharger le package `SDL2-devel-2.24.0-*.zip` (MingGW ou VC selon votre compilateur) sur le [github](https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0). \
Ensuite extraire l'archive dans le dossier `sdl2-lib/` du projet (à creer si non existant).

