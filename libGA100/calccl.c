
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
/*#include <timers.h>*/


/* prototipi di funzione */

double U_iniz(int n);
double supporto(double *u,int *pesi,int n);
double calcola_u(double *q,double *old_u,int n);
void  Max(double *u,int *pesi,int n);
void init_relax_net();
 
double *q,*u,*old_u;
double norma;
FILE *output, *input;
int n,*mat;
int num_iter=0,arcs=0;




main( int argc,char **argv )
{
  init_relax_net();
}




relax()
{
  do
    {
      supporto(u,mat,n);
      calcola_u(q,u,n);
      num_iter=num_iter+1;
      
    }while ( norma > (double)1e-10);
}



void init_relax_net()
     
{
  
  
  int h,k;

  /*int t1,t2;*/
  
  /* Apertura e lettura del file di input 
  
  if( argc!=3 )
    {
      printf( "\nUso: clique <input_file> <output_file>\n\n" );
      exit(1);
      } */


  if( (input=fopen("toy10","rt")) == NULL )  /*argv[1]*/
    {
      printf( "Impossibile aprire il file %s\n","argv[1]");
      exit(1);
    }
  
  /* lettura della dimensione del grafo in input */
  
  fscanf(input,"%d",&n);
  
  
  /* allocazione e controllo delle strutture del programma   */
  
  
  if ( (u=(double *) malloc(n*sizeof(double))) == NULL )
    {
      printf( "Impossibile allocare il vettore U \n" );
      exit(1);
    }
  
  if ( (old_u= (double *) malloc(n*sizeof(double)))  == NULL )
    {
      printf( "Impossibile allocare il vettore OLD_U\n" );
      exit(1);
    }
  
  if ( (q= (double *) malloc(n*sizeof(double))) == NULL )
    {
      printf( "Impossibile allocare il vettore Q \n" );
      exit(1);
    }
  
  
  /* allocazione,controllo e caricamento della matrice di input  */
  
  
  if ( (mat=(int*)malloc(n*n*sizeof(int))) == NULL )
    {
      printf( "Impossibile allocare la matrice\n" );
      exit(1);
    }
  
  for ( h=0;h<n;h++ )
    for (k=0;k<n;k++)
      {
	fscanf(input,"%d",&(mat[h*n+k]));
	arcs+=mat[h*n+k];
      }

  
  /* apertura in scrittura del file di output *********/
  
  if( (output=fopen("zzz","wt")) == NULL ) /*argv[2]*/
    {
      printf( "Impossibile aprire il file %s\n","argv[2]");
      exit(1);
    }
  
  
  
  fprintf(output,"Input file: %s\n ","argv[1]");
  fprintf(output,"%d nodi, %d archi, la densita' e' %5.2f\n",n,arcs,arcs/(float)(n*n));


 
  U_iniz(n);
  
  fclose(input);


  relax();
  
     
  
/* stampa del vettore su file di output ********************/

 
  fprintf(output,"\nU finale:\t [ ");

  for (h=0;h<n;h++)
    fprintf(output,"%.4f ",u[h]);
  fprintf(output,"]\n");

  fprintf(output,"Iterazioni:\t %d\n",num_iter);
  /*  fprintf(output,"Tempo:\t\t %d\n",t2-t1);*/

  Max(u,mat,n);

  fclose(output);

}




/* calcolo del vettore iniziale ******************************************/

double U_iniz(int n)
{
  int i;
  float tmp;
  
  for (i=0;i<n;i++)
    {
      fscanf(input,"%f",&tmp);
      u[i]=(double)tmp;
    }
  
  fprintf(output,"U iniz. = [");
  for (i=0;i<n;i++)
    {
      fprintf(output,"%5.2f ",u[i]);
    }
  fprintf(output,"]\n");
  return(*u);
}


/* calcolo del supporto Q *************************************************/

double supporto(double *u,int *pesi,int n)
{
  int i,j;
  double somma;

  for (i=0;i<n;i++)
  {
     somma=0.0;
     for (j=0;j<n;j++)
	somma=somma+(pesi[i*n+j]*u[j]);
     q[i]=somma;
  }

  return(*q);
}


/* calcolo del nuovo valore di U ******************************************/


double calcola_u(double *q,double *old_u,int n)
{
  double somma,*old;
  double som;
  int i;


     if( (old=(double*)malloc(n*sizeof(double))) == NULL )
	{
	  printf( "Impossibile allocare il vettore OLD\n" );
	  exit(1);
	}
  memcpy(old,old_u,n*sizeof(double));
  somma=0.0;

  for (i=0;i<n;i++)
    somma=somma+(old_u[i]*q[i]);

  for (i=0;i<n;i++)
    u[i]=(old_u[i]*q[i])/somma;

/* Calcolo della norma vettoriale 2 applicata al nuovo vettore u */
/* e al vecchio vettore old                                      */

  som=0.0;
  for (i=0; i<n; i++)
    {
	som=som+(pow(fabs(u[i]-old[i]),2));
    }
    norma = (som);

    free(old);
    return(*u,norma);
}

/* calcolo del massimo *************************************************/

void Max(double *v,int *pesi,int n)
{
   int i,j;
   double aux,max,max1=0.0,max2;
   double *prod;

   prod=(double *) malloc(n*sizeof(double));

   for (j=0;j<n;j++)
   {
     aux=0.00;
     for (i=0;i<n;i++)
     {
       aux=aux+((pesi[i*n+j])*(v[i]));
       prod[j]=aux;
     }
   }
  for (i=0;i<n;i++)
  {
    max1=max1+(v[i]*prod[i]);
    max2=max1;
  }

  max2=(max2/2.0);
  fprintf(output,"ALFA:\t\t %f\n",max2);
  max=1/(1-(2*max2));
  fprintf(output,"K:\t\t %f\n",max);
}

       
