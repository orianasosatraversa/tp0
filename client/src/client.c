#include "client.h"
#include <readline/readline.h>
int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger,"Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config, "CLAVE");


	// Loggeamos el valor de config

	log_info(logger,config);


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él



	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al s saje

	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);



	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log","TP0",1, LOG_LEVEL_INFO);


	if (nuevo_logger == NULL){
		printf("No se pudo crear el logger");
		exit(1);
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	
	nuevo_config = config_create("./cliente.config");

	if (nuevo_config == NULL){
		log_info(nuevo_config,"No se pudo crear el config");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	while (1){
		if(!(string_equals_ignore_case(leido,""))){
			log_info(logger,leido);

		}else{
			free(leido);
			break;
		}

		leido = readline("> ");
	}

	
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

//Leer de consola
//De los comandos básicos, nos queda leer de consola. Si bien existen muchas formas de hacerlo, vamos a usar la biblioteca readline.

//Necesitamos incluirla usando:

//c
//#include <readline/readline.h>
//Una vez incluida, la función readline("> ") va a hacer que el programa espere a que se ingrese una línea y devolverla en un string ya listo para loggear.

//La misma ya se encuentra agregada en el TP0, por lo que no hace falta hacer este include
	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

	agregar_a_paquete(paquete,,strlen(leido)+1);
	
	// Leemos y esta vez agregamos las lineas al paquete

	enviar_paquete(paquete,conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!

	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  if (logger != NULL){
		log_destroy(logger);
	  }
	  if (config != NULL){
		config_destroy(config);    
	  }

	  liberar_conexion(conexion);

}