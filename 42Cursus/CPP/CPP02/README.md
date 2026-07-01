# CPP02 - Ad-hoc Polymorphism, Overloading and OCCF 📐
Este tercer módulo marca un antes y un después en la forma de escribir clases en C++. Aquí se establecen las reglas de diseño profesional y se aprende a manipular el comportamiento interno de los operadores matemáticos y lógicos del propio lenguaje.

## Conceptos Clave 🧠
El CPP02 se centra en tres pilares fundamentales que te permitirán crear clases robustas y matemáticamente funcionales:
* **Forma Canónica Ortodoxa (OCCF):** Un estándar de diseño obligatorio en 42. A partir de ahora, toda clase debe tener (como mínimo): un constructor por defecto, un constructor de copia, un operador de asignación (`operator=`) y un destructor.
* **Sobrecarga de Operadores (Operator Overloading):** Aprender a redefinir qué hacen los símbolos matemáticos (`+`, `-`, `*`, `/`, `<`, `>`) o los de entrada/salida (`<<`, `>>`) cuando se usan con tus propios objetos. ¡Esto es el Polimorfismo Ad-hoc!
* **Números de Coma Fija (Fixed-Point Numbers):** Un concepto de bajo nivel. Vas a crear una clase para representar números fraccionarios usando solo enteros y operaciones de desplazamiento de bits (*bit-shifting*). Esto ofrece un equilibrio entre rendimiento y precisión, ideal para gráficos y procesadores sin FPU (Unidad de Coma Flotante).

---

## Ejercicios 🛠️

### ex00: My First Class in Orthodox Canonical Form 📝
El primer paso en el mundo de los números de coma fija.
* **Objetivo:** Construir el esqueleto básico de la clase `Fixed` respetando rigurosamente la Forma Canónica Ortodoxa. 
* **Detalles:** La clase debe contener un entero para guardar el valor del número de coma fija y una constante estática que define el número de bits fraccionarios (siempre 8 para este proyecto). Se implementan funciones básicas de *get* y *set* que interactúan con los bits puros.

### ex01: Towards a more useful fixed-point number class 🧮
El número de coma fija del ejercicio anterior era inútil porque no podíamos inicializarlo con números reales.
* **Objetivo:** Añadir constructores que acepten parámetros `int` y `float`, convirtiéndolos a nuestro formato interno de coma fija.
* **Novedad:** Se incluyen métodos para hacer el proceso inverso (`toInt()` y `toFloat()`) y se sobrecarga el operador de inserción `operator<<` para poder imprimir el objeto `Fixed` directamente con `std::cout`.

### ex02: Now we're talking 🚀
El patio de recreo definitivo para la sobrecarga de operadores.
* **Objetivo:** Hacer que la clase `Fixed` sea 100% operable, igual que si fuera un tipo de dato nativo del sistema (como un `int` normal).
* **Sobrecargas a implementar:**
  * Operadores de comparación: `>`, `<`, `>=`, `<=`, `==`, `!=`.
  * Operadores aritméticos: `+`, `-`, `*`, `/`.
  * Operadores de incremento/decremento: pre-incremento (`++a`), post-incremento (`a++`), pre-decremento (`--a`) y post-decremento (`a--`).
  * Funciones estáticas `min` y `max` para comparar dos objetos `Fixed`.

### ex03: BSP (Binary Space Partitioning) 🔺
Una aplicación práctica y matemática de tu recién creada clase `Fixed`.
* **Objetivo:** Dado un triángulo definido por tres puntos (A, B, C) y un cuarto punto solitario (P), escribir una función que determine si el punto P está estrictamente **dentro** del triángulo.
* **Reto:** Crear una clase `Point` inmutable (usando atributos `const`) y resolver el problema geométrico (usando productos vectoriales o coordenadas baricéntricas) aplicando exclusivamente la clase `Fixed` para todos los cálculos.

---

## Uso 🚀
Para compilar y probar cualquiera de los ejercicios, navega a su carpeta correspondiente y utiliza `make`:

```bash
cd ex0X
make
./<nombre_del_ejecutable>
```