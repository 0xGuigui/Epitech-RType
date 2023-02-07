<h2 align="center">r-type server</h2>

---

## 📝 Table of Contents

- [How does it work](#how-does-it-work)
- [Making requests](#making-requests)
    - [Resume](#resume)
    - [Commands](#commands)
- [Events](#events)

## How does it work

When a client want to contact the server, he must first connect using a tcp socket.
This allows the server to know the client's ip and port and know specifically which client is sending a request.
The client can then use multiple commands (listed bellow) to create and manage games.
After the game start, all game clients are notified with a port to connect on using udp.
They then has access to different commands to play the game (send actions, inputs and read game state).

## Making requests

### Resume

To make request, the client must use the sf::Packet provided by the sfml library.
The packet is a stream of bytes that can be read and written.
Client must then input the command type using the TcpRequest enum.

```c++
sf::Packet packet;

packet << REQ_CREATE_GAME;
// set the game name
packet << "My game";
// send the packet
socket.send(packet);
```

Then, server will response using the TcpResponse enum.
```c++
socket.receive(packet);

TcpResponse response;
packet >> response;

if (response == RES_OK) {
    // do something
}
```

### Commands

| Command         | Description           | Parameters  | Response                    |
|-----------------|-----------------------|-------------|-----------------------------|
| REQ_CREATE_GAME | Create a new game     | Game name   | RES_OK, RES_ERROR           |
| REQ_JOIN_GAME   | Join a game           | Game name   | RES_OK, RES_ERROR           |
| REQ_LEAVE_GAME  | Leave a game          | -           | RES_OK, RES_ERROR           |
| REQ_START_GAME  | Start a game          | -           | RES_GAME_STARTED, RES_ERROR |
| REQ_SET_NAME    | Set the client name   | Client name | RES_OK, RES_ERROR           |
| REQ_DISCONNECT  | Disconnect the client | -           | RES_OK, RES_ERROR           |
| REQ_LIST_GAMES  | List all games        | -           | RES_OK, RES_ERROR           |
