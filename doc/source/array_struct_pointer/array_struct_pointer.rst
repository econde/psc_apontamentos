*Arrays*, *structs* e ponteiros
*******************************

Array
=====

*Arrays* são sequências de valores do mesmo tipo, dispostas em posições contiguas da memória.

Sintaxe de definição de *array* unidimensional: ::

	type identifier [constant-expression];

**Exemplos**

*Array* com cinco elementos do tipo ``int``. ::

   int x[5];

Equivalente em Java: ``int[5] x;``
Equivalente em Kotlin: ``var x: IntArray(5)``

**Exemplo**

*Array* com cinco elementos do tipo ``int`` inicializado com os valores indicados. ::

   int x[] = { 10, 20, 30, 40, 50 };

Equivalente em Java: ``int[] x = { 10, 20, 30, 40, 50 };``
Equivalente em Kotlin: ``var x: IntArray = intArrayOf(10, 20, 30, 40, 50)``

O acesso aos elementos do *array* realiza-se através do operador indexação.
Os índices vão de 0 -- primeira posição -- à dimensão menos um -- última posição.

Em linguagem C não é válido escrever uma expressão de afetação de um *array*
com a totalidade do conteúdo de outro *array*.
Pode-se contudo, realizar a afetação posição a posição.

**Exemplo** ::

   int a[3];
   int b[] = {10, 20, 30}:

::

  a = b;

é inválido em linguagem C.

::

   a[0] = b[0];
   a[1] = b[1];
   a[2] = b[2];

é válido, embora não seja a solução adequada para copiar um *array* extenso.


Ponteiro
========

Os tipos básicos são representados em memória por grupos de células (*bytes*).
Um ponteiro é um grupo de células capaz de guardar um endereço da própria memória.
Na arquitetura **X86-64** um ponteiro tem a dimensão de 8 *bytes*. ::

   char c;
   char *p = &c;

O operador **&** aplica-se a uma variável e serve para obter o ponteiro para essa variável.
Ao nível da arquitetura do computador é o endereço de memória dessa variável. ::

   *p = 20;

O operador **\*** aplica-se a um ponteiro e dá acesso ao conteúdo da variável apontada (conteúdo de).
Também se designa por operador desreferenciação.

Sendo **q** um ponteiro para inteiro (``int *``), **\*q** representa o valor inteiro apontado por **q**
e pode aparecer na escrita de programas em qualquer lugar onde possa aparecer um valor inteiro.

Mnemónica: **&** -- \"ponteiro para\" **\*** -- \"conteúdo de\"

**Exemplo**

O programa da :numref:`print_pointer` escreve no terminal o endereço da variável ``var`` assim como o seu conteúdo,
fazendo uso de ponteiro.

.. literalinclude:: ../../../code/array_struct_pointer/pointer/print_pointer.c
   :language: c
   :linenos:
   :lines: 3-9
   :caption: Visualizar o valor de um ponteiro e do valor apontado
   :name: print_pointer


Ponteiro como argumento de função
=================================

A linguagem C só tem passagem de parâmetros por valor.
A utilização de ponteiro como tipo de parâmetro formal,
permite passar como argumento de função o ponteiro para uma variável (endereço).
Através desse ponteiro pode-se aceder ao conteúdo dessa variável,
simulando-se assim uma passagem de parâmetro por referência.

**Exemplo**

A função ``swap`` no programa da :numref:`swap_values` troca o conteúdo das variáveis ``a`` e ``b``
por via da utilização dos ponteiros para essas variáveis.

.. code-block:: c
   :caption: Trocar o valor entre duas variáveis através de ponteiros
   :name: swap_values

   void swap(int *pa, int *pb) {
   	int aux = *pa;
   	*pa = *pb;
   	*pb = aux;
   }

   int a = 22, b = 33;
   int main() {
   	swap(&a, &b);
   }

Ponteiros e arrays
==================
::

   int a[10], *p;

O identificador ``a`` isolado é equivalente ao ponteiro para a primeira posição do *array* -- ``&a[0]``.
Sendo ``p`` um ponteiro para ``int``, afetar ``p = a`` é equivalente a afetar ``p = &a[0]``.

