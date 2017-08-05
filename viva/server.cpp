#include "viva.h"

namespace viva
{
    namespace net
    {
        struct NetworkError
        {
            wstring message;
            int code;
        };

        class Base
        {
        protected:
            size_t id;
            std::queue<NetworkError> errors;
            std::mutex errorQueueMutex;
            std::function<void(const NetworkError& error)> onErrorHandler;
            IRoutine* activityRoutine;
        public:
            void _AddError(const NetworkError& error)
            {
                errorQueueMutex.lock();
                errors.push(error);
                errorQueueMutex.unlock();
            }

            size_t GetId() const
            {
                return id;
            }

            void OnError(const std::function<void(const NetworkError& error)>& handler)
            {
                onErrorHandler = handler;
            }
        };

        class Client : public net::Base
        {
        protected:
            std::string ip;
            unsigned short port;
            std::function<void()> onConnectHandler;
            std::function<void(const vector<byte>&)> onMsgHandler;
            bool isConnected;
            bool returnReceive;
            IRoutine* timeOutHandler;
            std::future<int> timeOut;
            std::future<bool> receiveThread;
            std::mutex msgQueueMutex;
            std::vector<byte> msg;
        public:
            Client(std::string _ip, unsigned short _port)
                : ip(_ip), port(_port), isConnected(false), timeOutHandler(nullptr), returnReceive(false)
            {
                activityRoutine = routineManager->AddRoutine([this]()
                {
                    this->_Activity();
                    return 1;
                }, L"", 0, 0, 0);
            }

            void OnConnect(const std::function<void()>& handler)
            {
                onConnectHandler = handler;
            }

            void OnMsg(const std::function<void(const vector<byte>&)>& handler)
            {
                onMsgHandler = handler;
            }

            void _Activity()
            {
                _ProcessMsg();
            }

            void _PushMsgBytes(byte* arr, int len)
            {
                msgQueueMutex.lock();
                size_t size = msg.size();
                msg.resize(msg.size() + len);
                memcpy(msg.data() + size, arr, len);
                msgQueueMutex.unlock();
            }

            void _ProcessMsg()
            {
                if (msg.size() > 0)
                {
                    msgQueueMutex.lock();
                    unsigned short size;
                    memcpy(&size, msg.data(), sizeof(unsigned short)); // endianess problem

                    if (msg.size() < size + 2)
                    {
                        msgQueueMutex.unlock();
                        return;
                    }

                    vector<byte> completeMsg(msg.begin() + 2, msg.begin() + 2 + size);
                    msg.erase(msg.begin(), msg.begin() + 2 + size);
                    msgQueueMutex.unlock();

                    if (onMsgHandler)
                        onMsgHandler(completeMsg);
                }
            }
            
            void _SetConnected(bool val)
            {
                isConnected = val;
            }

            const wstring& GetIp() const
            {
                return wstring(ip.begin(), ip.end());
            }

            void Send(vector<byte>& msg)
            {
                Send(msg.data(), (unsigned short)msg.size());
            }

            virtual void Send(byte* msg, unsigned short len) = 0;
            virtual void Connect(double timeoutSeconds) = 0;
            virtual void Disonnect() = 0;
            virtual void Destroy() = 0;
        };

        class Server : public net::Base
        {
        protected:
            unsigned short port;
            std::function<void(Client* c)> onConnectHandler;
            std::function<void(Client* c)> onDisconnectHandler;
            std::mutex errorQueueMutex;
            std::mutex clientQueueMutex;            
            std::queue<Client*> clients; // first clients are coming to queue
            vector<Client*> ackedClients; // main thread grabs clients from queue, calls onconnect callback and moves from queue to vector
            bool isRunning;
            bool returnAccept;
            std::future<bool> acceptThread;
            
        public:
            Server(unsigned short _port)
                : port(_port), isRunning(false), returnAccept(false)
            {
                activityRoutine = routineManager->AddRoutine([this]()
                {
                    this->_Activity();
                    return 1;
                }, L"", 0, 0, 0);
            }

            void OnConnect(const std::function<void(Client* c)>& handler)
            {
                onConnectHandler = handler;
            }

            void OnDisconnect(const std::function<void(Client* c)>& handler)
            {
                onDisconnectHandler = handler;
            }

            const vector<Client*>& GetClients() const
            {
                return ackedClients;
            }

            void _AddClient(Client* client)
            {
                clientQueueMutex.lock();
                clients.push(client);
                clientQueueMutex.unlock();
            }

            void _Activity()
            {
                if (clients.size() > 0)
                {
                    clientQueueMutex.lock();
                    Client* client = clients.front();
                    clients.pop();
                    clientQueueMutex.unlock();

                    ackedClients.push_back(client);
                    onConnectHandler(client);
                }
            }

            virtual void Start(int backlog) = 0;
            virtual void Stop() = 0;
            virtual void Destroy() = 0;
        };
    }
}