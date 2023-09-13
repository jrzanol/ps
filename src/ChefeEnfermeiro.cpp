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
				Log("Nebulizador %d esta sendo usado no Paciente %d.", neb->m_NebulizadorId, prox->m_PacienteId);

				neb->TrocaPaciente(prox);

				Sleep(SLEEP_TIMER);
			}
			else
				neb->m_SendoUtilizado = false;
		}

		Sleep(SLEEP_TIMER * 5);

	} while (!g_PS.Fechado() || g_PS.QntddPaciente() > 0);
}