``a`` não é uma variável, é um valor constante do tipo ponteiro cujo valor é o endereço da primeira posição do *array* ``int a[10]``.
Não é possível alterar o valor de ``a``. Por exemplo, ``a++`` ou ``a = p``.

As operações sobre *arrays* com operador indexação podem ser substituidas pela notação de ponteiros.

+---------------------+----------------------------------------+-----------------------------------+
|                     | acesso a conteúdo                      | ponteiros para posições do array  |
+---------------------+----------+--------------+--------------+-----------+------------+----------+
|operador indexação   | ``a[0]`` | ``a[1]``     | ``a[i]``     | ``&a[0]`` | ``&a[1]``  |``&a[i]`` |
+---------------------+----------+--------------+--------------+-----------+------------+----------+
|notação de ponteiro  | ``*a``   | ``*(a + 1)`` | ``*(a + i)`` | ``a``     | ``a + 1``  |``a + i`` |
+---------------------+----------+--------------+--------------+-----------+------------+----------+

**Exemplo**

Ordenar um array de inteiros.

.. code-block:: c
   :caption: Acesso aos elementos do array por indexação
   :name: array_index

   void sort(int array[], size_t size) {
   	for (size_t i = 0; i < size - 1; ++i)
   		for (size_t j = 0; j < size - i - 1; ++j)
   			if (array[j] > array[j + 1])
   				swap(&array[j], &array[j + 1]);
   }

Na :numref:`array_pointer` apresenta-se uma programação alternativa usando notação de ponteiro.
Estas duas formas de expressar o programa produzem resultados iguais.
As respetivas codificações em linguagem máquina dependem do compilador.
Podendo, nalgumas arquiteturas, uma ter tradução mais eficiente que a outra.

.. code-block:: c
   :caption: Acesso aos elementos do array por ponteiro
   :name: array_pointer

   void sort(int *array, size_t size) {
   	for (size_t i = 0; i < size - 1; ++i)
   		for (int *p = array; p < array + size - i - 1; ++p) {
   			if (*p > *(p + 1))
   				swap(p, p + 1);
   		}
   }

Ponteiro para caracteres
========================

``char message[] = “texto para teste”;`` define ``message`` como um *array* de elementos do tipo ``char``
(vulgarmente designado por *array* de carateres) inicializado com a *string* ``"texto para teste"``.

``char *pmessage = “texto para teste”;`` define ``pmessage`` como um ponteiro para caractere,
ao qual foi atribuido o ponteiro para o primeiro caractere da *string* ``"texto para teste"``.

Como o identificador de um *array* é equivalente ao ponteiro para a primeira posição do *array,
por coerência, um ponteiro pode ser encarado como endereço base de um **array**.

``pmessage[0]`` representa o mesmo caractere **\'t\'** que ``message[0]``.

*String*
========

Na linguagem C, **string** é uma sequência de caracteres terminada com o caractere cujo código é 0 (zero).
Uma *string* é guardada em memória numa variável do tipo *array* de caracteres
cujo conteúdo são os códigos numéricos dos caracteres que compõem a *string*
finalizados pelo código ``'\0'``.

A biblioteca normalizada da linguagem C define funções para manipulação de *strings*.

Array como argumento de função
==============================

Quando se passa um *array* como argumento de função,
efetivamente está-se a passar o ponteiro para a primeira posição do *array*.
Internamente à função, o parâmetro é como uma variável local do tipo ponteiro
para o tipo de elementos do *array*.

A declaração ``void to_upper(char str[])`` é equivalente a ``void to_upper(char *str)``.

Na invocação, o argumento pode ser um identificador de *array*
-- ``to_upper(array)`` sendo ``char array[10]`` --
ou uma variável do tipo ponteiro -- ``to_upper(ptr)`` sendo ``char *ptr``.


Aritmética de ponteiros
=======================

Princípio básico: se ``p`` é um ponteiro para um elemento de um *array*
então ``p + 1`` é o ponteiro para o elemento seguinte.

Considerando ``p`` um ponteiro para ``char``, se o tipo ``char`` ocupar um *byte* em memória,
``p + 1`` incrementa o endereço de uma unidade.

