// jrzanol
// 

#include "stdafx.h"
#include "Medico.h"
#include "ProntoSocorro.h"

Medico::Medico() : Pessoa(TipoPessoa::Medico)
{
}

Medico::~Medico()
{
}

void Medico::Executa()
{
	do
	{
		Sleep(SLEEP_TIMER * 5);

		Paciente* prox = NULL;

		if ((prox = g_PS.ProximoPacienteMed()) != NULL)
		{
			Sleep(SLEEP_TIMER);

			Log("Paciente %d esta sendo atendido pelo Medico.", prox->m_PacienteId);

			int tempoNecessario = (rand() % 10) + 20;
			Sleep(SLEEP_TIMER * tempoNecessario);

			prox->m_SinalVital = 10;
			prox->m_RecebeuAlta = true;

			Log("Paciente %d recebeu alta.", prox->m_PacienteId);
		}

	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

