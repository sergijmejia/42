# CPP03 - Inheritance 🧬
Este cuarto módulo es la puerta de entrada a uno de los pilares más poderosos de la Programación Orientada a Objetos: **La Herencia**. Aprenderemos cómo hacer que las clases compartan código entre sí, creando jerarquías de padres e hijos para evitar la repetición masiva de código.

## Conceptos Clave 🧠
El CPP03 te enseñará cómo expandir clases base en clases derivadas más especializadas, comprendiendo cómo funciona la memoria y el orden de construcción detrás de escena:
* **Herencia Simple:** La capacidad de una clase hija (Derivada) de absorber todos los atributos y métodos de una clase padre (Base).
* **El Modificador `protected`:** Una nueva capa de seguridad. A diferencia de `private` (que oculta todo incluso a los hijos), `protected` oculta los datos al mundo exterior (`main`), pero permite que las clases hijas puedan leerlos y modificarlos.
* **Orden de Construcción/Destrucción:** Comprobar visualmente que, al nacer un hijo, primero se construye el núcleo del padre y luego las piezas del hijo. Al morir, el orden se invierte.
* **Sobrescritura de Funciones (Overriding):** Cómo hacer que un hijo cambie la forma en que funciona una función heredada del padre (por ejemplo, tener un ataque diferente).
* **El Problema del Diamante (Herencia Múltiple):** Un dolor de cabeza clásico en C++ que ocurre cuando un hijo hereda de dos padres que, a su vez, heredan del mismo abuelo. Descubriremos cómo solucionarlo mediante la Herencia Virtual.

---

## Ejercicios 🛠️

### ex00: Aaaaand... OPEN! 🤖
Creación de la clase base, el robot primigenio.
* **Objetivo:** Construir la clase `ClapTrap` respetando la Forma Canónica Ortodoxa.
* **Detalles:** El robot tiene puntos de vida (*Hit points*), energía (*Energy points*) y daño de ataque. Se implementan métodos básicos en los que gasta energía para atacar (`attack`), recibe daño (`takeDamage`) y se repara a sí mismo (`beRepaired`). Si se queda sin vida o sin energía, no puede hacer nada.

### ex01: Serena, my love! 🛡️
Primera toma de contacto con la herencia.
* **Objetivo:** Crear una clase hija llamada `ScavTrap` que herede de `ClapTrap`.
* **Novedades:** El constructor de `ScavTrap` inicializa los atributos del padre con valores diferentes (más vida y más daño). Además, sobrescribe la función `attack` del padre para imprimir un mensaje distinto, e incluye una capacidad única: `guardGate()`, que pone al robot en modo "Guardián de la Puerta".
* **Importante:** Aquí es donde se hace necesario cambiar los atributos del padre de `private` a `protected`.

### ex02: Repetitive work 💥
Añadimos otro hermano a la familia.
* **Objetivo:** Crear una clase `FragTrap` que también herede directamente de `ClapTrap`.
* **Novedades:** Al igual que el anterior, nace con sus propias estadísticas de vida y energía por defecto. Su habilidad especial es `highFivesGuys()`, una función amigable para pedir los cinco en la consola.

### ex03: Now it's weird! 💎
El jefe final del módulo: La Herencia Múltiple y el temido "Problema del Diamante".
* **Objetivo:** Crear un monstruo llamado `DiamondTrap` que hereda **a la vez** de `ScavTrap` y de `FragTrap`.
* **Reto:** Como ambos padres heredan de `ClapTrap`, el `DiamondTrap` nacería con dos núcleos de `ClapTrap` duplicados, creando ambigüedad. La misión es usar la palabra clave `virtual` en las herencias de los padres para fusionar el abuelo en un solo núcleo.
* **Novedad:** El `DiamondTrap` tiene su propio atributo privado `_name`, ocultando el `_name` del `ClapTrap` original. Debe implementar la función `whoAmI()` para imprimir su nombre monstruoso y el nombre original de su abuelo.

---

## Uso 🚀
Para compilar y probar cualquiera de los ejercicios, navega a su carpeta correspondiente y utiliza `make`:

```bash
cd ex0X
make
./<nombre_del_ejecutable>
```