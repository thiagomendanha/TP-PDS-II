# Sistema de Votação

Este software é um sistema de votação desenvolvido em C++. Ele permite que os administradores gerenciem eleitores e candidatos, definam eleições e verifiquem os resultados. Os eleitores podem escolher entre as eleições disponíveis e votar em candidatos. Ele foi feito para funcionar em linux e Windoes

## Estrutura do Código

O código é dividido em várias classes, cada uma representando uma entidade específica no sistema de votação. Aqui está uma breve descrição de cada classe e seus métodos:

### Admin

Representa um administrador do sistema.

- `comparePass()`: Compara a senha fornecida com a senha do administrador.

### Candidate

Representa um candidato na eleição.

- `getId()`: Retorna o ID do candidato.
- `getName()`: Retorna o nome do candidato.
- `getParty()`: Retorna o partido do candidato.
- `getElection()`: Retorna a eleição em que o candidato está concorrendo.
- `getNumber()`: Retorna o número do candidato.
- `print()`: Imprime informações sobre o candidato.

### Election

Representa uma eleição.

- `getName()`: Retorna o nome da eleição.
- `getStartDate()`: Retorna a data de início da eleição.
- `getEndDate()`: Retorna a data de término da eleição.
- `setVotingPeriod()`: Define o período de votação.
- `isVotingOpen()`: Verifica se a votação está aberta.
- `print()`: Imprime informações sobre a eleição.
- `voteForCandidate()`: Registra um voto para um candidato.
- `hasVoted()`: Verifica se um eleitor já votou.
- `printResults()`: Imprime os resultados da eleição.

### Elector:

Representa um eleitor.

- `getId()`: Retorna o ID do eleitor.
- `comparePass()`: Compara a senha fornecida com a senha do eleitor.

### User:

Representa um usuário do sistema.

- `getLogin()`: Retorna o nome de login do usuário.
- `setLogin()`: Define o nome de login do usuário.
- `setPass()`: Define a senha do usuário.

### VotingSystem

Representa o sistema de votação.

- Métodos diversos para gerenciar administradores, eleitores, candidatos, eleições e interações de usuário.

## Como Usar

1. Compile o código C++.
2. Execute o programa.
3. Caso tenha o data.txt com informações salvas na mesma pasta do build, ele ira consumir esses dados, caso não, irá confirar seu primeiro acesso
4. Siga as instruções no menu principal para autenticar como administrador ou eleitor.
   - Como administrador, você pode:
     - Gerenciar eleitores: você pode adicionar, remover e listar todos os eleitores.
     - Gerenciar candidatos: você pode adicionar, remover e listar todos os candidatos.
     - Definir eleições: você pode adicionar e remover eleições, bem como listar todas as eleições.
     - Verificar os resultados: você pode verificar os resultados de uma eleição.
   - Como eleitor, você pode:
     - Escolher uma eleição: você pode escolher entre as eleições disponíveis para votar.
     - Votar: depois de escolher uma eleição, você pode votar em um candidato.

## Dependências

Este software requer um compilador C++ compatível com C++11 ou superior.

## Considerações

Os testes unitários foram feitos e rodaram com sucesso individualmente, mas não fui capaz de fazer o Makefile compilar junto o coverage com o build, dava todo tipo de erro, multiplos Main foi o principal, ele lia o main dentro da pasta de obj e de scr alé, de outros quando não era esse erro, mas os métodos públicos de todas as classes foram feitos testes e estão todos dentro de ./test

## Contribuições

O grupo é composto por:

Átila Santos Albuquerque
Thiago Mendanha Bahia Moura
Wara Amaral Silva Aranda

Os demais integrantes do grupo não se manifestaram no momento de fazer o trabalho e, portanto, não contribuíram com nada.