Considerando ``p`` um ponteiro para ``float``, se o tipo ``float`` ocupar quatro *bytes* em memória,
``p + 1`` incrementa o endereço de quatro unidades.

========= ======================================================================================
``p++``   pós-incrementa ``p`` do número de bytes igual à dimensão de um elemento.
``++*p``  pré-incrementa o valor apontado por ``p``.
``*++p``  pré-incrementa o ponteiro e depois desreferencía-o acedendo ao valor apontado.
``*p++``  desreferencía o ponteiro acedendo ao elemento apontado e depois incrementa o ponteiro.
``p + n`` aponta para o elemento ``n`` posições à frente do elemento apontado por ``p``.
``p - q`` representa o número de elementos entre os ponteiros ``p`` e ``q``.
========= ======================================================================================

As operações possíveis sobre ponteiros são a adição ou subtração de valores inteiros
ou a subtração de ponteiros.

Não é possível realizar outras operações sobre ponteiros.
Por exemplo, não é possível somar dois ponteiros ou multiplicar por inteiro.


Ponteiro para *void*
====================

Um ponteiro para ``void`` não pode ser desreferenciado, adicionado ou subtraído,
porque o elemento apontado é indefinido.
Por omissão, o compilador **gcc** trata o ponteiro para ``void``
como um ponteiro para ``char`` para efeito de aritmética de ponteiros (não está segundo a norma).
Uma variável do tipo ponteiro para ``void`` pode receber ponteiros de qualquer tipo.
Assim como afetar ponteiros de qualquer tipo.

Array bidimensional
===================

.. table::
   :widths: 20 20

   +-------------------------------------------+-----------------------------+
   | ``char a[6] = “abcd”;``                   | .. image:: array_char.svg   |
   +-------------------------------------------+-----------------------------+
   | ``char a[][5] = {“luis”, “rui”, “ana”};`` | .. image:: array_char_2.svg |
   +-------------------------------------------+-----------------------------+


**Visualização na memória**

   .. image:: array_char_3.svg

**Exemplo**

Ordenar uma sequência de nomes de pessoas, representados num *array* bidimensional de caracteres.

.. literalinclude:: ../../../code/array_struct_pointer/sort_names/sort_names_array_bi.c
   :language: c
   :linenos:
   :caption: Ordenação de nomes em *array* bidimensional

Array de ponteiros
==================

.. table::
   :widths: 20 20

   +-------------------------------------------+-----------------------------+
   | ``char *a[] = {“luis”, “rui”, “ana”};``   | .. image:: array_char_4.svg |
   +-------------------------------------------+-----------------------------+

**Visualização na memória**

   .. image:: array_char_5.svg



**Exemplo**

Ordenar uma sequência de nomes de pessoas, representada num *array* de ponteiros para *strings*.

.. literalinclude:: ../../../code/array_struct_pointer/sort_names/sort_names_array_ptr.c
   :language: c
   :linenos:
   :caption: Ordenação de nomes em *array* bidimensional

Argumentos na linha de comando
==============================

As palavras escritas na linha de comando são enviadas como argumentos para o programa.
São passadas como argumentos da função ``main``,
na forma de um *array* de ponteiros para caracteres,
apontando cada posição, para o início de cada palavra. ::

   int main(int argc, char *argv[]);

Por exemplo, na invocação do comando: ::

   $ gcc myprog.c -o myprog

o programa gcc vai receber os seguintes argumentos:

   .. image:: array_char_6.svg

**Exercícios**

   1. Fazer um programa que imprima os argumentos de um programa no terminal.
   2. Fazer uma função para separar as palavras numa linha de texto.
      ``size_t string_split(char *text_line, char *words[], size_t words_size);``
   3. Fazer um programa para listar as últimas **n** linhas do texto de entrada.
      ``$ tail -n``

Opções na linha de comando
--------------------------

As opções na linha de comando são de dois tipos curtas e longas.
As curtas são definidas por um sinal **\'-\'** seguido de uma letra
e as longas são definidas por dois sinais **\'- -\'** seguidos de uma palavra.
Há opções com e sem argumento.

