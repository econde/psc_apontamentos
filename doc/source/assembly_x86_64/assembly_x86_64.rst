Programação em *assembly* x86-64
********************************

.. Inserir aqui uma secção com os aspetos arquiturais importantes.
   Copiar algumas coisas dos slides

.. Tratar da questão do alinhamento. Tirar do capítulo dos valores e pôr aqui.

.. Também se deve inserir uma secção sobre a linguagem assembly

Suporte à linguagem C
=====================

Valores
-------
A arquitetura x86-64 realiza operações com palavras de 8, 16, 32 ou 64 *bits*.
Os registos tem nomes próprios que definem as diferentes porções. Por exemplo,
AL, AX, EAX e RAX.

Para valores operados em memória as instruções aceitam um indicador, em sufixo, que define a dimensão da palavra.

===== ============= ==========
**b** *byte*        8 *bits*
**w** *word*        16 *bits*
**l** *double word* 32 *bits*
**q** *quad word*   64 *bits*
===== ============= ==========

Existem instruções que estendem a representação
num número inferior de *bits* para um número superior de *bits*.

+-----------------------+-------------------------------+-----------------------------------------------------------------+
| movs\-\- *src*, *dst* | extensão com o *bit* de sinal | os tracinhos são substituídos pelos indicadores acima           |
+-----------------------+-------------------------------+                                                                 |
| movz\-\- *src*, *dst* | extensão com o valor zero     | o primeiro indica a dimensão da origem e o segundo a do destino |
+-----------------------+-------------------------------+-----------------------------------------------------------------+

Expressões
----------

Alguns exemplos de calculo de expressões numéricas.

Considerando **a** um valor expresso a 64 *bit*, previamente carregado em RAX.

+-----------------------+----------------------------+---------------------------------------+
| Deslocar p posições   |  .. code-block:: c         |  .. code-block:: asm                  |
| para a esquerda       |                            |                                       |
|                       |     a << p;                |     mov     p(%rip), %cl              |
|                       |                            |     shl     %cl, %rax                 |
+-----------------------+----------------------------+---------------------------------------+
| Afetar o bit da       | .. code-block:: c          | .. code-block:: asm                   |
| posição *p* com zero  |                            |                                       |
|                       |     a & ~(1 << p);         |     mov     p(%rip), %cl              |
|                       |                            |     mov     $1, %rdx                  |
|                       |                            |     shl     %cl, %rdx                 |
|                       |                            |     not     %rdx                      |
|                       |                            |     and     %rdx, %rax                |
+-----------------------+----------------------------+---------------------------------------+
| Afetar o bit da       |  .. code-block:: c         |  .. code-block:: asm                  |
| posição *p* com um    |                            |                                       |
|                       |     a | 1 << p;            |     mov     p(%rip), %cl              |
|                       |                            |     mov     $1, %rdx                  |
|                       |                            |     shl     %cl, %rdx                 |
|                       |                            |     or      %rdx, %rax                |
+-----------------------+----------------------------+---------------------------------------+
| Testar o valor do     |  .. code-block:: c         |  .. code-block:: asm                  |
| bit da posição p      |                            |                                       |
|                       |     if (a & (1 << p))      |     mov     p(%rip), %cl %cl          |
|                       |                            |     mov     $1, %rdx                  |
|                       |                            |     shl     %cl, %rdx                 |
|                       |                            |     test    %rdx, %rax                |
|                       |                            |     jz      label                     |
+-----------------------+----------------------------+---------------------------------------+
| Obter o campo de      |  .. code-block:: c         |  .. code-block:: asm                  |
| n bits a começar      |                            |                                       |
| na posição p.         |     (a >> p) & ~(~0 << n); |     mov     $~0, %rdx                 |
|                       |                            |     mov     n(%rip), %cl              |
|                       |                            |     shl     %cl, %rdx                 |
|                       |                            |     not     %rdx                      |
|                       |                            |     mov     p(%rip), %cl              |
|                       |                            |     shr     %cl, %rax                 |
|                       |                            |     and     %rdx, %rax                |
+-----------------------+----------------------------+---------------------------------------+
| Multiplicação por     |     .. code-block:: c      |  .. code-block:: asm                  |
| constante             |                            |                                       |
|                       |         a * 13;            |     # rax * 13  = (rax * 3) * 4 + rax |
|                       |                            |                                       |
|                       |                            |     lea   (%rax, %rax, 2), %rdx       |
|                       |                            |     lea   (%rax, %rdx, 4), %eax       |
+-----------------------+----------------------------+---------------------------------------+


Considerando **a** um valor expresso a 128 bit previamente carregado em RDX:RAX.

+-----------------------+----------------------------+---------------------------------------+
| Deslocar 1 posição    |      .. code-block:: c     |  .. code-block:: asm                  |
| para a esquerda       |                            |                                       |
|                       |         a <<= 1;           |     shl    $1, %rax                   |
|                       |                            |     rcl    $1, %rdx                   |
+-----------------------+----------------------------+---------------------------------------+
| Deslocar 1 posição    |      .. code-block:: c     |  .. code-block:: asm                  |
| para a direita        |                            |                                       |
|                       |         a >>= 1;           |     shr    $1, %rdx                   |
|                       |                            |     rcr    $1, %rax                   |
+-----------------------+----------------------------+---------------------------------------+
| Deslocar **p**        |     .. code-block:: c      |  .. code-block:: asm                  |
| posições              |                            |                                       |
| para a esquerda       |        a <<= p;            |     mov     p(%rip), %cl              |
|                       |                            |     shld    %cl, %rax, %rdx           |
|                       |                            |     shl     $cl, %rax                 |
+-----------------------+----------------------------+---------------------------------------+
| Deslocar **N**        |     .. code-block:: c      |  .. code-block:: asm                  |
| posições              |                            |                                       |
| para a direita        |        a >>= N;            |     shrd    $N, %rdx, %rax            |
|                       |                            |     shr     $N, %rdx                  |
+-----------------------+----------------------------+---------------------------------------+


