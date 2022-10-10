# Code du simulateur de labyrinthe

Compiler avec CMAKE 3.0, C11

# Organisation
```
LabySimulateur
├── algorithm |> implémentation de la résolution
│   └── path.c
├── api.h
├── laby |> code relatif à la génération, le chargement et la sauvegarde de labyrinthes
│   ├── laby_conf.h
│   ├── laby_gen.c
│   └── laby.h
├── main.c
├── simulator |> interface graphique avec OpenGL/SDL2 et fonctions de simulations
│   ├── factice_middleware.c
│   ├── gui.c
│   ├── gui.h
│   └── simulator.h
├── utils.c
└── sdl2-lib |> dossier pour la librairie SDL2 sous windows

```

# Librairies

La partie graphique est gérée par SDL2 (version **2.24.0**). Pour l'installer voir ci-dessous :

### Linux

```bash
sudo apt install libsdl2-dev
```

### Windows

Il faut télecharger le package `SDL2-devel-2.24.0-*.zip` (MingGW ou VC selon votre compilateur) sur le [github](https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0). \
Ensuite extraire l'archive dans le dossier `sdl2-lib/` du projet (à créer si non existant).

<hr>

# Middleware

Le middleware est la partie logiciel qui fait l'interface entre le code bas-niveau (gestion des moteurs et des capteurs) et
l'algorithme de au-niveau de résolution de labyrinthe. \
Les fonctions api sont déclarées dans le fichier `api.h`.

### Description des fonctions
> To do

<hr>
