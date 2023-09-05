/* Modelo MM1 - Un Servidor, Una Cola  */

#include <stdio.h>
#include <stdlib.h> 
#include "simlib.c"


//Definición de Eventos
#define Arribo_Pieza			  1  /*  Evento Arribo Pieza           */		 
#define Partida_Limpieza          2  /* Evento Partida Limpieza                   */
#define Partida_Lubricación       3  /* Evento Partida lubricación                      */
#define Partida_Operador          4  /* Evento Partida Operador          */
#define Partida_Ensambladora	  5 /* Evento Partida Ensambladora */    


//Definición de Listas 
#define Maquina_Refinacion          1
#define Maquina_Lubricacion         2
#define Operador_Humano             3
#define Maquina_Ensambladora        4
#define Cola_Limpeza_Y_Refinacion   5
#define Cola_Lubricación            6
#define Cola_Operador_humano        7
#define Cola_Ensambladora_A         8
#define Cola_Ensambladora_B         9

//Definición Listas Demoras 
#define Demora_Pieza_A     1 // Demora pieza A
# define Demora_Pieza_B    2 // Demora pieza B

// Definición Posiciones transfer
#define Tiempo_Evento     1
#define Tipo_Evento       2
#define Tipo_Pieza        3

/* Declaración de variables  */
bool falla, anomalia;
int min_interarribos, max_interarribos, tiempo_refinacion, media_tiempo_servicio_lubricacion, porcentaje_habitual_fallas, min_tiempo_operador, max_tiempo_operador, media_tiempo_ensambladora, desv_estandar_ensambladora, porcentaje_anomalias, probabilidad_pieza, probabilidad_falla, probabilidad_anomalias, cont_fallas,cont_producto_terminado,cont_anomalias, tipo_pieza, pieza_A = 1, Pieza_B = 2, numero_dias;

/* Rutinas */
int main();
void inicializa(void);
void Rutina_Arribo_Pieza(void);
void Generar_Arribo_Pieza();
void Rutina_Partida_Limpieza (void);
void Generar_Partida_Limpieza(int tipo_pieza);
void Rutina_Partida_Lubricacion(void);
void Generar_Partida_Lubricacion();
void Rutina_Partida_Operador(void);
void Generar_Partida_Operador();
void Rutina_Partida_Ensambladora(void);
void Generar_Partida_Ensambladora();
void estadisticos();


int main()  /* Main function. */
{

	/* Inicializar Simlib */
	init_simlib();


	/* Rutina de inicializacion */
	inicializa();

	/* Ejecutar la simulaci�n. */

	clientes_act = 0;

	while (sim_time <= numero_dias*21600)
	{

		/* Determinar pr�ximo Evento */
		timing();

		/* Invocar el evento correspondiente. */

		switch (next_event_type)
		{
		case Arribo_Pieza:
			Rutina_Arribo_Pieza();
			break;
		case Partida_Limpieza:
			Rutina_Partida_Limpieza();
			break;
		case Partida_Lubricación:
			Rutina_Partida_Lubricacion();
			break;
		case Partida_Operador:
			Rutina_Partida_Operador();
		case Partida_Ensambladora:
			Rutina_Partida_Ensambladora();
		}
	}

	/* Llamada al Reporte para mostrar los resultados */
	estadisticos();
	//getchar();
	system("pause");
}


