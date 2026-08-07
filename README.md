# Proyecto final - Computación de alta performance
##### Andrés Montoro 5.169.779-1, Matías Sención 5.263.989-9
### Grupo O - FING UDELAR 2026

La interacción con el sistema se da a través de consola. Los pasos para ejecutar son
- make BLOCK_SIZE=n (largo y ancho de los bloques)
- ./hpc_run.sh m params (o seq_run.sh para correr el secuencial)
- make clean (Para limpiar la compilación)

El parámetro "m" es el modo de ejecución: 

1- Ejecuta el algoritmo. Leerá las secuencias por defecto. params = none

2- Ejecuta el algoritmo. Leerá los archivos con los nombres especificados en /data. params = name1 name2

3- Generará una secuencia aleatoria que guardará en la carpeta correspondiente. params = largo

4- Muestra todas las secuencias guardadas en el directorio "data". Opcionalmente puede especificarse un subdirectorio. params = subdirectorio (opcional)

5- Imprime en consola la secuencia indicada. params = path



Por ejemplo:

make clean

make BLOCK_SIZE=1000

./hpc_run.sh 2 data/small/default_seq1 data/small/default_seq2

En caso de que se desee restablecer una ejecución que se vio interrumpida, ejecutar

./hpc_run.sh 2 {seq_path1} {seq_path2} --resume


Otras consideraciones:

- En el header primitives.h hay opciones de configuración del algoritmo, particularmente relacionados a la función de recompensa.

- En los archivos run.sh (paralelo o secuencial) hay variables para determinar hiperparámetros de ejecución: cantidad de esclavos y archivo con hosts.

- La alineación obtenida se puede ver en los archivos data/temp/matched_seq1 y data/temp/matched_seq2