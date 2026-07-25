#include "network.h"
#include "client/client.h"
#include "server/server.h"
#include "peer/peer.h"

std::unique_ptr<P2PConnection> p2p;
std::unique_ptr<RaymanClient> client;
std::unique_ptr<RaymanServer> server;
NetworkState state = NetworkState::NONE;
std::string username = "User";
long long bootTime = 0;

bool NTW_IsRunningServer() {
	return server != nullptr;
}

std::string NTW_GetUsername() {
	return username;
}

void NTW_SetUsername(std::string name) {
	if (name.length() >= 64) {
		LOG_Print("Invalid username, cannot exceed 64 characters!");
		return;
	}
	username = name;
	FILE* f = fopen("mp_settings.conf", "wb");
	if (f) {
		size_t len = username.size();
		fwrite(&len, sizeof(len), 1, f);
		fwrite(username.data(), 1, len, f);
		fclose(f);
	}
	LOG_Print("Username is now: %s", username.data());
}

long long NTW_GetBootTime() {
	return bootTime;
}

NetworkState NTW_GetState() {
	return state;
}

const char* GetStateName(NetworkState state) {
	switch (state) {
	case NetworkState::NONE: return "NONE";
	case NetworkState::SEARCHING: return "SEARCHING";
	case NetworkState::WAITING: return "WAITING";
	case NetworkState::HANDSHAKE: return "HANDSHAKE";
	case NetworkState::PLAYER: return "PLAYER";
	}
	return "UNKNOWN";
}

void NTW_ResetState() {
	// Destroy any created connections and reset to none so we can restart the process
	if (p2p != nullptr) {
		p2p->destroy();
		p2p = nullptr;
	}
	LOG_Print("State %s -> %s", GetStateName(state), GetStateName(NetworkState::NONE));
	state = NetworkState::NONE;
}

bool NTW_SetState(NetworkState from, NetworkState to) {
	// Update the state if it's coming from the correct one and debug print about it
	if (state != from) return false;
	state = to;
	LOG_Print("State %s -> %s", GetStateName(from), GetStateName(to));
	return true;
}

void NTW_Initialize(EnumTestMode testMode) {
	// Initialize the ENet connectivity
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);

	// Load the username from the settings
	FILE* f = fopen("mp_settings.conf", "rb");
	if (f) {
		size_t len;
		if (fread(&len, sizeof(len), 1, f) == 1) {
			username.resize(len);
			fread(username.data(), 1, len, f);
		}

		fclose(f);
	}

	if (testMode == EnumTestMode::Server) {
		username = "ServerTest";
	} else if (testMode == EnumTestMode::Client) {
		username = "ClientTest";
	}

	NTW_test(testMode);

	LOG_Print("Username is now: %s", username.data());

	// Determine the time when the game booted up
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	bootTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void NTW_StartSearch() {
	if (!NTW_SetState(NetworkState::NONE, NetworkState::SEARCHING)) {
		LOG_Print("Cannot start searching for connections while already connected");
		return;
	}
	p2p = createP2P();
}

void NTW_ConnectToPeer() {
	if (!NTW_SetState(NetworkState::WAITING, NetworkState::HANDSHAKE)) {
		LOG_Print("Cannot connect without being in waiting state");
		return;
	}
	p2p->connect();
}

static void NTW_test(EnumTestMode testMode) {

	if (testMode == EnumTestMode::None) return;

	if (testMode == EnumTestMode::Server) {

		// Create a server instance to test
		server = createServer();
	}

	// Create the client
	client = createClient();

	// Attempt to connect to the server
	client->connect("127.0.0.1", DEFAULT_SERVER_PORT);
}