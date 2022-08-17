# **Web Server 1.1**

## Descripción del problema

Este programa consiste en un servidor web concurrente capáz de obtener las sumas de Goldbach para uno o varios números que el usuario desee introducir. La lista de números a calcular se obtine mediante solicitudes recibidas desde la aplicación web.

El matemático prusiano Christian Goldbach propuso que todo número entero mayor que cinco se puede expresar como la suma de un conjunto de números primos. Esta propuesta se divide en dos conjeturas:

* **Conjetura fuerte:** Todo número par se puede escribir como la suma de dos números primos. Ejemplo: 8 = 3 + 5.
* **Conjetura débil:** Todo número impar se puede escribir como la suma de tres números primos. Ejemplo: 9 = 2 + 2 + 5.

Este proyecto pretende simular el comportamiento real de concurrencia en u  servidor web, donde cada solicitud es recibida y ejecutada por un hilo. Se emplea el patrón de diseño de **Productor-Consumidor**.

## Manual de uso

En el resultado proporcionado al usuario, se mostrarán los datos y la cantidad de sumas de Golbach válidas para cada valor. En el caso del que el usuario ingrese algún número negativo el programa lo entenderá como que aparte de lo anterior el usuario solicita que se listen las sumas de Goldbach para ese valor. Por otro lado, si se ingresa un valor menor que cinco se mostrará un NA (No Aplica) y en el caso de que se ingrese un dato inválido (un caracter que no sea un número o un número excesivamente grande) se validará y se desplegará un mensaje de error en la salida. Ejemplo:

| Input            | Output                                                         |
|------------------|----------------------------------------------------------------|
|a                 | VALUE IS NOT VALID                                             |
|2                 | NA                                                             |
|7                 | 1 sums                                                         |
|-21               | 5 sums:  2 + 2 + 17, 3 + 5 + 13, 3 + 7 + 11, 5 + 5 + 11, 7 + 7 |

### Compilación

Para compilar el código se utiliza el siguiente comando:

``` text
make 
```

Este comando generará una carpeta **bin** en la cual se guardará el archivo **Web-Server.o**

### Ejecución

Existen tres formas de ejecutar el servidor, la primera es utilizando los valores por defecto. Para ello se emplea el siguiente comando sin introducir parámetros:

``` text
bin/Web-Server 
```

En este ejemplo anterior el servidor correrá en el puerto 8080 que es el puerto que se designó por defecto y utilizará la cantidad máxima de CPU's disponibles.

Si se desea indicar un puerto específico a utilizar se envia como parámetro de la siguiente forma:

``` text
bin/Web-Server 3000
```

En el ejemplo anterior el servidor correrá en el puerto 3000 y utilizará tantos hilos como CPU's disponibles halla. Se recomienda no insertar un número de puerto menor a 1024 ya que se necesitará de permisos de administrador para hacerlo.

Si en cambio se desea ejecutar el servidor con una cantidad de hilos determinada se puede indicar el número de puerto como segundo parámetro:

``` text
bin/Web-Server 3000 8
```

En este caso el servidor correrá en el puerto 3000 y utilizará solamente ocho hilos de ejecución.

Para detener la ejecución, hay dos maneras: 

1. La primera es apretando la combinación de teclas 
``` text
Ctrl+C
```
2. La segunda es poniendo los comandos:
``` text
ps -eu
```
``` text
kill PID
```

[Captura del navegador](img/Browser_screenshot.png)

[Captura de la consola](img/terminal_screenshot.png)


## Créditos

Proyecto desarrollado por:

* Esteban Castañeda Blanco, correo: esteban.castaneda@ucr.ac.cr
* Daniel Lizano Morales, correo: daniel.lizanomorales@ucr.ac.cr
* Andrea Ramírez Rojas, correo: andrea.ramirezrojas@ucr.ac.cr
* Carlos Ramírez Masís, correo: carlos.ramirezmasis@ucr.ac.cr
