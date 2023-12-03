# Compilador de C-

```
bison -d parse.y
make
```

- Pedro Henrique de Almeida
- Piero Andreeto Liduvino

### Common

Contém estruras de dados usadas em vários diferentes módulos:

- LinkedList
- TokenNode

### Debug

Contém arquivos utilizados para teste do compilador. Como diferentes inputs, testes, backups e implementações.

### Lexical Analyzer

Contém todos os arquivos necessários para a análise léxica:

- CharTypeChecker: análise dos carácteres de um buffer.
- GenericTypes: estruturas de dados utilizadas para ler da entrada e salvar os lexemas.
- GetToken: retorna tokens sobre demanda.
- Hash: hash usado para classificação das keywords.
- InputReader: lê caractér por caractér de um buffer.
- Lexem: procedimentos para o uso do buffer de lexema.
- Table: tabela de um DFA.
- Token: procedimentos para classificação dos lexemas em tokens.

### Parser

Contém os arquivos utilizados pelo Bison na análise sintática e na geração da árvore sintática.

- Stack: estrutura de stack utilizada na árvore
- SyntaxTree: estrutura da árvore.

### Semantic Analyzer

Contém os arquivos utilizados na construção da tabela de símbolos e na análise semântica.

- SymbolTable: Estrutura da tabela de símbolos.
