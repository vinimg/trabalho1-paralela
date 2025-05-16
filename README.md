# trabalho1-paralela
Primeiro Trabalho Laboratório Paralela

# Run instructions

## build
./build.sh build
## clean
./build.sh clean
## run
./run_bench.sh

# Proposta:
Execute os dois programas de Cálculo de Números Primos (Naive e Bag of Tasks), usando as seguintes instruções de comunicação de envio ponto-a- ponto:

MPI_Send <br />
MPI_Isend <br />
MPI_Rsend <br />
MPI_Bsend <br />
MPI_Ssend <br />

Combinando com as operações de  MPI_Recv ou MPI_Irecv, sempre que possível.

1. Casos Naive (10 combinações)

(5 modos de envio × 2 modos de recebimento)

    MPI_Send + MPI_Recv

    MPI_Send + MPI_Irecv

    MPI_Isend + MPI_Recv

    MPI_Isend + MPI_Irecv

    MPI_Rsend + MPI_Recv

    MPI_Rsend + MPI_Irecv

    MPI_Bsend + MPI_Recv

    MPI_Bsend + MPI_Irecv

    MPI_Ssend + MPI_Recv

    MPI_Ssend + MPI_Irecv

2. Casos Bag-of-Tasks (9 combinações)

(neste código omitimos MPI_Bsend+MPI_Irecv, seja por falta de buffer-attach ou porque não é garantido que o Irecv já esteja postado)

    MPI_Send + MPI_Recv

    MPI_Send + MPI_Irecv

    MPI_Isend + MPI_Recv

    MPI_Isend + MPI_Irecv

    MPI_Rsend + MPI_Recv

    MPI_Rsend + MPI_Irecv

    MPI_Ssend + MPI_Recv

    MPI_Ssend + MPI_Irecv

    MPI_Bsend + MPI_Recv

 <br />  <br />
Código Base para o Naive: https://github.com/gpsilva2003/MPI/blob/main/src/mpi_primos.c  <br />  <br />
Código Base para o Bag:  https://github.com/gpsilva2003/MPI/blob/main/src/mpi_primosbag.c  <br />

# Relatório

# Slides