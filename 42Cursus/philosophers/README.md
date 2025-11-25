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

## BONUS: Procesos y Semáforos 🚥

La parte **Bonus** plantea el mismo problema de "Los Filósofos Cenando", pero con un cambio radical en la arquitectura interna: **Procesos en lugar de Hilos**.

En esta versión, cada filósofo es un proceso independiente (`fork`), lo que significa que **no comparten memoria**. Un filósofo no puede leer las variables de otro. Esto nos obliga a cambiar por completo la estrategia de sincronización.

---

### Diferencias Clave 🔄

| Característica | Mandatory (Hilos) 🧵 | Bonus (Procesos) 🏭 |
| :--- | :--- | :--- |
| **Memoria** | Compartida (Data Races posibles). | Aislada (Copia exacta pero separada). |
| **Sincronización** | `mutex` (bloqueo local). | `semáforos` (bloqueo a nivel de S.O.). |
| **Tenedores** | Tienen dueño (izq/der) y son mutexes. | Están en el centro (pila común) y son un semáforo contador. |
| **Muerte** | Un hilo monitor vigila variables compartidas. | El proceso hijo muere (`exit`) y el padre recibe la señal. |

---

### Nuevos Desafíos Técnicos 🧠

Al pasar a multiproceso, surgen problemas nuevos que no existían con los hilos:

✔️ **Gestión de Recursos del Sistema (Semáforos)** Los mutexes desaparecen al cerrar el programa, pero los **semáforos con nombre** (`named semaphores`) persisten en el Sistema Operativo. El desafío aquí es asegurar una limpieza perfecta (`sem_unlink`) tanto al inicio como al final, incluso si el programa se interrumpe con `Ctrl+C`, para evitar empezar una nueva simulación con semáforos "sucios" o bloqueados.

✔️ **El Problema de los Zombies y Huérfanos** El proceso principal (Padre) debe actuar como un gestor estricto. Debe usar `waitpid` para detectar si algún hijo muere (de hambre o éxito) y, en ese caso, encargarse de finalizar (`kill`) a todos los demás procesos hijos inmediatamente para evitar que queden procesos "zombis" consumiendo recursos en segundo plano.

✔️ **Deadlock por Acorralamiento** Como los tenedores están en el centro, si todos los filósofos intentan comer a la vez, el semáforo de tenedores llegaría a 0 y todos tendrían un solo tenedor.  
**Solución:** Se implementa un semáforo adicional ("portero") que limita el aforo a `N-1` filósofos intentando comer simultáneamente, garantizando matemáticamente que al menos uno siempre podrá completar su comida.

---

### Herramientas Utilizadas 🛠️

En el bonus sustituimos las herramientas de hilos por las de procesos y semáforos POSIX:

* **`fork`**: Crea un proceso nuevo (filósofo) idéntico al padre pero con memoria aislada.
* **`sem_open` / `sem_close` / `sem_unlink`**: Para crear, cerrar y borrar los semáforos del sistema.
* **`sem_wait`**: Decrementa el semáforo (coger tenedor). Si es 0, bloquea el proceso.
* **`sem_post`**: Incrementa el semáforo (soltar tenedor). Despierta a procesos en espera.
* **`kill` y `waitpid`**: Para el control del ciclo de vida de los procesos hijos.
* **`pthread_create` (Híbrido)**: Aunque usamos procesos, cada filósofo crea internamente un **único hilo monitor** separado para comprobar su propia muerte mientras el hilo principal espera por los semáforos.

---

### Cómo Ejecutar el Bonus

La compilación y ejecución es idéntica a la parte obligatoria, generando un ejecutable distinto:

```bash
make bonus
./philo_bonus [num_philo] [time_to_die] [time_to_eat] [time_to_sleep] [num_meals]