void inicializa(void)  /* Inicializar el Sistema */
{
	/* Asignación de valores a las variables  */
	//sim_time inicia en cero por defecto
	min_interarribos = 1;
	max_interarribos = 2.5;
	tiempo_refinacion = 2.8;
	media_tiempo_servicio_lubricacion = 3.5;
	porcentaje_habitual_fallas = 5;
	min_tiempo_operador = 3;
	max_tiempo_operador = 5;
	media_tiempo_ensambladora = 3.1;
	desv_estandar_ensambladora = 0.8;
	porcentaje_anomalias = 4;
	falla = false;
	anomalia = false
	cont_fallas = 0;

	// Pronostico el primer arribo de pieza y lo cargo a la lista de eventos
	probabilidad_pieza = lcgrand(Arribo_Pieza)
		if (probabilidad_pieza <= 0,5)
		{
			transfer[Tipo_Pieza] = 1
		}
		else
		{
			
			transfer[Tipo_Pieza] = 2
		}
		float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza);
		transfer[Tiempo_Evento] = sim_time + tiempo;
		transfer[Tipo_Evento] = Arribo_Pieza;
		list_file(INCREASING, LIST_EVENT);
}
	void Rutina_Arribo_Pieza()
	{
		// Generar el próximo arribo de piezas
		probabilidad_pieza = lcgrand(Arribo_Pieza)
			if (probabilidad_pieza <= 0,5)
			{
				transfer[Tipo_Pieza] = 1
			}
			else
			{

				transfer[Tipo_Pieza] = 2
			}
			float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza);
			transfer[Tiempo_Evento] = sim_time + tiempo;
			transfer[Tipo_Evento] = Arribo_Pieza;
			list_file(INCREASING, LIST_EVENT);

		// Ver si puede ingresar a la maquina de refinacion
		if (list_size[Maquina_Refinacion] == 0)
		{
				list_file(FIRST, Maquina_Refinacion);
				Generar_Partida_Limpieza(Tipo_Pieza)
		}
		else
		{
			// Va a Cola_Limpieza
			transfer[Tiempo_Evento] = sim_time;
			list_file(LAST, Cola_Limpieza_Y_Refinación)
		}
		
	}
void Rutina_Partida_Limpieza()
		{
			int TipoPieza=transfer(Tipo_Pieza)
			if (TipoPieza==1)
				{
					// Ver si está libre la maquina de lubricacion
					if (list_size[Maquina_Lubricacion]==0)
						{	
							list_file(FIRST, Maquina_Lubricacion);
							sampst (0, 0, Demora_Pieza_A);
							Generar_Partida_Lubricacion();
						}
					else
					{
						// Va a Cola_lubricación
						list_file(LAST, Cola_Lubricación);
					}
	
				}
			else
			{
				// ver si está libre el operador humano
				if (list_size[Operador_Humano]==0)
				{
					list_file(FIRST,Operador_Humano);

					// ver si la pieza tiene fallas

					probabilidad_falla = lcgrand(Partida_Limpieza)
					if (probabilidad_falla<=0,05)
						{
							cont_fallas++;
						}
						sampst(0, 0, Demora_Pieza_B);
						Generar_Partida_Operador();
				}
				else
				{
					// Va a Cola_Operador_Humano
					list_file(LAST, Cola_Operador_humano)
				}
			}
			// ver si hay trabajo en cola
			if (list_size[Cola_Limpeza_Y_Refinacion]>0)

				{

					list_remove(FIRST, Cola_Limpeza_Y_Refinacion);
					int TipoPieza = transfer[Tipo_Pieza];
					sampst(sim_time - transfer[1], Demora_Pieza_A);
					list_file(FIRST, Maquina_Refinacion);
					Generar_Partida_Limpieza(Tipo_Pieza);

				}
	}
void Rutina_Partida_Lubricacion()
	{
			// Ver si está libre la ensambladora
			if (list_size[Maquina_Ensambladora]==0)
				{
					list_file(FIRST, Maquina_Ensambladora);
					sampst(0, 0, Demora_Pieza_A);
					Generar_Partida_Ensambladora();
				}
			else
				{
					// Va a cola_ensambladora_A
					list_file[LAST, Cola_Ensambladora_A];
				}
			// Ver si hay trabajo en cola
			if (list_size[Cola_Lubricación]>0)
				{
					list_remove(FIRST, Cola_Lubricación);
					TipoPieza = transfer[Tipo_Pieza];
					sampst(sim_time - transfer[Tiempo_Evento], Demora_Pieza_A);
					// Ocupar Cola_Lubricación
					list_file(Maquina_Lubricacion);
					// Generar Partida Lubricación
					Generar_Partida_Lubricacion();
				}
	}