Controlo da execução
--------------------

*if*
....

*if* sem *else*

+----------------------------------------------------------------+----------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/if.c | .. literalinclude:: ../../../code/assembly_x86_64/control/if.s |
|   :language: c                                                 |    :language: asm                                              |
|                                                                |                                                                |
| \(a\)                                                          | \(b\)                                                          |
+----------------------------------------------------------------+----------------------------------------------------------------+

*if* com *else*

+---------------------------------------------------------------------+---------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/if_else.c | .. literalinclude:: ../../../code/assembly_x86_64/control/if_else.s |
|   :language: c                                                      |    :language: asm                                                   |
|                                                                     |                                                                     |
| \(a\)                                                               | \(b\)                                                               |
+---------------------------------------------------------------------+---------------------------------------------------------------------+

switch
......

+---------------------------------------------------------------------+---------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/switch.c  | .. literalinclude:: ../../../code/assembly_x86_64/control/switch.s  |
|   :language: c                                                      |    :language: asm                                                   |
|                                                                     |                                                                     |
| \(a\)                                                               | \(b\)                                                               |
+---------------------------------------------------------------------+---------------------------------------------------------------------+

do while
........

+----------------------------------------------------------------------+----------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/do_while.c | .. literalinclude:: ../../../code/assembly_x86_64/control/do_while.s |
|    :language: c                                                      |    :language: asm                                                    |
|                                                                      |                                                                      |
| \(a\)                                                                | \(b\)                                                                |
+----------------------------------------------------------------------+----------------------------------------------------------------------+

while
.....

+----------------------------------------------------------------------+----------------------------------------------------------------------+----------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/while.c    | .. literalinclude:: ../../../code/assembly_x86_64/control/while1.s   | .. literalinclude:: ../../../code/assembly_x86_64/control/while2.s   |
|    :language: c                                                      |    :language: asm                                                    |    :language: asm                                                    |
|                                                         seguinte, representa o endereço da variável ``a``.
É codificado como a diferença entre o endereço da instrução e a *label* ``a``
e é calculado adicionando este valor ao RIP.
A utilização que se faz do endereço da variável depende da semântica da instrução.
No caso de ``movb    $0, a(%rip)`` é realizada a escrita do valor 0 na posição de memória com esse endereço.

No caso de ``incq    i(%rip)`` é realizada uma leitura e uma escrita do valor depois de incrementado.
Um valor do tipo ``int`` é representado em memória p             |                                                                      |                                                                      |
| \(a\)                                                                | \(b\)                                                                | \(c\)                                                                |
+----------------------------------------------------------------------+----------------------------------------------------------------------+----------------------------------------------------------------------+



for
...

+----------------------------------------------------------------------+----------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/control/for.c      | .. literalinclude:: ../../../code/assembly_x86_64/control/for.s      |
|    :language: c                                                      |    :language: asm                                                    |
|                                                                      |                                                                      |
| \(a\)                                                                | \(b\)                                                                |
+----------------------------------------------------------------------+----------------------------------------------------------------------+

Funções
-------

A chamada a função é realizada com a instrução **call**
e o retorno é realizado com a instrução **ret**.

A instrução **call** empilha o endereço da próxima instrução no topo do *stack*.
Nessa altura RIP já contém o endereço da instrução seguinte, designado por endereço de retorno.
Depois executa um salto para o endereço de início da função chamada (*callee*).

A instrução **call <endereço>** é equivalente à sequência **push rip; jmp <endereço**.
Exemplos:

   * ``call label``	salto relativo; a distância até à *label* é embutida no código da instrução.
   * ``call *%rax``	salto absoluto; o registo RAX contém o endereço da função
   * ``call *(%rax)``	salto absoluto; o registo RAX contém o endereço da posição de memória ende se encontra o endereço da função


Para retornar à função chamadora (*caller*), a função chamada executa,
em último lugar, a instrução **ret**.
Esta instrução desempilha para o registo RIP, o endereço empilhado pela última instrução **call**,
provocando o regresso à função chamadora.

A instrução **ret** é equivalente a **pop rip**

Função sem parâmetros
.....................

+----------------------------------------------------------------------+--------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/delay.c   | .. literalinclude:: ../../../code/assembly_x86_64/function/delay_asm.s   |
|    :language: c                                                      |    :language: asm                                                        |
|    :caption: delay.c                                                 |    :caption: delay_asm.s                                                 |
+----------------------------------------------------------------------+--------------------------------------------------------------------------+

+--------------------------------------------------------------------------+------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/use_delay.c   | .. literalinclude:: ../../../code/assembly_x86_64/function/use_delay_asm.s   |
|    :language: c                                                          |    :language: asm                                                            |
|    :caption: use_delay.c                                                 |    :caption: use_delay_asm.s                                                 |
+--------------------------------------------------------------------------+------------------------------------------------------------------------------+

Geração do executável: ::

   $ gcc -Og -g use_delay.c delay_asm.s -o use_delay

Teste com *debugger*: ::

   $ insight use_delay

Função com parâmetros
.....................

Os argumentos de uma função são passados nos registos RDI, RSI, RDX, RCX, R8 e R9,
por esta ordem, até se esgotarem estes registos.
Caso seja necessário, os restantes argumentos, são passados em *stack*.
O retorno é feito em AL, AX, EAX, RAX ou em RDX:RAX, conforme o tipo.

No caso de retorno de uma struct com dimensão superior a 128 bits,
o chamador passa um argumento extra, que é o endereço de uma zona de memória,
reservada pelo chamador, onde a função deposita o resultado.

+------------------------------------------------------------------------+----------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/packdate.c  | .. literalinclude:: ../../../code/assembly_x86_64/function/packdate_asm.s  |
|    :language: c                                                        |    :language: asm                                                          |
|    :caption: packdate.c                                                |    :caption: packdate.s                                                    |
+------------------------------------------------------------------------+----------------------------------------------------------------------------+

