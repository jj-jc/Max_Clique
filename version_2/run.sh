
#/usr/bin/sh
prog=GA-test
conf=GAconfig_ejemplo_perms

date > results.txt

for i in  1 2 3 4 5 9 8 8 9 10
do
		echo Executing run $i of $prog with configuration file $conf 
		./$prog >> results.txt
		echo "************************************" >> results.txt
done

