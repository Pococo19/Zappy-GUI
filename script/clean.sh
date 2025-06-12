#!/usr/bin/env bash

if [ ! -f assets/models/models.zip ]; then
    python3 script/compression.py zip assets/models assets/models.zip
fi

if [ ! -f assets/textures/texture.zip ]; then
    python3 script/compression.py zip assets/textures assets/textures/texture.zip
fi

rm -rf assets/models/*.obj assets/models/*.mtl assets/textures/*.png
