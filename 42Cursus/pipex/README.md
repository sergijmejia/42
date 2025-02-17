## Pipex 🚰

**Pipex** es un proyecto que replica el comportamiento de la redirección de tuberías (`|`) en shell. Permite ejecutar dos comandos en secuencia, donde la salida del primer comando se convierte en la entrada del segundo, utilizando pipes en C.

---

## Funcionamiento ⚙️

El programa se ejecuta con la siguiente sintaxis:

```shell
./pipex in_file "cmd1" "cmd2" out_file
```

- `in_file`: Archivo de donde leerá la entrada el primer comando.
- `cmd1`: Primer comando que se ejecutará, su salida será redirigida al segundo comando.
- `cmd2`: Segundo comando que tomará la salida del primero como entrada.
- `out_file`: Archivo donde se guardará la salida final del segundo comando.

**Ejemplo de uso:**

```shell
./pipex in_file "cat" "wc -l" out_file
```

Equivale a ejecutar en la shell:

```shell
< in_file cat | wc -l > out_file
```

Esto toma el contenido de `in_file`, lo pasa por `cat`, luego ese resultado lo cuenta `wc -l`, y finalmente lo guarda en `out_file`.

---

## BONUS ⭐️

Para completar el bonus, el programa debe soportar múltiples pipes, permitiendo ejecutar más de dos comandos en cadena:

```shelll
./pipex archivo_entrada "cmd1" "cmd2" "cmd3" ... "cmdN" out_file
```

Ejemplo con tres comandos:

```shell
./pipex in_file "ls -l" "grep .c" "wc -l" out_file
```

Esto lista los archivos (`ls -l`), filtra los `.c` (`grep .c`), cuenta las líneas (`wc -l`) y guarda el resultado en `out_file`.

## Here\_doc 📜

Como seunda parte del bonus pipex también soporta el modo **here\_doc**, que permite simular la entrada estándar a partir de un delimitador definido por el usuario.

**Sintaxis:**

```shell
./pipex here_doc LIMITER "cmd1" "cmd2" out_file
```

- Se leen líneas de entrada hasta que el usuario escriba `LIMITER`.
- Esas líneas se pasan como entrada al `cmd1`.
- El resultado pasa a `cmd2` y se guarda en `out_file`.

**Ejemplo:**

```bash
./pipex here_doc END "cat" "wc -l" outfile
```

El programa esperará la entrada manual hasta que se escriba `END`.

---

## Control de errores ⚠️

El programa debe gestionar errores como:

- Archivos inexistentes o sin permisos.
- Comandos inválidos o que no existen.
- Errores en la creación y cierre de pipes.
- Manejo correcto de `execve`, `fork`, `wait`, `dup2` y todas las funciones permitidas en este proyecto.
