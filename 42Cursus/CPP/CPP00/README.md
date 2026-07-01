# CPP00 - Basics of C++ 🚀
Este es el primer módulo de C++. El objetivo principal de **CPP00** es dar el salto definitivo de C a C++, abandonando herramientas clásicas como `printf`, `scanf` o `malloc` para abrazar la **Programación Orientada a Objetos (POO)** y los *streams* de entrada/salida.

## Conceptos Clave 🧠
En este módulo se sientan las bases de C++98. A través de los ejercicios aprenderás y aplicarás:
* **Entrada y Salida (I/O):** Uso de `std::cout`, `std::cin`, `std::endl` y la librería `<iomanip>` para formatear texto en la consola.
* **Namespaces:** Entender cómo C++ organiza las librerías estándar (el famoso `std::`).
* **Clases y Objetos:** Creación de esqueletos de clases (`.hpp`), instanciación de objetos y llamadas a métodos.
* **Encapsulación:** Diferencia entre atributos/métodos `public` y `private`. Uso de *getters* y *setters* para proteger la información.
* **Constructores y Destructores:** El ciclo de vida básico de un objeto.
* **Atributos estáticos:** Uso de variables y funciones `static` compartidas por todas las instancias de una clase (crucial para el `ex02`).

---

## Ejercicios 🛠️

### ex00: Megaphone 📣
Un programa sencillo para calentar motores. Actúa como un megáfono que convierte todos los argumentos pasados por consola a letras mayúsculas.
* **Objetivo:** Familiarizarse con `std::cout`, manipulación de *strings* de C++ y bucles básicos.

### ex01: My Awesome PhoneBook 📖
Creación de una agenda telefónica interactiva que funciona como una pequeña CLI (*Command Line Interface*). 
* **Objetivo:** Diseñar y relacionar dos clases distintas (`PhoneBook` y `Contact`).
* **Funcionalidades:** * Comando `ADD`: Añade hasta un máximo de 8 contactos. Si la agenda se llena, el contacto más antiguo es reemplazado (lógica de array circular).
  * Comando `SEARCH`: Muestra una tabla formateada con los contactos guardados. Al seleccionar un índice válido, muestra la información detallada de ese contacto.
  * Comando `EXIT`: Cierra el programa de forma segura, limpiando todo rastro.

### ex02: The Job Of Your Dreams 🏦
Un ejercicio de ingeniería inversa muy interesante. El sujeto proporciona un archivo de cabecera (`Account.hpp`), un programa principal (`tests.cpp`) y un archivo de registro (`19920104_091532.log`). 
* **Objetivo:** Escribir el archivo `Account.cpp` desde cero para que, al compilar y ejecutar, la salida generada coincida exactamente (salvo por las marcas de tiempo) con el archivo de registro proporcionado.
* **Reto:** Entender cómo funcionan los miembros `static` de una clase y realizar llamadas a funciones internas para llevar la contabilidad de las cuentas bancarias.

---

## Uso 🚀
Para compilar y probar cualquiera de los ejercicios, navega a su carpeta correspondiente y utiliza `make`:

```bash
cd ex0X
make
./<nombre_del_ejecutable>
```