// jrzanol
// 

#include "stdafx.h"
#include "Nebulizador.h"
#include "ProntoSocorro.h"

Nebulizador::Nebulizador() : Pessoa(TipoPessoa::Nebulizador)
{
	static int g_NebulizadorIdCounter = 1;
	m_NebulizadorId = g_NebulizadorIdCounter++;

	m_Count = 0;
	m_Utilizador = NULL;
	m_SendoUtilizado = false;

	pthread_mutex_init(&m_MutexPac, NULL);
}

Nebulizador::~Nebulizador()
{
	pthread_mutex_destroy(&m_MutexPac);
}

void Nebulizador::Executa()
{
	do
	{
		if (m_SendoUtilizado)
		{
			pthread_mutex_lock(&m_MutexPac);

			if (m_Utilizador)
			{
				if (m_Count == 0)
					m_Count = 15;

				m_Utilizador->m_SinalVital += (rand() % 3) + 2;

				if (m_Utilizador->m_SinalVital > 10)
					m_Utilizador->m_SinalVital = 10;

				if (--m_Count <= 0)
				{
					m_Utilizador->m_UtilizandoNebulizador = false;

					m_Count = 0;
					m_Utilizador = NULL;
					m_SendoUtilizado = false;

					Log("Nebulizador %d esta livre.", m_NebulizadorId);
				}
			}

			pthread_mutex_unlock(&m_MutexPac);
		}

		Sleep(SLEEP_TIMER);
	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

void Nebulizador::TrocaPaciente(Paciente* pac)
{
	pthread_mutex_lock(&m_MutexPac);

	m_Utilizador = pac;

	pthread_mutex_unlock(&m_MutexPac);
}

