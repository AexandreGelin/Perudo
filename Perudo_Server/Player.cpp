#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <thread>
#include "Player.h"
#include "Output.h"

#ifdef _WIN32
Player::Player(int id, SOCKET socket, const int MAXDATASIZE) : id(id), socket(socket), MAXDATASIZE(MAXDATASIZE), is_alive(true)
{
	buffer = new char[MAXDATASIZE];
}
#else
Player::Player(int id, int socket, const int MAXDATASIZE) : id(id), socket(socket), MAXDATASIZE(MAXDATASIZE), is_alive(true)
{
	buffer = new char[MAXDATASIZE];
}
#endif

Player::~Player()
{
	end_thread();
	delete[] buffer;
}

bool Player::close_socket()
{
	if (socket == NULL || !is_alive)
		return true;

	int result;
	Output::GetInstance()->print("[PLAYER_", id, "] Closing client socket...\n");

#ifdef _WIN32
	result = closesocket(socket);
#else
	result = close(socket);
#endif

	if (result == -1) {
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[PLAYER_%d] Error while closing socket ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return false;
	}
	else {
		Output::GetInstance()->print("[PLAYER_", id, "] Player socket closed successfully.\n");
	}

	return true;
}
bool Player::send_message(const char* buffer)
{
	if (socket == NULL || !is_alive)
		return false;

	if (send(socket, buffer, strlen(buffer), 0) == -1) {
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[PLAYER_%d] Error while sending message to client ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return false;
	}

	return true;
}
int Player::recv_message()
{
	if (socket == NULL || !is_alive)
		return -1;

	int length;
	if ((length = recv(socket, buffer, MAXDATASIZE, 0)) == -1)
	{
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[PLAYER_%d] Error while receiving message from client ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return length;
	}

	// Suppression des retours chariots (\n et \r)
	while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r'))
		length--;
	// Ajout de backslash zero a la fin pour en faire une chaine de caracteres
	if (length >= 0 && length < MAXDATASIZE)
		buffer[length] = '\0';

	return length;
}

void Player::execute_thread()
{
	int length;
	time_t time_value;
	struct tm* time_info;

	Output::GetInstance()->print("[PLAYER_", id, "] Thread client starts with id=", id, ".\n");

	// Boucle infinie pour le player
	while (1) {

		if (socket == NULL || !is_alive) {
			send_message("[SERVER] : Tu peux plus jouer la frérot");
			return;
		}

		// On attend un message du player
		if ((length = recv_message()) == -1) {
			break;
		}

		if (socket == NULL || !is_alive) {
			send_message("[SERVER] : Tu peux plus jouer la frérot");
			return;
		}

		// Affichage du message
		Output::GetInstance()->print("[PLAYER_", id, "] Message received : ", buffer, "\n");

		if (strcmp(buffer, "DISCONNECT") == 0) {
			break;
		}
		else {
			// On recupere l'heure et la date
			time(&time_value);
			time_info = localtime(&time_value);

			// Traitement du message reçu
			if (strcmp(buffer, "DATE") == 0)
				strftime(buffer, MAXDATASIZE, "%e/%m/%Y", time_info);
			else if (strcmp(buffer, "DAY") == 0)
				strftime(buffer, MAXDATASIZE, "%A", time_info);
			else if (strcmp(buffer, "MONTH") == 0)
				strftime(buffer, MAXDATASIZE, "%B", time_info);
			else if (strcmp(buffer, "READY") == 0) {
				send_message("[SERVER] : Player ready");
				is_ready = true;
				Output::GetInstance()->print("[PLAYER_", id, "] is ready \n");
			}
			else if (strcmp(buffer, "NTM") == 0) {
				send_message(buffer);
				is_ready = false;
				Output::GetInstance()->print("[PLAYER_", id, "] is not ready \n");
			}
			else
				sprintf(buffer, "%s is not recognized as a valid command", buffer);

			if (socket == NULL || !is_alive) {
				return;
			}

			// On envoie le buffer
			Output::GetInstance()->print("[PLAYER_", id, "] Sending message \"", buffer, "\" to client...\n");
			if (!send_message(buffer)) {
				break;
			}

			Output::GetInstance()->print("[PLAYER_", id, "] Message \"", buffer, "\" send to client successfully.\n");
		}
	}

	end_thread();
}

void Player::start_thread()
{
	join_thread();
	// Start player thread
	thread = std::thread(&Player::execute_thread, this);
}

void Player::end_thread()
{
	if (!is_alive)
		return;

	Output::GetInstance()->print("[PLAYER_", id, "] Thread client is ending...\n");

	// Sending close connection to player
	send_message("CONNECTION_CLOSED");

	is_alive = false;

	// End thread
	thread.detach();
	thread.~thread();

	// Close connection
	close_socket();

	Output::GetInstance()->print("[PLAYER_", id, "] Thread client ends.\n");
}

void Player::join_thread()
{
	if (thread.joinable()) {
		thread.join();
	}
}
