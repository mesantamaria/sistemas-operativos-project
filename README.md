# Proyecto Sistemas Operativos - SIGKILLERS

## Integrantes

| # | Nombre                 | N° Alumno | Mail UC                                       |
|---|------------------------|-----------|-----------------------------------------------|
| 1 | Sebastián Carreño      | 15639746  | [sgcarreno@uc.cl](mailto:sgcarreno@uc.cl)     |
| 2 | Ignacio Castañeda      | 15634728  | [ifcastaneda@uc.cl](mailto:ifcastaneda@uc.cl) |
| 3 | Andres Jahr            | 14636638  | [asjahr@uc.cl](mailto:asjahr@uc.cl)           |
| 4 | Maximiliano Santamaria | 1563714J  | [mesantamaria@uc.cl](mailto:mesantamaria@uc.cl)|

#### Instrucciones para ejecutar el programa

Para utilizar el programa se utilizan 3 ejecutables, 1 de servidor y 2 de cliente. Específicamente las instrucciones de uso se pueden ver así:

1. Compilar con el comando make para crear un ejecutable de nombre *server* y otro de nombre *client*.
2. Abrir 3 consolas.
3. En una consola ejecutar la siguiente instrucción para abrir el servidor:
	        ` $ ./server -i <ip_address> -p <tcp-port> -l `
	        
	Donde:

	- **-i < ip-address >** es la dirección IP que va a ocupar el servidor para iniciar, o la dirección IP en la cual el cliente se va a conectar.

	- **-p < tcp-port >** es el puerto TCP donde se establecerán las conexiones.

	- **-l** flag opcional que indicará, si es que está presente, que se guarde el log en un archivo log.txt.
    
	    Un ejemplo de uso de esta ejecución es:
	    
		`$ ./server -i 127.0.0.1 -p 8888`

4. En otra consola ejecutar la siguiente instrucción para abrir ejecutar a un cliente:
	        ` $ ./client -i <ip_address> -p <tcp-port> -l `
	     
	  Un ejemplo de uso de esta ejecución es:
	     
	`$ ./client -i 127.0.0.1 -p 8888`

5. El servidor preguntara por el *nickname* del cliente. Para continuar se debe responder por la consola.
6. Repetir paso 4.
7. Repetir paso 5.
8. El servidor enviará a cada cliente el *nickname* de su contrincante y sus scores iniciales. Posterior a esto se puede jugar desde cada consola con normalidad.

#### Decisiones de Diseño

Se crearon 2 carpetas: client y server las cuales separan los dos tipos de ejecutables del programa. En cada una se creó un módulo por cada protocolo asociado. Cada módulo de por sí tiene una función que hace el manejo de *package*, de acuerdo al protocolo respectivo,  que se debe enviar entre cliente- servidor o servidor-cliente. 

Además, se crearon módulos llamados **estructuras.c** en los que se almacena una estructura **Package** que guarda el *id*, *payload_size* y el *payload* de un paquete, y una estructura **Client** la que guarda el *socket*, el *nickname*, el *puntaje* y el *id* del cliente para su uso posterior en el programa. 

El desarrollo del juego se realiza a través de los módulos **main.c** del cliente y del servidor. En estos se puede encontrar la recepción y el envió de los *packages* entre ellos.

#### Principales funciones del programa

Se puede encontrar una función por cada protocolo establecido en el enunciado. 

Además, se utilizaron 2 funciones para inicializar al servidor y a los clientes:

- **initializeClient(char*ip, int port)**: función que inicializa al cliente dado una *ip* y un *port* . En esta función el cliente se conecta a través de su socket iniciado al servidor. Retorna el socket.

 - **initializeServer(char*ip, int port)**: función que inicializa al servidor dado una *ip* y un *port* . En esta función espera la recepción de los sockets de los dos clientes y se hace el manejo de los primeros 6 protocolos. Una vez que ambos clientes se inicializaron, se almacenan en la estructura **Client** y se envía el *package* del protocolo *start game*. Retorna un arreglo de clientes del tipo **Client**.

Se creó también un módulo **util.c** que tiene las siguientes funciones:

- **recieveMessage(int socket)**: recibe un mensaje del *socket* ingresado el cual se desenvuelve en un *id*, un *payload_size* y un *payload* si el *payload_size* es distinto de cero.  Esta información se almacena y se retorna en una estructura **Package**.

- **sendMessage(int socket, char*package)**: envía a el *socket* ingresado el *package* con su respectivo tamaño.

#### Supuestos Adicionales

A pesar de que el cliente es *dumb* , los paquetes sin payload son interpretados por su *id*, por parte del cliente, y luego de acuerdo a esta información, se imprime un mensaje en consola. 





