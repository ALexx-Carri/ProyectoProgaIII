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

## 2. Tecnologías Utilizadas

| Elemento | Tecnología |
|---|---|
| IDE utilizado | CLion |
| Lenguaje de programación | C++ 20 |
| Control de versiones | Git y GitHub |
| Librerías utilizadas | STL (Standard Template Library) |
| Formato de almacenamiento de datos | CSV |

---

## 3. Arquitectura

El sistema sigue una arquitectura modular orientada al procesamiento, almacenamiento y búsqueda eficiente de información de películas. El flujo inicia con la lectura de archivos CSV que contienen títulos, sinopsis y atributos como género, director y elenco. Posteriormente, los datos pasan por una etapa de limpieza y tokenización, donde se normalizan caracteres, se eliminan símbolos innecesarios y el texto se divide en palabras para optimizar las búsquedas. Una vez procesados los datos, el sistema construye dos estructuras principales: un Inverted Index, encargado de relacionar palabras completas con las películas donde aparecen para realizar búsquedas exactas, y un Suffix Trie, utilizado para búsquedas parciales o por subcadenas dentro de títulos y sinopsis.

Ambas estructuras son utilizadas por un motor de búsqueda híbrida que combina precisión y eficiencia. El Inverted Index permite filtrar rápidamente películas candidatas mediante coincidencias exactas, mientras que el Suffix Trie complementa el proceso verificando coincidencias parciales dentro de los resultados obtenidos. Finalmente, el sistema organiza las películas mediante un algoritmo de relevancia que prioriza coincidencias en títulos, sinopsis, tags e interacciones del usuario, mostrando como resultado las cinco películas más relevantes según la búsqueda realizada. 

![Texto alternativo](images/arquitectura.png)


## 4. Explicación de algoritmos:

Inverted Index: Es una estructura de datos que relaciona palabras con las películas en las que aparecen. Su objetivo es optimizar búsquedas exactas dentro de títulos, sinopsis y tags, permitiendo acceder rápidamente a los documentos asociados a una palabra específica. 

| En lugar de almacenar | El sistema almacena |
|---|---|
| película → palabras | palabra → películas |

a) Inserción: Durante la construcción del índice, el sistema tokenizar el texto de cada película y almacena cada palabra dentro de una tabla hash junto con su identificador

![Texto alternativo](images/arquitectura.png)

b) Búsqueda exacta: Cuando el usuario realiza una búsqueda exacta, el sistema consulta directamente el índice utilizando la palabra ingresada.

![Texto alternativo](images/arquitectura.png)

Por otro lado, la complejidad temporal de la inserción y búsqueda dentro del Inverted Index utilizan tablas hash (unordered_map), permitiendo tiempos de acceso promedio muy bajos.

| Operación | Complejidad |
|---|---|
| Inserción | O(1) |
| Búsqueda exacta | O(1) |

Suffix Trie: Es una estructura de árbol que almacena todos los sufijos posibles de un texto. Su función principal es permitir búsquedas parciales o por subcadenas dentro de palabras y frases. Gracias a esta estructura, el sistema puede encontrar coincidencias incluso cuando el usuario ingresa únicamente una parte de la palabra.

a) Inserción: Para construir el Suffix Trie, el sistema genera todos los sufijos posibles del texto e inserta cada uno carácter por carácter dentro del árbol.

![Texto alternativo](images/arquitectura.png)

b) Búsqueda parcial: Cuando el usuario realiza una búsqueda parcial, el sistema recorre el árbol carácter por carácter verificando si el patrón existe dentro de los sufijos almacenados.

![Texto alternativo](images/arquitectura.png)

La complejidad temporal de la búsqueda parcial depende únicamente de la longitud del patrón buscado, ya que el recorrido del árbol se realiza carácter por carácter.

| Operación | Complejidad |
|---|---|
| Complejidad Construcción del Trie | O(n²) |
| Búsqueda parcial | O(m) |

> *Donde n representa la longitud total del texto y m representa la longitud del patrón buscado.*

Búsqueda Híbrida: La búsqueda híbrida combina el uso del Inverted Index y el Suffix Trie para mejorar la precisión del sistema. Por un lado, el Inverted Index se encarga de reducir el universo de búsqueda seleccionando únicamente las películas que contienen palabras clave exactas de la consulta. Luego, el Suffix Trie verifica si la frase o subcadena completa realmente aparece dentro del título o sinopsis, refinando así los resultados obtenidos.

![Texto alternativo](images/arquitectura.png)
