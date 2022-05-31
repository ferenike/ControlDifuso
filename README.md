# ControlDifuso
Control difuso aplicado a un balancín  
### Descripción del proyecto
Este proyecto trata sobre realizar un control de un balancín, el cual tiene por propósito, mantener una pelota en el punto medio de su longitud.
La longitud será tomada por medio del sensor ultrasónico y en base a los datos percibidos, un servomotor hará que el balancín se incline hacia un sentido u otro, según sea el caso para mantener la pelota en el punto medio de este. Todo este control hará uso de la lógica difusa.
### Caracterización del proyecto
Para obtener el código que realizará el control difuso es necesario caracterizar la entrada y la salida del sistema. Por lo que, para la entrada se definen los siguientes estados:
### Entrada

| Designación  | Centro |   K   |
|    :---:     |  :---: | :---: |
| Cerca (CE)   |  0     | 0.03  |
| Centrado (CN)|  20    | 0.03  |
| Lejos (L)    |  40    | 0.03  |

En base a los estados, se definen el error en base a la posición deseada: 

### Error

| Designación  | Centro |   K   |
|    :---:     |  :---: | :---: |
| Positivo (P) |  20    | 0.03  |
| Centro (C)   |   0    | 0.03  |
| Megativo (L) |  -20   | 0.03  |

Y se propone el hecho:
### Hecho
| Designación  | Centro |   K   |  Rango |
|    :---:     |  :---: | :---: | :---:  |
|  AP          |  10    | 0.02  | [0,40] |

Justo como se requiere posicionar la pelota, se define que el sistema se inclinará a la izquierda y derecha cuando esta se encuentre en la posición contraria y centro para cuando la pelota esté en el centro.

### Salida

| Designación  | Centro |   K    |
|    :---:     |  :---: | :---:  |
| Derecha (C)  |   0    | 0.0009 |
| Centro (C)   |  90    | 0.0009 |
| Izquierda (I)|  180   | 0.0009 |

Las anteriores definiciones dan como resultado las siguientes gráficas
![image](https://user-images.githubusercontent.com/45903954/171090183-546ce855-db21-4cb0-91e0-2ccb5874b14f.png)

### Caso: Una variable de entrada y una de salida con una referencia
Partiendo de:
Regla j: Si $X_1$ es $A_j$ entonces Y es $B_j$
Ahora consideramos el hecho $A^{'}$ y una segunda variable expresada como error = k-x donde k es el valor de referencia. Ahora las reglas tienen la forma:

Regla j: Si $X_1$ es $A_j$ y error es $C_j$ entonces Y es $B_j$

Definimos a k=20 por lo que el error es error = 20-x y con esto, construimos las siguientes reglas:

Regla 1: Si X es CE y error es P entonces Y es D

Regla 2: Si X es CE y error es M entonces Y es C

Regla 3: Si X es CN y error es P entonces Y es C

Regla 4: Si X es CN y error es C entonces Y es C

Regla 5: Si X es CN y error es N entonces Y es C

Regla 6: Si X es L y error es M entonces Y es C

Regla 7: Si X es L y error es N entonces Y es I

Ahora con las reglas, se calcula el antecedente $k_j=min⁡(A_j,C_j)$

Luego, se calcula el grado de consistencia  $α_j$ para la regla j, de la forma $α=min⁡(k_j,A'(x))$

Y finalmente, la defusificación con 
$$ y_{1} = \frac{\sum α_{j}C_{j}}{\sum α_{j}}$$


