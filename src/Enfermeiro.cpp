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

		if ((prox = g_PS.ProximoPaciente()) != NULL)
		{
			if (prox->m_SinalVital > 0)
			{
				int prev = prox->m_SinalVital;

				prox->m_SinalVital -= (rand() % 3) + 1;
				if (prox->m_SinalVital < 0)
					prox->m_SinalVital = 0;

				Log("Paciente %d teve seu Sinal Vital mudado de %d para %d.", prox->m_PacienteId, prev, prox->m_SinalVital);
			}

			if (prox->m_SinalVital == 0)
			{
				Log("Paciente %d esta em risco!", prox->m_PacienteId);
				g_PS.m_NiveisVitaisBaixo++;
			}

			prox->m_SendoExaminado = false;
		}

		Sleep(SLEEP_TIMER * 5);
	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