+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/use_packdate.c  | .. literalinclude:: ../../../code/assembly_x86_64/function/use_packdate_asm.s  |
|    :language: c                                                            |    :language: asm                                                              |
|    :caption: use_packdate.c                                                |    :caption: use_packdate_asm.s                                                |
+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+

+------------------------------------------------------------------------+----------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/getbits.c   | .. literalinclude:: ../../../code/assembly_x86_64/function/getbits_asm.s   |
|    :language: c                                                        |    :language: asm                                                          |
|    :caption: getbits.c                                                 |    :caption: getbits_asm.s                                                 |
+------------------------------------------------------------------------+----------------------------------------------------------------------------+

+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/use_getbits.c   | .. literalinclude:: ../../../code/assembly_x86_64/function/use_getbits_asm.s   |
|    :language: c                                                            |    :language: asm                                                              |
|    :caption: use_getbits.c                                                 |    :caption: use_getbits_asm.s                                                 |
+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+

Geração do executável: ::

   $ gcc -Og -g use_getbits.c getbits_asm.s -o use_getbits

Teste com *debugger*: ::

   $ insight use_getbits


Acesso a variáveis
------------------

As variáveis são alojadas em memória ou em registos.
As variáveis alojadas em memória podem ter endereço fixo,
é o caso das variáveis globais e locais com atributo ``static``,
ou endereço variável, é o caso das variáveis locais alojadas em *stack*.

O compilador **gcc** na arquitetura **x86_64** utiliza duas formas de acesso a variáves.
Endereçamento relativo ao RIP ou endereçamento indireto.

O endereçamento relativo consiste em codificar a distância em número de *bytes*
desde o endereço presente em RIP até ao endereço da variável.

Este modo de endereçamento aplica-se às variáveis globais
e ás variáveis locais com atributo ``static``.
Estas variáveis são no conjunto designadas por variáveis estáticas e
são alocadas em memória na altura da compilação.

Em linguagem C quando se define uma variável estabelece-se um símbolo
(no exemplo **a** ou **i**) que representa o conteúdo dessa variável. ::

    char a;
    int i;

Na tradução para linguagem *assembly* esse símbolo origina uma *label* que representa um endereço de memória,
ou seja, o endereço da variável. ::

       .bss
   a:
       .byte	0
       .align	4
   i:
       .long	0

A notação ``a(%rip)``, utilizada nos exemplo seguinte, representa o endereço da variável ``a``.
É codificado como a diferença entre o endereço presente em RIP e a *label* ``a``.

A utilização que se faz do endereço da variável depende da semântica da instrução.
No caso de ``movb    $0, a(%rip)`` é realizada a escrita do valor 0 na posição de memória com esse endereço.
No caso de ``incq    i(%rip)`` é realizada uma leitura e uma escrita do valor depois de incrementado.

Um valor do tipo ``int`` é representado em memória por uma palavras de quatro *bytes*, por isso,
o acesso processa-se sobre as quatro posições de memória contiguas ao endereço calculado.

A dimensão da palavra operada é definida pela dimensão de um registo operando
ou pelo sufixo da instrução (letras ``b``, ``w``, ``l``, ``q``).

.. table::
   :widths: auto
   :align: center

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      a = 0;                        |      movb    $0, a(%rip)                 |
   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      i++;                          |      incl    i(%rip)                     |
   +------------------------------------+------------------------------------------+

Exemplos -- variáveis como argumentos
.....................................

+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_packdate.c  | .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_packdate_asm.s  |
|    :language: c                                                               |    :language: asm                                                                 |
|    :caption: use_packdate.c                                                   |    :caption: use_packdate_asm.s                                                   |
+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+

+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_getbits.c   | .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_getbits_asm.s   |
|    :language: c                                                               |    :language: asm                                                                 |
|    :caption: use_getbits.c                                                    |    :caption: use_getbits_asm.s                                                    |
+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+

*Array*
.......

Em linguagem C quando se define um *array* estabelece-se um símbolo
(no exemplo seguinte, ``ca``)
equivalente ao ponteiro para o primeiro elemento do *array*. ::

   char ca[10];

Na tradução para linguagem *assembly*, este símbolo origina uma *label*
que representa o endereço inicial da zona de memória onde o *array* está alojado. ::

   ca:
       .space	10

Para reservar uma zona de memória utiliza-se a diretiva ``.space`` cujos parâmetros são,
respetivamente, a dimensão da zona de memória a reservar, medida em número de *bytes*, e
o valor inicial de cada *byte*.

No caso de um *array* de tipo ``char`` a dimensão de memória a reservar é igual
ao número de elementos do *array* porque op elemento do tipo ``char`` ocupa 1 *byte* em memória.

Generalizando, a dimensão da memória a reservar é igual ao número de elementos do *array*
vezes a dimensão do elemento.

O *array* de valores inteiros ``int ia[10]`` é concretizado em *assembly* por: ::

   ia:
       .space    10 * 4

porque um elemento do tipo ``int`` ocupa 4 *bytes* em memória.

Em programação *assembly*, para acesso aos elementos do *array*
é necessário fazer corresponder os índices dos elementos no *array*
ao endereço dos elementos na memória.

O acesso utilizando operador indexação ``ca[i]``
é concretizado como um endereçamento indireto, na forma de dois registos,
um para o endereço base -- ``rdx`` e outro para o índice -- ``rcx``.

.. table::
   :widths: auto
   :align: center

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      ca[i] = 0;                    |       movb   $0, (%rdx, %rcx)            |
   +------------------------------------+------------------------------------------+

No caso do *array* do tipo ``int``, a utilização do operador indexação ``ia[i]``
é semelhante ao caso do *array* do tipo ``char``,
com diferença do fator de escala a aplicar ao registo índice.

No calculo do endereço do elemento do *array*,
o dígito 4 na instrução ``(%rdx, %rcx, 4)`` significa que o registo RCX é multiplicado por 4
antes de ser adicionado a RDX.

