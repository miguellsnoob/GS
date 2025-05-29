
# Sistema de Cadastro de Relatos de Catástrofes Naturais

Este sistema permite o cadastro, listagem e consulta de relatos sobre catástrofes naturais (como enchentes e tornados), ocorridas em um raio de até 10 km da localização do usuário.

## Funcionalidades:
- Cadastro de relatos com nome, email, tipo de catástrofe, data, localização e descrição
- Consulta por raio geográfico (10 km)
- Listagem de todos os relatos
- Armazenamento dos relatos em arquivo .txt

## Como compilar:
gcc main.c -o sistema

## Como executar:
./sistema

## Arquivo de dados:
Os relatos são salvos automaticamente no arquivo `relatos.txt`.
