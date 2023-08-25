// jrzanol
// 

#include "stdafx.h"
#include "Medico.h"
#include "ProntoSocorro.h"

Medico::Medico() : Pessoa(TipoPessoa::Medico)
{
	m_TempoNecessario = 0;
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

			printf("Paciente %d esta sendo atendido pelo Medico.\n", prox->m_PacienteId);

			Sleep(SLEEP_TIMER * m_TempoNecessario);

			prox->m_SinalVital = 10;
			prox->m_RecebeuAlta = true;

			printf("Paciente %d recebeu alta.\n", prox->m_PacienteId);
		}

	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

