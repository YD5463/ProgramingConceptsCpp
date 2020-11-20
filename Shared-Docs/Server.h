#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include "Helper.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>

#define FILE_NAME "shared_doc.txt"
using namespace std;

class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	vector<SOCKET> sockets;
	mutex mtx;
	Helper help;
	vector<string> users;
	SOCKET _serverSocket;
	string get_next_user(int i);
	string update_file(SOCKET clientSocket);
	void accept();
	void clientHandler(SOCKET clientSocket);
	void disconnect_client(SOCKET clientSocket, string name);
	void send_101_msg_to_all_users(string text);
	string user_login(SOCKET clientSocket);
	string read_shared_file();
	void change_edit_queue(SOCKET clientSocket);
};

