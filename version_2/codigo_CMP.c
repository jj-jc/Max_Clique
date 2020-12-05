
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

// #define MAX_NODOS 500

/* Variables globales */

int **pgraph=NULL;


// char graph[MAX_NODOS][MAX_NODOS];  // matriz de adyacencia
int nnodes, nedges;

/* Declaración de funciones */

int obj_fun(Chrom_Ptr); // función pare calcular el fitness
int read_instance(); // función para leer el contenido de las instancias
int print_chrom_nodes(GA_Info_Ptr);
int obj_fun_aristas(Chrom_Ptr);
/* Función principal */

int main() {

   GA_Info_Ptr ga_info;
   int i;

   /* Se rellena la matriz "graph" con los datos del fichero y se inicializa nnodes y nedges */
   // read_instance("Instances/keller4.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/san200_0.7_1.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/p_hat500-2.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/p_hat500-1.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/p_hat300-2.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   read_instance("Instances/p_hat300-1.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/johnson8-4-4.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/johnson8-2-4.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/hamming6-4.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/hamming6-2.clq.txt");  //  Se pasa el nombre del archivo de la instancia
   // read_instance("Instances/Toy4.clq.txt");

   /* Se inicializa el agoritmo genético */
   // ga_info = GA_config("Archivos_Config/GAconfig_keller4", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_p_san200_0.7_1", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_p_hat500-2", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_p_hat500-1", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_p_hat300-2", obj_fun_aristas);
   ga_info = GA_config("Archivos_Config/GAconfig_p_hat300-1", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_johnson8-4-4", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_johnson8-2-4", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_hamming6-4", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_hamming6-2", obj_fun_aristas);
   // ga_info = GA_config("Archivos_Config/GAconfig_Toy4", obj_fun_aristas);

   /* Se cambia la longitud del chromosoma con la info del fichero*/

   ga_info->chrom_len = nnodes;

   /* Se ejecuta el algoritmo genético */

   GA_run(ga_info);



   printf("\nBest chrom:  ");
   for(i=0;i<ga_info->chrom_len;i++)
      printf("%5.4f  ",ga_info->best->gene[i]);
   
   printf("\n(fitness: %g)\n\n",ga_info->best->fitness);
   print_chrom_nodes(ga_info);

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
   

   pgraph=malloc(nnodes*sizeof(int*));
   for(int i=0;i<nnodes;i++){
      pgraph[i]=malloc(nnodes*sizeof(int));
   }
   if(pgraph==NULL){
      printf("Error at malloc function\n");
      return 0;
   }else{printf("Malloc function ok\n");}


  for(i=0;i<nnodes;i++)
    for(j=0;j<nnodes;j++)
      pgraph[i][j] = 0;

  // Se lee la lista de nodos
  for(i=0;i<nnodes;i++)
    fscanf(inputf,"%c  %d %d\n",&dummy1,&dummy3,&dummy3);

  // Se leen las aristas
  for(i=0;i<nedges;i++)
    {
      fscanf(inputf,"%c %d %d\n",&dummy1,&n1,&n2);
      pgraph[n1-1][n2-1] = 1;  
      pgraph[n2-1][n1-1] = 1;
    }
  
  fclose(inputf);
  
}

int print_chrom_nodes(GA_Info_Ptr info){
   int n_nodes_gene=0;
   printf("\nNumber of nodes: ");
   for(int i =0;i<info->chrom_len;i++)
      if(info->best->gene[i]==1){
         printf("%d ",i);
         n_nodes_gene++;
      }
   printf("[%d]\n\n ",n_nodes_gene);
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
            if ((chrom->gene[j] == 1)&&(pgraph[i][j] == 1))
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
int obj_fun_aristas(Chrom_Ptr chrom) {
   int i, j; 
   int N = 0; // Numero de nodos del sub-grafo
   int A = 0; // Numero de aristas del sub-grafo
   int aristas_clique=0; // Numero de aristas que debe haber en el sub-grafo para que sea un clique
   int densidad_aristas=0;
   // int nvertices=0;
   // int naristas=0;
   /* Se halla el número de nodos del sub-grafo escogido y se almacena en la variable 'N' */
  
   // nvertices=nnodes;
   // naristas=nedges;
   for(i = 0; i < chrom->length; i++) {        
      if (chrom->gene[i] == 1)     
         N++;
   }

   /* Para cada pareja de nodos del sub-grafo se comprueba si hay arista entre ellos */
   for(i = 0; i < chrom->length; i++) {        
      if (chrom->gene[i] == 1) {
         for(j = i; j < chrom->length; j++) {
            if ((chrom->gene[j] == 1)&&(pgraph[i][j] == 1))
               A++;
         }
      }    
   }

   /* Se calcula el número de aristas que debe tener un clique de 'N' nodos */
   aristas_clique = N*(N-1)/2;
   densidad_aristas=nedges/(nnodes*(nnodes-1)/2);
   if (aristas_clique==A){
      chrom->fitness = 100*N;//Trato de benificiar mucho más a los cliques que a los que no lo son.
   }else{
      chrom->fitness = (densidad_aristas*(100*N/nnodes)+2*(100*(aristas_clique - A)/aristas_clique)-0.9*(100*(aristas_clique - A)/nedges))/(N);
   }
   return 0;
}
