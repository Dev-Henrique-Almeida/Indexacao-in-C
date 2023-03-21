# Aed-II - Projeto 1 VA
Indexação em C

Implemente um pequeno "Banco de dados" para gerenciar apenas uma tabela, na linguagem C, utilizando a técnica de indexação, de acordo com as definicioes a seguir:

- a) A tabela deve armazenar registros que contem ao menos 5 campos. A definicao do registro/campos a serem gerenciados é de live escolha, desde que seja algo adequado ao ambiente academico.
- b) Pelo menos um dos campos deve ser de string com alocacao dinamica.
- c) Utilize tres indices na tabela, um indice BST, um AVL, e um RB.
- d) Os daods dos registros devem ser armazenados em um arquivo sequencial. Deve ser utilizada umas das tecnicas de separacao de registro estudadas (caractere separador, xml, json, etc).
- e) Cada indice deve ser salvo em um arquivo proprio.
- f) Implemente a funcao de adicionar registro, que insere o registro no arquivo de dados e atualiza os tres indices.
- g) Impremente a funcao de remover registro, que remove apenas as referencias ao registro nos indices, sem a necessidade de modificar o arquivo de dados.
- h) Implemente uma funcao de busca para cada indice. Essa funcao deve imprimir em tela todos os satelite do registro referenciado pelo indice passado como parametro.
- i) Implemente uma funcao para exibir os registros ordenados de acordo com um dos indices a sua escolha(inOrder)
- j) Implemente a funcao main que permite ao usuario utilizar o sistema com todas as opcoes de funcoes implementadas.
