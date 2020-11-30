
/* Inteligencia Artificial */

/* Ejercicio 2 */

/* Resolución del problema de máximo clique mediante algoritmos evolutivos */

/* Autores:
	    Álvaro Benito Oliva
	    Germán Andrés Di Fonzo Caturegli
	    Juan José Jurado Camino */

/* Librería */

#include "libGA_ALL/ga.h"

/* Macros */

#define MAX_NODOS 500

/* Variables globales */

char graph[MAX_NODOS][MAX_NODOS];  // matriz de adyacencia
int nnodes, nedges;

/* Declaración de funciones */

int obj_fun(Chrom_Ptr); // función pare calcular el fitness
int read_instance(); // función para leer el contenido de las instancias

/* Función principal */

int main() {

   GA_Info_Ptr ga_info;
   int i;

   /* Se rellena la matriz "graph" con los datos del fichero y se inicializa nnodes y nedges */
   
   read_instance("Instances/MANN_a9.clq.txt");  //  Se pasa el nombre del archivo de la instancia

   /* Se inicializar el agoritmo genético */

   ga_info = GA_config("Archivos_Config/GAconfig_MANN_a9", obj_fun);

   /* Se cambia la longitud del chromosoma con la info del fichero*/

   ga_info->chrom_len = nnodes;

   /* Se ejecuta el algoritmo genético */

   GA_run(ga_info);

   printf("\nBest chrom:  ");
   for(i=0;i<ga_info->chrom_len;i++)
      printf("%5.4f  ",ga_info->best->gene[i]);
   
   printf("   (fitness: %g)\n\n",ga_info->best->fitness);

}

/* Definición de funciones */

int read_instance(char *filename) {

  char dummy1;
  char dummy2[100];
  int dummy3;
  int n1,n2;
  FILE *inputf;
  int i,j;
  
  
  nnodes = 0;
  nedges = 0;
  
  if( (inputf=fopen(filename,"rt")) == NULL )
    {
      printf( "Cannot open file %s\n",filename);
      exit(-1);
    }

  // Se lee la cabecera
  fscanf(inputf,"%c %s %d %d\n",&dummy1,dummy2,&nnodes,&nedges);
  
  printf("Opening %s (%d nodes, %d edges)\n",filename,nnodes,nedges);
   
  for(i=0;i<MAX_NODOS;i++)
    for(j=0;j<MAX_NODOS;j++)
      graph[i][j] = 0;

  // Se lee la lista de nodos
  for(i=0;i<nnodes;i++)
    fscanf(inputf,"%c  %d %d\n",&dummy1,&dummy3,&dummy3);

  // Se leen las aristas
  for(i=0;i<nedges;i++)
    {
      fscanf(inputf,"%c %d %d\n",&dummy1,&n1,&n2);
      graph[n1-1][n2-1] = 1;  
      graph[n2-1][n1-1] = 1;
    }
  
  fclose(inputf);
  
}

int obj_fun(Chrom_Ptr chrom) {

   int i, j; 
   int N = 0; // Numero de nodos del sub-grafo
   int A = 0; // Numero de aristas del sub-grafo
   int aristas_clique; // Numero de aristas que debe haber en el sub-grafo para que sea un clique

   /* Se halla el número de nodos del sub-grafo escogido y se almacena en la variable 'N' */
  
   for(i = 0; i < chrom->length; i++) {        
      if (chrom->gene[i] == 1)     
         N++;
   }

   /* Para cada pareja de nodos del sub-grafo se comprueba si hay arista entre ellos */

   for(i = 0; i < chrom->length; i++) {        
      if (chrom->gene[i] == 1) {
         for(j = i; j < chrom->length; j++) {
            if ((chrom->gene[j] == 1)&&(graph[i][j] == 1))
               A++;
         }
      }    
   }

   /* Se calcula el número de aristas que debe tener un clique de 'N' nodos */

   aristas_clique = N*(N-1)/2;

   /* Se calcula la fitness del chromosoma */

   if (aristas_clique != A) // Se penalizan los que no son cliques
      //chrom->fitness = 0; // solo vale para toy4, toy6 y toy8
      chrom->fitness = 0.5*(N - (aristas_clique - A)); // vale para MANN_a9 también
   else
      chrom->fitness = N - (aristas_clique - A); // Cuanto mayor es la fitness mejor es el chromosoma
  
   return 0;
  
}

