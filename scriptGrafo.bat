@echo off

setlocal enabledelayedexpansion

for /L %%N in (1,1,5) do (

  for %%F in (.\Arquivos_entrada\*) do (
    set "nomeArquivo=%%~nxF"
    echo Arquivo: !nomeArquivo!

    echo Repeticao: %%N
    set "variavelSaida=saida_%%N_!nomeArquivo!"
    .\execGrupoX .\Arquivos_entrada\!nomeArquivo! !variavelSaida! 0 0 1
  )  
)

pause
endlocal

