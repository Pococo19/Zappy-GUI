<h1 align="center">
  Zappy-GUI - EPITECH PROJECT 2025<br>
  <img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/palette/macchiato.png" width="600px"/>
  <br>
</h1>

<p align="center">
  🎮 Zappy-GUI 🎮<br>
  A GUI for the Zappy end of year project
</p>

---

## 📰 Description

> TODO

### Group leaders

> TODO

---

## 📦 Installation

Clone the repo with its submodules.

```bash
git clone --recurse-submodules -j$(nproc) git@github.com:Pococo19/Zappy-GUI.git
```

### Dependencies

Get the dependencies and build the project using `nix`:

```bash
nix develop
```

Or manually install them. We use `cmake` `bash` `python3`.<br>
All others dependencies are managed by **github submodules**.

### Build

Build the project using our multithreading build `bash` script:

```bash
./build.sh
```

Or manually run `cmake`:

```bash
mkdir build/ && cd build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
```

### Run and play!

> TODO

---

## 🖼️ Graphical backend

- Raylib (C bind in C++ by our engine)

---

## 🚀 Extra-Features

> TODO

---

## 🛠️ Development

> TODO

---

## Tested on

- MacOS
- Fedora
- Debian
- EndeavourOS
- Arch
- Ubuntu

---

## License

Project developed as part of the B-YEP-400 module at EPITECH.
See [**LICENSE**](/LICENSE.md).
