#pragma once

#include <list>
#include <mutex>
#include <thread>

#include "server.h"
#include "tlssession.h"
#include <openssl/ssl.h>
#include <openssl/provider.h>
#include <cstdlib>
#include <string>

struct TlsServer : public Server {
    int acceptSock_;
    SSL_CTX *ctx_;

    struct TlsSessionList : std::list<TlsSession*> {
    protected:
        std::mutex m_;
    public:
        void lock() { m_.lock(); }
        void unlock() { m_.unlock(); }
    } sessions_;

    std::string pemFileName_;
    bool start(int port) override;
    bool stop() override;

private:
    std::thread* acceptThread_{nullptr};
    void acceptRun();
    void _run(TlsSession* session);

    // oqsprovider 로드 함수
    int load_oqs_provider();

    // 환경 변수 설정 확인 함수
    //void check_env_path();

    // SSL_CTX 초기화 함수
    //bool init_ssl_context();
};
