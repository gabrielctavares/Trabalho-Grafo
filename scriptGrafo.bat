@echo off

setlocal enabledelayedexpansion

for %%F in (.\Arquivos_entrada\*) do (
  set "nomeArquivo=%%~nxF"
  echo Arquivo: !nomeArquivo!

  for /L %%N in (1,1,10) do (
    echo Repeticao: %%N
    set "variavelSaida=saida_%%N_!nomeArquivo!"
    .\execGrupoX .\Arquivos_entrada\!nomeArquivo! !variavelSaida! 0 0 1
  )  
)

pause
endlocal

