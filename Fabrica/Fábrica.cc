/* Modelo MM1 - Un Servidor, Una Cola  */

#include <stdio.h>
#include <stdlib.h> 
#include "simlib.c"


//Definición de Eventos
#define Arribo_Pieza			  1  /*  Evento Arribo Pieza           */		 
#define Partida_Limpieza          2  /* Evento Partida Limpieza                   */
#define Partida_Lubricación       3  /* Evento Partida lubricación                      */
#define Partida_Operador          4  /* Evento Fin Día            */
#define Partida_Ensambladora	  5 /* Evento Partida Ensambladora A*/    


//Definición de Listas 
#define Cola_Limpieza_Y_Refinación  1
#define Cola_Lubricación            2
#define Cola_Operador_humano        3
#define Cola_Ensabladora_A          4
#define Cola_Ensambladora_B         5

//Definición Listas Demoras 
#define Demora_Pieza_A     1 // Demora pieza A
# define Demora_Pieza_B    2 // Demora pieza B

// Definición Posiciones transfer
#define Tiempo_Evento     1
#define Tipo_Evento       2
#define Tipo_Pieza        3

/* Declaración de variables  */
bool falla, anomalia;
float min_interarribos, max_interarribos, tiempo_refinacion, media_tiempo_servicio_lubricacion, porcentaje_habitual_fallas, min_tiempo_operador, max_tiempo_operador, media_tiempo_ensambladora, desv_estandar_ensambladora,porcentaje_anomalias, probabilidad_pieza;
int tipo_pieza, numero_dias;

/* Rutinas */
int main()
void inicializa(void);
void Rutina_Arribo_Pieza(void);
void Generar_Arribo_Pieza(int tipo_pieza);
void Rutina_Partida_Limpieza (void);
void Generar_Partida_Limpieza(int tipo_pieza);
void Rutina_Partida_Lubricacion(void);
void Generar_Partida_Lubricacion(void);
void Rutina_Partida_Operador(void);
void Generar_Partida_Operador(void);
void Rutina_Partida_Ensambladora_A(void);
void Generar_Partida_Ensambladora_A(void);
void Rutina_Partida_Ensambladora_B(void);
void Generar_Partida_Ensambladora_B(void);
void estadisticos(void);


