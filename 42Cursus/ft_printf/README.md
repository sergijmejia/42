# 📝 Printf

## Descripción 

Este proyecto consiste en replicar el funcionamiento de la función original de printf. 
Se deben implementar las siguientes conversiones:

| Conversión  | Descripción														 			|
|-------|-----------------------------------------------------------------------------------|
| **%c** | Imprime un solo carácter.       													|
| **%s** | Imprime una string (como se define por defecto en C).											|
| **%p** | El puntero void * dado como argumento se imprime en formato hexadecimal.								|
| **%d** | Imprime un número decimal (base 10).																	|
| **%i** | Imprime un entero en base 10.               											|
| **%u** | Imprime un número decimal (base 10) sin signo.               									|
| **%x** | Imprime un número hexadecimal (base 16) en minúsculas.                				|
| **%X** | Imprime un número hexadecimal (base 16) en mayúsculas.                				|
| **%%** | Imprime el símbolo del porcentaje.                 											|

◦ La función printf retorna el número de caracteres impresos, o un valor negativo si ocurre un error.

◦ No se debe implementar la gestión del buffer del original.

Prototipo de la función:

```C
int ft_printf(char const *s, ...);
```

## Bonus 🏆

Se tienen que incorporar diversos flags que presentan las siguientes interacciones y prioridades:

| **Flags** | **Descripción** | **`c`** | **`s`** | **`p`** | **`d`/`i`** | **`u`** | **`x`/`X`** |
|---|---|:---:|:---:|:---:|:---:|:---:|:---:|
| `-` | Alinea a la izquierda, rellenando con espacios si hay ancho mínimo. | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| `0` | Rellena con ceros a la izquierda (solo si no hay `-` o `.`). | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ |
| `#` | Prefijo `0x`/`0X` para hexadecimales. | ❌ | ❌ | ❌ | ❌ | ❌ | ✅ |
| `+` | Muestra el signo `+` para enteros (`d`, `i`). | ❌ | ❌ | ❌ | ✅ | ❌ | ❌ |
| (espacio) | Añade un espacio para enteros positivos si `+` no está presente. | ❌ | ❌ | ❌ | ✅ | ❌ | ❌ |
| `.` | Ajusta precisión para enteros o recorta cadenas (`s`). | ❌ | ✅ | ❌ | ✅ | ✅ | ✅ |

### Interacciones y Prioridades entre Flags

1. **`-` y `0`**:
   - Para **`d`/`i`**: Si ambos están presentes, `-` tiene prioridad y `0` se ignora.
   - Para **`x`/`X`**: La alineación `-` predomina, y no se usa `0` para relleno.
  
2. **`+` y (espacio)**:
   - Para **`d`/`i`**: Si se usan ambos, `+` tiene prioridad sobre el espacio `( )`.

3. **`#` y `0`**:
   - Para **`x`/`X`**: `#` añade `0x` o `0X`, y si `0` también está presente, los ceros se añaden después del prefijo.

4. **`#` y `.` (precisión)**:
   - Para **`x`/`X`**: La precisión desactiva el relleno con `0` y `#` solo añade el prefijo.

5. **`0` y `.` (precisión)**:
   - Para **`d`/`i`/`u`/`x`/`X`**: La precisión tiene prioridad sobre el relleno con `0`.

---

### Ejemplos de Combinaciones

| **Formato** | **Salida** | **Explicación** |
|---|---|---|
| `%-10d` | `42        ` | Alineado a la izquierda en un campo de ancho 10. |
| `%08d` | `00000042` | Relleno con ceros a la izquierda para un ancho de 8. |
| `%#x` | `0x2a` | Formato hexadecimal con prefijo `0x`. |
| `%+10.4d` | `     +0042` | Ancho de 10, precisión de 4, signo `+`. |
| `%#08x` | `0x00002a` | Relleno con ceros después del prefijo `0x`. |
| `% .5d` | ` 00042` | Precisión de 5 dígitos con un espacio inicial. |