.. table::
   :widths: auto
   :align: center

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      ia[i] = 0;                    |       movq   $0, (%rdx, %rcx, 4)         |
   +------------------------------------+------------------------------------------+


Exemplos --  acesso a elementos de *array*
..........................................

+------------------------------------------------------------------------+----------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/strlen.c    | .. literalinclude:: ../../../code/assembly_x86_64/function/strlen_asm.s    |
|    :language: c                                                        |    :language: asm                                                          |
|    :caption: strlen.c                                                  |    :caption: strlen_asm.s                                                  |
+------------------------------------------------------------------------+----------------------------------------------------------------------------+

+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/use_strlen.c    | .. literalinclude:: ../../../code/assembly_x86_64/function/use_strlen_asm.s    |
|    :language: c                                                            |    :language: asm                                                              |
|    :caption: use_strlen.c                                                  |    :caption: use_strlen_asm.s                                                  |
+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+

Geração do executável: ::

   $ gcc -Og -g use_strlen.c strlen_asm.s -o use_strlen

Teste com *debugger*: ::

   $ insight use_strlen

+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/use_strlen2.c   | .. literalinclude:: ../../../code/assembly_x86_64/function/use_strlen2_asm.s   |
|    :language: c                                                            |    :language: asm                                                              |
|    :caption: use_strlen2.c                                                 |    :caption: use_strlen2_asm.s                                                 |
+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+


+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/findbigger.c    | .. literalinclude:: ../../../code/assembly_x86_64/data_access/findbigger_asm.s    |
|    :language: c                                                               |    :language: asm                                                                 |
|    :caption: findbigger.c                                                     |    :caption: findbigger_asm.s                                                     |
+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_findbigger.c  | .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_findbigger_asm.s  |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: use_findbigger.c                                                   |    :caption: use_findbigger_asm.s                                                   |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+

Ponteiros
.........

Considere-se a seguinte definição de variáveis
e a respetiva tradução para linguagem *assembly*.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      char a, b;                    |      a:                                  |
   |      char *cp;                     |          .byte    0                      |
   |      int i, j;                     |      b:                                  |
   |      int *ip;                      |          .byte    0                      |
   |                                    |          .align   8                      |
   |                                    |      cp:                                 |
   |                                    |          .quad    0                      |
   |                                    |      i:                                  |
   |                                    |          .long    0                      |
   |                                    |      j:                                  |
   |                                    |          .long    0                      |
   |                                    |      ip:                                 |
   |                                    |          .quad    0                      |
   +------------------------------------+------------------------------------------+

O operador ``&`` aplicado a uma variável dá o ponteiro para essa variável.
Um ponteiro para uma variável é concretizado como o endereço de memória dessa variável.

A expressão ``cp = &a;`` afeta a variável ``cp``, do tipo ponteiro para ``char``,
com o ponteiro para a variável ``a``.

Na notação da linguagem *assembly* a expressão ``a(%rip)`` representa o endereço da *label* ``a``.
A instrução ``lea   a(%rip), %rax`` calcula o endereço definido por ``a(%rip)`` e afeta RAX com o endereço calculado.
O cálculo é realizado pela adição do valor atual de RIP com a distância, calculada em compilação,
da instrução corrente até à *label* ``a``.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      cp = &a;                      |      lea    a(%rip), %rax                |
   |                                    |      mov    %rax, cp(%rip)               |
   +------------------------------------+------------------------------------------+

Comparando a instrução ``lea   a(%rip), %rax`` com a instrução ``mov   %rax, cp(%rip)``.
Ambas cálculam endereços de memória.
A primeira afeta o endereço calculado ao registo RAX,
a segunda escreve o conteúdo de RAX nas posições de memória definidas pelo endereço calculado.
Posições, porque se trata de escrever o conteúdo de RAX que contém um endereço de memória (8 *bytes*).

A obtenção do ponteiro para uma variável, é indiferente ao tipo dessa variável.
No exemplo abaixo, pode verificar-se que a expressão ``ip = &i;``
é traduzida para *assembly* com o mesmo padrão de código que a expressão ``cp = &a;``.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      ip = &i;                      |      lea    i(%rip), %rax                |
   |                                    |      mov    %rax, ip(%rip)               |
   +------------------------------------+------------------------------------------+

O acesso a uma variável por desreferenciação de ponteiro,
programa-se em dois passos. Primeiro carrega-se o ponteiro num registo,
em seguida aplica-se endereçamento indireto com base nesse registo para efetivar o acesso à variável.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      *cp = 'a';                    |      mov    cp(%rip), %rax               |
   |                                    |      movb   $'a', (%rax)                 |
   +------------------------------------+------------------------------------------+

No exemplo ``*cp = 'a';`` o valor do ponteiros ``cp`` é carregado no registo RAX,
como uma variável comum -- ``mov    cp(%rip), %rax``.
Em seguida escreve-se o valor ``'a'`` na memória por endereçamento indireto simples -- ``movb $0'a', (%rax)``.
O sufixo ``b`` na instrução ``movb`` é necessário para definir a dimensão da palavra.
Por se tratar do tipo ``char`` é apenas um *byte*.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      b = *cp;                      |      mov    cp(%rip), %rax               |
   |                                    |      mov    (%rax), %dl                  |
   |                                    |      mov    %dl, b(%rip)                 |
   +------------------------------------+------------------------------------------+

No exemplo ``b = *cp;``, depois de carregado o ponteiro ``cp`` em RAX, a instrução ``mov   (%rax), %dl``
descarrega o valor apontado por ``cp`` no registo DL.
Através da designação DL o *assembler* dispensa a utilização de sufixo ``b``.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      *ip = j;                      |      mov    j(%rip), %ecx                |
   |                                    |      mov    ip(%rip), %rax               |
   |                                    |      mov    %ecx, (%rax)                 |
   +------------------------------------+------------------------------------------+

