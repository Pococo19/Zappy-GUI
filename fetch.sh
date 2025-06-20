#!/usr/bin/env bash

GREEN="\033[1;32m"
RED="\033[1;31m"
ILC="\033[3m"
ORG="\033[1;33m"
RST="\033[0m"

function _info()
{
    echo -e "${ORG}[💡] INFO:\t${RST} ${ILC}$1${RST}"
}

function _success()
{
    echo -e "${GREEN}[✅] SUCCESS:\t${RST} ${ILC}$1${RST}"
}

_info "fetching latest changes from the master branch..."
git pull origin master
_success "fetched latest changes from the master branch!"
_info "updating submodules..."
git submodule update --init --recursive
_success "updated submodules!"
_info "fetching latest changes in submodules..."
git submodule foreach '
  echo "Updating $name..."
  git fetch origin master
  git checkout master
  git pull origin master
'
_success "fetched latest changes in submodules!"
_info "all done! you can now commit and push your changes."
