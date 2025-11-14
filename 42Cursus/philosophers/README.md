## Philosophers 🍽️

**Philosophers** es un proyecto en C que simula el problema clásico de concurrencia "Los Filósofos Cenando". Es una introducción a la programación multihilo, donde el objetivo principal es aprender a gestionar hilos (`pthreads`) y proteger datos compartidos (`mutexes`) para evitar que los filósofos mueran o que el programa se bloquee.

---

## El Problema y la Simulación ⚙️

El escenario consiste en un número de filósofos sentados en una mesa redonda. Hay un tenedor entre cada par de filósofos.

Las reglas de la simulación son:
* Un filósofo alterna entre tres estados: **pensar**, **comer** y **dormir**.
* Para **comer**, un filósofo necesita tomar sus dos tenedores (el de su izquierda y el de su derecha).
* Mientras come, los filósofos vecinos no pueden comer, ya que les falta un tenedor.
* Si un filósofo no ha comido en un tiempo (`time_to_die`), **muere** y la simulación termina.

El programa se ejecuta desde la terminal:
```bash
./philo [num_philo] [time_to_die] [time_to_eat] [time_to_sleep] [num_meals]
```

* **`num_philo`**: El número de filósofos (y tenedores).
* **`time_to_die`**: (en ms) Si un filósofo no come en este tiempo, muere.
* **`time_to_eat`**: (en ms) El tiempo que tarda un filósofo en comer.
* **`time_to_sleep`**: (en ms) El tiempo que tarda un filósofo en dormir.
* **`num_meals`**: (Opcional) Si se especifica, la simulación termina cuando todos los filósofos han comido este número de veces.

---

## Desafíos Técnicos 🧠

Este proyecto se centra en resolver dos problemas fundamentales de la concurrencia:

✔️ **Evitar Deadlocks (Interbloqueo)**
El reto principal. Si todos los filósofos cogen su tenedor derecho al mismo tiempo, todos se quedarán esperando indefinidamente por el tenedor izquierdo (que tiene su vecino). Esto congela el programa. La solución requiere implementar una estrategia de bloqueo (como la de par/impar) para romper este "círculo de espera".


✔️ **Evitar Data Races (Condiciones de Carrera)**
Múltiples hilos (filósofos + un monitor) leen y escriben datos compartidos al mismo tiempo (ej. `time_last_eat`, o una bandera que indica el fin de la simulación). Todos estos accesos deben estar protegidos por mutexes para evitar la corrupción de datos y comportamientos impredecibles.

✔️ **Precisión del Tiempo**
La simulación debe ser precisa. Los filósofos deben morir en el momento justo. Esto requiere una gestión cuidadosa del tiempo (usando `gettimeofday`) y la creación de una función `usleep` más precisa que la estándar.

---

## Herramientas Utilizadas 🛠️

La simulación se construye utilizando la librería `pthread` (POSIX Threads):

* **`pthread_create`**: Para crear un hilo por cada filósofo y un hilo supervisor (monitor).
* **`pthread_join`**: Para que el hilo principal espere a que todos los filósofos terminen antes de limpiar y salir.
* **`pthread_mutex_init` / `pthread_mutex_destroy`**: Para inicializar y destruir los mutexes.
* **`pthread_mutex_lock` / `pthread_mutex_unlock`**: Para proteger las "secciones críticas" (el acto de coger tenedores o de modificar variables compartidas).

---

## BONUS ⭐️
### 🚧 En Desarrollo 🚧
La parte bonus de este proyecto aún está en desarrollo y puede contener errores o funciones incompletas. 
