#!/usr/bin/env bash
set -euo pipefail

# Número de processos (MPI) e tamanho de entrada (por exemplo, número máximo a testar)
NP=${1:-4}
SIZE=${2:-1000}
OUTFILE="results_np${NP}_size${SIZE}.csv"

# Header do CSV
echo "executable,category,np,size,time_sec" > "$OUTFILE"

# Função que executa um binário e registra o tempo real (em segundos)
bench_one() {
  local exe="$1"
  local cat="$2"
  # -f "%e" → tempo real em segundos
  # stderr capturado por time, stdout suprimido
  t=$(/usr/bin/time -f "%e" mpirun -np "$NP" "$exe" "$SIZE" 2>&1 >/dev/null)
  echo "$(basename "$exe"),$cat,$NP,$SIZE,$t" >> "$OUTFILE"
}

# Itera sobre executáveis em cada pasta
for dir in primosNaive primosBag; do
  [[ -d $dir ]] || { echo "⚠️  Diretório '$dir' não existe, pulando."; continue; }
  for exe in "$dir"/*; do
    [[ -x $exe ]] || continue
    echo "🔨 Running $exe (category: $dir) with $NP procs, input size $SIZE..."
    bench_one "$exe" "$dir"
  done
done

echo "✔ Resultados gravados em $OUTFILE"
