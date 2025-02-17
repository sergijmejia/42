## Get_next_line 📄

**get_next_line** es una función en C que permite leer un archivo línea por línea de manera eficiente. Esta función es útil para procesar archivos de texto, manejar entradas de usuario o trabajar con flujos de datos de manera incremental.

---

## Funcionamiento ⚙️

La función `get_next_line` lee una línea completa de un archivo cada vez que se llama, devolviendo un puntero a la cadena de caracteres que contiene la línea leída. La lectura se realiza utilizando un buffer de tamaño configurable.

```c
char *get_next_line(int fd);
```

- **`fd`**: Descriptor del archivo desde el cual se leerá la línea.
- **Retorno**:
  - Una cadena de caracteres terminada en `\0` con la línea leída (incluye el salto de línea `\n` si existe en el archivo).
  - `NULL` si se ha alcanzado el final del archivo o si ocurre un error.

---

## Características principales 🔍

✔️ Lee archivos línea por línea sin cargar el archivo completo en memoria.  
✔️ Utiliza un **buffer dinámico** para optimizar la lectura.  
✔️ Soporta archivos de cualquier tamaño.  
✔️ Funciona con **file descriptors** estándar (`stdin`, `stdout`, `stderr`) y archivos.  

---

## BONUS ⭐️

La versión bonus de `get_next_line` extiende su funcionalidad para **gestionar múltiples archivos simultáneamente** sin interferencias. Esto significa que se puede llamar a `get_next_line(fd1)`, luego a `get_next_line(fd2)`, y la función recordará la posición de lectura de cada archivo de forma independiente.
