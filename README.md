# compressor
Aplicación de consola que permitir comprimir y descomprimir archivos mediante el algoritmo de Huffman realizado para practicar la manipulación de la operaciones de bit

## Ejecución

Generar los archivos de salida

```bash
  make
```

Ejecutar el programa en el directorio donde están los directorios y archivos a evaluar

```bash
  ./compressor <comando> <archivo>
```

## Comprimir archivo

```bash
  ./compressor zip input.txt
```
 Se va a generar un archivo de extensión *.rol* si se quisiera quitar la extensión previa a la compresión se podrían crear rutinas para añadir y leer del archivo.
 
 ## Descomprimir archivo
 
 ```bash
  ./compressor unzip input.txt.rol
```
