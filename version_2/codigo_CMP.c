
/* Ejercicio 2 de Inteligencia Artificial */

/* Resolución del problema de máximo clique mediante algoritmos evolutivos */

/* Autores:
	    Álvaro Benito Oliva
	    Germán Andrés Di Fonzo Caturegli
	    Juan José Jurado Camino */

/* Includes */

#include "libGA_ALL/ga.h"

/* De claración de funciones */

int obj_fun();

/* Función principal */

int main() 
{
   GA_Info_Ptr ga_info;
   int i;

   /* Inicializar el agoritmo genético */

   ga_info = GA_config("Archivos_Config/GAconfig_ejemplo_bits", obj_fun);

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
  
  for(i = 0; i < chrom->length; i++)
    {        
      val +=  chrom->gene[i];
    }
  
  chrom->fitness = val;
  
  return 0;
  
}

