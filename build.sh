for dotc_file in ./src/*.c; do
  clang -g -fPIC -c "$dotc_file" -I./include/ -I./src/ -o "$dotc_file.o"
done

doto_files=""

for doto_file in ./src/*.c.o; do
  doto_files="${doto_files} ${doto_file}"
done

ar rcs bin/libxpandarray.a $doto_files
clang -g -shared -o bin/libxpandarray.so $doto_files
 
clang -g -o bin/program program/program.c -I./include -L./bin -l:libxpandarray.a

rm ./src/*.c.o
