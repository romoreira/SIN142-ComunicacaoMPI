# SIN142 Comunicação de Processos - Massaging Passing Interface (MPI)

## Nesta aula prática, vamos utilizar duas máquinas UBUNTU.

## Antes de Começar:

* Saber o endereço IP das duas máquinas.
    - IPS: [List]
* Configurar o SSH Pass

## Configuração do Ambiente

* `sudo apt-get update` 
* `sudo apt-get install gcc make mpich`

## Configuração do SSH Pass:

* `ssh-keygen -t rsa -b 4096 -C "seu_email@example.com" -f ~/.ssh/<nome_chave>`
* `ssh-keygen -t rsa -b 4096 -C "email@example.com" -f ~/.ssh/id_rsa`
* `ssh-copy-id -i ~/.ssh/id_rsa.pub ubuntu@<IP_REMOTO>`
* `ssh ubuntu@<IP_REMOTO>`
* `sudo vim /etc/hosts` Adicionar aqui os hosts que estarão envolvidos no processamento distribuído.
* `ssh ubuntu@<IP_REMOTO>`
* `ping <IP_REMOTO>`
* `ssh ubuntu@HOSTNAME`

  >  `Neste ponto as conexões SSHs entre os hosts deverão estar funcionando sem prompt de senha.`

## Passos - Configurando o Programa Distribuído com MPI

* `git clone https://github.com/romoreira/SIN142-ComunicacaoMPI.git`
* `cd SIN142-ComunicacaoMPI`
* `which mpicc`
* `export MPICC=/usr/bin/mpicc`
* `export MPI_HOSTS=host_file` Deverão estar listados todos os hosts do cluster como neste [arquivo](https://github.com/romoreira/SIN142-ComunicacaoMPI/blob/309c9dcbaca34aa8ae3fe6cbdfbb312d47d82227/host_file).

* `mpicc -o mpi_hello_world mpi_hello_world.c`