A biblioteca POSIX define a função ``getopt`` e um conjunto de variáveis
para auxiliar na programação com opções curtas

::

   #include <unistd.h>

   int getopt(int argc, char *const argv[], const char *optstring);
   extern char *optarg;
   extern int opterr, optind, optopt;

A função ``getopt``recebe os argumentos passados ao programa -- ``argc`` e ``argv``
-- e a *string* ``optstring`` com a definição das opções.
A função é invocada sucessivamente e em cada invocação devolve uma opção.

========== =============================================
``optarg`` ponteiro para o argumento da opção
``optind`` índice da opção corrente no *array* ``argv``
``opterr`` indicação da ocorrência de erro
``optopt`` opção onde ocorreu erro
========== =============================================

**Exemplo**

Considere-se um programa apto a receber quatro opções,
``-a`` e ``-b`` com argumento e ``-c`` e ``-e`` sem argumento.

Invocações possíveis: ::

   $ program -a aaa -c ccc -d -e argument1 argument2

   $ program argument1 argument2

   $ program -d argument1 -c argument2 -a aaa

Nos exemplos de invocação ``argument1`` e ``argument2`` são argumentos do programa
e ``aaa`` e ``ccc`` são argumentos das opções.


.. literalinclude:: ../../../code/application/getopt.c
   :language: c
   :linenos:
   :caption: Exemplo de utilização da função ``getopt``.

As opções e argumentos do programa podem ser intercalados por qualquer ordem.
A função ``getopt`` reposiciona o conteúdo de ``argv`` de modo que
em primeiro lugar ficam as opções e respetivos argumentos
e em segundo lugar os argumentos do programa que não são opções.

Variáveis de ambiente
=====================

Variáveis de ambiente são pares chave-valor disponíveis nos ambientes de execução de um programa.

Tanto a chave como o valor são *strings* C.

Podem ser definidas e consultadas através de comandos de linha e programaticamente.

Definir uma variável de ambiente na linha de comando: ::

   $ export MY_DIR=/home/ezequiel/my_dir

Consultar variáveis de ambiente na linha de comando: ::

   $ env | grep MY_DIR
   MY_DIR=/home/ezequiel/my_dir

Consultar uma variável de ambiente num programa em C: ::

   #include <stdlib.h>
   #include <stdio.h>

   int main() {
   		const char *name = "MY_DIR";
   		const char *dir = getenv(name);
   		if (dir != NULL)
   			printf("A variável %s é equivalente a %s\n", name, dir);
   	}

Uma variável de ambiente criada num dado processo é propagada para os processos
descendentes, não afeta o sistema na globalidade.


*Struct*
========

O tipo **struct** agrega variáveis de tipos diferentes.

Declaração do tipo: ::

   struct person {
   	char name[100];
   	int age;
   	int weight;
   	float height;
   };

Definição de variável do tipo *struct*: ::

   struct person user;

Para simplificar a escrita pode-se usar: ::

   typedef struct person Person;

e escrever ``Person`` em vez de ``struct person``: ::

   Person user;

Acesso a membro da **struct** (<nome da struct>.<membro>): ::

	user.age;

As *struct* podem ser copiadas com o operador afetação: ::

   struct person a, b;

   a = b;

A passagem de *struct* como argumento de função é feita por valor. ::

   int bmi(struct person p) {
   	return p.weight / (p.height * p.height);
   }

Uma *struct* pode ser retornada como valor de uma função: ::

   struct person new_person(char n[], int a, int w, int h) {
   	struct person temp;
   	strcpy(temp.name, n);
   	temp.age = a;
   	temp.height = h;
   	temp.weight = w;
   	return temp;
   }

Inicialização na definição de variável do tipo *struct*: ::

   struct person user1 = {“António”, 53, 80, 1.76};
   struct person user2 = {
   	.name = “Joaquim”,
   	.height = 1.76
   }

Os campos não mencionados são inicializados com zero.

Ponteiro para *struct*
======================

Se for necessário passar uma *struct* como argumento de função,
deve-se considerar a passagem por ponteiro. ::

   int bmi(struct person *p) {
   	return (*p).weight / ((*p).height * (*p).height);
   }

