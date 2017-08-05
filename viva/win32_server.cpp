#include "viva.h"

namespace viva
{
    namespace net
    {
        bool wsInitialized = false;
        WSAData wsadata;

        bool AcceptThread(Win32Server* server)
        {
            int size = sizeof(sockaddr_in);
            sockaddr_in address;
            SOCKET acceptedSocket;
            char hello[] = "Hello";

            while (!server->GetReturnAccept())
            {
                acceptedSocket = accept(server->GetSocket(), (sockaddr*)(&address), &size);

                if (acceptedSocket == INVALID_SOCKET)
                {
                    auto code = WSAGetLastError();
                    wstring msg = GetLastWinsockErrorMessage(code);
                    NetworkError err = { msg, code };
                    server->_AddError(err);
                }
                else
                {
                    int sent = 0;
                    while (sent < 5)
                    {
                        int temp = send(acceptedSocket, (const char*)hello + sent, 5 - sent, 0);
                        if (temp == SOCKET_ERROR)
                            return false;

                        sent += temp;
                    }

                    Win32Client* client = new Win32Client(acceptedSocket, address, "", 0);
                    server->_AddClient(client);
                }
            }

            return false;
        }

        bool ReceiveThread(Win32Client* client)
        {
            byte tempBuffer[256];

            while (!client->GetReturnReceive())
            {
                int len = recv(client->GetSocket(), (char*)tempBuffer, 256, NULL);

                if (len == SOCKET_ERROR)
                {
                    auto code = WSAGetLastError();
                    wstring msg = GetLastWinsockErrorMessage(code);
                    NetworkError err = { msg, code };
                    client->_AddError(err);
                }
                /*else if (len == 0)
                {
                    break;
                }*/

                client->_PushMsgBytes(tempBuffer, len);
            }

            return false;
        }

        int ConnectThread(Win32Client* client)
        {
            char buf[5] = { 0,0,0,0,0 };

            if (connect(client->GetSocket(), (sockaddr*)&(client->GetSockAddr()), sizeof(sockaddr_in)) == SOCKET_ERROR)
                return WSAGetLastError();

            // welcome protocol
            int received = 0;
            while(received < 5)
                received += recv(client->GetSocket(), (char*)buf, 5 - received, 0);

            if (memcmp(buf,"Hello",5) != 0)
                return 10060; // error 10060 is timed out

            client->_SetConnected(true);

            return 0;
        }

        wstring GetLastWinsockErrorMessage(DWORD errorCode)
        {
            wchar_t str[300];
            SecureZeroMemory(str, sizeof(wchar_t) * 300);
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 
                MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), str, 300, 0);
            return wstring(str);
        }

        class Win32Client : public Client
        {
        private:
            SOCKET handle;
            sockaddr_in address;
            
        public:
            Win32Client(SOCKET socket, sockaddr_in address, std::string ip, unsigned short port)
                : Client(ip, port), handle(socket), address(address)
            {
                isConnected = true;
            }

            Win32Client(std::string ip, unsigned short port)
                : Client(ip, port)
            {
                // WSAStartup
                if (!wsInitialized)
                {
                    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
                    if (res != 0)
                    {
                        wstring msg = GetLastWinsockErrorMessage(res);
                        throw viva::Error("WSAStartup", msg);
                    }

                    wsInitialized = true;
                }
                
                // socket()
                handle = socket(AF_INET, SOCK_STREAM, NULL);
                if (handle == INVALID_SOCKET)
                {
                    wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                    throw viva::Error("socket", msg);
                }
                id = (size_t)handle;

                // sockaddr_in
                SecureZeroMemory(&address, sizeof(address));
                address.sin_family = AF_INET;
                inet_pton(AF_INET, ip.c_str(), &(address.sin_addr));
                address.sin_port = htons(port);
            }

            void Connect(double timeoutSeconds) override
            {
                if (isConnected)
                    throw Error(__FUNCTION__, "Client is already running");

                msg.clear();
                timeOut = std::async(ConnectThread, this);
                timeOutHandler = routineManager->AddRoutine([&]()
                {
                    auto state = timeOut.wait_for(std::chrono::milliseconds(0));

                    if (state != std::future_status::ready)
                    {
                        closesocket(handle);
                        handle = socket(AF_INET, SOCK_STREAM, NULL);
                        id = (long long)handle;
                        WSASetLastError(10060);
                        wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                        NetworkError err = { msg, 10060 };
                        _AddError(err);
                    }
                    else if (timeOut.get() != 0)
                    {
                        closesocket(handle);
                        handle = socket(AF_INET, SOCK_STREAM, NULL);
                        id = (long long)handle;
                        WSASetLastError(10060);
                        wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                        NetworkError err = { msg, 10060 };
                        _AddError(err);
                    }
                    else
                    {
                        onConnectHandler();
                        receiveThread = std::async(ReceiveThread, this);
                    }

                    return 0;
                }, L"", timeoutSeconds, 0, 0);
            }

            SOCKET GetSocket() const
            {
                return handle;
            }

            sockaddr_in GetSockAddr() const
            {
                return address;
            }

            bool GetReturnReceive() const
            {
                return returnReceive;
            }

            void Send(byte* msg, unsigned short len) override
            {
                vector<byte> buf;
                buf.resize(2 + len);
                memcpy(buf.data(), &len, 2);
                memcpy(buf.data() + 2, msg, len);
                int sent = 0;

                while (sent < buf.size())
                {
                    int temp = send(handle, (char*)buf.data() + sent, buf.size() - sent, 0);

                    if (temp == SOCKET_ERROR)
                    {
                        wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                        throw viva::Error("Send", msg);
                    }

                    sent += temp;
                }
            }

            void Disonnect() override
            {
            }

            void Destroy() override
            {
            }
        };

        class Win32Server : public Server
        {
        private:
            sockaddr_in address;
            SOCKET handle;
        public:
            Win32Server(unsigned short port) : Server(port)
            {
                // WSAStartup
                if (!wsInitialized)
                {
                    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
                    if (res != 0)
                    {
                        wstring msg = GetLastWinsockErrorMessage(res);
                        throw viva::Error("WSAStartup", msg);
                    }

                    wsInitialized = true;
                }

                // socket()
                SecureZeroMemory(&address, sizeof(address));
                handle = socket(AF_INET, SOCK_STREAM, NULL);
                if (handle == INVALID_SOCKET)
                {
                    wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                    throw viva::Error("socket", msg);
                }

                // sockaddr
                address.sin_port = htons(port);
                address.sin_addr.s_addr = htonl(INADDR_ANY);
                address.sin_family = AF_INET;
                sockaddr* paddress = (sockaddr*)&address;

                // bind()
                if (bind((SOCKET)handle, paddress, (int)sizeof(sockaddr)) == SOCKET_ERROR)
                {
                    wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                    throw viva::Error("bind", msg);
                }
            }

            bool GetReturnAccept() const
            {
                return returnAccept;
            }

            SOCKET GetSocket() const
            {
                return handle;
            }

            void Start(int backlog) override
            {
                if (isRunning)
                    throw viva::Error(__FUNCTION__, L"Server already running");

                // listen()
                if (listen(handle, backlog) == SOCKET_ERROR)
                {
                    wstring msg = GetLastWinsockErrorMessage(WSAGetLastError());
                    throw viva::Error("listen", msg);
                }

                isRunning = true;

                acceptThread = std::async(AcceptThread, this);
            }

            void Stop() override
            {
            }

            void Destroy() override
            {
                activityRoutine->Destroy();
            }
        };
    }
}