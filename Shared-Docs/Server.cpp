#include "Server.h"

Server::Server()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("0.0.0.0");

	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (::listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	cout << "Listening on port " << port << endl;

	while (true)
	{
		cout << "Waiting for client connection request" << endl;
		accept();
	}
}


/*
accept new client(create new socket and thread for him and back to the last function to listen to anther users)
*/
void Server::accept()
{
	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	thread* temp;
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	cout << "Client accepted. Server and client can speak" << endl;

	// the function that handle the conversation with the client
	mtx.lock();
	sockets.push_back(client_socket);
	temp = new thread(&Server::clientHandler, this, client_socket);

	mtx.unlock();
}
/*
find who the next user
*/
string Server::get_next_user(int i)
{
	string next_user = "";
	if (users.size() > i + 1)
	{
		next_user = users[i + 1];
	}
	else if (i == users.size() - 1 && users.size() > 1)
	{
		next_user = users[0];
	}
	return next_user;
}
/*
update the shared file after the user finish to edit
*/
string Server::update_file(SOCKET clientSocket)
{
	int size;
	string text;
	ofstream shared_file;
	size = help.getIntPartFromSocket(clientSocket, 5);
	text = help.getStringPartFromSocket(clientSocket, size);
	shared_file.open(FILE_NAME, ofstream::out | ofstream::trunc);
	shared_file << text;
	shared_file.close();
	return text;
}
/*
caregiver of the client
*/
void Server::clientHandler(SOCKET clientSocket)
{
	string name;
	int msg_type = 0;
	int count = 0;
	try
	{
		while (msg_type != MT_CLIENT_EXIT)//208
		{
			msg_type = help.getMessageTypeCode(clientSocket);
			if (msg_type == MT_CLIENT_LOG_IN)//200
			{
				mtx.lock();
				name = user_login(clientSocket);
				mtx.unlock();
			}
			else if (msg_type == MT_CLIENT_UPDATE)//204
			{
				mtx.lock();
				count++;
				if (count > 3)
				{
					count = 0;
				}
				send_101_msg_to_all_users(update_file(clientSocket));
				mtx.unlock();
			}
			else if (msg_type == MT_CLIENT_FINISH || count == 3)//207
			{
				mtx.lock();
				count = 0;
				change_edit_queue(clientSocket);
				mtx.unlock();
			}
		}
		mtx.lock();
		disconnect_client(clientSocket,name);
		mtx.unlock();
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}
/*
This function disconnect from the client that exit and send 101 msg to all users
*/
void Server::disconnect_client(SOCKET clientSocket,string name)
{
	string text;
	ifstream shared_file;
	vector<string>::iterator user_name_it;
	vector<SOCKET>::iterator user_socket_it;
	user_socket_it = find(sockets.begin(), sockets.end(), clientSocket);
	user_name_it = find(users.begin(), users.end(), name);
	sockets.erase(user_socket_it);
	users.erase(user_name_it);
	send_101_msg_to_all_users(read_shared_file());
	closesocket(clientSocket);
}
/*
send 101 to all users
*/
void Server::send_101_msg_to_all_users(string text)
{
	int i;
	for (i = 0; i < sockets.size(); i++)
	{
		help.sendUpdateMessageToClient(sockets[i], text, users[0], get_next_user(i), i + 1);
	}
}
/*
send 101 msg to all users after user ask to log in 
*/
string Server::user_login(SOCKET clientSocket)
{
	string text;
	int size;
	string username;
	size = help.getIntPartFromSocket(clientSocket, 2);
	username = help.getStringPartFromSocket(clientSocket, size);
	users.push_back(username);
	text = read_shared_file();
	help.sendUpdateMessageToClient(clientSocket, text, users[0], get_next_user(0), users.size());
	return username;
}
/*
return the data in the shared file
*/
string Server::read_shared_file()
{
	ifstream shared_file;
	string text;
	string line;
	shared_file.open(FILE_NAME);
	while (getline(shared_file, line))
	{
		text += line;
	}
	cout << text << endl;
	shared_file.close();
	return text;
}
/*
after the user finish to edit the function put him in the 
back of the queue and send 101 msg to all users
*/
void Server::change_edit_queue(SOCKET clientSocket)
{
	SOCKET temp;
	string name;
	name = users[0];
	users.erase(users.begin());
	users.push_back(name);
	temp = sockets[0];
	sockets.erase(sockets.begin());
	sockets.push_back(temp);
	send_101_msg_to_all_users(update_file(clientSocket));
}