No exemplo ``*ip = j;``, depois de carregado o ponteiro ``ip`` em RAX, a instrução ``mov   %ecx, (%rax)``
escreve o valor da variável ``j``, entretanto carregado em ECX, na memória apontada por ``ip``.
Através da designação ECX o *assembler* dispensa a utilização de sufixo ``l``.

Exemplo -- ponteiros como argumentos

+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/unpackdate.c    | .. literalinclude:: ../../../code/assembly_x86_64/data_access/unpackdate_asm.s    |
|    :language: c                                                               |    :language: asm                                                                 |
|    :caption: unpackdate.c                                                     |    :caption: unpackdate_asm.s                                                     |
+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_unpackdate.c  | .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_unpackdate_asm.s  |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: use_unpackdate.c                                                   |    :caption: use_unpackdate_asm.s                                                   |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+


**Aritmética de ponteiros**

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      char ca[10];                  |      ca:                                 |
   |      int ia[10];                   |          .space   10                     |
   |      char *cp;                     |          .align   4                      |
   |      int *ip;                      |      ia:                                 |
   |                                    |          .space   10 * 4                 |
   |                                    |          .align   8                      |
   |                                    |      cp:                                 |
   |                                    |          .quad    0                      |
   |                                    |      ip:                                 |
   |                                    |          .quad    0                      |
   +------------------------------------+------------------------------------------+

A aritmética de ponterios engloba dois casos: adição de inteiro a ponteiro e diferença de ponteiros.
Estas operações fazem sentido quando os ponteiros apontam para *arrays*.
A adição de um inteiro significa deslocar o ponteiro um número de posições.
A subtração de um ponteiro a outro ponteiro significa obter o número de posições entre esses ponteiros.

Na linguagem *assembly* um ponteiro é concretizado como um endereço de memória.
Quando se traduz a adição de um valor inteiro a um ponteiro é necessário aplicar o fator de escala
que consiste em multiplicar o valor inteiro pela dimensão do elemento apontado,
antes de efetuar a adição.

Nos exemplos seguintes, a operação ``cp++`` implica adicionar uma unidade à variàvel ``cp``;
a operação ``ip++`` implica adicionar 4 unidades à variável ``ip``.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      cp++                          |      incq   cp(%rip)                     |
   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      ip++                          |      addq   $4, ip(%rip)                 |
   +------------------------------------+------------------------------------------+

Na expressão ``ip + i`` é necessário múltiplicar o valor de ``i`` por 4 -- instrução ``shl   $2, %rax`` --
antes da instrução ``add  %rax, ip(%rip)``

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      ip = ip + i                   |      mov    i(%rip), %eax                |
   |                                    |      shl    $2, %rax                     |
   |                                    |      add    %rax, ip(%rip)               |
   +------------------------------------+------------------------------------------+

A diferença de dois ponteiros faz sentido se ambos os ponteiros
apontarem para elementos do mesmo *array*
e significa o número de elementos entre as posições apontadas.

Em linguagem *assembly*, como os ponteiros são concretizados por endereços,
a diferença de endereços é um número de posições de memória.

Para converter para número de elementos é necessário dividir a diferença de endereços
pela dimensão do elemento. Tratando-se de um *array* de ``int``,
a instrução ``shr   $2, %rax`` divide por 4 a diferença de endereços.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      j = ip - iq                   |      mov    iq(%rip), %rax               |
   |                                    |      sub    ip(%rip), %rax               |
   |                                    |      shr    $2, %rax                     |
   |                                    |      mov    %eax, j(%rip)                |
   +------------------------------------+------------------------------------------+


A notação de indexação ``ip[i]`` é equivalente à notação ``*(p + i)``.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      j = *(ip + i);                |      mov    ip(%rip), %rax               |
   |                                    |      mov    i(%rip), %esi                |
   |   .. code-block:: c                |      mov    (%rax, %rsi, 4), %eax        |
   |                                    |      mov    %eax, j(%rip)                |
   |      j = ip[i];                    |                                          |
   +------------------------------------+------------------------------------------+

*Struct*
........

Considere-se a seguinte definição da ``struct y`` e da variável ``x`` desse mesmo tipo: ::

   struct y {
       char a;
       int b;
       short c;
   } x = {
	.a = '1',
	.b = 1000,
   };

A definição da variável ``x`` em linguagem *assembly* consiste na definição de uma *label*
na direção do primeiro campo e da reserva de memória para alojamento de todos os campos. ::

   x:
       .align   4
       .byte    '1'	    # campo a - distância 0
       .align   4
       .long    1000    # campo b - distância 4
       .word    0       # campo c - distância 8

A forma comum de aceder aos campos de uma variável do tipo *struct* é por endereçamento indireto.
Coloca-se o endereço da variável num registo e pela adição da distância do campo ao início da *struct* define-se o endereço do campo.

No exemplo ``x.c = 222;`` a instrução ``lea    x(%rip), %rax`` coloca em RAX o endereço da *label* ``x``
que corresponde ao endereço do primeiro campo -- do campo ``a``.
Na instrução ``mov    $222, 8(rax)`` o valor 8 corresponde à distância do campo ``c`` desde o início da *struct*.
O endereço do campo ``c`` na variável ``x``, é obtido pela adição de 8 ao registo RAX.

.. table::
   :widths: auto

   +------------------------------------+------------------------------------------+
   |   .. code-block:: c                |   .. code-block:: asm                    |
   |                                    |                                          |
   |      x.c = 222;                    |      lea    x(%rip), %rax                |
   |                                    |      mov    $222, 8(%rax)                 |
   +------------------------------------+------------------------------------------+

Exemplo -- *Array* de *struct*
..............................

+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/getlighter.c    | .. literalinclude:: ../../../code/assembly_x86_64/data_access/getlighter_asm.s    |
|    :language: c                                                               |    :language: asm                                                                 |
|    :caption: getlighter.c                                                     |    :caption: getlighter_asm.s                                                     |
+-------------------------------------------------------------------------------+-----------------------------------------------------------------------------------+

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_getlighter.c  | .. literalinclude:: ../../../code/assembly_x86_64/data_access/use_getlighter_asm.s  |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: use_getlighter.c                                                   |    :caption: use_getlighter_asm.s                                                   |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+


