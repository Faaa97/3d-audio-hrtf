# 3d-audio-hrtf

Prueba de concepto: Usamos filtros HRTF para sintetizar audio 3D binaural. De esta manera podemos escuchar los sonidos en una localización específica.

Es posible integrarlo a cualquier sistema de sonido que use xAudio2 y xAPOs.

Se puede probar en el programa de ejemplo el funcionamiento de este sintetizador.

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
