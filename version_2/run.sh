#Un script shell es un archivo de texto que contiene los comandos 
#Unix/Linux internos o externos así como las palabras claves del shell.

#Basta con cambiar el archivo de results para que se creen los resultados de cada instancia 
#/usr/bin/sh
prog=mi_programa
conf=GAconfig_hamming6-2
results=./Results/results_hamming6-2.txt


date > $results

for i in  1 2 3 4 5 6 7 8 9 10
do
		echo "************************************Start rep. $i************************************" >> $results
		echo Executing run $i of $prog with configuration file $conf 
		./$prog >> $results
		echo "************************************Finish rep. $i************************************" >> $results
done

