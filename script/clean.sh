#!/usr/bin/env bash

if [ ! -f assets/models/models.zip ]; then
    python3 script/compression.py zip assets/models assets/models/models.zip
fi

if [ ! -f assets/textures/textures.zip ]; then
    python3 script/compression.py zip assets/textures assets/textures/textures.zip
fi

rm -rf assets/models/*.obj assets/models/*.glb assets/models/*.mtl assets/textures/*.png

echo "all clean!"
