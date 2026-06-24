# ACTIVIDAD: Procesamiento en Etapas de una Red

## Contexto

Una organización analiza una red de interacción entre distintos elementos. Esta red puede ser modelada como una estructura donde existen conexiones entre pares de elementos.

Se requiere construir un sistema de procesamiento dividido en **dos etapas**, donde la salida de la primera etapa será la entrada de la segunda.

---

##  Etapa 1: Análisis de influencia indirecta

Se desea analizar, para cada elemento de la red, su **nivel de influencia indirecta**.

Se define la influencia indirecta de un elemento como:

> La cantidad de elementos distintos a los que puede llegar en exactamente dos pasos, sin considerar el propio elemento ni repeticiones.

---

###  Requerimiento

Implemente una función que:

* Reciba una representación de la red
* Calcule la influencia indirecta de cada elemento
* Almacene estos valores en una estructura adecuada que permita:

  * Insertar valores dinámicamente
  * Acceder eficientemente al menor valor almacenado

---

### Restricción

No está permitido utilizar arreglos auxiliares como estructura principal de salida.
Debe elegir una estructura de datos acorde al comportamiento requerido.

---

##  Etapa 2: Selección de elementos relevantes

A partir de los valores generados en la etapa anterior, se desea seleccionar los elementos más relevantes.

---

###  Requerimiento

Implemente una segunda función que:

* Reciba la estructura generada en la etapa 1
* Procese todos sus elementos
* Genere una nueva estructura que:

  * Permita acceder eficientemente al mayor valor
  * Contenga únicamente los **N valores más altos**

---

###  Restricciones

* No se puede acceder directamente a la representación interna de la estructura recibida
* Debe utilizar las operaciones propias de la estructura
* La nueva estructura debe construirse dinámicamente

---

##  Consideraciones generales

* Ambas funciones deben ser independientes
* La salida de la primera función debe ser utilizada directamente como entrada de la segunda
* Justifique brevemente (en comentarios) la elección de las estructuras utilizadas

---

##  Objetivo de la actividad

Esta actividad evalúa su capacidad para:

* Interpretar un problema y modelarlo correctamente
* Seleccionar estructuras de datos adecuadas según su comportamiento
* Encadenar soluciones en múltiples etapas
* Utilizar correctamente operaciones propias de cada estructura
