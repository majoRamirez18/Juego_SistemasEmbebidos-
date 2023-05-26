# Juego_SistemasEmbebidos-

Bienvenido al nuestro repositorio de juego con leds como proyecto de la materia Sistemas embebidos.
Como puedes observar vas a encontrar varios archivos en este repositorio que muestran su significado a continuación.

1. Materiales.csv. En este archivo vas a encontrar la lista de materiales que usamos y el costo de los mismos

2. Carpeta llamada "Estructura del hardware". Aquí encontraras los pdf´s que muestran la estructura física del hardware de este sistema embebido. Además de que encontraras los archivos originales de esta estructura que se hizo con ayuda de un software llamado KiCad. Los importantes son: 
- Juego (parte 1) primeras 2 filas de leds y botones.pdf
- Juego (parte 2) siguientes 2 filas de leds .pdf

3. Carpeta llamada “Código”. Aquí encontraras el código del juego versión 1 que se uso en nuestro sistema embebido.
El archivo es un Arduino file pues se uso el IDE de Arduino para poder programar su función y también lo encontraras elaborado en platformio.


Antes de iniciar con este proyecto se tiene que mencionar que es la creación de un sistema embebido muy básico y para poder hacerlo es importante que se tengan conceptos básicos de electrónica como lo son: manejo de voltajes, pull down, pull up, manejo de resistencias, calcular la resistencia de un led con voltaje o de un botón, entre otros. Además que mas adelante también debes de saber sobre programación básica y el manejo de bits para entender un poco de cómo funciona el programa.
Una vez mencionado esto vamos a hacer el paso a paso el proyecto.

# Descripción general del proyecto.
El proyecto trata de un juego inspirandonos en un bark game. Hicimos desde cero una pantalla de leds 8x8 usando registros de desplazamiento por cada una de las filas para controlar los leds y hacer un control muy básico que se maneja por voltaje para que se pueda mover en este caso el personaje del juego que se representa con un led.
							
![image](https://user-images.githubusercontent.com/106703825/235551403-dbbedd13-ecb7-497f-832a-acb14096a39e.png)
						

## Materiales.
Lo primero es comprar los materiales. Estos podrás encontrarlos en el archivo Excel en este repositorio.

### Entendiendo la estructura del hardware.
La estructura del hardware del proyecto fue elaborado en kitcad en donde se presentan todos los materiales que se van a usar de la mejor manera.
Consulta los PDFs dentro de la carpeta estructura de hardware.

El pdf del Juego (parte 1) primeras 2 filas de leds y botones.pdf es el esquema de la primera parte del juego que son los botones y las primeras dos filas de leds conectados a un registro de desplazamiento

El pdf del Juego (parte 2) siguiente 2 filas de leds.pdf es la otra parte faltante del esquema del juego que son las demas filas (seis) de la matriz a formar.

Con estos esquemas te puedes guiar para saber como iran cada uno de los componentes electronicos: leds, resistencias, arduino, botones y registros de desplazamiento. Te recomendamos buscar el simbolo electronico de cada componente si no estas familiarizado con el mismo.

# 1. Pasos
## 1.1	Soldar los sockets para los leds y para los registros de desplazamiento.
En esta sección se adquirieron sockets para facilitar la colocación de los LEDs, ya que cada placa perforada tiene dos hileras de 8 LEDs. Además, se soldaron las resistencias de cada hilera para evitar que se crucen y se dispongan en diferentes direcciones.
![image](https://user-images.githubusercontent.com/125621118/236074730-86fd650f-ce3d-4626-9700-0d7bd0670a64.png)

## 1.2	 Soldar los cables para los leds hacia los registros de desplazamiento
Soldamos los cables de cada LED cuidando que a la patita del led en la cual soldamos los cables sea la mas grande pues es (+), la otra patita es la mas pequeña (-) la cual es la de tierra y por ende iran las resistencias conectada a esa patita pequeña.
Para esto también te explicamos los registros de desplazamiento que tienen la siguiente esctructura:
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/093beec8-cb14-4388-9afc-5f0bd830e77e)

Como se ve son 16 entradas las que se tienen. Las patillas desde Q0 a Q7 son en donde se van a soldar la otra parte de los cables pues estas patitas van a mandar información a los leds. La que se conecte a Q0 es el led mas importante procura que sea el primero empezando de tu lado izquierdo.
Y las tres entradas que irán conectadas a las salidas de nuestra placa de Arduino son DS (patilla 2), STCP (patilla 3) y SHCP (patilla 4).

Retomando lo anterior los cables conectados al led de la patita mas larga iran al registro de desplazamiento, comenzando desde el exterior y avanzando hacia el interior, siguiendo el diagrama del proyecto.
![WhatsApp Image 2023-05-03 at 5 20 27 PM](https://user-images.githubusercontent.com/125621118/236075335-4efe38bf-87e6-487a-a82f-e1521ed8d78c.jpeg)
![image](https://user-images.githubusercontent.com/125621118/236074861-fd31cbd3-62a4-4767-ae56-52ee5ecf9b39.png)

## 1.3	Soldar las resistencias y puentear a tierra
Las resistencias que ya estan soldadas a la patita del led estan bien. El otro lado de las resistencias las vamos a conectar entre ellas como en fila. Esto se le llama puentear a tierra pues la ultima resistencia que se solde va a ir a tierra conectada.
![WhatsApp Image 2023-05-03 at 5 21 08 PM](https://user-images.githubusercontent.com/125621118/236075156-46bf646c-226e-4998-8806-ee68dbac7db5.jpeg)


## 1.4	Soldar las entradas de voltaje de los registros de desplazamiento hacia voltaje y las entradas de tierra hacia tierra
En este paso te pedimos que pongas atención
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/e538217a-9259-4fcb-aaf5-dd236755030e)

Hay que identificar los pines de corriente y de tirra, para ello checa la siguiente imagen.
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/d8d96c82-1d94-4ed0-b240-d34dc6b3b568)

Los cables negros son tierra y los cables rojos son corriente. En el prototipo conectalas de esta forma.

## 1.5	Pin data, latch y clock
Cada placa contiene 2 registros el data, latch y clock se conectan entre sí de cada registro
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/16b94ec9-f370-4afe-af22-1ed0f3b830e9)

Los pines son los cables de color: azul, verde y amarillo. Si los conectamos entre si se veria de la siguiente manera
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/e77bc125-c33e-4973-b545-a2fbbe1ea8f7)