int main()  /* Main function. */
{

	/* Inicializar Simlib */
	init_simlib();


	/* Rutina de inicializacion */
	inicializa();

	/* Ejecutar la simulaci�n. */

	clientes_act = 0;

	while (sim_time <= numero_dias*1440)
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
		case Partida_Ensambladora_A:
			Rutina_Partida_Ensambladora_A();
		case Partida_Ensambladora_B:
			Rutina_Partida_Ensambladora_B()
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
	anomalia=false

void Rutina_Arribo_Pieza()
	{
		// Determinar primer arribo y cargar en lista de eventos
		probabilidad_pieza=lcgrand(Arribo_Pieza)
		if (probabilidad_pieza <= 0,5)
			{
				float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza);
				transfer[Tiempo_Evento] = sim_time + tiempo;
				transfer[Tipo_Evento] = Arribo_Pieza;
				transfer[Tipo_Pieza]='A'
			}
		else
		{
			float tiempo = uniform(min_interarribos, max_interarribos, Arribo_Pieza)
			transfer[Tiempo_Evento] = sim_time + tiempo;
			transfer[Tipo_Evento]=Arribo_Pieza
			transfer[Tipo_Pieza]='B'
		}
		// Ver si puede ingresar a la maquina de refinacion
		if (list_size[Cola_Limpieza_Y_Refinación]==0)
		{
			list_file(FIRST,TipoPieza)
			Generar_Partida_Limpieza(Tipo_Pieza)
		}
		else
		{
			// Va a Cola_Limpieza
			transfer[Tiempo_Evento] = sim_time;
			list_file(LAST,Cola_Limpieza_Y_Refinación)
		}
		// Generar Proximo arribo pieza
		Generar_Arribo_Pieza(Tipo_Pieza)
		  
	}
	void Rutina_Partida_Limpieza()
		{
			int TipoPieza=transfer(Tipo_Pieza)
			if (TipoPieza=='A')
				{
					// Ver si está libre la máquina de lubricación
					if (list_size[Cola_Lubricación]==0)
						{
							list_file(FIRST, Cola_Lubricación);
							sampst(0,0, Demora_Pieza_A)
						}
					else
					{
						// Va a Cola_lubricación
						list_file(LAST, Cola_Lubricación)
					}
				}
			else
			{
				// ver si está libre el operador humano
				if (list_size[Cola_Operador_humano]==0)
				{
					list_file(FIRST,Cola_Operador_humano)
					sampst(0,0, Demora_Pieza_B)
				}
				else
				{
					// Va a Cola_Operador_Humano
					list_file(LAST, Cola_Operador_humano)
				}
			}
		}
	void reporte(void)  /* Generar Reporte de la Simulaci�n */
	{

		/* Mostrar Par�metros de Entrada */

		/* -------- Por pantalla -------- */

		printf("Sistema M/M/1 - Simulaci�n con Simlib \n\n");
		printf("Media de Interarribos          : %8.3f minutos\n", media_interarribos);
		printf("Media de Servicios             : %8.3f minutos\n", media_servicio);
		printf("Cantidad de Clientes Demorados : %i \n\n", num_clientes);

		/* Calcular los Estad�sticos */

		/* Estad�sticos Escalaras - Sampst */
		sampst(0.0, -Demora_cola);
		printf("\nDemora en Cola                 : %f \n ", transfer[1]);


		/* Estad�sticos Temporales - Timest y Filest */

		filest(Cola);
		printf("\nN�mero Promedio en Cola        : %f \n ", transfer[1]);
		filest(Servidor);
		printf("\nUtilizaci�n Servidor           : %f \n ", transfer[1]);
		printf("\nTiempo Final de Simulation     : %10.3f minutes\n", sim_time);


		/* Estad�sticos Temporales - Timest y Filest */

		filest(Cola);
		printf("\nN�mero Promedio en Cola        : %f \n ", transfer[1]);
		filest(Servidor);
		printf("\nUtilizaci�n Servidor           : %f \n ", transfer[1]);
		printf("\nSimulation end time            : %10.3f minutes\n", sim_time);


	}

	void Rutina_Arribo_Cliente(void)
	{
		/* Determinar pr�ximo arribo y cargar en Lista de Eventos */
		tipo_cliente = transfer[3]

			if (tipo_cliente == cliente_solo_caja)
			{
				transfer[1] = sim_time + expon(media_interarribos_solo_caja, 4)
					transfer[2] = Arribo_Cliente;
				transfer[3] = cliente_solo_caja;
				list_file(INCREASING, LIST_EVENT);
			}
			else
			{
				probabilidad_cliente = lcgrand(Arribo_Cliente);
				if (probabilidad_cliente <= 0, 6)
				{
					transfer[1] = sim_time + expon(media_interarribos_primera_vez, 2)
						transfer[3] = cliente_nuevo //Cliente Primera Vez
				}

				else
				{
					transfer[1] = sim_time + expon(media_interarribos_viejo, 3)
						transfer[3] = cliente_viejo //Cliente Viejo
				}
				tranfer[2] = Arribo_Cliente;
				list_file(INCREASING, LIST_EVENT);
			}

		/////Control visto en clase 12/06/2023

			/* Chequear si el Servidor est� desocupado */

		if (list_size[Servidor] == 0)
		{

			++clientes_act;

			/* Si est� desocupado ocuparlo y generar la partida */

			list_file(FIRST, Servidor);
			sampst(0.0, Demora_cola);

			/* Programar el evento partida */
			transfer[1] = sim_time + expon(media_servicio, Partida);
			transfer[2] = Partida;
			list_file(INCREASING, LIST_EVENT);

		}

		else
		{

			/* Si el Servidor est� ocupado poner el Trabajo en Cola
			guardo en el transfer [1] - cuando se coloco el evento en la cola
			*/

			transfer[1] = sim_time;
			list_file(LAST, Cola);
		}
	}

	void Rutina_Partida_Srv_Att_Cli(void)
	{
	}

	void Partida_Caja(void)
	{
	}

	void Inicio_Jornada(void)
	{
	}

	void Fin_Jornada(void)
	{
	}
}