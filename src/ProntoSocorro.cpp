// jrzanol
// 

#include "stdafx.h"
#include "ProntoSocorro.h"

ProntoSocorro::ProntoSocorro()
{
	m_Iniciado = false;
	m_Fechado = false;

	m_Atendimentos = 0;
	m_Encaminhados = 0;
	m_NiveisVitaisBaixo = 0;

	pthread_mutex_init(&m_MutexMovPac, NULL);
	pthread_mutex_init(&m_MutexMedicos, NULL);
}

ProntoSocorro::~ProntoSocorro()
{
}

bool ProntoSocorro::Chegada(Pessoa* p)
{
	bool success = true;

	pthread_mutex_lock(&m_MutexMovPac);

	if (p->Tipo() == TipoPessoa::Paciente)
	{
		Paciente* pp = (Paciente*)p;

		if (m_ListPac.size() >= 16)
		{
			Log("Paciente %d foi encaminhado para outro lugar.", pp->m_PacienteId);
			success = false;
		}
		else
		{
			Log("Paciente %d entrou no Pronto Socorro.", pp->m_PacienteId);

			m_ListPac.push_back(pp);
		}
	}
	else
		m_ListMedicos.push_back(p);

	pthread_mutex_unlock(&m_MutexMovPac);
	return success;
}

void ProntoSocorro::Fechamento()
{
	m_Fechado = true;
}

Nebulizador* ProntoSocorro::ProximoNebulizador()
{
	Nebulizador* nebr = NULL;

	pthread_mutex_lock(&m_MutexMedicos);

	for (auto* it : m_ListMedicos)
	{
		if (it->Tipo() != TipoPessoa::Nebulizador)
			continue;

		Nebulizador* neb = (Nebulizador*)it;

		if (neb->m_SendoUtilizado)
			continue;

		neb->m_SendoUtilizado = true;

		nebr = neb;
		break;
	}

	pthread_mutex_unlock(&m_MutexMedicos);
	return nebr;
}

Paciente* ProntoSocorro::ProximoPaciente()
{
	long lower = -1, timer = _time32(0);
	Paciente* lowerPac = NULL;

	pthread_mutex_lock(&m_MutexMovPac);
	
	for (auto* it : m_ListPac)
	{
		if (it->m_SendoExaminado || it->m_UtilizandoNebulizador)
			continue;

		if (it->m_UltimaVezExaminado < lower)
		{
			lower = it->m_UltimaVezExaminado;
			lowerPac = it;
		}
	}

	if (lowerPac)
		lowerPac->m_SendoExaminado = true;

	pthread_mutex_unlock(&m_MutexMovPac);
	return lowerPac;
}

Paciente* ProntoSocorro::ProximoPacienteNeb()
{
	long lower = -1;
	Paciente* lowerPac = NULL;

	pthread_mutex_lock(&m_MutexMovPac);

	for (auto* it : m_ListPac)
	{
		if (it->m_SendoExaminado || it->m_UtilizandoNebulizador)
			continue;

		if (it->m_SinalVital < lower)
		{
			lower = it->m_SinalVital;
			lowerPac = it;
		}
	}

	if (lowerPac)
		lowerPac->m_UtilizandoNebulizador = true;

	pthread_mutex_unlock(&m_MutexMovPac);
	return lowerPac;
}

Paciente* ProntoSocorro::ProximoPacienteMed()
{
	long year = -1;
	Paciente* pac = NULL;

	pthread_mutex_lock(&m_MutexMovPac);

	for (auto* it : m_ListPac)
	{
		if (it->m_SendoExaminado || it->m_UtilizandoNebulizador)
			continue;

		if (it->m_Idade > year)
		{
			year = it->m_Idade;
			pac = it;
		}
	}

	if (pac)
		m_ListPac.remove(pac);

	pthread_mutex_unlock(&m_MutexMovPac);
	return pac;
}

void ProntoSocorro::RemovePaciente(Paciente* pac)
{
	pthread_mutex_lock(&m_MutexMovPac);

	if (pac)
		m_ListPac.remove(pac);

	pthread_mutex_unlock(&m_MutexMovPac);
}

void ProntoSocorro::Exibir()
{
	Log("Dados do Pronto Socorro:");
	Log("Atendimentos realizados: %d", m_Atendimentos);
	Log("Encaminhamentos realizados: %d", m_Encaminhados);
	Log("Niveis Vitais que ficaram baixos: %d", m_NiveisVitaisBaixo);
}

