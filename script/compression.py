##
## EPITECH PROJECT, 2025
## Zappy-GUI
## File description:
## compression.py
##

import argparse
import os
import sys
import zipfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path


def collect_files(base_path: Path) -> list[tuple]:
    """
    collects all files in the given directory and returns a list of tuples
    """

    base_path = Path(base_path).resolve()
    files: list[tuple] = []

    for root, _, filenames in os.walk(base_path):
        for name in filenames:

            if name.endswith(".zip"):
                continue

            file_path = Path(root) / name
            arcname = file_path.relative_to(base_path)
            files.append((file_path, arcname))

    return files


def read_file(path_tuple: tuple[str, str]) -> tuple | None:
    """
    reads a file and returns its content as a tuple (arcname, data)
    """

    file_path, arcname = path_tuple

    try:
        with open(file_path, "rb") as f:
            data = f.read()
        return (arcname, data)

    except Exception as e:
        print(f"Error reading {file_path}: {e}", file=sys.stderr)
        return None


def zip_assets_threaded(source_path: Path, zip_path: Path) -> None:
    """
    zips all files in the given directory using threading pool for parallel reading
    """

    source_path = Path(source_path).resolve()
    zip_path = Path(zip_path).resolve()

    if source_path.suffix == ".zip":
        print("Error: source path must not be a .zip file!", file=sys.stderr)
        sys.exit(84)


    print("Collecting files...")
    file_list = collect_files(source_path)

    print(f"Reading {len(file_list)} files in parallel...")
    with ThreadPoolExecutor() as executor:
        results = list(executor.map(read_file, file_list))

    print("Writing to zip...")
    with zipfile.ZipFile(zip_path, "w", compression=zipfile.ZIP_DEFLATED) as zipf:

        for item in results:

            if item:
                arcname, data = item
                zipf.writestr(str(arcname), data)

    print(f"Zipped {len(file_list)} files → {zip_path}")


def unzip_assets(zip_path: Path, extract_to: Path) -> None:
    """
    unzips the given zip file to the specified directory
    """

    zip_path = Path(zip_path).resolve()
    extract_to = Path(extract_to).resolve()

    with zipfile.ZipFile(zip_path, "r") as zipf:
        zipf.extractall(extract_to)

    print(f"Unzipped to {extract_to}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Fast zip/unzip script with threading."
    )

    parser.add_argument("mode", choices=["zip", "unzip"])
    parser.add_argument("source")
    parser.add_argument("destination")
    args = parser.parse_args()

    if args.mode == "zip":
        zip_assets_threaded(args.source, args.destination)
    elif args.mode == "unzip":
        unzip_assets(args.source, args.destination)