Convenções de utilização de registos
------------------------------------

Os conteúdos dos registos RAX, RCX, RDX, RSI, RDI, R8, R9, R10 e R11 podem ser modificados pela função chamada,
os conteúdos dos registos RBX, RBP, R12, R13, R14 e R15 devem ser mantidos.
Manter não implica a não possam ser utilizados.
Implica que devem apresentaser à saída da função os mesmos conteúdos que tinham à entrada.
Se forem utilizados, os seus conteúdos devem ser resguardadados, por exemplo em *stack*.

.. figure:: register_rules.svg
   :align: center
   :scale: 120%

A cadeia de chamadas a funções num programa pode ser visualizada como uma árvore
em que a função **main** se situa na posição da raiz.
As funções que são chamadas e que também chamam outras funções,
situam-se nas posições dos ramos e são designadas por \"funções ramo\";
as funções que apenas são chamadas situam-se nas posições das folhas
e são designadas por \"funções folha\".

Para efeitos de escolha dos registos a utilizar,
interessa classificar as funções como \"funções folha\" ou como \"funções ramo\".

Função folha
..............

   * Deve-se operar os argumentos diretamente no registos que os transportam.
   * Deve-se preferir utilizar os registos *caller saved*.
   * Se tiver que se utilizar os registos *callee saved* deve-se assegurar à saída da função o mesmo conteúdo que tinham à entrada.

As funções ``get_lighter``, ``find_bigger``, ``strlen`` e ``unpack_date`` usadas em exemplos anteriores
são casos de funções folha, programadas segundo os critérios enumerados acima.

Função ramo
...........

   * Reutiliza os registos de parâmetros na chamada a outras funções.
   * Deve-se salvar os argumentos recebidos em registos *callee saved* ou em *stack*.
   * Deve-se alojar variáveis locais em registos *callee saved* ou em *stack*.
   * Se se optar por utilizar registos *caller saved* ou manter os argumentos recebidos no registos originais
     deve-se salvar esses registos antes de proceder à chamada de outra função.


+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/function/sort.c          | .. literalinclude:: ../../../code/assembly_x86_64/function/sort_asm.s          |
|    :language: c                                                            |    :language: asm                                                              |
|    :caption: sort.c                                                        |    :caption: sort_asm.s                                                        |
+----------------------------------------------------------------------------+--------------------------------------------------------------------------------+

Organização da *stack frame*
----------------------------
Na *stack frame* alojam-se os conteúdos dos registos a preservar,
as variáveis locais e argumentos de chamada a outras funções.

.. figure:: stack_frame.svg
   :align: center
   :scale: 140%

Variáveis locais em *stack*
---------------------------

As variáveis locais são alojadas em *stack* se:

   * a sua quantidade excede o número de registos disponíveis;
   * a sua dimensão não permite o alojamento em registo -- é o caso dos *arrays*;
   * é necessário aceder a essas variáveis através de ponteiros.

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use_unpackdate.c  | .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use_unpackdate_asm.s  |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: use_unpackdate.c                                                   |    :caption: use_unpackdate_asm.s                                                   |
|                                                                                 |    :linenos:                                                                        |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+

.. figure:: stack4.svg
   :align: center
   :scale: 120%

À entrada da função o registo RSP apresenta o endereço de memória ``0x7fffffffdd58``.
A instrução ``sub $24, %rsp`` ao subtrair 24 a RSP,
reserva espaço para alojar as variáveis ``year``, ``month`` e ``day``.
Para alojar três variáveis do tipo int são necessários 12 *bytes*.
Como RSP deve estar alinhado num endereço múltiplo de 16 na chamada a uma função,
são subtraídas 24 posições de memória.
As posições de memória entre ``0x7fffffffdd40`` e ``0x7fffffffdd43`` e entre ``0x7fffffffdd50`` e ``0x7fffffffdd57`` não são utilizadas.
Nas linhas 5, 6 e 7 são preparados os argumentos para a chamada à função ``unpack_date``, que são os ponteiros para as variáveis ``year``, ``month`` e ``day``.
A instrução ``add $24, %rsp`` reposiciona RSP no endereço inicial.

*Array* de dimensão variável
............................

Alojamento de *array* local de dimensão variável em *stack*. (Sem proteção de *stack clash*.)

Consideremos a função ``get_year`` que extrai a componente ano, na forma de inteiro,
de uma data representada numa *string* com o formato "2020-9-3".

+---------------------------------------------------------------------------+------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/getyear.c   | .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/getyear_asm.s  |
|    :language: c                                                           |    :language: asm                                                            |
|    :caption: getyear.c                                                    |    :caption: getyear_asm.s                                                   |
|                                                                           |    :linenos:                                                                 |
+---------------------------------------------------------------------------+------------------------------------------------------------------------------+

A reserva de espaço para o *array* local ``buffer`` é realizada nas linhas 14, 15 e 16.
A dimensão necessária é estabelecida na linha 13 -- valor retornado por ``strlen`` mais um.

Na linha 14 e 15 essa dimensão em EAX é arredondada por excesso para um valor múltiplo de 16.
((EAX + 15)  / 16)  * 16 ( o sinal / representa divisão inteira).

Na linha 16 esse valor é subtraído a RSP consumando a reserva de espaço de memória para o array local buffer.
No final da função, RSP é restabelecido com o valor de RBP -- linha 26. Sendo uma solução simples para de reajuste do RSP e libertação do espaço de memória reservado.
Nas circunstâncias em que o espaço de memória a reservar em stack é variável, o gcc por omissão gera código de mitigação do efeito stack clash. O código apresentado acima foi gerado pelo gcc sob o efeito da opção -fno-stack-clash-protection.

