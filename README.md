# Juego_SistemasEmbebidos-

Bienvenido al nuestro repositorio de juego con leds como proyecto de la materia Sistemas embebidos.
Como puedes observar vas a encontrar varios archivos en este repositorio que muestran su significado a continuación.

1. Materiales.csv. En este archivo vas a encontrar la lista de materiales que usamos y el costo de los mismos

2. Carpeta llamada "Estructura del hardware". Aquí encontraras los pdf´s que muestran la estructura física del hardware de este sistema embebido. Además de que encontraras los archivos originales de esta estructura que se hizo con ayuda de un software llamado KiCad. Los importantes son: 
- Juego (parte 1) primeras 2 filas de leds y botones.pddf
- Juego (parte 2) siguientes 2 filas de leds .pdf

3. Carpeta llamada “Código”. Aquí encontraras el código del juego versión 1 que se uso en nuestro sistema embebido.
El archivo es un Arduino file pues se uso el IDE de Arduino para poder programar su función y también lo encontraras elaborado en platformio.


Antes de iniciar con este proyecto se tiene que mencionar que es la creación de un sistema embebido muy básico y para poder hacerlo es importante que se tengan conceptos básicos de electrónica como lo son: manejo de voltajes, pull down, pull up, manejo de resistencias, calcular la resistencia de un led con voltaje o de un botón, entre otros. Además que mas adelante también debes de saber sobre programación básica y el manejo de bits para entender un poco de cómo funciona el programa.
Una vez mencionado esto vamos a hacer el paso a paso el proyecto.

#Descripción general del proyecto.
El proyecto trata de hacer desde cero una pantalla de leds 8x8 usando registros de desplazamiento por cada una de las filas para controlar los leds y hacer un control muy básico que se maneja por voltaje para que se pueda mover en este caso el personaje del jeugo que se representa con un led.
							
							
							
							
							
							
							
							

##Materiales.
Lo primero es comprar los materiales. Estos podrás encontrarlos en el archivo Excel en este repositorio.

###Entendiendo la estructura del hardware.
La estructura del hardware del proyecto fue elaborado en kitcad en donde se presentan todos los materiales que se van a usar de la mejor manera.
Consulta los PDFs dentro de la carpeta estructura de hardware.

# 1. Pasos
1.1	Soldar los sockets para los leds y para los registros de desplazamiento.
1.2	 Soldar los cables para los lesd hacia los registros de desplazamiento
1.3	Soldar las resistencias y puentear a tierra
1.4	Soldar las entradas de voltaje de los registros de desplazamiento hacia voltaje y las entradas de tierra hacia tierra
1.5	Pin data, latch y clock


