#!/bin/bash

for file in ./Arquivos_entrada/*; do
  nomeArquivo=$(basename "$file")
  echo "Arquivo: $nomeArquivo"

  for ((i=1; i<=10; i++)); do
    echo "Repeticao: $i"
    variavelSaida="saida_${i}_${nomeArquivo}"
    ./execGrupoX ./Arquivos_entrada/"$nomeArquivo" "$variavelSaida" 0 0 1
  done
done
