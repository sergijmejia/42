# C++ Modules - 42 🚀
**C++ Modules** es un conjunto de 10 proyectos (del CPP00 al CPP09) diseñados para realizar la transición de C a **C++**. El objetivo principal es dominar la Programación Orientada a Objetos (POO), la gestión manual de memoria en clases, el polimorfismo, las plantillas (templates) y la Standard Template Library (STL), todo ello bajo el estándar **C++98**.

## Funcionamiento ⚙️
Este repositorio funciona como un **monorepo**. Cada módulo está contenido en su propia carpeta (`CPP00`, `CPP01`, etc.) y dentro de cada uno se encuentran los distintos ejercicios (`ex00`, `ex01`, ...).

Para compilar y ejecutar cualquier ejercicio, la sintaxis estándar es:

```bash
cd CPP0X/ex0Y
make
./<nombre_del_ejecutable>
```

### Reglas de Oro del Proyecto
A diferencia de los proyectos de C en 42, aquí no se aplica la *Norminette*, pero existen reglas estrictas de diseño:
1. **Estándar C++98:** Todo el código debe compilar con las flags `-Wall -Wextra -Werror -std=c++98`.
2. **Forma Canónica Ortodoxa:** A partir del CPP02, todas las clases deben incluir un constructor por defecto, un constructor de copia, un operador de asignación y un destructor.
3. **Cero Leaks:** La gestión de memoria es implacable. Cada `new` debe tener su correspondiente `delete`. Ningún ejercicio pasará si Valgrind detecta fugas.

## Resumen de Módulos 📚
| Módulo | Conceptos Clave Aprendidos |
|-------|-----------------------------------------------------------------------------------|
| **CPP00** | Namespaces, clases, funciones miembro, *streams* de E/S (`std::cout`, `std::cin`). |
| **CPP01** | Asignación de memoria (`new`/`delete`), punteros a miembros, referencias, sentencias `switch`. |
| **CPP02** | Polimorfismo Ad-hoc, sobrecarga de operadores y la Forma Canónica Ortodoxa. |
| **CPP03** | Herencia y visibilidad de clases (Public, Private, Protected). |
| **CPP04** | Polimorfismo de subtipos, funciones virtuales, destructores virtuales y clases abstractas. |
| **CPP05** | Manejo de excepciones (`try`, `catch`, `throw`). |
| **CPP06** | Conversiones de tipo (*Casts*): `static_cast`, `dynamic_cast`, `const_cast` y `reinterpret_cast`. |
| **CPP07** | Plantillas de C++ (*Templates*) para funciones y clases genéricas. |
| **CPP08** | Contenedores templados, iteradores y algoritmos básicos de la STL. |
| **CPP09** | Uso avanzado de la STL (Standard Template Library) resolviendo problemas complejos de algoritmia y estructuras de datos. |

## Estructura del Repositorio 📁
```text
42_CPP/
├── README.md               (Este documento)
├── CPP00/
│   ├── README.md           (Apuntes y detalles del módulo 00)
│   ├── ex00/
│   └── ex01/
├── CPP01/
│   ├── README.md
│   └── ex00/
...
└── CPP09/
```

*Nota: Cada carpeta `CPP0X` incluye su propio `README.md` detallando las particularidades y los comandos de ese módulo específico.*

## Comandos `make` 🛠️
Todos los ejercicios incluyen un `Makefile` con las siguientes reglas básicas:

◦ `make`: Compila el código fuente y genera el ejecutable.

◦ `make clean`: Elimina los archivos objeto (`.o`).

◦ `make fclean`: Elimina los archivos objeto y el ejecutable final.

◦ `make re`: Ejecuta `fclean` seguido de `make`, recompilando todo desde cero.


## 🚧 Proyecto en Desarrollo 🚧

Este proyecto aún está en desarrollo y puede contener errores o funciones incompletas. 