A linguagem C dispões de um operador alternativo para acesso
ao membro de uma **struct** baseado em ponteiro: **->** ::

   return p->weight / (p->height * p->height);

Os operadores **.** e **->**, em conjunto com **()** e **[]**,
são os mais prioritários.

Exemplos de acesso a campos de *struct*: ::

   struct person *p;

================ =====================================================================================
``++p->age``     incrementa o membro ``age``.
``(p++)->age``   incrementa ``p`` depois de aceder a ``age``. Só faz sentido num *array* de pessoas.
``*p->name``     dá acesso ao primeiro caracter de ``name``.
``*p++->name``   incrementa ``p`` depois de aceder ao primeiro caractere de ``name``.
``(*p->name)++`` incrementa o código do primeiro caracter de ``name``.
================ =====================================================================================

**Exercícios**

   1. Fazer um programa para ordenar um *array* de ``struct person`` pela ordem alfabética dos nomes.
   2. Fazer um programa para ordenar um *array* de ponteiros para ``struct person`` pelas idades.

Alojamento de *struct* em memória
=================================

   * Os membros de uma **struct** são dispostos em memória
     seguindo as regras de alinhamento do tipo a que pertencem,
     mesmo que para isso seja necessário inutilizar posições de memória
     entre campos consecutivos.
   * O endereço de início da **struct** é alinhado no maior alinhamento necessário
     a um dos seus campos.
   * A dimensão de uma *struct* é múltipla do seu alinhamento.

Considere-se a seguinte definição da variável **x**: ::

   struct y {
   	char a;
   	int b;
   	short c;
   } x;

Num processador a 32 ou 64 bits, com compilador GNU,
para alinhar o campo ``b``, é necessário avançar três posições de memória.
A dimensão total desta **struct** é de 12 *bytes*.

.. figure:: struct_1.svg
   :align: center
   :scale: 120

A dimensão de uma *struct* depende da ordem e do tipo dos campos.
Considerando a definição alternativa da variável **x**: ::

   struct {
   	char a;
   	short c;
   	int b;
   } x;

.. figure:: struct_2.svg
   :align: center
   :scale: 120

Na arquitetura Intel é possível alojar variáveis desalinhadas.
Um acesso desalinhado consome duas operações de acesso à memória.
Um acesso alinhado consome apenas uma operação de acesso à memória.

Na arquitetura ARM, por definição, acessos desalinhados são interditos.
A implementação *hardware* não contempla essa operação.
Em algumas implementações, se isso acontecer, o processador interrompe o programa,
noutras o resultado é indefinido.

**Exercícios**

   1. Desenhar a ocupação de memória para um *array* de duas *struct* do tipo ``struct y``.
   2. Tentar desenhar a ocupação de memória para um *array* de duas *struct* do tipo ``struct y``,
      colocando o campo ``a`` da *struct* da primeira posição do *array*,
      num endereço ímpar e mantendo o critério de alinhamento para todos os campos.

*Array* de *struct*
===================

**Exemplo**

O programa da :numref:`word_count` determina as dez palavras mais frequêntes de um texto.
A operação engloba três etapas: leitura e contabilização das palavras,
seleção das mais frequentes e apresentação dos resultados.

A informação das palavras é registada em ``struct word`` com dois campos,
um *array* de caracteres para armazenar a palavra
e um campo do tipo inteiro para acumular a contagem (linhas 5 a 8).

A informação de todas as palavras é agrupada num *array* de ``struct word`` (linha 10).

As palavras são lidas de *standard input* pela função ``word_read``.

À medida que vão sendo lidas, as palavras são procuradas no *array* de ``struct word``.
Se a palavra já existir, o respetivo contador é incrementado.
Se não existir, é inserida no final do *array* (função ``word_insert``).

As palavras mais frequentes são determinadas depois de o *array* de ``struct word``
ser ordenado por ordem decrescente do valor do contador. As palavras mais frequentes
são as que ficam nas primeiras posições.

.. literalinclude:: ../../../code/array_struct_pointer/word_count/word_count.c
   :language: c
   :linenos:
   :lines: 13-47, 74-75, 79-80, 87, 91-92
   :caption: Programa que determina as dez palavras mais frequêntes num texto
   :name: word_count

