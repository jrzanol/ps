// jrzanol
// 

#pragma once
#include "Pessoa.h"
#include "Paciente.h"
#include "Medico.h"
#include "ChefeEnfermeiro.h"
#include "Enfermeiro.h"
#include "Nebulizador.h"

class ProntoSocorro
{
public:
	ProntoSocorro();
	~ProntoSocorro();

	void Iniciar() { m_Iniciado = true; }
	bool Fechado() { return m_Iniciado && m_Fechado; }

	int QntddPaciente();
	bool Chegada(Pessoa*);
	void Fechamento();

	Nebulizador* ProximoNebulizador();

	Paciente* ProximoPaciente();
	Paciente* ProximoPacienteNeb();
	Paciente* ProximoPacienteMed();
	void RemovePaciente(Paciente*);

	void Exibir();

	int m_NiveisVitaisBaixo;

private:
	bool m_Iniciado;
	bool m_Fechado;

	int m_Atendimentos;
	int m_Encaminhados;

	pthread_mutex_t m_MutexMovPac; // Mutex para m_ListPac.
	pthread_mutex_t m_MutexMedicos; // Mutex para m_ListMedicos.

	std::list<Paciente*> m_ListPac;
	std::list<Pessoa*> m_ListMedicos;

	bool MedicoEstaEsperando();
};

extern ProntoSocorro g_PS;

