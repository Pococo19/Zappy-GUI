# Documentation Complète - Zappy-GUI

## Table des Matières

1. [Vue d'ensemble](#vue-densemble)
2. [Architecture du projet](#architecture-du-projet)
3. [Installation et compilation](#installation-et-compilation)
4. [Structure des fichiers](#structure-des-fichiers)
5. [Modules principaux](#modules-principaux)
6. [API et interfaces](#api-et-interfaces)
7. [Système de rendu 3D](#système-de-rendu-3d)
8. [Protocole réseau](#protocole-réseau)
9. [Configuration et utilisation](#configuration-et-utilisation)
10. [Développement](#développement)
11. [Tests et débogage](#tests-et-débogage)
12. [Contribution](#contribution)
13. [Licence](#licence)

---

## Vue d'ensemble

**Zappy-GUI** est un client de visualisation 3D pour le projet Zappy, transformant le monde de jeu 2D traditionnel en un système planétaire 3D immersif. Le projet utilise C++20 moderne et la bibliothèque graphique raylib pour créer une expérience visuelle unique où la carte de jeu devient la planète "Zappy" dans un système stellaire complet.

### Caractéristiques principales

- **🌌 Simulation spatiale 3D** : Transformation de la carte 2D en système planétaire
- **🔄 Communication réseau temps réel** : Connexion TCP au serveur Zappy
- **⚡ Architecture C++20 moderne** : Utilisation des dernières fonctionnalités du langage
- **🎮 Moteur graphique intégré** : Framework ZapGUI personnalisé basé sur raylib
- **🎨 Rendu avancé** : Shaders personnalisés et éclairage dynamique
- **🏗️ Conception modulaire** : Séparation claire des responsabilités

### Informations du projet

- **Version** : 0.1.1
- **Auteurs** : Léo QUINZLER, Luka VUJANOVIC
- **École** : EPITECH (Promotion 2025)
- **Licence** : GNU General Public License v3.0
- **Langage** : C++20
- **Bibliothèque graphique** : raylib 5.5

---

## Architecture du projet

Le projet suit une architecture en couches avec une séparation claire des responsabilités :

```
┌─────────────────────────────────────┐
│           Application Layer         │
│    (zappy::Application)            │
├─────────────────────────────────────┤
│         Star System Layer          │
│  (Planets: Zappy, Slavia, Sun)     │
├─────────────────────────────────────┤
│        Network Protocol Layer      │
│     (TCP Communication)            │
├─────────────────────────────────────┤
│         ZapGUI Framework           │
│  (Engine, Rendering, Networking)   │
├─────────────────────────────────────┤
│           raylib Library           │
│      (OpenGL Abstraction)         │
└─────────────────────────────────────┘
```

### Composants principaux

#### 1. **Application Layer** (`src/App/`)
Gère le cycle de vie principal de l'application et la logique métier.

#### 2. **Star System** (`src/App/Stars/`)
Implémente les objets célestes du système planétaire.

#### 3. **Network Protocol** (`src/App/Protocol/`)
Gère la communication avec le serveur Zappy via TCP.

#### 4. **ZapGUI Framework** (`src/ZapGUI/`, `include/ZapGUI/`)
Framework graphique personnalisé construit sur raylib.

---

## Installation et compilation

### Prérequis système

```bash
# Outils de développement
- Compilateur C++20 (GCC 10+ ou Clang 12+)
- CMake 3.16+
- Make
- pkg-config

# Bibliothèques système
- OpenGL 3.3+
- X11 (Linux)
```

### Installation rapide

#### Compilation standard
```bash

# Compiler
./build.sh
```

### Scripts utilitaires

- **`build.sh`** : Script de compilation principal avec gestion d'erreurs
- **`fetch.sh`** : Téléchargement et extraction des ressources
- **`script/clean.sh`** : Nettoyage des artefacts de compilation
- **`script/dependencies.sh`** : Installation automatique des dépendances

---

## Structure des fichiers

```
Zappy-GUI/
├── 📁 assets/                   # Ressources du jeu
│   ├── 📁 models/               # Modèles 3D (.obj, .mtl)
│   ├── 📁 shaders/              # Shaders GLSL
│   └── 📁 textures/             # Textures et matériaux
│
├── 📁 build/                    # Artefacts de compilation
│   ├── 📄 CMakeCache.txt
│   ├── 📄 compile_commands.json
│   └── 📁 CMakeFiles/
│
├── 📁 external/                 # Dépendances externes
│   └── 📁 raylib/               # Bibliothèque graphique
│
├── 📁 include/                  # Headers publics
│   └── 📁 ZapGUI/               # Framework headers
│       ├── 📄 Types.hpp         # Types de base
│       ├── 📄 Macro.hpp         # Macros système
│       ├── 📄 Version.hpp       # Information de version
│       ├── 📄 Logger.hpp        # Système de logging
│       └── 📄 Error.hpp         # Gestion d'erreurs
│
├── 📁 src/                      # Code source
│   ├── 📄 Main.cpp              # Point d'entrée
│   ├── 📁 App/                  # Logique applicative
│   │   ├── 📄 Application.{hpp,cpp}  # Classe principale
│   │   ├── 📄 Arguments.{hpp,cpp}    # Parsing des arguments
│   │   ├── 📁 Protocol/         # Communication réseau
│   │   ├── 📁 Stars/            # Système planétaire
│   │   ├── 📁 Seed/             # Génération procédurale
│   │   └── 📁 Maths/            # Utilitaires mathématiques
│   ├── 📁 Utils/                # Utilitaires génériques
│   └── 📁 ZapGUI/               # Implémentation du framework
│       ├── 📁 Engine/           # Moteur de jeu
│       ├── 📁 Render/           # Système de rendu
│       ├── 📁 Drawable/         # Objets dessinables
│       ├── 📁 Network/          # Réseau
│       └── 📁 Event/            # Gestion d'événements
│
├── 📁 script/                    # Scripts utilitaires
│   ├── 📄 clean.sh             # Nettoyage
│   ├── 📄 dependencies.sh      # Installation de dépendances
│   └── 📄 compression.py       # Extraction d'assets
│
├── 📄 CMakeLists.txt            # Configuration CMake
├── 📄 build.sh                 # Script de compilation
├── 📄 fetch.sh                 # Récupération d'assets
├── 📄 flake.nix                # Environnement Nix
├── 📄 LICENSE                  # Licence GPL v3
└── 📄 zappy_gui                # Exécutable final
```

---

## Modules principaux

### 1. Application (`src/App/Application.{hpp,cpp}`)

La classe `Application` est le cœur du programme, héritant de `zap::abstract::GameEngine`.

```cpp
namespace zappy {
class Application final : public zap::abstract::GameEngine {
public:
    Application(const parser::Flags &flags);
    ~Application() override;
    
    void init() override;
    void update() override;
    
private:
    std::shared_ptr<zap::NetworkClient> _net;
    void _init_network();
};
}
```

**Responsabilités :**
- Initialisation du système
- Gestion du cycle de vie
- Coordination entre les composants
- Communication réseau

### 2. Gestion des arguments (`src/App/Arguments.{hpp,cpp}`)

Parser robuste pour les arguments de ligne de commande.

```cpp
namespace parser {
struct Flags {
    u16 port = 0;
    std::string hostname;
};

Flags parse(int argc, const char **argv);
void usage();
void version();
}
```

**Fonctionnalités :**
- Validation des ports (0-65535)
- Gestion des erreurs d'arguments
- Messages d'aide et de version
- Support des formats hostname/IP

### 3. Système planétaire (`src/App/Stars/`)

#### BasePlanet (`BasePlanet.{hpp,cpp}`)
Classe abstraite de base pour tous les objets célestes.

```cpp
class BasePlanet : public zap::ShaderModel {
public:
    explicit BasePlanet(std::shared_ptr<zap::ZapCamera>);
    
    virtual void draw() const override;
    virtual void update(const f32 dt) override;
    
    f32 getRadius() const;
    Vector3 getPosition() const;
    
protected:
    std::shared_ptr<zap::ZapCamera> _camera;
    f32 _radius = 0.0f;
    Vector3 _position = {0.0f, 0.0f, 0.0f};
};
```

#### Zappy (`Zappy.{hpp,cpp}`)
Planète principale représentant la carte de jeu.

```cpp
class Zappy final : public BasePlanet {
public:
    explicit Zappy(const protocol::GUI_Map &map, 
                   std::shared_ptr<zap::ZapCamera> camera);
    
    void setCamera(std::shared_ptr<zap::ZapCamera> camera);
    void update(const f32 dt) override;
    
private:
    void _init(const protocol::GUI_Map &map);
    Mesh _create_deformed_mesh(const protocol::GUI_Map &map);
};
```

**Fonctionnalités :**
- Déformation de maillage 2D vers 3D sphérique
- Mapping des ressources sur la surface
- Génération procédurale de terrain
- Mise à jour dynamique depuis le serveur

#### Slavia (`Slavia.{hpp,cpp}`)
Planète secondaire orbitant autour de Zappy.

```cpp
class Slavia final : public BasePlanet {
public:
    explicit Slavia(std::shared_ptr<zap::ZapCamera> camera, 
                    const f32 zappy_radius);
    
    void update(const f32 dt) override;
    
private:
    f32 _rotation = 0.0f;
    f32 _zappy_radius = 0.0f;
};
```

#### Sun (`Sun.{hpp,cpp}`)
Étoile centrale du système avec éclairage dynamique.

### 4. Protocole réseau (`src/App/Protocol/`)

#### Protocol (`Protocol.{hpp,cpp}`)
Définit les structures de données et la logique de communication.

```cpp
namespace zappy::protocol {

#define ZAP_MAX_RESOURCES 7

enum ResourceType {
    UNKNOWN = -1,
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6
};

struct GUI_Map {
    u32 width;
    u32 height;
    std::vector<std::vector<ResourceType>> tiles;
};

class Protocol {
public:
    void handleMessage(const std::string &message);
    void sendCommand(const std::string &command);
    
private:
    void _parse_map_size(const std::string &data);
    void _parse_tile_content(const std::string &data);
};
}
```

#### Callback (`Callback.{hpp,cpp}`)
Système de callbacks pour les événements réseau.

---

## API et interfaces

### ZapGUI Framework

Le framework ZapGUI fournit une abstraction complète pour le développement d'applications 3D.

#### Types de base (`include/ZapGUI/Types.hpp`)
```cpp
// Types numériques
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
using f64 = double;

// Types raylib étendus
using Color3 = Vector3;
using Position2D = Vector2;
using Position3D = Vector3;
```

#### Macros système (`include/ZapGUI/Macro.hpp`)
```cpp
#define ZAP_DEFAULT_WINDOW_SIZE Vector2{1280, 720}
#define ZAP_DEFAULT_MAX_FRAMERATE 60

#define SUCCESS 0
#define ERROR 84

#ifdef DEBUG
    #define ZAP_DEBUG_LOG(msg) zap::logger::debug(msg)
#else
    #define ZAP_DEBUG_LOG(msg)
#endif
```

#### Système de logging (`include/ZapGUI/Logger.hpp`)
```cpp
namespace zap::logger {
    void info(const std::string &message);
    void warn(const std::string &message);
    void error(const std::string &message);
    void debug(const std::string &message);
    void fatal(const std::string &message);
}
```

#### Gestion d'erreurs (`include/ZapGUI/Error.hpp`)
```cpp
namespace zap::exception {
class Error : public std::exception {
public:
    explicit Error(const std::string &message);
    const char *what() const noexcept override;
    
private:
    std::string _message;
};
}
```

### Moteur de jeu (`src/ZapGUI/Engine/`)

#### GameEngine (`GameEngine.{hpp,cpp}`)
```cpp
namespace zap::abstract {
class GameEngine {
public:
    virtual ~GameEngine() = default;
    
    virtual void init() = 0;
    virtual void update() = 0;
    
protected:
    bool _should_close = false;
    f32 _delta_time = 0.0f;
};
}
```

#### Context (`Context.{hpp,cpp}`)
```cpp
namespace zap::context {
void run(std::unique_ptr<zap::abstract::GameEngine> engine,
         Vector2 window_size,
         const std::string &title,
         i32 target_fps);
}
```

### Système de rendu (`src/ZapGUI/Render/`)

#### Camera (`Camera.{hpp,cpp}`)
```cpp
class ZapCamera {
public:
    ZapCamera(Vector3 position, Vector3 target, Vector3 up);
    
    void update();
    void setPosition(Vector3 position);
    void setTarget(Vector3 target);
    
    Camera3D getRaylibCamera() const;
    
private:
    Camera3D _camera;
    bool _enabled = true;
};
```

### Objets dessinables (`src/ZapGUI/Drawable/`)

#### ShaderModel (`ShaderModel.{hpp,cpp}`)
```cpp
class ShaderModel {
public:
    ShaderModel(const std::string &vertex_shader_path,
                const std::string &fragment_shader_path);
    
    virtual void draw() const = 0;
    virtual void update(const f32 dt) = 0;
    
protected:
    Shader _shader;
    Model _model;
    bool _loaded = false;
};
```

---

## Système de rendu 3D

### Shaders

Le système utilise des shaders GLSL personnalisés pour un rendu avancé.

#### Shader de planète (`assets/shaders/planet.vert`)
```glsl
#version 330 core

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

out vec3 fragPosition;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main() {
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));
    fragTexCoord = vertexTexCoord;
    fragNormal = normalize(vec3(matNormal * vec4(vertexNormal, 0.0)));
    
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
```

#### Shader de fragment (`assets/shaders/planet.frag`)
```glsl
#version 330 core

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 finalColor;

void main() {
    vec3 lightColor = vec3(1.0);
    vec3 ambient = 0.15 * lightColor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular);
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    finalColor = vec4(result, 1.0) * texelColor * colDiffuse;
}
```

### Génération de maillage

La transformation 2D vers 3D utilise une projection sphérique :

```cpp
Mesh Zappy::_create_deformed_mesh(const protocol::GUI_Map &map) {
    const u32 width = map.width;
    const u32 height = map.height;
    
    Mesh mesh = {0};
    mesh.triangleCount = (width - 1) * (height - 1) * 2;
    mesh.vertexCount = mesh.triangleCount * 3;
    
    mesh.vertices = new float[mesh.vertexCount * 3];
    mesh.texcoords = new float[mesh.vertexCount * 2];
    mesh.normals = new float[mesh.vertexCount * 3];
    
    // Projection sphérique
    for (u32 y = 0; y < height - 1; y++) {
        for (u32 x = 0; x < width - 1; x++) {
            // Calcul des coordonnées sphériques
            float phi1 = (float)x / width * 2.0f * PI;
            float phi2 = (float)(x + 1) / width * 2.0f * PI;
            float theta1 = (float)y / height * PI;
            float theta2 = (float)(y + 1) / height * PI;
            
            // Conversion vers coordonnées cartésiennes
            Vector3 p1 = {
                radius * sinf(theta1) * cosf(phi1),
                radius * cosf(theta1),
                radius * sinf(theta1) * sinf(phi1)
            };
            // ... autres points
        }
    }
    
    return mesh;
}
```

---

## Protocole réseau

### Architecture de communication

```
Client (Zappy-GUI) ←→ [TCP Socket] ←→ Serveur (Zappy)
```

### Messages du protocole

#### Messages serveur → client
- `msz X Y` : Taille de la carte
- `bct X Y q0 q1 q2 q3 q4 q5 q6` : Contenu d'une case
- `tna N` : Nom d'équipe
- `pnw #n X Y O L N` : Connexion d'un joueur
- `ppo #n X Y O` : Position d'un joueur
- `plv #n L` : Niveau d'un joueur
- `pin #n X Y q0 q1 q2 q3 q4 q5 q6` : Inventaire d'un joueur

#### Messages client → serveur
- `GRAPHIC` : Connexion en tant que client graphique
- `mct` : Demande du contenu de toute la carte
- `bct X Y` : Demande du contenu d'une case
- `tna` : Demande des noms d'équipes

### Implémentation réseau

```cpp
class NetworkClient {
public:
    bool connect(const std::string &hostname, u16 port);
    void disconnect();
    
    void sendMessage(const std::string &message);
    std::string receiveMessage();
    
    bool isConnected() const;
    
private:
    i32 _socket_fd = -1;
    std::mutex _send_mutex;
    std::mutex _receive_mutex;
    
    bool _create_socket();
    bool _connect_to_server(const std::string &hostname, u16 port);
};
```

### Gestion asynchrone

```cpp
class Protocol {
private:
    std::thread _network_thread;
    std::atomic<bool> _running{false};
    std::queue<std::string> _message_queue;
    std::mutex _queue_mutex;
    
    void _network_loop();
    void _process_message(const std::string &message);
};
```

---

## Configuration et utilisation

### Arguments de ligne de commande

```bash
# Affichage de l'aide
./zappy_gui --help
./zappy_gui -h

# Affichage de la version
./zappy_gui --version
./zappy_gui -v

# Connexion à un serveur
./zappy_gui --hostname localhost --port 4242
./zappy_gui -n localhost -p 4242

# Connexion avec IP
./zappy_gui -n 192.168.1.100 -p 8080
```

### Configuration par défaut

```cpp
// Taille de fenêtre par défaut
#define ZAP_DEFAULT_WINDOW_SIZE Vector2{1280, 720}

// FPS cible
#define ZAP_DEFAULT_MAX_FRAMERATE 60

// Paramètres de rendu
#define ZAP_PLANET_DEFAULT_RADIUS 10.0f
#define ZAP_CAMERA_DEFAULT_DISTANCE 25.0f
```

### Contrôles

#### Caméra
- **Souris** : Rotation de la vue
- **Molette** : Zoom avant/arrière
- **Clic droit + déplacement** : Pan de la caméra

#### Navigation
- **WASD** : Déplacement libre de la caméra
- **Espace** : Montée
- **Shift** : Descente
- **Échap** : Quitter l'application

### Variables d'environnement

```bash
# Chemin vers les assets (si différent du défaut)
export ZAP_ASSETS_PATH="/custom/path/to/assets"

# Niveau de log
export ZAP_LOG_LEVEL="DEBUG"  # DEBUG, INFO, WARN, ERROR, FATAL

# Désactiver le VSync
export ZAP_DISABLE_VSYNC=1
```

---

## Développement

### Standards de code

#### Style C++
```cpp
// Nommage des classes : PascalCase
class NetworkClient {
public:
    // Méthodes publiques : camelCase
    void sendMessage(const std::string &message);
    
private:
    // Membres privés : _snake_case avec préfixe underscore
    i32 _socket_fd = -1;
    std::string _hostname;
};

// Nommage des namespaces : snake_case
namespace zappy::protocol {
    // Énumérations : SCREAMING_SNAKE_CASE
    enum ResourceType {
        UNKNOWN = -1,
        FOOD = 0
    };
}
```

#### Conventions de fichiers
```cpp
/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ClassName.hpp
*/

#pragma once

// Headers système
#include <string>
#include <memory>

// Headers du projet
#include <ZapGUI/Types.hpp>
#include <ZapGUI/Error.hpp>
```

### Compilation en mode debug

```bash
# Configuration debug
mkdir build-debug && cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=ON
make -j$(nproc)

# Exécution avec gdb
gdb ./zappy_gui
(gdb) run -n localhost -p 4242
```

### Outils de développement

#### Analyse statique
```bash
# Cppcheck
cppcheck --enable=all --inconclusive --std=c++20 src/

# Clang-tidy
clang-tidy src/**/*.cpp -- -std=c++20 -I include/
```

#### Formatage de code
```bash
# Clang-format (configuration dans .clang-format)
find src/ include/ -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

#### Profiling
```bash
# Valgrind pour les fuites mémoire
valgrind --leak-check=full --show-leak-kinds=all ./zappy_gui

# Perf pentru les performances
perf record ./zappy_gui
perf report
```

### Ajout de nouvelles fonctionnalités

#### 1. Nouvelle planète
```cpp
// 1. Créer la classe dans src/App/Stars/
class NewPlanet final : public BasePlanet {
public:
    explicit NewPlanet(std::shared_ptr<zap::ZapCamera> camera);
    void update(const f32 dt) override;
};

// 2. Enregistrer dans Application.cpp
_planets.push_back(std::make_unique<NewPlanet>(_camera));
```

#### 2. Nouveau type de ressource
```cpp
// 1. Ajouter dans Protocol.hpp
enum ResourceType {
    // ... existing
    NEW_RESOURCE = 7
};

// 2. Mettre à jour ZAP_MAX_RESOURCES
#define ZAP_MAX_RESOURCES 8
```

#### 3. Nouveau shader
```glsl
// 1. Créer assets/shaders/new_shader.vert et .frag
// 2. Définir les macros dans le header approprié
#define ZAP_SHADER_NEW_VERT "assets/shaders/new_shader.vert"
#define ZAP_SHADER_NEW_FRAG "assets/shaders/new_shader.frag"
```

---

## Tests et débogage

### Système de logging

```cpp
// Utilisation du système de logging
zap::logger::info("Application started successfully");
zap::logger::warn("Network connection unstable");
zap::logger::error("Failed to load texture: " + filename);
zap::logger::debug("Player position: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
zap::logger::fatal("Critical system failure");
```

### Tests de réseau

```bash
# Test de connexion
nc -l 4242  # Terminal 1 (serveur de test)
./zappy_gui -n localhost -p 4242  # Terminal 2 (client)
```

### Tests de rendu

```cpp
// Test de chargement de modèle
try {
    Model model = LoadModel("assets/models/test.obj");
    if (model.meshCount == 0) {
        throw zap::exception::Error("Failed to load model");
    }
} catch (const zap::exception::Error &e) {
    zap::logger::error(e.what());
}
```

### Debugging avec GDB

```bash
# Compilation avec symboles de debug
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Lancement avec GDB
gdb ./zappy_gui
(gdb) set args -n localhost -p 4242
(gdb) break main
(gdb) run
(gdb) backtrace
(gdb) print variable_name
```

### Profiling mémoire

```bash
# Valgrind
valgrind --tool=memcheck --leak-check=full ./zappy_gui

# AddressSanitizer (compilation)
cmake .. -DCMAKE_CXX_FLAGS="-fsanitize=address -g"
```

---

## Contribution

### Workflow de développement

```bash
# 1. Fork du projet sur GitLab/GitHub
git clone <your-fork-url>
cd Zappy-GUI

# 2. Créer une branche de fonctionnalité
git checkout -b feature/nouvelle-fonctionnalite

# 3. Développement et tests
# ... modifications ...

# 4. Commit avec message descriptif
git add .
git commit -m "feat: ajout du système de particules pour les planètes"

# 5. Push et merge request
git push origin feature/nouvelle-fonctionnalite
```

### Conventions de commit

```
feat: nouvelle fonctionnalité
fix: correction de bug
docs: mise à jour documentation
style: formatage, pas de changement de code
refactor: refactoring sans changement de fonctionnalité
test: ajout ou modification de tests
chore: tâches de maintenance
```

### Code review checklist

- [ ] Code compilable sans warnings
- [ ] Tests passent
- [ ] Documentation mise à jour
- [ ] Style de code respecté
- [ ] Pas de fuites mémoire
- [ ] Performance acceptable
- [ ] Gestion d'erreurs appropriée

### Issues et bugs

Lors de la création d'une issue :

1. **Description claire** du problème
2. **Étapes de reproduction**
3. **Environnement** (OS, compilateur, version)
4. **Logs d'erreur** si applicable
5. **Comportement attendu** vs comportement observé

---

## Licence

```
Copyright (C) 2025 Léo QUINZLER, Luka VUJANOVIC

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```

### Dépendances et licences

- **raylib** : zlib/libpng License
- **C++ Standard Library** : Varies by implementation
- **OpenGL** : Free API specification

---

## Appendices

### A. Ressources externes

- [raylib Documentation](https://www.raylib.com/)
- [OpenGL Documentation](https://docs.gl/)
- [CMake Documentation](https://cmake.org/documentation/)
- [C++20 Reference](https://en.cppreference.com/)

### B. Glossaire

- **Mesh** : Structure de données représentant un modèle 3D
- **Shader** : Programme exécuté sur le GPU pour le rendu
- **Vertex** : Point dans l'espace 3D
- **Fragment** : Pixel potentiel lors du rendu
- **MVP Matrix** : Model-View-Projection matrix pour les transformations 3D
- **VBO** : Vertex Buffer Object (OpenGL)
- **VAO** : Vertex Array Object (OpenGL)

### C. Configuration système

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake pkg-config git
sudo apt install libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libasound2-dev
```

### D. Troubleshooting

#### Problèmes de compilation
- **Erreur C++20** : Vérifier la version du compilateur (GCC 10+ ou Clang 12+)
- **Erreur OpenGL** : Installer les drivers graphiques appropriés
- **Erreur raylib** : Vérifier l'initialisation des sous-modules Git

#### Problèmes de réseau
- **Connexion refusée** : Vérifier que le serveur Zappy fonctionne
- **Timeout** : Vérifier les paramètres de firewall
- **Format de message** : Vérifier la compatibilité du protocole

#### Problèmes de performance
- **FPS bas** : Vérifier l'accélération matérielle OpenGL
- **Latence réseau** : Optimiser la fréquence des mises à jour
- **Mémoire élevée** : Profiler avec Valgrind ou AddressSanitizer

---

**Fin de documentation - Version 1.0 - Juin 2025**
