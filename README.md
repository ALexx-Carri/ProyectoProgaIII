# PROYECTO: Motor de búsqueda para plataformas de streaming

CURSO: Programación III
Enlace de repositorio de GitHub: https://github.com/ALexx-Carri/ProyectoProgaIII

---

## INTEGRANTES

| Nombre y apellido | Código |
|---|---|
| Alvaro Mallky Alagón Aguilar | 202520221 |
| Sebastian Falvy Mendoza | 202510469 |
| Omar Sotelo Cusi | 202510448 |
| Joaquim Alexander Carrión Diaz | 202510461 |
| Rodrigo Muñoz Dominguez | 202410784 |

---

## 1. Objetivo del proyecto

El proyecto tiene como objetivo desarrollar una plataforma de streaming capaz de administrar y realizar búsquedas eficientes de películas a partir de información almacenada en archivos CSV previamente limpiados.
La plataforma permitirá realizar búsquedas por palabras exactas, frases y subcadenas parciales, con el propósito de optimizar la búsqueda de información dentro de títulos y sinopsis de películas.

Para esta tarea, el sistema implementa tres estructuras de datos:

### a) Inverted Index
Es una estructura que almacena palabras completas y las relaciona con las películas en las que aparecen. Su función principal es permitir una búsquedas exactas de acceso rápido.

### b) Suffix Tree
Es un árbol que almacena todos los sufijos posibles de un texto. Esto permite realizar búsquedas parciales o por subcadenas dentro de palabras y frases. El sistema puede encontrar coincidencias incluso cuando el usuario busca solo una parte de la palabra.

### c) Búsqueda híbrida
Combinación entre algoritmos previamente mencionados, el Inverted Index se utiliza para localizar rápidamente películas candidatas mediante coincidencias exactas, mientras que el Suffix Trie permite verificar coincidencias parciales dentro de dichas películas sobrantes. Esta combinación reduce el tiempo de búsqueda en sistemas de grandes volúmenes de información.

---

| Estructura | Tipo de búsqueda |
|---|---|
| Inverted Index | búsqueda exacta por palabras |
| Suffix Trie | búsqueda parcial por subcadenas |
| Búsqueda Híbrida | búsqueda por frases y coincidencias complejas |

---

Además se implementa un sistema de recomendación utilizando un enfoque de Content-Based Filtering, recomendando películas según similitudes en género, palabras clave, contenido de la sinopsis, e interacciones realizadas por el usuario mediante “Like”. Asimismo, para determinar la relevancia de una película al momento de la búsqueda, el sistema asigna un puntaje acumulativo basado en los criterios ya mencionados.
