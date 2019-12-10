/*
Verificação cíclica de redundância (CRC):
Código de detecção de erros que são dados adicionais adicionados a uma determinada mensagem digital para nos ajudar a detectar se ocorreu algum erro durante a transmissão da mensagem.
A abordagem básica usada para a detecção de erros é o uso de bits de redundância, onde bits adicionais são adicionados para facilitar a detecção de erros.

*/

#include<iostream>

using namespace std;

string xorfunction( string encoded , string crc)							//Operação XOR bit a bit
{
	int crclen = crc.length();

	for ( int i = 0 ; i <= (encoded.length() - crclen) ; )			// executando operação xor bit a bit
	{																// " 0 xor 0 = 0"     " 1 xor 1 = 0 "
		for( int j=0 ; j < crclen ; j++)							// " 0 xor 1 = 1 "    " 1 xor 0 = 1"
		{
			encoded[i+j] = encoded[i+j] == crc[j] ? '0' : '1' ;			//se bit codificado e bit crc forem iguais, substitua-o por zero
		}
	for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;

	}

	return encoded;
}

int main()
{
	string data , crc , encoded = "";
	cout<<endl<<"-----------Remetente --------------"<<endl;
	cout<<"Inserir bits de dados: "<<endl;
	cin>>data;														//bits de dados a serem transmitidos

	cout<<"Digite o polimônio gerador: "<<endl;
	cin>>crc;														//crc - polinômio do gerador

	encoded += data;			//bits codificados são inicializados em bits de dados

	int datalen = data.length();
	int crclen = crc.length();

	for(int i=1 ; i <= (crclen - 1) ; i++)
		encoded += '0';			//anexando comprimento de (gerador polinomial -1) número de zeros aos bits codificados

	encoded = xorfunction(encoded , crc);	//executando xor bit a bit para obter

	cout<<"A soma de verificação gerada é: ";
	cout<<encoded.substr(encoded.length() - crclen + 1)<<endl<<endl;   //bits de dados + bit de soma de verificação é o que será enviado para o receptor
	cout<<"Mensagem a ser transmitida: ";
	cout<<data + encoded.substr(encoded.length() - crclen + 1);    	//esta é a mensagem que será enviada ao receptor




	cout<<endl<<"---------------Receptor-----------------"<<endl;


    	string msg;
	cout<<"Digite a mensagem recebida: "<<endl;             //O receptor entra na mensagem recebida
	cin>>msg;

	msg = xorfunction( msg , crc);

	for( char i : msg.substr(msg.length() - crclen + 1))	//depois de executar xor, se os últimos bits forem zero, não haverá erro na transmissão
		if( i != '0' )
			{
				cout<<"Erro na transmissão!!! "<<endl;	//se bits não forem zero; ERRO NA TRANSMISSÃO
				return 0;
			}

	cout<<"Nenhum erro!"<<endl;												//bit a bit xor é realizado entre os bits recebidos e os bits crc do gerador
	return 0;
}
