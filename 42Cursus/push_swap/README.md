## Push_swap 🔢

Push_swap es un proyecto de algoritmia simple, en donde se debe que ordenar
datos. Se tiene a disposición un conjunto de valores int, dos stacks y un conjunto de
instrucciones para manipular ambos. La ordenación se debe reaizar en el minimo de movimientos posibe.



## Operaciones 🔁

| Operaciones | Explicación |
| :--- | :--- |
| sa | swap a - intercambia los dos primeros elementos encima del stack a. |
| sb | swap b - intercambia los dos primeros elementos encima del stack b. |
| ss | swap a y swap b a la vez. |
| pa | push a -  toma el primer elemento del stack b y lo pone encima del stack a. |
| pb | push b -  toma el primer elemento del stack a y lo pone encima del stack b. |
| ra | rotate a - desplaza hacia arriba todos los elementos del stack a una posición, el primer elemento se convierte en el último. |
| rb | rotate b - desplaza hacia arriba todos los elementos del stack b una posición, el primer elemento se convierte en el último. |
| rr | ra y rb a la vez. |
| rra | reverse rotate a - desplaza hacia abajo todos los elementos del stack a una posición, el último elemento se convierte en el primero. |
| rrb | reverse rotate b - desplaza hacia abajo todos los elementos del stack b una posición, el último elemento se convierte en el primero. |
| rrr | rra y rrb a la vez. |

## BONUS ⭐️

Solo se puede hacer el bonus si la parte obligatoria esta al 100%. El bonus consiste en el desarrollo de un programa llamado checker , que verificará
si el stack A esta ordenado. Para ello se debe mandar como argumentos los numeros del stack y una vez se ejecute el programa se deben mandar las operaciones necesarias para realizar la ordenación. Cuando se queira dejar de enviar operaciones se debe hacer ```Ctrl + D``` y el checker debe decir "OK" si esta ordenado o "KO" si no lo esta. El control de errores del checker debe ser igual que en push_swap.
