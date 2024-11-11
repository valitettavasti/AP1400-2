#include "server.h"
#include <crypto.h>
#include <random>
#include <regex>

std::vector<std::string> pending_trxs{};

Server::Server(){
   Server::clients = std::map<std::shared_ptr<Client>, double>();
}

std::shared_ptr<Client> Server::add_client(std::string id){
    if(!clients.empty()){
        if(get_client(id) != nullptr){
            std::mt19937 e(std::random_device{}());
            std::uniform_int_distribution u(1000, 9999);
            auto number = u(e);
            id = id + std::to_string(number);
        }
    }
    Client client(id,*this); 
    auto clientPtr = std::make_shared<Client>(client);
    clients.insert(std::make_pair(clientPtr,5.00));
    return clientPtr;
}

std::shared_ptr<Client> Server::get_client(std::string id) const{
    for(auto it = clients.begin();it !=clients.end();++it){
        if (it->first->get_id() == id){
            return it->first;
        }
    }
    return nullptr;
}

double Server::get_wallet(const std::string id) const{
     for(auto it = clients.begin();it !=clients.end();++it){
        if (it->first->get_id() == id){
            return it->second;
        }
    }
    return 0;   //考虑是不是没有这个人
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value){
    std::regex reg("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
    std::smatch m;
    if(std::regex_match(trx,m,reg)){
        sender = m.str(1);
        receiver = m.str(2);
        value = std::stod(m.str(3));
        return true;
    }else{
        throw std::runtime_error("This trx doesn't match!");
    }
    return false;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender;
    std::string receiver;
    double value;
    if(parse_trx(trx,sender,receiver,value)){
        if(get_client(sender)!=nullptr&&get_client(receiver)!=nullptr&&crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature)){
            pending_trxs.push_back(trx);
            return true;
        }
    }
    return false;
}

size_t Server::mine(){
    std::string mempool{};
    if(!pending_trxs.empty()){
        for(auto trx:pending_trxs){
            mempool = mempool + trx;
        }
    }
    size_t nonce = 0;
    bool is_found = false;
    while(!is_found){
        for(auto client_pair:clients){
            nonce= client_pair.first->generate_nonce();
            std::string mempool_nonce = mempool + std::to_string(nonce);
            std::string hash{crypto::sha256(mempool_nonce).substr(0,10)};
            if(hash.find("000")!=std::string::npos){
                client_pair.second += 6.25;
                std::cout<<client_pair.first->get_id();
                for(auto trx:pending_trxs){
                    std::string sender;
                    std::string receiver;
                    double value;
                    parse_trx(trx,sender,receiver,value);
                    clients[get_client(sender)]-=value;
                    clients[get_client(receiver)]+=value;
                }
                pending_trxs.clear();
                is_found =true;
                break;
            }
        }
    }
    return nonce;
}

 void  show_wallets(const  Server& server)
 {
 	std::cout << std::string(20, '*') << std::endl;
 	for(const auto& client: server.clients)
 		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
 	std::cout << std::string(20, '*') << std::endl;
 }