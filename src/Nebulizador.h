// jrzanol
// 

#pragma once
#include "Paciente.h"

class Nebulizador : public Pessoa
{
public:
	Nebulizador();
	~Nebulizador();

	void Executa();
	void TrocaPaciente(Paciente*);

	int m_NebulizadorId;
	bool m_SendoUtilizado;

private:
	Paciente* m_Utilizador;
	int m_Count;

	pthread_mutex_t m_MutexPac;
};

