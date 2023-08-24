// jrzanol
// 

#pragma once
#include "Pessoa.h"
#include "Paciente.h"
#include "Medico.h"
#include "ChefeEnfermeiro.h"
#include "Enfermeiro.h"

class ProntoSocorro
{
public:
	ProntoSocorro();
	~ProntoSocorro();

	void Chegada(Pessoa*);
	void Fechamento();

private:
	bool m_Fechado;

	pthread_mutex_t m_MutexMovPac;

	std::list<Paciente*> m_ListPac;
	std::list<Pessoa*> m_ListMedicos;
};

