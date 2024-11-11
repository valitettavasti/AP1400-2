#include "client.h"
#include "crypto.h"
#include <random>

Client::Client(std::string id, const Server& server)
    : id(std::move(id)), server(&server) {
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id()const{
    return this->id;
}

std::string Client::get_publickey() const{
    return this->public_key;
}

double Client::get_wallet() const{
    return this->server->get_wallet(get_id());
}

std::string Client::sign(std::string txt) const{
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) const{
    std::string trx;
    if (value <= get_wallet())
    {
        trx = get_id() + "-" + receiver + "-" + std::to_string(value);
        std::string signature = sign(trx);
        if(this->server->add_pending_trx(trx,signature)){
            return true;
        }
    }
    return false;
}

size_t Client::generate_nonce() const{
    std::mt19937 e(std::random_device{}());
    std::uniform_int_distribution<int> u(0, INT_MAX);
    return u(e);
}
