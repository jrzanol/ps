// jrzanol
// 

#include "stdafx.h"
#include "Medico.h"
#include "ProntoSocorro.h"

Medico::Medico() : Pessoa(TipoPessoa::Medico)
{
	Waiting = true;
}

Medico::~Medico()
{
}

void Medico::Executa()
{
	do
	{
		Paciente* prox = NULL;

		if ((prox = g_PS.ProximoPacienteMed()) != NULL)
		{
			Waiting = false;
			prox->m_SinalVital = 10;

			Sleep(SLEEP_TIMER);

			Log("Paciente %d esta sendo atendido pelo Medico.", prox->m_PacienteId);

			int tempoNecessario = (rand() % 20) + 30;
			Sleep(SLEEP_TIMER * tempoNecessario);

			prox->m_RecebeuAlta = true;

			Log("Paciente %d recebeu alta.", prox->m_PacienteId);

			Sleep(SLEEP_TIMER);
		}

		Waiting = true;

		Sleep(SLEEP_TIMER * 5);
	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

