#!/bin/env sh

set -e

git add -A
git commit -m ${1:-"update"}
git push
