**MIEIC, 2ºA Sistemas Operativos – 2020/21 FEUP**

## 2º Mini Projeto:

# Application Server

## Objetivos

Completando com sucesso todas as fases deste trabalho, os alunos demonstram conhecere saber utilizar a interface programática de UNIX em C para conseguir:
- criar programas multithread;
- promover a intercomunicação entre processos através de canais com nome (namedpipes ou FIFOs);
- evitar   conflitos   entre   entidades   concorrentes,   por   via   de   mecanismos   desincronização.

## Client - Descrição Geral 

A ferramenta a desenvolver, denominada **client c** que permite comunicação com um servidor dado s.

```
Pretende-se obter uma aplicação do tipo cliente-servidor capaz de lidar com pedidos de execução  de  tarefas
de diferente  carga.
As  tarefas são  executadas  por  código  numa Biblioteca B externa, e um Servidor Smultithread gere os 
pedidos de execução e devolveos resultados.
Os pedidos de tarefas são enviados ao Servidor S por um processo Cliente Cmultithread; ficarão   numa   
fila   de   atendimento   até  terem   vez,   altura   em   que   a   tarefarequisitada é passada por um
thread  Produtor 
à Biblioteca para ser executada, sendo oresultado colocado num armazém (buffer).
Este armazém é monitorizado por um  threadConsumidor que, havendo resultados, os recolhe um a um e
os envia de volta ao Cliente.
A aplicação deve ser desenvolvida em 2 etapas, de complexidade crescente, a primeirafocando-se   no
desenvolvimento   do   Cliente  C,
assumindo   a   existência   de   umaimplementação   do   Servidor  S (que   será   disponibilizada), 
e   a   segunda   focando-se   
nodesenvolvimento do Servidor S, sendo então disponibilizado um exemplo de um Cliente C
(os alunos podem usar o cliente que desenvolveram anteriormente, 
mas devem semprevalidar o funcionamento com a versão disponibilizada).
Em ambas as etapas a Biblioteca Bexterna atua como  caixa-negra e  é disponibilizada.
No  final de cada etapa,
o  códigodesenvolvido será submetido para avaliação: código Cliente C no final da 1ª etapa e
códigoServidor S no final da 2ª etapa.
```
![image](https://user-images.githubusercontent.com/55672106/116570273-0bec5b00-a902-11eb-89be-11ad5d1f2fc5.png)

## Requisitos Funcionais

Requisitos comuns ao Cliente e ao Servidor
- tanto o Cliente como o Servidor deverão ser programas multithread;
- ambos funcionam com o máximo de paralelismo possível e evitam situações de encravamento (deadlock), de "colisão" e "esperas activas" (busy-waiting) com o auxílio de primitivas de sincronização do tipo das estudadas;
- as tarefas a executar no Servidor (pelo código na Biblioteca) são identificadas porum inteiro único universal e exigem uma carga de processamento que é classificadapor um número entre 1 e 9; o resultado da execução de cada tarefa é um valorinteiro único.
![image](https://user-images.githubusercontent.com/55672106/116574042-40ade180-a905-11eb-9267-4f9fff88a215.png)

## Requisitos para o Cliente C
O Cliente C é invocado com o comando: c "-t nsecs" "fifoname"
- nsecs - nº (aproximado) de segundos que o programa deve funcionar
- fifoname - nome (absoluto ou relativo) do canal público de comunicação com nome(FIFO) por onde o Cliente envia pedidos ao Servidor
O seu funcionamento, de forma sumarizada, é o seguinte:
- inicialmente, recolhe os argumentos de linha de comando e executa as operaçõesfundamentais para o funcionamento do programa;
- o  thread  principal  c0  lança  continuamente  threads  de pedido  c1, ...,  cn  (comintervalos   (pseudo-)aleatórios   de   alguns   milisegundos,   por   forma   de   exacerbarcondições de competição), cada um ficando associado a um pedido ao Servidor;
- cada  thread  de pedido  c1, ...,  cn gera os parâmetros do pedido pelo qual éresponsável (especificamente, o seu número de identificação universal único e acarga   da   tarefa   pedida,   valor   aleatório   inteiro   entre   1   e   9),   trata   de   toda   acomunicação com o servidor, incluindo a criação e posterior eliminação de um FIFOprivado por onde receberá a resposta do Servidor, pela qual terá de esperar embloqueamento;  chegada a resposta, termina (não sem antes efectuar eventuaisoperações de registo ou disponibilização do resultado ao utilizador);
- caso o Servidorfeche, o FIFO, o Cliente deverá detectar tal situação e terminar ageração de novos pedidos; os threads com pedidos já colocados deverão aguardarresposta, que será: o resultado normal do pedido de tarefa (que indica que o pedidoainda foi atendido a tempo pelo Servidor) ou uma indicação de encerramento (nocaso de o pedido já não ser atendido);
- após o prazo de funcionamento especificado pelo utilizador, o Cliente deve terminara execução fazendo com que os threads em espera de resposta desistam mas nãosem antes garantir que todos os recursos tomados ao sistema são libertados.

## Comunicação entre C e S
Para ambos os programas **C** e **S**:

as mensagens trocadas são sempre aos pares:
- cada pedido terá sempre uma resposta;

os pontos de comunicação são:
- um canal público do tipo FIFO, cujo nome é passado como argumento daslinhas de comando de **C** e de **S**, por onde são colocados os pedidos;
- canais privados do tipo FIFO, cada um criado pelo  thread responsável porum pedido e que receberá a correspondente resposta do servidor; os nomestêm a estrutura: **/tmp/pid.tid**:
      ● **pid** - identificador de sistema do processo Cliente **C**;
      ● **tid** - identificador de sistema Posix do respectivo thread de pedido;
      
as   mensagens   trocadas   em   ambas   as   direções   são   estruturalmente   idênticas,diferindo possivelmente no conteúdo de alguns campos. A sua estrutura é, em C
        
**struct msg { int i; int t; pid_t pid; pthread_t tid; int res; };**

- **i** - número universal único do pedido (gerado pelo Cliente);
- **t** - inteiro entre 1 e 9 que representa a carga associada à execução  tarefa dopedido;
- **pid** - identificador de sistema do processo (Cliente  C, no caso do pedido;Servidor S, no caso da resposta);
- **tid** - identificador de sistema Posix do thread (do Cliente C, no caso do pedido; do Servidor S, no caso da resposta)
- **res** - do Servidor, pode ser:
    - o resultado devolvido pela execução da tarefa;
    - o   valor   -1   como   indicação   ao   Cliente   de   que   o   serviço   já   estáencerrado (pelo que o pedido não foi atendido);
- **res** - do Cliente, é sempre o valor -1.
  
## Registo das operações

Diversas   fases   da   operação   dos   programas,   intimamente   associadas   à  expedição   erecepção de mensagens,
devem ser registadas na saída padrão (stdout), através de linhasde texto, emitidas pelo processo apropriado. 
Cada linha terá a seguinte estrutura :

**inst ; i ; t ; pid ; tid ; res ; oper**
  
  - **i**, **t**, **pid**, **tid**, **res** - têm o mesmo significado que os campos correspondentes naestrutura das mensagens;
  - **oper** - são palavras de 5 letras ajustadas às fases da operação que cada processo/thread  acabou   de   executar   e   que   variam   conforme   se   trate   do   Cliente   ou   doServidor:
        - **IWANT** - um thread de pedido do Cliente c1, ..., cn faz pedido inicial
        - **RECVD** - o thread principal s0 do Servidor acusa a recepção de pedido
        - **TSKEX** - um thread produtor do Servidor s1, ..., sn informa que já tem oresultado de tarefa
        - **TSKDN** - o thread consumidor do Servidor sc informa que enviou ao Clienteo resultado de tarefa
        - **GOTRS** - um thread de pedido do Cliente c1, ..., cn acusa a recepção doresultado da execução da tarefa
        - **2LATE**  - o  thread  consumidor do Servidor  sc  informa que o pedido foirejeitado por o serviço já ter encerrado
        - **CLOSD** - um thread de pedido do Cliente c1, ..., cn acusa informação deque o Servidor rejeitou pedido por estar encerrado
        - **GAVUP** - um thread de pedido do Cliente c1, ..., cn informa que não podeesperar mais pela resposta do Servidor, porque o prazo de funcionamento doCliente venceu, e desiste
        - **FAILD**  - o  thread consumidor do Servidor  sc  informa que não consegueresponder a pedido, porque a FIFO privada do thread do cliente fechou, etermina

![image](https://user-images.githubusercontent.com/55672106/116624786-7b813b00-a940-11eb-92d8-6e7d117bf23c.png)


## Ligação das comunicações aos registos

O   diagrama   seguinte   exemplifica   a   ligação   entre   as   mensagens   trocadas   entre 
os processos/threads  e  os registos  efectuados  na  saída padrão   de cada   um.
Cada  setarepresenta uma mensagem emitida por um thread e recebida por outro; o tempo cresce decima para baixo.
Neste exemplo, o Servidor termina a execução antes do Cliente terminar.

Neste exemplo, o thread principal do Cliente c0 gerou três threads de pedidos (c1, c2 ec3).
O primeiro deles envia um pedido ao Servidor pelo FIFO público fifoname e registaesse pedido (IWANT).
O thread principal do Servidor s0 recebe esse pedido e acusa esseevento (RECVD), criando um thread
Quando o  threadc1  do Cliente recebe o resultado daexecução, acusa essa receção (GOTRS).
Quando o pedido de c2 chega ao Servidor, já sedeu o timeout e o pedido já não será atendido, pelo que o thread Produtor s2
não executa atarefa em  B  e coloca um item disso indicativo no armazém (-1). Nesse caso o  threadConsumidor  sc  vai   responder   ao   Cliente   com   o   resultado   -1   e   informa   desse   envio(2LATE);
quando  c2  recebe   essa   mensagem   acusa   a   receção   do   encerramento   doServidor (CLOSD).
Enquanto o thread de pedido c3 espera pela resposta, dá-se o timeoutdo Cliente. 
Nessa altura o  thread  deixa de esperar pela resposta e acusa esse evento(GAVUP).
Vai também fechar o seu FIFO privado, pelo que quando o Servidor tentareventualmente responder vai falhar e acusar essa ocorrência (FAILD).


## Entrega do Trabalho

O projeto foi realizado sempre em conjunto sendo que dessa forma consideramos que cada membro fez 25% do trabalho.
Trabalho realizado por :
- Afonso Monteiro up201907284
- Carlos Gomes up201906622
- Fernando Rego up201905951
- Miguel Amorim up201907756


## Avaliação

A avaliação funcional do programa **xmod** será feita no GNOMO.FE.UP.PT e da forma o mais automática
possível. Pormenores dos testes de verificação (e de avaliação) dos programas submetidos pelos grupos serão
publicados muito em breve.


