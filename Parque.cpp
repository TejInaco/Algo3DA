#include "Parque.h"
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////////Infocartao
Info::Infocartao(string name): nome (nome){
	presente =false;
}


///////////////////////////////////////////////////////////////////////////////Parque de Estacionamento
/*
 * @Param  lotação do parque e o número máximo de clientes com acesso ao parque
 * vector<InfoCartao> clientes; //tinha posto a inicializacao do vector a zero
 * _> lotacao e numMaximoClientes sao const
 */
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
		lotacao(lot), numMaximoClientes(nMaxCli){
		vagas = lot; //o parque encontra-se vazio logo as vagas = a lotacao
}


/*
 * @Return - o índice no vetor clientes do cliente de nome nome, retornando -1 caso não exista
 */
int ParqueEstacionamento::posicaoCliente(const string & nome) const{
	for(unsigned int i=0; i < clientes.size(); i++){
			if (nome == clientes[i].nome)
				return i;
			}
	return -1;
}


/*
 *@Return o sucesso (true) ou insucesso (false) na adição/registo de um novo cliente ao
 *	parque de estacionamento. Considere que o cliente está inicialmente fora do parque
 *	Confirmar se o parque está cheio ou nao
 *	Ver se é um novo cliente ou nao
 *	se for adicionar cliente
 *
 */
bool ParqueEstacionamento::adicionaCliente(const string & nome){
	if (clientes.size() == numMaximoClientes)
		return false;
	if (posicaoCliente(nome) != -1) //ve se o cliente existe no vector
		return false;

	InfoCartao info;  // tenho de criar um objectodo tipi InfoCartao
	info.nome = nome;
	info.presente =false;
	clientes.push_back(info);
	return true;
}

/*
 * *dereference operators 
 *Retorna false se o cliente não puder entrar
 * A forma com eu vazia era da forma velha: logo
 * A stl way é como representada neste exemplo em baixo
 */
bool ParqueEstacionamento::retiraCliente(const string & nome){
	for(vector<InfoCartao>::iterator it =clientes.begin(): it != clientes.end(); it++){
		if ( (*it).nome == nome){
				clientes.erase(it);
				return true;
		}
		else{return false};
	}
	return false;
}

/*
 *tem que verificar se o cliente existe no vector clientes
 *se existem tem cartao
 *se verifica se já entrou
 *se tudo antes ok entao muda-se o estado presente
 */
bool ParqueEstacionamento::entrar(const string & nome){
	int pos = posicaoCliente(nome);

	if (pos== -1)
		return false;
	else {
		if(clientes[pos].presente == true)
			return false;
		else{
			if (vagas == 0)
				return false;
			else{
				clientes[pos].presente = true;
				vagas--;
				return true;
				}
			}
		}
}

/*
 * Regista a saida do clinte
 */
bool ParqueEstacionamento::sair(const string & nome){
	int pos = posicaoCliente(nome);
	if (pos == -1) return false;
	if(clientes[pos].presente == false)
		return false;
	else{
		clientes[pos].presente = false;
		vagas++;
		return true;
	}
}


///////////////////////////////////////////////////////////////////////// Get methods
/*
 * @Return lotacao do parque
 */
unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

/*
 * @Return Numero de Maximo de clientes
 */
unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}

/*
 * tb podiamos por "return lotacao-vagas"
 */
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	unsigned int lugaresOcupados = lotacao - vagas;
	return lugaresOcupados;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size;
}

/*Incrementa o parque de um valor p2. Equivale a adicionar ao clientes deste parque os clientes de p2.
 * Se tale excede o numero maximo de clientes do parqe, só sao adicionados os primeiros clientes p2 até
 * esse liite máximo
 *
 *Nota: this means pointer to the object, so *this is an object. So you are returning an object ie,
 * *this returns a reference to the object.
 */
const ParqueEstacionamento::ParqueEstacionamento & operator += (const ParqueEstacionamento & p2){
	for (vector<InfoCartao>::const_iterator it = p2.clientes.begin(); it != p2.clientes.end(); it++){
		adicionaClientes(it->nome);
		if (clientes.size() == numMaximoClientes) break;
	}
	return *this;
}

/*
 Compound Assignment Operators += -= *=

I discuss these before the arithmetic operators for a very specific reason, but we will get to that in a moment. The important point is that these are destructive operators, because they update or replace the values on the left-hand side of the assignment. So, you write:

  MyClass a, b;
  ...
  a += b;    // Same as a.operator+=(b)
In this case, the values within a are modified by the += operator.
How those values are modified isn't very important - obviously, what MyClass represents will dictate what these operators mean.

The member function signature for such an operator should be like this:

  MyClass & MyClass::operator+=(const MyClass &rhs) {
    ...
  }
We have already covered the reason why rhs is a const-reference. And, the implementation of such an operation should also be straightforward.
But, you will notice that the operator returns a MyClass-reference, and a non-const one at that. This is so you can do things like this:

  MyClass mc;
  ...
  (mc += 5) += 3;
Don't ask me why somebody would want to do this, but just like the normal assignment operator, this is allowed by the primitive data types. Our user-defined datatypes should match the same general characteristics of the primitive data types when it comes to operators, to make sure that everything works as expected.

This is very straightforward to do. Just write your compound assignment operator implementation, and return *this at the end, just like for the regular assignment operator. So, you would end up with something like this:

  MyClass & MyClass::operator+=(const MyClass &rhs) {
    ...   // Do the compound assignment work.

    return *this;
  }
As one last note, in general you should beware of self-assignment with compound assignment operators as well. Fortunately, none of the C++ track's labs require you to worry about this, but you should always give it some thought when you are working on your own classes.
 */
 */