void Rutina_Partida_Operador()
	{
				if (probabilidad_falla > 0,05)
				// Ver si está libre la ensambladora
					if (list_size[Maquina_Ensambladora]==0)
						{
							list_file(FIRST, Maquina_Ensambladora];
							sampst(0, 0, Demora_Pieza_B);
							Generar_Partida_Ensambladora();

						}
					else
					{
						// Va a Cola_ensambladora_B
						list_file(LAST, Cola_Ensambladora_B);
					}
				// Ver si hay trabajo en cola
				if (list_size[Cola_Operador_humano] > 0)
					{
						list_remove(FIRST, Cola_Operador_humano);
						sampst(sim_time - transfer[Tiempo_Evento], Demora_Pieza_B);
						// Ocupar Cola_Operador_Humano
						list_file(Cola_Operador_humano);
						Generar_Partida_Operador();
					}
				else
					{
						cont_fallas++
					}
	}
void Rutina_Partida_Ensambladora()
	{
		probabilidad_anomalias = lcgrand(Partida_Ensambladora);
		int TipoPieza = transfer[Tipo_Pieza];
		if (probabilidad_anomalias<= 0.05)
			{
				list_file[Cola_Limpieza_Y_Refinación]==0)	
			}
		else
		{
			cont_producto_terminado++;
		}
				
		}
		
		void Generar_Arribo_Pieza()
		{
				probabilidad_pieza = lcgrand(Arribo_Pieza)
				if (probabilidad_pieza <= 0,5)
				{
					float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza);
					transfer[Tiempo_Evento] = sim_time + tiempo;
					transfer[Tipo_Pieza] = 1
				}
				else
				{
					float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza);
					transfer[Tiempo_Evento] = sim_time + tiempo;
					transfer[Tipo_Pieza] = 2
				}
				transfer[Tipo_Evento] = Arribo_Pieza;
				list_file(INCREASING, LIST_EVENT);
		}
		void Generar_Partida_Limpieza(int TipoPieza)
			{
				if (TipoPieza==1)
					{
						transfer[Tipo_Pieza]='A'
					}
				else
				{
					transfer[Tipo_Pieza]='B'
				}
				transfer[Tiempo_Evento] = 2.8
				transfer[Tipo_Evento] = Partida_Limpieza;
				list_file(INCREASING, LIST_EVENT)
			}
			
		void Generar_Partida_Lubricacion()
			{
				transfer[Tiempo_Evento] = expon(media_tiempo_servicio_lubricacion, Partida_Lubricación);
				transfer[Tipo_Evento] = Partida_Lubricación;
				transfer[Tipo_Pieza] = 1;
				list_file(INCREASING, LIST_EVENT)
			}
		void Generar_Partida_Operador()
			{
				transfer[Tiempo_Evento] = uniform(min_tiempo_operador, max_tiempo_operador, Partida_Operador)
				transfer[Tipo_Evento] = Partida_Operador;
				transfer[Tipo_Pieza] = 2;
				list_file(INCREASING, LIST_EVENT)
			}
	void estadisticos(void)  /* Generar Reporte de la Simulaci�n */
	{
		// Utilización de todos los "procesadores" del sistema


		printf("comienza el reporte.....\n\n");

		// Demora en cada una de las colas de la pieza A
		sampst(0, 0, -Demora_Pieza_A);
		printf("\nDemora Pieza A: %f \n ", transfer[1]);

		// Demora en cada una de las colas de la pieza B
		sampst(0, 0 - Demora_Pieza_B);
		printf("\nDemora Pieza B: %f \n ", transfer[1]);

		// Cantidad de piezas B rechazadas
		printf("\nCantidad Piezas B rechazadas: %f \n ", transfer[1]);

		// Cantidad de productos terminados
		printf("\nCantidad Productos terminados: %f \n ", transfer[1]);

		// Cantidad de productos con anomalias
		printf("\nCantidad Productos terminados: %f \n ", transfer[1]);


