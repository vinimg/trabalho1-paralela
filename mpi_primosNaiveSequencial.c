// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include<time.h>

// int primo(long int n)
// { /* mpi_primos.c  */
// 	int i;

// 	for (i = 3; i < (int)(sqrt(n) + 1); i += 2)
// 	{
// 		if (n % i == 0)
// 			return 0;
// 	}
// 	return 1;
// }

// int main(int argc, char *argv[])
// {
// 	double t_inicial, t_final;
// 	int cont = 0, total = 0;
// 	// int valor = 0;
// 	long int i, n;
// 	int inicio, salto;


// 	if (argc < 2)
// 	{
// 		printf("Valor inválido! Entre com um valor do maior inteiro\n");
// 		return 0;
// 	}
// 	else
// 	{
// 		n = strtol(argv[1], (char **)NULL, 10);
// 	}

// 	/*
// 	Sequencial para calculo do speedup e eficiencia
// 	*/
// 	t_inicial = clock();
// 	inicio = 3;
// 	salto = 2;
// 	for (i = inicio; i <= n; i += salto)
// 	{
// 		if (primo(i) == 1)
// 			cont++;
// 	}


// 	t_final =clock();


// 	total += cont;
// 	total += 1; /* Acrescenta o dois, que também é primo */
// 	printf("Quant. de primos entre 1 e n: %d \n", total);
// 	printf("Tempo de execucao: %1.3f \n", ((t_final - t_inicial)/ CLOCKS_PER_SEC) );
	

// 	return (0);
// }