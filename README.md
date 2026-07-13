# Proyecto final - Computación de alta performance
### Grupo O - FING UDELAR 2026
### Andrés Montoro 5.169.779-1
### Matías Sención 5.263.989-9

La interacción con el sistema se da a través de consola. Los pasos para ejecutar son
- make
- ./run.sh m params
- make clean (Para limpiar la compilación)


El parámetro "m" es el modo de ejecución: 
1- Ejecuta el algoritmo. Leerá las secuencias por defecto. 
    - params = none
2- Ejecuta el algoritmo. Leerá los archivos con los nombres especificados en /data. 
    - params = name1 name2
3- Ejecuta el algoritmo. Leerá las secuencias recibidas en consola. 
    - params = seq1 seq2
4- Generará una secuencia aleatoria que guardará en la carpeta correspondiente. 
    - params = exponente
5- Muestra todas las secuencias guardadas en el directorio "data". Opcionalmente puede especificarse un subdirectorio
    - params = subdirectorio (opcional)
6- Imprime en consola la secuencia indicada.
    - params = path
7- Elimina la secuencia indicada. 
    - params = path
