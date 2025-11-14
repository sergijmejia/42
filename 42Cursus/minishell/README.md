## Minishell 🐚

**Minishell** es un proyecto en C que recrea las funcionalidades principales de un intérprete de comandos de UNIX (como `bash`). Es unproyecto en donde se requiere un profundo entendimiento de la gestión de procesos, descriptores de archivos, y el análisis sintáctico de entradas.

Este proyecto es capaz de leer una línea de comandos, interpretarla y ejecutarla, gestionando un amplio rango de características de una shell estándar.

---

## Arquitectura ⚙️

A diferencia de un enfoque simple, este `minishell` está construido sobre una arquitectura robusta que separa el análisis de la ejecución:

1.  **Lexer (Tokenizador):** Lee la entrada del usuario (`readline`) y la descompone en una lista de *tokens* (palabras, operadores como `|` o `>`, comillas, etc.).
2.  **Parser (Analizador Sintáctico):** Recibe los tokens y los organiza en un **Árbol de Sintaxis Abstracta (AST)**. Esta estructura de árbol representa la lógica de los comandos, agrupando pipes, redirecciones y operadores lógicos.
3.  **Ejecutor:** Recorre el AST nodo por nodo y ejecuta los comandos. Si encuentra un nodo "pipe", prepara un *pipe* y ejecuta sus ramas izquierda y derecha. Si encuentra un comando, lo ejecuta (ya sea un *builtin* o un ejecutable del sistema).



---

## Características Principales 🔍

✔️ **Prompt Interactivo**: Muestra un *prompt* y gestiona un historial de comandos (usando `readline`).

✔️ **Ejecución de Comandos**: Busca y ejecuta programas externos.

✔️ **Builtins Fundamentales**: Reimplementa los siguientes comandos internos:
* `echo`
* `cd` (con rutas relativas y absolutas)
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

✔️ **Pipes (`|`)**: Permite encadenar múltiples comandos, donde la salida de uno es la entrada del siguiente.

✔️ **Redirecciones**: Soporta:
* `<` (Redirección de entrada)
* `>` (Redirección de salida, truncando)
* `>>` (Redirección de salida, añadiendo)
* `<<` (Here Documents)

✔️ **Gestión de Señales**: Maneja `Ctrl+C` (SIGINT), `Ctrl+\` (SIGQUIT) y `Ctrl+D` (EOF) de forma interactiva, similar a `bash`.

✔️ **Expansión de Variables**: Expande variables de entorno, variables locales, y el estado del último comando (`$?`).

---

## BONUS ⭐️

**El bonus incluye algunas caracterisicas extra**

✔️ **Wildcards (`*`)**: Expande los asteriscos para que coincidan con nombres de archivos en el directorio actual.

✔️ **Operadores Lógicos (`&&` y `||`)**: Ejecuta comandos basándose en el éxito o fallo del comando anterior.

✔️ **Agrupación (`( )`)**: Gestiona agrupación de comandos para alterar el orden de prioridad.

---

## Uso 🚀

1.  Clona el repositorio.
2.  En la raíz del proyecto, ejecuta `make`.
3.  Inicia la shell con `./minishell`.

```bash
make
./minishell
