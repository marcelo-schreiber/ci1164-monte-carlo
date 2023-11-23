#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND ((double)rand() / RAND_MAX) // drand48()
#define SRAND(a) srand(a)                 // srand48(a)

double styblinskiTang(double *x, int order)
{
  double sum = 0.0;
  for (int i = 0; i < order; ++i)
  {
    double x1_squared = x[i] * x[i];
    sum += (x1_squared * x1_squared - 16 * x1_squared + 5 * x[i]);
  }
  return sum / 2.0;
}

// Integral Monte Carlo da função Styblinski-Tang dimensoes variaveis
double monte_carlo(double a, double b, int namostras, int d)
{
  double resultado;
  double soma = 0.0;

  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, d);

  double t_inicial = timestamp();

  /* AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO MÉTODO DE MONTE CARLO */
  double *x = (double *)malloc(sizeof(double) * d);

  for (int i = 0; i < namostras; ++i)
  {
    for (int j = 0; j < d; ++j)
    {
      x[j] = a + (double)NRAND * (b - a);
    }
    soma += styblinskiTang(x, d);
  }

  resultado = soma * (b - a) / namostras;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  free(x);

  return resultado;
}

// sempre 2 dimensoes
double retangulos_xy(double a, double b, int npontos)
{
  double h = (b - a) / npontos;
  double resultado;
  double soma = 0.0;

  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);

  double t_inicial = timestamp();

  /* AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO MÉTODO DOS RETÂNGULOS */

  for (int i = 0; i < npontos; ++i)
  {
    double x = a + i * h;
    for (int j = 0; j < npontos; ++j)
    {
      double y = a + j * h;
      double x1_squared = x*x;
      double x2_squared = y*y;
      soma += ((x1_squared*x1_squared - 16 * x1_squared + 5 * y) + (x2_squared*x2_squared - 16 * x2_squared + 5 * y)) / 2;
    }
  }

  resultado = soma * h * h;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

  return resultado;
}

int main(int argc, char **argv)
{

  if (argc < 5)
  {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int namostras = atoi(argv[3]);
  int d = atoi(argv[4]);

  // INICIAR VALOR DA SEMENTE
  srand(20232);
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  // na função de monte-carlo deve ser testado para 2, 4 e 8 dimensões e 10^7 pontos
  // na função de retângulos deve ser testado para 2 dimensões e 10^7 pontos

  // double monte_carlo_resultado = monte_carlo(a, b, namostras, d);
  double retangulos_resultado = retangulos_xy(a, b, namostras);

  // printf("Resultado Monte Carlo: %f\n", monte_carlo_resultado);
  printf("Resultado Retangulos: %f\n", retangulos_resultado);

  return 0;
}
