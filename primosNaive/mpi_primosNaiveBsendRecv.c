#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>

int primo(long int n) {
    int i;

    for (i = 3; i < (int)(sqrt(n) + 1); i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    double t_inicial, t_final;
    int cont = 0, total = 0;
    int valor = 0;
    long int i, n;
    int meu_ranque, num_procs, inicio, salto;
    int etiq = 0;
    int raiz = 0;
    // MPI_Request pedido_envia;
    MPI_Request pedido_recebe;
    MPI_Status estado;
    void* buffer;
    int tamanho_buffer;

    if (argc < 2) {
        printf("Valor inválido! Entre com um valor do maior inteiro\n");
        return 0;
    } else {
        n = strtol(argv[1], (char **)NULL, 10);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Aloca buffer para BSend
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &tamanho_buffer);
    tamanho_buffer += MPI_BSEND_OVERHEAD;
    buffer = malloc(tamanho_buffer);
    MPI_Buffer_attach(buffer, tamanho_buffer);

    t_inicial = MPI_Wtime();
    inicio = 3 + meu_ranque * 2;
    salto = num_procs * 2;
    
    for (i = inicio; i <= n; i += salto) {
        if (primo(i) == 1)
            cont++;
    }

    if (meu_ranque != 0) {
        // Envia de forma não bloqueante usando BSend
        MPI_Bsend(&cont, 1, MPI_INT, raiz, etiq, MPI_COMM_WORLD);
    } else {
        for (int origem = 1; origem < num_procs; origem++) {
            // Recebe de forma não bloqueante
            MPI_Irecv(&valor, 1, MPI_INT, origem, etiq, MPI_COMM_WORLD, &pedido_recebe);
            // Espera o recebimento completar
            MPI_Wait(&pedido_recebe, &estado);
            total += valor;
        }
    }

    t_final = MPI_Wtime();

    if (meu_ranque == 0) {
        total += cont;
        total += 1; // Acrescenta o dois, que também é primo
        printf("Quant. de primos entre 1 e n: %d \n", total);
        printf("Tempo de execucao: %1.3f \n", t_final - t_inicial);
    }

    // Desanexa o buffer antes de finalizar
    MPI_Buffer_detach(&buffer, &tamanho_buffer);
    free(buffer);
    
    MPI_Finalize();
    return 0;
}