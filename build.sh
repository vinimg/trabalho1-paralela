#!/usr/bin/env bash
set -euo pipefail

# MPI compiler e flags
CC=mpicc
CFLAGS="-Wall -O2"
LDFLAGS="-lm"  # math library

usage() {
  echo "Uso: $0 [build|clean]"
  exit 1
}

if [[ "${1:-build}" == "clean" ]]; then
  echo "🧹 Removendo binários..."
  for dir in primosBag primosNaive; do
    for src in "$dir"/*.c; do
      exe="${src%.c}"
      [ -f "$exe" ] && rm -f "$exe" && echo "  removido $exe"
    done
  done
  echo "✔ Clean concluído."
  exit 0
elif [[ "$1" != "build" ]]; then
  usage
fi

# Função de compilação por diretório
compile_dir() {
  local dir="$1"
  if [[ ! -d "$dir" ]]; then
    echo "⚠️  Diretório '$dir' não encontrado, pulando."
    return
  fi

  shopt -s nullglob
  local srcs=("$dir"/*.c)
  shopt -u nullglob

  if [[ ${#srcs[@]} -eq 0 ]]; then
    echo "⚠️  Sem .c em '$dir', pulando."
    return
  fi

  for src in "${srcs[@]}"; do
    exe="${src%.c}"
    echo "🔨 Compilando $src → $exe"
    $CC $CFLAGS -o "$exe" "$src" $LDFLAGS
  done
}

# Build
compile_dir "primosBag"
compile_dir "primosNaive"

echo "✔ Build concluído com sucesso."
