# Otimização de operações bancárias – Um protótipo

Um banco deseja melhorar seus sistema de operações bancárias.
Atualmente o sistema deles armazenatodas as informações dos clientes e uma lista ordenada. A proposta do banco é para sua equipe desen-volver uma organização dos dados em forma de Árvore AVL, pois o gerente de T.I. do banco sabe que asoperações em uma AVL têm custo de O(logn).Desta forma, você estará focado em elaborar um TAD para uso de Árvore AVL e uma interface de teste que seja capaz de receber dados pela entrada padrãoe computar a saída.

## Simulação
A entrada constará de uma sequência de operações que seu programa deve conseguir computá-las eretornar uma saída determinada. Assim como na versão completa da simulação, será informada umaquantidadeNde operações. Cada operação será identificada com uma letra seguida dos seus devidos parâmetros. Os dados de entrada são as informações dos cliente: Código_cliente: Inteiro; Operação:1para saque e0para depósito; e Valor: valor inteiro. A `chave de ordenação` deve ser o código do cliente.

A árvore deve guardar as informações e gerar um relatório descrito posteriormente que consta naquantidade de clientes distintos que foram inseridos bem como as informações referêntes ao código docliente, quantidade de operações e saldo final.

## Formato de entrada
A entrada constará de uma sequência de operações, terminada com umaoperação de término desequência de operações. As operações que podem ocorrer são:

- **insere nó:** esta operação consiste de uma linha contendo a letra `i`, seguida de um espaço e três números inteiros separados com um espaço que serão respectivamente `código_cliente`, `operação` e `valor`.  Esta operação causa a inserção de um nó na árvore cuja chave será o número inteiro referente ao código_cliente. Caso já haja nó na árvore com valor de chave igual a este número, o nó com tal chave deve ter seus dados atualizados de acordo com a operação informada.

- **consulta nó:** esta operação consiste de uma linha contendo a letra `c`, seguida por um espaço, seguido por um valor inteiro. Esta operação verifica se há ou não nó na árvore com valor de chaveigual ao número inteiro digitado.

- **remove nó:** esta operação consiste de uma linha contendo a letra `r`, seguida por um espaço, seguido por um valor inteiro. Esta operação retira o nó da árvore que tiver chave igual ao número inteiro indicado, se houver. Se não houver, esta operação não gera efeito.

- **lista chaves dos nós da árvore em ordem:** esta operação consiste de uma linha contendo aletra `p`, seguida de um espaço, seguido da letra `c` ou `d`. Se a segunda letra é `c`, esta operaçãolista as chaves dos nós da árvore em ordem crescente. Se a segunda letra for `d`, esta operaçãolista as chaves dos nós da árvore em ordem decrescente.

- **lista chaves de um determinado nível da árvore:** esta operação consiste de uma linhacontendo a letra `n`, seguida de um espaço, seguido de um número inteiro maior ou igual a 1. Estaoperação lista as chaves dos nós da árvore que tiverem nível igual ao número fornecido. Assuma que a raiz da árvore possui nível 1.

- **informa altura:** esta operação consiste de uma linha contendo a letra `h`. Esta operação informa a altura da árvore.

- **término da entrada:** a sequência de operações será terminada por uma linha com a letra `f`.

## Formato da Saída
Cada operação deverá apresentar a saída da seguinte forma:

- **insere nó:** esta operação não gera saída.

- **consulta nó:** se houver um nó na árvore com a chave informada, esta operação gera, na saída, a sequência de caracteres "existe no com chave:  X", onde X é a chave informada. Caso não haja, esta operação gera, na saída, a sequência de caracteres "nao existe no com chave:  X", onde X é a chave informada.

*Observação: Não usamos nenhum tipo de acentuação.*

- **remove chave:** esta operação não gera saída (independentemente se há ou não nó com o valor de chave indicado na operação).

- **lista chaves dos nós da árvore em ordem:** esta operação lista os dados contidos nos nós, um em cada linha. Os dados serão três inteiros que correspondem respectivamente ao código_cliente, quantidade_de_operação e saldo.

- **lista chaves de um determinado nível da árvore:** esta operação lista as chaves dos nós, uma em cada linha. A sequência das chaves dos nós listados deve seguir a ordem da representação
gráfica da árvore, da esquerda para a direita.

- **informa altura:** esta operação deve retornar um inteiro que informa a altura da árvore corrente. Considere que a árvore vazia tem algura zero.

- **término da entrada:** esta operação irá gerar um relatório com todos os dados armazenados na árvore.  Para tal, deve iniciar imprimindo a seguinte sequência de caracteres

`-+- Inicio relatorio -+-`

, depois imprimir o inteiro L que representa a quantidade distintas de clientes seguido de L linhas que devem conter três inteiros Ci,Qi e Si, para 1 ≤ i ≤ L, separados por um espaço em branco e finalizar com a seguinte sequência de caractere

`-+- Fim relatorio -+-`

A ordem de impressão dos dados é dada pela operação de remoção da raiz da árvore.

## Restrições
Algumas restrições para a implementação das estruturas de dados do sistema:

- Deve-se utilizar a entrada padrão para receber os dados e a saída padrão para imprimir os dados;

- Cada nó da árvore deve, no mínimo, ter três ponteiros onde se referenciam, respectivamente, ao seu filho esquerdo, filho direito e pai;

- O sistema tem que utilizar **fortemente** o conceito de tipo abstrato de dados (TAD) na implementação da árvore AVL, i.e., as definições dos nós e das estruturas de dados da árvore devem estar definidas no arquivo `avl.c` e as interfaces/assinaturas das funções e tipos no arquivo `avl.h`;

- Não deve utilizado em nenhuma hipótese variáveis globais tanto no arquivo principal quanto no TAD;

- O conjunto: TAD + arquivo principal deve gerenciar a memória de maneira ótima, i.e., tudo que for alocado deve ser desalocado;

- No arquivo principal, cada operação de entrada possível deve ter uma função para chamar as funções do TAD e formatar sua saída.

