Programação genérica
********************

Em resumo, a programação genérica permite definir algoritmos,
sem concretizar no momento da sua definição, os tipos de dados sobre os quais operam.

A linguagem C dispõe dos seguintes mecanismos para realizar esse tipo de programação:

   * Ponteiro ``*void``
   * Ponteiro para função
   * Função com número de parâmetros variável

Ponteiro \*void
===============

Não existem objetos do tipo ``void`` mas existem objetos do tipo ``void *``.
São ponteiros para objetos sem tipo definido.
Utilizam-se para programar algoritmos do modo independente do tipo de dados concreto.

As funcões ``memcpy`` e ``memmove`` são exemplos destes casos. Servem para copiar 
objetos tendo como referência os ponteiros para esses objetos.
Como, para efeitos de cópia, a diferença entre os objetos é apenas a quantidade de memória que ocupam,
o terceiro parâmetro -- ``count`` -- serve para fornecer essa informação.
Em termos algoritmicos estas funções operam como se um *array* de *bytes* de tratasse.
O primeiro parâmetro recebe o endereço de destino,
o segundo o endereço fonte e o terceiro a quantidade de *bytes* a copiar.

A diferença de funcionamento entre estas funções deve-se a razões de eficiencia.
A função ``memmove`` acautela a eventual sobreposição das zonas de memória em causa
e por isso é menos eficiente que ``memcopy``.
A função ``memcpy`` só deve ser usada se as zonas de memória em causa não tiverem zonas de interseção. ::

   void *memcpy(void *dest, const void *src, size_t count);

   void *memmove(void *dest, const void *src, size_t count);

**Exemplo**

Deslocar cada elemento de um *array* para a posição seguinte.
O elemento da posição 0 é copiado para a posição 1; o elemento da posição 1 é copiado para a posição 2
e assim sucessivamente até à penúltima posição. O último elemento é descartado.

Os elementos do *array*, desde a posição 1 até à última,
são copiados como um bloco de *bytes*.
Escolhe-se a função ``memmove`` porque as zonas de memória em causa não são disjuntas.
A dimensão deste bloco é calculada pela expressão ``sizeof array - sizeof array[0]``
-- a dimensão de ``array`` menos a dimensão de um elemento.

.. literalinclude:: ../../../code/generic_programming/use_memmove.c
   :language: c
   :linenos:
   :caption: Utilização de ``memmove`` para deslocar elementos num *array*
   :name: use_memmove

Ponteiro para função
====================

Um ponteiro para função pode ser afetado a uma variável, passado como argumento ou devolvido como valor de função.
É utilizado para invocar uma operação de forma indireta.
Exemplos de aplicação deste método são as funções de biblioteca ``qsort`` e ``bsearch``,
em que se parametriza o critério de comparação dos elementos de um *array* com vista à ordenação
ou à procura.

Nestas funções é também aplicado um método de definição de *array* genérico com base em três componentes:
ponteiro inicial; número de elementos; dimensão dos elementos. ::


   void qsort( void* ptr, size_t count, size_t size,
               int (*comp)(const void*, const void*) );

   void* bsearch( const void *key, const void *ptr, size_t count, size_t size,
                  int (*comp)(const void*, const void*) );

**Exemplo**

No exemplo da :numref:`use_qsort` a função ``qsort`` é utilizada para ordenar um *array* de inteiros.
O critério de comparação é programado na função específica, ``cmp_int`` cujo ponteiro é passado como último argumento
na invocação de ``qsort``.

Esta função é invocada em *callback* sempre que o algoritmo determina a comparação de elementos do *array*,
recebemdo como argumentos os ponteiros para as posições a comparar.

A função de comparação é programada no contexto do conhecimento do tipo de dados em causa.
Os seus parâmetros formais, do tipo ``void *``, são convertidos explicitamente
para ponteiros para o tipo dos elementos do *array*.
No exemplo, os parâmetros ``a`` e ``b`` são convertidos para ``int *`` nas linhas 10 e 12.

.. literalinclude:: ../../../code/generic_programming/use_qsort.c
   :language: c
   :linenos:
   :caption: Ordenação de *array* de inteiros utilizando ``qsort``
   :name: use_qsort

