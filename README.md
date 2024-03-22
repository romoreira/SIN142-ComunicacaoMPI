# SIN142 - Sistemas Distribuídos
## Comunicação de Processos Massaging Passing Interface (MPI) :musical_note:

### Objetivos :globe_with_meridians:

Nesta aula prática de MPI (Message Passing Interface), os alunos aprenderão os fundamentos da programação paralela e distribuída, incluindo comunicação entre processos, divisão de tarefas e otimização de desempenho em sistemas distribuídos. O objetivo é capacitá-los a desenvolver e otimizar programas paralelos utilizando o MPI para melhorar a eficiência e escalabilidade de suas aplicações distribuídas.

## Antes de Começar: :earth_americas:

* Saber o endereço IP das máquinas envolvidas na programação distribuída.
    - IPs: [192.168.1.1](#), [192.168.1.2](#), [192.168.1.3](#)
* Configurar o SSH Pass

## Configuração do Ambiente :cloud:

* `sudo apt-get update` 
* `sudo apt-get install gcc make mpich`
* Configurando o arquivo `/etc/hosts` ele deve estar configurado (nas duas máquinas) com o mapeamento estático do IP <-> Host como no [arquivo](https://github.com/romoreira/SIN142-ComunicacaoMPI/blob/3a174287412ab2dd2a273971efc3d9306fe7cd57/hosts).

## Configuração do SSH Pass :hammer:

* `ssh-keygen -t rsa -b 4096 -C "email@example.com" -f ~/.ssh/id_rsa`
* `ssh-copy-id -i ~/.ssh/id_rsa.pub ubuntu@<IP_REMOTO>`
* `ssh ubuntu@<IP_REMOTO>`
* `sudo vim /etc/hosts` Adicionar aqui os hosts que estarão envolvidos no processamento distribuído.
* `ssh ubuntu@<IP_REMOTO>`
* `ping <IP_REMOTO>`
* `ssh ubuntu@HOSTNAME`

  >  `Neste ponto as conexões SSHs entre os hosts deverão estar funcionando sem prompt de senha.`

## Configuração do Programa Distribuído com MPI :clipboard:

* `git clone https://github.com/romoreira/SIN142-ComunicacaoMPI.git`
* `cd SIN142-ComunicacaoMPI`
* `which mpicc`
* `export MPICC=/usr/bin/mpicc`
* `export MPI_HOSTS=host_file` Deverão estar listados todos os hosts do cluster como neste [arquivo](https://github.com/romoreira/SIN142-ComunicacaoMPI/blob/309c9dcbaca34aa8ae3fe6cbdfbb312d47d82227/host_file).
* `mpicc -o mpi_hello_world mpi_hello_world.c` Neste ponto o arquivo executável do mpi_hello_world deverá estar disponível no diretório e pronto para execução.

## Execução e Testes :notebook_with_decorative_cover:

* Para executar utilize: `mpirun -n 2 -f host_file ./mpi_hello_world`
* Você deverá observar a saída, onde cada host (distribuído) executou sua instância e devolveu o resultado.

## Proposição de Estudo/Desafio Extra :trollface:

1. Proponha que os processos distribuídos façam operações matemáticas e devolvam o resultado.
2. Proponha um algoritmo de ordenação distribuído (Mergesort). Valide se o programa no [arquivo](https://github.com/romoreira/SIN142-ComunicacaoMPI/blob/6e648670a7f800655e89e3a017ab8e45a7dbf323/merge_distribuido_exemplo.c) funciona para esse propósito.
