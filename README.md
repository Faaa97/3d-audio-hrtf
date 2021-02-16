# tfg-videojuegos-felipe
Añadimos procesamiento de audio 3D a un motor de videojuegos

## Funcionamiento

Primero añadir solución a visual studio, abrir xaudio.sln.

Se puede ejecutar en modo debug (lento) o modo release, directamente desde VisualStudio2019

## Ficheros

Hay 3 ficheros:
* xaudio.cpp - Carga xAudio2 e intenta reproducir un fichero de audio
* myXapo.h - Definición de la clase de procesamiento
* myXapo.cpp - Métodos de la clase de procesamiento


## TODO:

* Implementar método overlap-add
* Estrucuturar mejor los métodos de procesamiento, en un nuevo fichero.
* Cargar los filtros que quuedan en xaudio.cpp
* Quitar código innecesario

## Hecho:

* ~~Subir al repositorio muestras de audio para probar.~~
* ~~Reparar solución VS2019~~
* ~~Mover la carga de los filtros de myXapo.cpp a xaudio.cpp~~

