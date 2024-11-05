#pragma once

#include "client.h"
#include "tcpclient.h"
#include "tlssession.h"
#include <openssl/ssl.h>
#include <openssl/provider.h>
#include <cstdlib>
#include <string>

struct TlsClient : public Client, public TlsSession {
    TcpClient tcpClient_;
    SSL_CTX *ctx_{nullptr};

    int config_ctx();
    bool connect(Ip ip, int port) override;

    // oqsprovider 로드 함수
    int load_oqs_provider();

    // 환경 변수 설정 확인 함수
    void check_env_path();
};