Passagem de argumentos em *stack*
---------------------------------

Na invocação de funções com mais de seis parâmetros,
os argumentos para além do sexto são passados em *stack*.
Estes argumentos são empilhados no *stack* pela ordem inversa da lista de parâmetros da função.
O argumento correspondente ao último parâmetro é o primeiro a ser empilhado
e consequentemente ocupará o endereço mais alto.
O argumento do parâmetro mais à esquerda é o que fica no topo do *stack*.

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use_func8args.c   | .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use_func8args_asm.s   |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: use_func8args.c                                                    |    :caption: use_func8args_asm.s                                                    |
|                                                                                 |    :linenos:                                                                        |
+---------------------------------------------------------------------------------+                                                                                     |
| .. figure:: stack1.svg                                                          |                                                                                     |
|    :align: center                                                               |                                                                                     |
|    :scale: 100%                                                                 |                                                                                     |
|                                                                                 |                                                                                     |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+

Na linha 6 empilha-se o oitavo argumento -- o ponteiro para ``x4``.
Na linha 8 empilha-se o sétimo argumento -- o valor de ``x4``.
Note-se que apesar de ser do tipo ``char`` a passagem é feita numa palavra de 64 *bits*.
Entre as linhas 9 e 14 procede-se à passagem em registo dos restantes seis argumentos.

A convenção de chamada a funções define que na altura da execução da instrução ``call``
o registo RSP deve estar alinhado num endereço múltiplo de 16.
Como consequência, à entrada de uma função, o RSP está sempre desalinhado de endereço múltiplo de 16.
Assim, a função atual pode basear-se neste pressuposto para efeito de alinhamento do RSP ao realizar outras chamadas.
A instrução ``sub  $8, %rsp`` na linha 4 serve para cumprir esta convenção.
Até à instrução ``call`` na linha 15, o RSP vai ser decrementado de 24 ficando alinhado num endereço múltiplo de 16.

+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/func8args.c       | .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/func8args_asm.s       |
|    :language: c                                                                 |    :language: asm                                                                   |
|    :caption: func8args.c                                                        |    :caption: func8args_asm.s                                                        |
|                                                                                 |    :linenos:                                                                        |
+---------------------------------------------------------------------------------+                                                                                     |
| .. figure:: stack2.svg                                                          |                                                                                     |
|    :align: center                                                               |                                                                                     |
|    :scale: 100%                                                                 |                                                                                     |
|                                                                                 |                                                                                     |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------------------------+

No início da execução de uma função o endereço de retorno apresenta-se no topo do *stack*,
depois dos argumentos da função.
O acesso aos argumentos é realizado com base em RSP.
O acesso a ``a4p`` é realizado na linha 4.
``16(%rsp)`` equivale ao endereço ``0x7fffffffdd60`` que é o local do *stack* onde ser encontra o argumento ``&x4``.

O acesso a ``a4`` é realizado na linha 8. ``8(%rsp)`` equivale ao endereço ``0x7fffffffdd58``
que é o local do *stack* onde se encontra o argumento ``x4``.

Exemplo -- função com mais de seis argumentos
.............................................

Neste exemplo vai ser mostrada uma utilização do *stack* mais abrangente.
Além de utilizado na passagem de argumentos vai também ser utilizado para alojamento de variáveis locais.
O exemplo é semelhante ao anterior com a diferença das variáveis ``x1``, ``x2``, ``x3`` e ``x4``
serem locais à função ``use_func8args``.

.. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use2_func8args.c
   :language: c
   :caption: use2_func8args.c
   :linenos:

+------------------------------------------------------------------------------------+-------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/stack_frame/use2_func8args_asm.s | .. figure:: stack5.svg        |
|    :language: asm                                                                  |    :align: center             |
|    :caption: use2_func8args_asm.s                                                  |    :scale: 100%               |
|    :linenos:                                                                       |                               |
+------------------------------------------------------------------------------------+-------------------------------+

O bloco de código inicial linhas 4 a 6 designa-se por preâmbulo da função.
No preâmbulo, linhas 4 e 5, o registo RBP é preparado para acesso aos valores em stack
-- argumentos e variáveis locais.
Na linha 6 a adição de 16 a RSP reserva espaço de memória em *stack* para as variáveis locais.

O registo RSP sofre um decremento de 40 unidades até à instrução ``call`` o que garante o alinhamento a múltiplo de 16.

O registo RBP indica sempre a mesma posição do *stack*
-- a seguir ao endereço de retorno, onde é salvo o conteúdo de RBP da função chamadora
-- e  mantém-se fixo durante a execução da função.

Para aceder aos parâmetros são usados deslocamentos positivos em relação a RBP:
``8(%rbp)`` corresponde ao primeiro argumento em *stack*,
``16(%rbp)`` corresponde ao segundo argumento e assim sucessivamente.

Para aceder às variáveis locais são usados deslocamentos negativos em relação a RBP:
``-8(%rbp)`` corresponde à primeira variável local -- ``x1``,
``-12(%rbp)`` corresponde à segunda variável local -- ``x2``,
``-14(%rbp)`` corresponde à terceira variável local -- ``x3`` e
``-15(%rbp)`` corresponde à quarta variável local -- ``x4``.

Ao retornar da função é necessário repor RSP exatamente no estado inicial
-- libertar o espaço usado para passagem de argumentos,
libertar o espaço reservado para variáveis locais
e repor em RBP o conteúdo original.

O código responsável por esta operação designa-se por epílogo
e neste caso é formado pelas instruções das linhas 31 e 32.
A instrução ``mov    %rsp, %rbp`` ao reposicionar RSP na posição de RBP,
liberta simultaneamente o espaço ocupado em *stack* quer no alojamento de variáveis locais,
quer na passagem de argumentos.

*Red zone*
==========

