// jrzanol
// 

#include "stdafx.h"
#include "ChefeEnfermeiro.h"
#include "ProntoSocorro.h"

ChefeEnfermeiro::ChefeEnfermeiro() : Pessoa(TipoPessoa::ChefeEnfermeiro)
{
}

ChefeEnfermeiro::~ChefeEnfermeiro()
{
}

void ChefeEnfermeiro::Executa()
{
	do
	{
		Paciente* prox = NULL;
		Nebulizador* neb = NULL;

		if ((neb = g_PS.ProximoNebulizador()) != NULL)
		{
			if ((prox = g_PS.ProximoPacienteNeb()) != NULL)
			{
				Sleep(SLEEP_TIMER);

				int timer = 2;

				if (prox->m_SinalVital < 6)
					timer++;
				else if (prox->m_SinalVital < 4)
					timer += 2;
				else if (prox->m_SinalVital < 2)
					timer += 3;

				neb->TrocaPaciente(prox);

				Sleep(SLEEP_TIMER * timer);

				neb->TrocaPaciente(NULL);
			}

			neb->m_SendoUtilizado = false;

			Sleep(SLEEP_TIMER);
		}

		Sleep(SLEEP_TIMER * 5);
	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

