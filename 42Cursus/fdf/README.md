# Fdf 🗺️
**Fdf** es un proyecto que transforma un archivo con datos de elevación en una representación gráfica 3D de un mapa de líneas (wireframe), usando la biblioteca gráfica **MLX42**. El objetivo es desarrollar habilidades en gráficos en 2D/3D, manejo de eventos y estructuras de datos.

## Funcionamiento ⚙️
El programa se ejecuta con la siguiente sintaxis:

bash
Copiar
Editar
./fdf archivo.fdf
archivo.fdf: Es un archivo de texto que contiene coordenadas de elevación en una grilla. Cada número representa la altura (z) de un punto en el mapa.

### ¿Qué hace el programa?
1. Lee el archivo `.fdf` y genera una matriz de puntos con sus coordenadas (x, y, z).

2. Calcula las proyecciones isométricas o en perspectiva.

3. Dibuja las líneas que unen los puntos, generando un modelo 3D en una ventana gráfica.

4. Permite interacción con el usuario mediante teclado y mouse para mover, rotar y hacer zoom en el mapa.

## Controles 🕹️
| Tecla / Acción  | Función														 			|
|-------|-----------------------------------------------------------------------------------|
| **Flechas** | Mover el mapa.       													|
| **+ / -** | Zoom in / Zoom out.											|
| **Scroll del mouse** | Zoom in / Zoom out (alternativo).								|
| **Clic izquierdo** | Mover el mapa.																	|
| **Clic derecho** | Rotar el mapa.																	|
| **ESC** | Cierra el programa.               											|
| **A** | Cambio proyección isometrica / persectiva.               											|
| **C** | Cambio gama de colores.               											|
| **Barra espaciadora** | Reinicio vista.               											|

Todos los eventos están manejados usando los hooks de MLX42.

## Ejemplo de archivo `.fdf` 📁
```c
0 0 0 0 0
0 1 2 1 0
0 2 4 2 0
0 1 2 1 0
0 0 0 0 0
```
Cada número representa la altitud del punto. El resultado es un mapa tridimensional donde los picos y valles se muestran visualmente.

## Bonus ⭐️
Además de la funcionalidad básica, el programa incluye:

◦ Cambio de colores según la altura del terreno.

◦ Proyección perspectiva además de la clásica isométrica.

◦ Rotación con el mouse respecto al centro de la pantalla.

◦ Rotación con el mouse respecto a cualquier punto de la pantalla.

◦ Reinicio de la vista.