A *read zone* é a área de *stack*, livre, além da posição indicada pelo registo SP (endereços inferiores, na arquitetura x86_64).
Esta área tem a dimensão de 128 *bytes* e está resguardada de modificações por rotinas de atendimento de interrupções ou de excepções.
Pode ser utilizada para armazenamento temporário de dados que não sejam necessários entre chamadas a funções.
Nas funções folha pode ser utilizada para alojar toda a *stack frame* sem necessidade de ajustar do registo SP.

Exemplo -- utilização da *red zone*
...................................

.. literalinclude:: ../../../code/assembly_x86_64/stack_frame/mfd.c
   :language: c
   :caption: mfd.c


.. literalinclude:: ../../../code/assembly_x86_64/stack_frame/mfd_asm.s
  :language: asm
  :caption: mfd_asm.s
  :linenos:

*Buffer overflow*
=================

A situação conhecida como *buffer overflow* caracteriza-se pelo acesso a posições de memória
além dos limites das variáveis.
O caso mais conhecido passa-se com a função **gets**. ::

   char* gets( char *str );

A função **gets** lê caracteres do *standard input*
e escreve-os no *array* passado em parâmetro
até ler uma marca de fim de linha -- **\\n**.
Se o *array* apontado por ``str`` tiver uma dimensão inferior ao número de caracteres lidos,
a função **gets** escreve-os para além do limite do *array*,
corrompendo informação armazenada na vizinhança.

A função **gets** foi retirada da biblioteca normalizada da linguagem C
pelo potencial de falha que permite introduzir num programa.

No exemplo, se o número de caracteres lido for superior a 7, irá ocorrer falha.
Quais as consequências dessa falha?

+------------------------------------------------------------------------------+---------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/buffer_overflow/secret.c   | .. literalinclude:: ../../../code/assembly_x86_64/buffer_overflow/secret_asm.s  |
|    :language: c                                                              |    :language: asm                                                               |
|    :caption: secret.c                                                        |    :caption: secret_asm.s                                                       |
|                                                                              |    :linenos:                                                                    |
+------------------------------------------------------------------------------+---------------------------------------------------------------------------------+

Geração do executável: ::

   $ gcc secret.c -fno-stack-protector -o secret

**Exercícios**

   1. Fazer com que a sequência de caracteres introduzida provoque a execução de print_secret(1).

   2. Fazer com que a sequência de caracteres introduzida provoque a execução de print_secret(2).


*Stack protector*
=================

O **gcc** dispõe de um meio de deteção da ocorrência de *buffer overflow*.
À entrada na função é posicionada uma marcação no limite da *stack frame*;
à saída da função verifica-se se a marcação foi corrompida.
Esta marcação é designada por \"canário\".

Este método não completamente eficaz. Se o acesso se der para além do canário sem o modificar,
não será detetado.

Esta funcionalidade é ativada/desativada através das opções seguintes.
Por omissão, é ativada. ::

   -fstack-protector
   -fno-stack-protector

+---------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------+
| .. literalinclude:: ../../../code/assembly_x86_64/buffer_overflow/stack_protector.c   | .. literalinclude:: ../../../code/assembly_x86_64/buffer_overflow/stack_protector_asm.s  |
|    :language: c                                                                       |    :language: asm                                                                        |
|    :caption: stack_protector.c                                                        |    :caption: stack_protector_asm.s                                                       |
|                                                                                       |    :linenos:                                                                             |
+---------------------------------------------------------------------------------------+------------------------------------------------------------------------------------------+

*Stack clash*
=============

O *stack clash* acontece quando a dimensão de uma variável local depende de um parâmetro (a dimensão é variável).
As variáveis locais são alojadas no *stack* por deslocação do *stack pointer*.
Se esta deslocação ultrapassar certos limites pode colidir com outras zonas de memória.

O *gcc* dispõe de uma opção de compilação para ativar/desativar
a geração de código de mitigação de *stack clash*. ::

   -fstack-clash-protection
   -fno-stack-clash-protection


Recomendações para escrita em *assembly*
========================================

Na escrita de programas em geral, usam-se convenções de formatação para facilitar
a leitura do programa por parte do humano.
Em seguida lista-se um conjunto de regras geralmente utilizadas na programação em linguagem *assembly*
e que são aplicadas nos programas de exemplo.

* O texto do programa é escrito em letra minúscula,
  exceto os identificadores de constantes, que são escritos em letra maiúscula.

* Nos identificadores formados por várias palavras
  usa-se como separador o carácter ‘_’ (sublinhado).

* O texto do programa é disposto na forma de uma tabela de quatro colunas.
  Na primeira coluna insere-se apenas a *label*, se existir;
  na segunda coluna a mnemónica da instrução ou a diretiva;
  na terceira coluna os parâmetros da instrução ou da diretiva;
  na quarta coluna os comentários até ao fim da linha
  (começados por \';\' ou envolvidos por /\* \*/).

* Cada linha contém apenas uma label, uma instrução ou uma diretiva.

* Para definir as colunas deve usar-se o carácter TAB
  configurado com a largura de oito espaços.

* A terceira coluna ­-- a dos parâmetros ­-- pode ocupar mais que um espaçamento.

* As linhas com *label* não devem conter nenhum outro elemento.
  Isso permite usar *labels* compridas sem desalinhar a tabulação
  e criar separações na sequência de instruções,
  que ajudam na interpretação do programa.

.. figure:: assembly_layout.svg
   :align: center
   :scale: 100%

Referências
===========

   * Calling conventions for different C++ compilers and operating systems, https://www.agner.org/optimize/calling_conventions.pdf

   * System V Application Binary Interface -- AMD64 Architecture Processor Supplement, https://wiki.osdev.org/System_V_ABI#x86-64

   * Application Binary Interface for the Arm® Architecture -- The Base Standard https://developer.arm.com/documentation/ihi0036/d/?lang=en#the-generic-c-abi

   * Compiler Explorer, https://gcc.godbolt.org/

   * Using AS, https://sourceware.org/binutils/docs-2.25/as/index.html

   * Intel® 64 and IA-32 Architectures Software Developer Manuals, http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html

