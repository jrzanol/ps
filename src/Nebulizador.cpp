// jrzanol
// 

#include "stdafx.h"
#include "Nebulizador.h"
#include "ProntoSocorro.h"

Nebulizador::Nebulizador() : Pessoa(TipoPessoa::Nebulizador)
{
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
				Sleep(SLEEP_TIMER);

				m_Utilizador->m_SinalVital += (rand() % 3) + 2;

				if (m_Utilizador->m_SinalVital > 10)
					m_Utilizador->m_SinalVital = 10;

				Sleep(SLEEP_TIMER);
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

