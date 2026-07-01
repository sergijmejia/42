# CPP01 - Memory, Pointers and References 🧠
Este segundo módulo profundiza en las entrañas de C++: la gestión de memoria. Abandonamos por fin el clásico `malloc` y `free` de C para dar la bienvenida a `new` y `delete`. Además, se introducen herramientas exclusivas de C++ que cambiarán por completo la forma de pasar variables: las Referencias.

## Conceptos Clave 🧠
A lo largo de este módulo comprenderás las diferencias fundamentales entre cómo se almacena la memoria y cómo acceder a ella de forma segura:
* **Stack vs Heap:** Diferenciar cuándo un objeto nace y muere automáticamente (Stack) y cuándo es tu responsabilidad asignarlo y destruirlo manualmente (Heap).
* **Punteros vs Referencias:** Descubrir la sintaxis `&`. Entender que una referencia es como un puntero constante y seguro que nunca puede ser `NULL` y no requiere desreferenciación explícita.
* **File Streams:** Leer y escribir archivos utilizando las clases `std::ifstream` y `std::ofstream`.
* **Punteros a Funciones Miembro:** Una técnica avanzada para llamar a métodos específicos de una clase guardando sus direcciones en un array, eliminando la necesidad de cadenas infinitas de `if/else`.
* **El uso de `switch`:** Dominar la sentencia `switch` y el comportamiento de *fallthrough* (cuando omites el `break`).

---

## Ejercicios 🛠️

### ex00: BraiiiiiiinnnzzzZ 🧟
Creación de la clase `Zombie`. Este ejercicio demuestra de forma visual la diferencia entre la memoria estática y dinámica.
* **`newZombie`:** Crea un zombi en el **Heap** (usando `new`). El zombi sobrevive fuera del ámbito de la función y debe ser destruido manualmente.
* **`randomChump`:** Crea un zombi en el **Stack** (como variable local). El zombi anuncia su nombre y es destruido automáticamente en cuanto la función termina.

### ex01: Moar brainz! 🧟‍♂️🧟‍♀️
Escalar el concepto anterior. Se pide crear una horda de zombis de una sola vez.
* **Objetivo:** Aprender a usar `new[]` para alojar arrays de objetos dinámicos y, lo más importante, usar `delete[]` para destruirlos correctamente sin provocar *leaks*.

### ex02: HI THIS IS BRAIN 🧠
Un ejercicio técnico y muy directo para comparar la sintaxis de un puntero (`*`) y una referencia (`&`) a un simple `std::string`. Muestra cómo ambas herramientas pueden acceder a la misma dirección de memoria y al mismo valor, pero con reglas de escritura distintas.

### ex03: Unnecessary violence ⚔️
Un ejercicio de diseño arquitectónico. Tienes un arma (`Weapon`) y dos tipos de humanos (`HumanA` y `HumanB`).
* **`HumanA`:** Siempre nace con un arma y nunca la suelta. Por tanto, su arma se pasa por **Referencia**.
* **`HumanB`:** Puede no tener arma o cambiarla. Por tanto, su arma se maneja mediante un **Puntero** (que puede ser `NULL`).

### ex04: Sed is for losers 📝
Creación de un programa que simula el comando `sed`. Recibe un archivo y dos strings (`s1` y `s2`). 
* **Objetivo:** Abrir el archivo, buscar todas las ocurrencias de `s1`, reemplazarlas por `s2` y volcar el resultado en un nuevo archivo llamado `<archivo>.replace`. Todo esto gestionado mediante *streams* de C++ (`<fstream>`) y sin usar la función prohibida `std::string::replace`.

### ex05: Harl 2.0 🗣️
Harl es un cliente muy quejica que emite comentarios en 4 niveles de gravedad: `DEBUG`, `INFO`, `WARNING` y `ERROR`.
* **Objetivo:** Llamar a la función adecuada según el nivel de queja, pero **está estrictamente prohibido usar `if/else`**. 
* **Solución:** Utilizar un array de punteros a funciones miembro para ejecutar la acción de forma directa e indexada.

### ex06: Harl filter 🤫
El mismo cliente quejica, pero esta vez automatizado con un filtro. Pasamos un nivel por consola (ej. `WARNING`) y Harl debe imprimir todas las quejas desde ese nivel hacia arriba (imprimirá `WARNING` y `ERROR`, pero ignorará `DEBUG` e `INFO`).
* **Objetivo:** Utilizar la sentencia `switch` aprovechando deliberadamente el *fallthrough* (no poner `break`) para ejecutar las funciones en cascada.

---

## Uso 🚀
Para compilar y probar cualquiera de los ejercicios, navega a su carpeta correspondiente y utiliza `make`:

```bash
cd ex0X
make
./<nombre_del_ejecutable>
```