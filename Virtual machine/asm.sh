echo "Enter the File name: "
read filename

gcc pass1.c -o pass1.out

./pass1.out "$filename"

if [ $? -ne 0 ]; then
	echo "Error: pass1.out encountered an error. Stopping assembly."
	exit 1
fi

gcc pass2.c -o pass2.out
./pass2.out

if [ $? -ne 0 ]; then
	echo "Error: pass2.out encountered an error. Stopping assembly."
	exit 1
else 
	echo "Assembly completed!"
fi



echo "Starting Virtual machine"
gcc vm.c -o vm.out
./vm.out
echo "Virtual machine stopped"
