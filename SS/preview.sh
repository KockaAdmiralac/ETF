while :
do
    gcc -c "$1.c" -o "$1.o" -fno-stack-protector
    objdump -drwC -Mintel "$1.o"
    rm "$1.o"
    sleep 1s
    clear
done
