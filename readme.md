# **Chess game project**

# Members

- Juliusz Neuman
- Arkadiusz Rybski
- Krystian Szewczak

# Modules

Modules are in separate libs.

Modules:

- Chess - implements chess logic: pieces, board, moves.
- Controller - controls game.
- Engine - gets best moves to prompt user or choose move for AI player.
- Loader - implements loading game, storing it and creating new one.
- Logger - implements singleton logger with multiple possible channels.
- Player - implements players (human and AI).
- Starter - don't know yet?
- View - implements viewing game.

# Tests

- Tests specific for given library should be placed in its directory.
- Tests combining multiple libraries should be placed in common tests directory.