**Exercício**

Modifique o programa da :numref:`use_qsort` de modo a exemplificar a ordenação
de um *array* de ponteiros para *strings* pelo critério da ordem alfabética do conteúdo das *strings*.

Função com número de parâmetros variável
========================================

A função com número de parâmetros variável mais conhecida é a função ``printf``,
com a seguinte assinatura: ::

   int printf(const char *format, ...);

As reticências significam que a função pode ser invocada com qualquer número e tipo de argumentos,
depois do argumento do parâmetro ``format``.
 
Como é que a função ``printf`` "sabe" quantos e de que tipo são os argumentos
que lhe foram passados numa dada invocação?
É pela análise da *string* passada no argumento ``format``. As definições de conversão 
marcadas com ``%``, caraterizam os retantes argumento a processar, em número e em tipo.

O acesso aos argumentos da zona variável faz-se segundo o seguinte modelo:
   * os argumentos constituem uma sequência;
  
   * a *macro* ``va_start`` inicializa um ponteiro para o inìcio da sequência
     tomando como referência o último parâmetro fixo;

   * o valor dos argumentos é obtido através da *macro* ``va_arg``;
   
   * a macro ``va_arg`` além de extrair o valor do argumento corrente
     avança para o próximo argumento.

**Exemplo**

.. image:: va_arg.svg

.. literalinclude:: ../../../code/generic_programming/va_arg/sum_var.c
   :language: c
   :lines: 9-
   :linenos:
   :caption: Função que adiciona um número variável de valores.
   :name: sum_var

A função ``sum`` realiza a adição dos valores de uma sequência variável de valores inteiros.
A dimensão da sequência é indicado pelo parâmetro ``n``.

Na linha 8, a variável ``ap`` é inicializada por ``va_start(ap, n)`` tomando ``n`` como referência.

Na linha 11, cada um dos valores a adicionar é obtido por ``va_arg(ap, int)``.
``ap`` é avançado para a posição seguinte.
O argumento ``int`` indica o tipo do valor a extarir.

A título ilustrativo, apresenta-se uma definição simplificada (e imprecisa) das *macros* ``va_start`` e ``va_arg``: ::

   #define va_start(ap, fixed)   ap = &fixed + 1
   
   #define va_arg(ap, type)      *((type) *)ap++)
     
No final, a *macro* ``va_end`` deve ser invocada, após o que, o ponteiro ``ap`` fica indefinido. 

**Exemplo**

Outro exemplo bem ilustrativo do funcionamento dos mecanismos de processamento de lista de parâmetros variável é a programação da função *printf*.
Da qual se apresenta uma versão reduzida da variante *snprintf*.

Destaca-se a invocação da *macro* ``va_arg`` nas linhas 23, 33, 43 e 52.
O tipo do valor a extrair, indicado como segundo argumento, depende do especicicador *%*.
Este argumento determina também a amplitude do avanço de ``ap``.
 
.. literalinclude:: ../../../code/generic_programming/va_arg/mini_snprintf.c
   :language: c
   :lines: -72
   :linenos:
   :caption: Implementação reduzida de *snprintf*.
   :name: mini_snprintf

Variante *vprintf*
------------------

A lista de argumentos variável pode ser propagada como argumento de outras funções
sem ser processada localmente.

Para que isso aconteça, é necessário que a função invocada receba como parâmetro fixo
um ponteiro do tipo ``va_list``.

As variantes de *printf* prefixadas com "**v**" são casos de funções
que recebem uma lista de parâmetros variável pertencente a outra função. ::

   int vprintf(const char* format, va_list vlist);

**Exemplo**

A função ``trace`` escreve em *stdout* uma *string* de informação etiquetada com uma referência de tempo. 
Depois de escrever a indicação de tempo -- linha 11 --
invoca ``vprintf`` para escrever a informação,
passando a lista de argumentos variável através do parâmetro ``vlist``.

.. literalinclude:: ../../../code/generic_programming/va_arg/trace.c
   :language: c
   :linenos:
   :caption: Registo de informação com etiqueta de tempo.
   :name: trace

  
Referências
===========

The C Programming Language, secçãos 5.11, secção 7.3
