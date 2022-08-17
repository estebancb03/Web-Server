# **Web Server 1.1**

## Diseño e implementacion:

Para resolver el proyecto se usará un código base proveido por el profesor para hacer la implementación mas sencilla. Este código base contiene un servidor web y una aplicación web, ambos seriales, que resuelvan solicitudes de los usuarios. Dichas solicitudes consisten en encontrar sumas Goldbach de los números que el usuario ingrese. La idea es que el servidor web reciba solicitudes de los usuarios o clientes para que sean desarrolladas por la aplicación web (que resuelve sumas de Goldbach) y mostradas al cliente en forma de resultados. En la versión entregada por el profesor, tenemos un hilo de tipo servidor (`HttpServer`) que recibe una solicitud, la atiende, la procesa y muestra un resultado por defecto que será siempre el mismo, a modo de prueba. Como se puede notar, el servidor es en su totalidad serial, y no aceptará ninguna otra solicitud hasta haber terminado con la anterior. Claramente esta no es la idea del proyecto, y hay que solucionarlo usando programación concurrente y paralela.

Para la primera entrega del presente proyecto se desea tener un servidor web concurrente con una aplicación web serial. Para lograr esto, se implementó una nueva clase llamada `HttpConnectionHandler`, que representan hilos que atienden y procesan las solicitudes (sockets) de los clientes. Dichas solicitudes fueron previamente recibidas por el hilo de tipo servidor (`HttpServer`) y puestas en una cola de sockets. Los hilos `HttpConnectionHandler` van a atender (consumir) dichos sockets de la cola, y posteriormente van a resolverlos en la aplicación web `GoldbachWebApp`, y finalmente van a mostrar los resultados al cliente. Esta explicación se aprecia con más detalle en el siguiente diagrama: [Diagrama del primer avance](../img/Diagrama_primer_avance.png)

Se había mencionado antes que el `HttpServer` y los `HttpConnectionHandler` usan una cola de sockets para comunicarse. En el siguiente diagrama UML se puede ver cómo se logró dicha comunicación a través de la cola: [Diagrama UML](../img/diagramaUML_primer_avace.png)

En conclusión, se puede ver que el servidor `HttpServer` ahora se dedica únicamente a recibir solicitudes de n cantidad de clientes, solicitudes que serán procesadas por varios hilos de tipo `HttpConnectionHandler`. Por eso, el servidor ahora es concurrente y permite que atienda una cantidad arbitraria de solicitudes de clientes. La aplicación web sigue siendo serial (se resuelven las sumas Goldbach para los números ingresados de cada solicitud de manera serial), pero es en el segundo avance donde tocará hacerla concurrente también.


## Créditos

Proyecto desarrollado por:

* Esteban Castañeda Blanco, correo: esteban.castaneda@ucr.ac.cr
* Daniel Lizano Morales, correo: daniel.lizanomorales@ucr.ac.cr
* Andrea Ramírez Rojas, correo: andrea.ramirezrojas@ucr.ac.cr
* Carlos Ramírez Masís, correo: carlos.ramirezmasis@ucr.ac.cr
