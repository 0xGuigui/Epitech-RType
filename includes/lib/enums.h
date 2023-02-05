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
};

enum GameStatus {
    GAME_WAITING,
    GAME_STARTED,
    GAME_ENDED,
};
