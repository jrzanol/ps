// jrzanol
// 

#include "stdafx.h"
#include "ProntoSocorro.h"

ProntoSocorro::ProntoSocorro()
{
	m_Fechado = false;

	pthread_mutex_init(&m_MutexMovPac, NULL);
}

ProntoSocorro::~ProntoSocorro()
{
}

void ProntoSocorro::Chegada(Pessoa* p)
{
	pthread_mutex_lock(&m_MutexMovPac);

	if (p->Tipo() == TipoPessoa::Paciente)
	{
		Paciente* pp = (Paciente*)p;

		if (m_ListPac.size() >= 16)
			printf("Paciente %d foi encaminhado para outro lugar.\n", pp->m_PacienteId);
		else
		{
			printf("Paciente %d entrou no Pronto Socorro.\n", pp->m_PacienteId);

			m_ListPac.push_back(pp);
		}
	}
	else
		m_ListMedicos.push_back(p);

	pthread_mutex_unlock(&m_MutexMovPac);
}

void ProntoSocorro::Fechamento()
{
	m_Fechado = true;
}

