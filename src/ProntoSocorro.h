// jrzanol
// 

#pragma once

class ProntoSocorro
{
public:
	ProntoSocorro();
	~ProntoSocorro();

	void ChegadaDePaciente(pthread_t th, int pacId);
	void Fechamento();
};
