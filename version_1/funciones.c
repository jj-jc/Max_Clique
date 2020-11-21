

// PONER ESTO ANTES DEL MAIN (VAR GLOBALES)

/* Global Variables*/
char graph[500][500];  // se podría optimizar usando malloc...
int nnodes, nedges;

/* function prototypes */
int obj_fun(Chrom_Ptr);
int read_instance();


/******************************************************************/
/******************************************************************/

// PONER ESTO EN EL MAIN 


// Rellena la matriz "graph" con los datos del fichero
// Tb. inicializa nnodes y nedges
read_instance("Toy4.clq.txt");  //  Nombre de la instancia
  
// IMPORTANTE: se puede cambiar la longitud del chromosoma con la
//             info del fichero (despues de llamar GA_config(...)  )
ga_info->chrom_len = nnodes;


/******************************************************************/
/******************************************************************/




// read DIMACS format
int read_instance(char *filename)
{
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

  // lee la cabecera
  fscanf(inputf,"%c %s %d %d\n",&dummy1,dummy2,&nnodes,&nedges);
  
  printf("Opening %s (%d nodes, %d edges)\n",filename,nnodes,nedges);
   
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
  
}


