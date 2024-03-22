# SIN142 Comunicação de Processos - Massaging Passing Interface (MPI)

## Nesta aula prática, vamos utilizar duas máquinas UBUNTU.

## Antes de Começar:

* Saber o endereço IP das duas máquinas.
    - IPS: [List]
* Configurar o SSH Pass

## Passos:

sudo apt-get update
sudo apt-get install gcc make mpich
ssh-keygen -t rsa -b 4096 -C "seu_email@example.com" -f ~/.ssh/<nome_chave>
ssh-keygen -t rsa -b 4096 -C "email@example.com" -f ~/.ssh/id_rsa
ssh-copy-id -i ~/.ssh/id_rsa.pub ubuntu@<IP_REMOTO>
ssh ubuntu@10.0.0.4
sudo vim /etc/hosts
ssh ubuntu@<IP_REMOTO>
ping <IP_REMOTO>
ssh ubuntu@HOSTNAME
git clone https://github.com/romoreira/SIN142-ComunicacaoMPI.git
ls
cd mpitutorial/tutorials/mpi-hello-world/
ls
cd code/
ls
which mpi
which mpicc
export MPICC=/usr/bin/mpicc
mpicc -o mpi_hello_world mpi_hello_world.c
