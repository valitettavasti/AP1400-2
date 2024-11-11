#ifndef SERVER_H
#define SERVER_H
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "client.h"

class Client;

extern std::vector<std::string> pending_trxs;
class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id)const;
	double get_wallet(const std::string id) const;
	static bool parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value);
	bool add_pending_trx(std::string trx, std::string signature) const;
	size_t mine();
	friend void show_wallets(const  Server& server); 
private:
	std::map<std::shared_ptr<Client>, double> clients;
};



#endif //SERVER_H