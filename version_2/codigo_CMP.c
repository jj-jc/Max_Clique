
/* Ejercicio 2 de Inteligencia Artificial */

/* Resolución del problema de máximo clique mediante algoritmos evolutivos */

/* Autores:
	    Álvaro Benito Oliva
	    Germán Andrés Di Fonzo Caturegli
	    Juan José Jurado Camino */

/* Includes */

#include "libGA_ALL/ga.h"
#define Configuration_PATH  "/home/juanjo/practica2_ia_cmp/version_2/Archivos_Config/GAconfig_ejemplo_bits"
#define Instances_PATH "/home/juanjo/practica2_ia_cmp/version_2/Instances/Toy4.clq.txt"
/* Declaración de funciones */
#define N 100
int obj_fun();
int read_instance();
void print_graph();
int **graph;
/* Función principal */

int main() 
{
  graph=read_instance(Instances_PATH);  //  Nombre de la instancia
  // printf(graph);
  GA_Info_Ptr ga_info;
  int i;
  /* Inicializar el agoritmo genético */
  ga_info = GA_config(Configuration_PATH, obj_fun);

  /* Ejecutar el algoritmo genético */
  GA_run(ga_info);
  printf("\nBest chrom:  ");
  for(i=0;i<ga_info->chrom_len;i++)
      printf("%5.4f  ",ga_info->best->gene[i]);

  printf("   (fitness: %g)\n\n",ga_info->best->fitness);

}

/* Definición de funciones */

int obj_fun(Chrom_Ptr chrom) 
{
  int i; 
  double val = 0.0;
  
  /*Función fitness*/

  for(i = 0; i < chrom->length; i++)
    {        
      val +=  chrom->gene[i];
    }
  



  chrom->fitness = val;
  
  return 0;
  
}


// read DIMACS format
int read_instance(char *filename)
{
  char dummy1;
  char dummy2[100];
  int dummy3;
  int n1,n2;
  FILE *inputf;
  int i,j;

  int nnodes = 0;
  int nedges = 0;

  
  if( (inputf=fopen(filename,"rt")) == NULL )
    {
      printf( "Cannot open file %s\n",filename);
      exit(-1);
    }

  // lee la cabecera
  fscanf(inputf,"%c %s %d %d\n",&dummy1,dummy2,&nnodes,&nedges);
  
  printf("Opening %s (%d nodes, %d edges)\n",filename,nnodes,nedges);


  //Se crea y se inicializan a ceros la matriz de adyacencia
  int graph[nnodes][nnodes];
  for(i=0;i<nnodes;i++)
    for(j=0;j<nnodes;j++)
      graph[i][j] = 0;

  // salta la lista de nodos
  for(i=0;i<nnodes;i++)
    fscanf(inputf,"%c  %d %d\n",&dummy1,&dummy3,&dummy3);

  // lee los edges
  for(i=0;i<nedges;i++)
    {
      fscanf(inputf,"%c %d %d\n",&dummy1,&n1,&n2);
      graph[n1-1][n2-1] = 1;  // ojo que los vectores en C empiezan desde 0
      graph[n2-1][n1-1] = 1;
    }
  
  fclose(inputf);
  return &graph;
}

void print_graph(int **graph){

  for(int i=0;i<1;i++){
    for(int j=0;j<1;j++){
      printf("%d ",graph[i][j]);
    }
    printf("\n");
  }
}