*Array* de ponteiros para *struct*
==================================

**Exemplo**

No exemplo da secção anterior a lista de palavras é implementada num *array* de ``struct word``.
Para obter a ordenação é necessário movimentar estas *struct* ao longo do *array*.

Uma maneira alternativa e mais eficiente de obter a ordenação,
consiste em criar um *array* de ponteiros para as *struct*
e obter a ordenação movimentando apenas os ponteiros.

A eficiência resulta da menor quantidade de memória que é necessária movimentar durante a ordenação.
Esta eficiência é tão mais significativa quanto maior for a dimensão de memória da *struct* de dados,
relativamente à dimensão de memória ocupada por um ponteiro.

Além do *array* de ``struct word`` onde a informação é efetivamente guardada (linha 10),
existe um *array* de ponteiros para ``struct word``
onde são agrupados todos os ponteiros para as *struct* com informação (linha 11).

As diferenças da nova versão do programa (:numref:`word_count_ptr`) para a versão anterior (:numref:`word_count`) são: o
registo do ponteiro para a *struct* com a informação da nova palavra (linha 26);
a programação da função de ordenação (``sort``) que acede ao campo contador via ponteiro (linha 33)
e atua sobre o *array* de ponteiros para obter a ordenação (linhas 34 a 36).

.. literalinclude:: ../../../code/array_struct_pointer/word_count/word_count_ptr.c
   :language: c
   :linenos:
   :lines: 13-50, 77-78, 82-83, 89, 93-94
   :caption: Programa que determina as dez palavras mais frequêntes num texto
   :name: word_count_ptr

*Struct* com campos baseados em *bits*
======================================

Justificação:

   * casos em que se pretenda reduzir a memória ocupada;
   * permite acesso a *bits* de forma simplificada.

**Exemplo 1**

Representação de uma data de forma compactada. ::

   struct date {
   	short day: 5;
   	short month: 4;
   	short year: 7;
   };

   struct date date_pack(int year, int month, int day) {
   	struct date tmp = {year – 2000, month, day };
   	return tmp;
   }

``sizeof (struct date)`` é igual a dois, o mesmo que ``sizeof (short)``

**Exemplo 2**

Acesso a registo de periférico mapeado no espaço de memória: ::

   struct register_status {
   	char counter_enable:1;
   	char counter_reset: 1;
   };

   struct register_status *status = 0xe0008004;

   status->counter_enable = 1;

Como a unidade mínima de endereçamento no acesso à memória é o *byte*,
para afetar um número de *bits* inferior sem modificar os restantes
é necessário ler, alterar os *bits* em causa e voltar a escrever.
Resultando em dois acessos à memória, um de leitura e um de escrita.

Apesar da aparente vantagem em relação à utilização de operadores lógicos bit-a-bit,
nem sempre é conveniente a sua utilização:

   1. Se, no acesso a um registo de periférico, este for só de escrita a operação de leitura é inútil.
   2. Se o operação de leitura sobre um registo de periférico provocar a alteração de estado do periférico, ela é certamente indesejada.

*Union*
=======

Uma *union* é uma variável que pode armazenar, em tempos diferentes,
valores de diferentes tipo e tamanhos.

Através de uma *union* é possível encarar um dado conteúdo de memória
na perspectiva de diferentes tipos.

**Exemplo 1** ::

   struct symbol {
   	char *name;
   	int flags;
   	union {
   		int value_int;
   		float value_float;
   		char *value_string;
   	};
   };

Os campos ``value_int``, ``value_float`` e ``value_string`` ocupam as mesmas posições da memória.
Apenas um deles tem significado num dado momento.
O campo ``flags`` pode servir para identificar o significado atual.


**Exemplo 2**

Imprimir em binário a respresentação interna de um *float*.

::

   typedef union {
   	unsigned i;
   	struct {
   		unsigned mantissa: 23;
   		unsigned exponent: 8;
   		unsigned signal: 1;
   	};
   	float f;
   } Float;

   ...
   Float real = {.f = -45.1};

   printf("%b %08b %023b\n", real.signal, real.exponent, real.mantissa);
   ...

