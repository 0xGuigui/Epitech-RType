#pragma once

enum TcpRequest {
    REQ_SET_NAME,
    REQ_DISCONNECT,
    REQ_LIST_GAMES,
    REQ_CREATE_GAME,
    REQ_JOIN_GAME,
    REQ_LEAVE_GAME,
    REQ_START_GAME,
};

enum TcpResponse {
    RES_ERROR,
    RES_OK,
    RES_LIST_GAMES,
    RES_USER_LEAVED,
    RES_GAME_STARTED,
    RES_USER_JOINED,
};

enum UdpRequest {
    REQ_GAME_TICK,
};

enum UdpResponse {
    RES_GAME_TICK,
};

enum GameStatus {
    GAME_WAITING,
    GAME_STARTED,
    GAME_ENDED,
    GAME_STOPPED,
};