De forma fisica debio de quedarte así

![image](https://user-images.githubusercontent.com/125621118/236074849-6874242f-a578-4e31-84a3-0201caf9c36e.png)

## 1.6 Repetir, repetir y repetir.
El mismo proceso hay que hacerlo por 3 veces para que obtengas tu matriz de 8x8 leds.


# 2. Control

Simulación. Primero simulamos de manera virtual el circuito de la cruceta de botones.
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/108145f7-50b4-4c5b-85e6-6bb3926f66b5)
 

Con la simulación virtual empezamos a medir el voltaje de cada uno de los botones con un multímetro de manera digital, los resultados fueron los siguientes:


Botones	Voltaje	Corriente	Media
Botón 1 (A)	4V	817	
Botón 2 (B)	3V	613	204
Botón 3 (C)	2V	408	205
Botón 4 (D)	1V	204	204
Tabla 1 voltaje de los botones


Sacamos la moda que es 204, partiendo de ello sacamos la medida dividiéndola entre 6 para tener un limite de voltaje de cada botón y así no se confunda el usuario al momento apretar uno u otro botón.
 ![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/40a21a70-2c16-41f3-8e01-f83c7fbaf413)


Definir el límite de voltaje. Como se ve en la ilustración 3 los limites de cada botón no se topan uno con el otro por lo que la medida de dividirlo entre 6 nos va a beneficiar. 
Codificamos el programa. Los comentarios lo explican:
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/0b04cc7c-46f7-487f-91d0-853881030976)
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/51df3214-3706-4565-a5e6-282919310672)




## 2.1 Elementos.
Preparamos los elementos físicos ya adecuados teniendo consideraciones y los colocamos en la placa antes de soldarlos para tener una idea.
 ![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/d0eb56b8-178d-4a6e-9bed-cd1a523d6cc2)

Va a ver 3 alambres sueltos los cuales son: la corriente que se conectara al pin de 5 volts, uno de tierra que se conectara al GND del Arduino y el ultimo al pin 2 que es la entrada analógica del Arduino

![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/eee1c357-049d-4d4d-9a51-ef4b8f3e48a9)


Como se ve el alambre de corriente inicia conectándose a una resistencia, del otro lado de la resistencia se conecta al botón, del botón a otra resistencia y así hasta que la última resistencia se va a conectar a tierra.
En la tierra se conectará la resistencia de 1M de ahí al último botón puesto, después de ese botón a otro y así hasta que llego al alambre del pin analógico.

## 2.2 Soldar
Se empezaron a soldar todos los componentes en la placa fenólica.
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/107c92a2-de31-4c1d-a25a-8ad33026d738)
![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/d2a6bf60-c6a2-4c58-b36e-12148a674e17)


## 2.3 Probar.
Una vez todo preparado se cargó el programa en el Arduino y se probó. Cada salida se conectó en su lugar correspondiente, la primera de lado derecho de la imagen es el del voltaje conectado al pin 5V de Arduino, el segundo es el de tierra y el tercero fue el analógico.
Esto es solo prueba para ver que se hizo correctamente

![image](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/db142bbb-512b-413e-8e2c-2e2d9a7f02e3)


# 3. Montar todo.
Tenemos el boton y la matriz. Montamos todo en la arduino.
![WhatsApp Image 2023-05-03 at 5 53 33 PM](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/49262645-6d92-44c7-b5e4-ed46b3589106)
![WhatsApp Image 2023-05-24 at 12 29 00 AM](https://github.com/majoRamirez18/Juego_SistemasEmbebidos-/assets/106703825/0bb7e6fa-c092-4b34-a579-6d016257ba15)

# 3.1 Programa

Dentro de la carpeta de código podremos encontrar el código del proyecto en dos versiones:
1. Arduino. Usa el IDE de arduino, conecta tu arduino y carga el codigo del proyecto
2. Platformio. Usa Visual Studio Code y descarga la extensión de platformio, carga el proyecto y listo. Sino tambipen puese hacerlo en forma de cmd.

# 4. Consideraciones finales.

Puede alimentar el proyecto con una bateria de 5 volts o con tu computadora. Si tienes alguna duda no dudes en escribirnos y te ayudaremos lo antes posiblem.




 
