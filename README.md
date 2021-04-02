# 3d-audio-hrtf
Añadimos procesamiento de audio 3D a un motor de videojuegos

## Funcionamiento

Para ver el funcionamiento de la librería: [Wiki](https://github.com/alu0100969535/tfg-hrtf-felipe/wiki)

## Desarrollo:

Primero añadir solución a visual studio, abrir xaudio.sln.

Se puede ejecutar en modo debug (lento) o modo release, directamente desde VisualStudio2019

### Ficheros

Hay 3 ficheros:
* xaudio.cpp - Carga xAudio2 e intenta reproducir un fichero de audio.
* myXapo.h - Definición de la clase de procesamiento.
* myXapo.cpp - Métodos de la clase de procesamiento.
* coordinates.h - Funciones de ayuda a conversión entre sistemas de coordenadas.
* filter_data.h - Estructuras para agrupar los datos.
