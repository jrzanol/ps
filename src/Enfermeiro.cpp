// jrzanol
// 

#include "stdafx.h"
#include "Enfermeiro.h"
#include "Paciente.h"
#include "ProntoSocorro.h"

Enfermeiro::Enfermeiro() : Pessoa(TipoPessoa::Enfermeiro)
{
}

Enfermeiro::~Enfermeiro()
{
}

void Enfermeiro::Executa()
{
	do
	{
		Paciente* prox = NULL;

		while ((prox = g_PS.ProximoPaciente()) != NULL)
		{
			Sleep(SLEEP_TIMER);

			if (prox->m_SinalVital > 0)
			{
				int prev = prox->m_SinalVital;
				prox->m_SinalVital -= (rand() % 2) + 1;

				printf("Paciente %d teve seu Sinal Vital mudado de %d para %d.\n", prox->m_PacienteId, prev, prox->m_SinalVital);
			}
			else
				printf("Paciente %d esta em risco!\n", prox->m_PacienteId);

			Sleep(SLEEP_TIMER);
		}

		Sleep(SLEEP_TIMER * 5);
	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

