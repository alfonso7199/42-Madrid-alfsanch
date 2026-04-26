*This project has been created as part of the 42 curriculum by rzamolo-, alfsanch*

# ft_irc — Internet Relay Chat Server

## Description

`ft_irc` is a fully functional IRC server written in C++ 98. It implements the core IRC protocol, allowing real IRC clients (such as HexChat or WeeChat) to connect, authenticate, join channels, exchange messages and manage channel settings through operators.

The server handles multiple simultaneous clients without blocking, using a single `poll()` call for all I/O operations. No forking is used.

Implemented commands: `PASS`, `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `KICK`, `INVITE`, `TOPIC`, `MODE`, `QUIT`, `PING/PONG`.

### Commands usage

The table below shows the syntax of every command implemented by the server. Parameters in `<...>` are required, `[...]` are optional, and a leading `:` marks the trailing parameter (which may contain spaces).

| Command | Syntax | Description | Example |
|---------|--------|-------------|---------|
| `PASS` | `PASS <password>` | Provide the server password. Must be sent before `NICK` and `USER` to register | `PASS mypassword` |
| `NICK` | `NICK <nickname>` | Set or change the user's nickname | `NICK my_user` |
| `USER` | `USER <username> <mode> <unused> :<realname>` | Provide username and real name to complete registration | `USER my_user 0 * :Real Name` |
| `JOIN` | `JOIN <#channel> [key]` | Join a channel (creating it if it does not exist). `JOIN 0` leaves all channels | `JOIN #general` / `JOIN #secret hunter2` |
| `PART` | `PART <#channel> [:reason]` | Leave a channel, optionally with a reason | `PART #general :see you later` |
| `PRIVMSG` | `PRIVMSG <target> :<message>` | Send a message to a user or channel | `PRIVMSG #general :Hello!` / `PRIVMSG bob :Hi` |
| `TOPIC` | `TOPIC <#channel> [:topic]` | View the channel topic, or set it (subject to mode `+t`) | `TOPIC #general` / `TOPIC #general :New topic` |
| `INVITE` | `INVITE <nickname> <#channel>` | Invite a user to a channel (required when the channel is `+i`) | `INVITE bob #general` |
| `KICK` | `KICK <#channel> <nickname> [:reason]` | Remove a user from a channel (operator only) | `KICK #general bob :spamming` |
| `MODE` | `MODE <#channel> [+\|-]<modes> [arguments...]` | Query or change channel modes (see below) | `MODE #general +itk-l secret` |
| `QUIT` | `QUIT [:reason]` | Disconnect from the server, optionally with a reason | `QUIT :bye` |
| `PING` | `PING <token>` | Sent by the client to check liveness; the server replies with `PONG <token>` | `PING :server.name` |
| `PONG` | `PONG <token>` | Reply to a `PING` from the server | `PONG :server.name` |

Supported channel modes: `i` (invite-only), `t` (topic restricted to operators), `k` (channel key/password), `o` (give/take operator privilege), `l` (user limit).

### Channel modes usage

The `MODE` command is used to query or change a channel's modes. Only channel operators can change them. Modes are toggled with `+` (set) or `-` (unset) and may take an argument.

General syntax:

```
MODE <#channel> [+|-]<modes> [arguments...]
```

| Mode | Argument | Description | Example |
|------|----------|-------------|---------|
| `i` | none | Invite-only: only invited users may join | `MODE #channel +i` / `MODE #channel -i` |
| `t` | none | Restrict `TOPIC` changes to channel operators | `MODE #channel +t` / `MODE #channel -t` |
| `k` | password (on set) | Set or remove a channel key required to join | `MODE #channel +k secret` / `MODE #channel -k` |
| `o` | nickname | Grant or revoke operator privilege to a user on the channel | `MODE #channel +o my_user` / `MODE #channel -o my_user` |
| `l` | number (on set) | Set or remove the maximum number of users allowed in the channel | `MODE #channel +l 10` / `MODE #channel -l` |

## Instructions

### Compilation

```bash
make
```

Requires a C++ 98 compatible compiler (`g++` or `clang++`). No external libraries needed.

### Running the server

```bash
./ircserv <port> <password>
```

- `port`: listening port (e.g. `6667`)
- `password`: connection password required by IRC clients

Example:

```bash
./ircserv 6667 mypassword
```

### Connecting with HexChat

1. Open HexChat and go to **HexChat → Network List**
2. Click **Add**, name the network (e.g. `ft_irc`) and click **Edit**
3. Under **Servers**, add `localhost/6667`
4. Set **Server password** to your chosen password
5. Disable SSL if enabled
6. Change Login Method to **Server Password (/PASS password)**
7. Click **Connect**

Or directly from the HexChat input bar:

```
/server localhost 6667 mypassword
```

### Connecting with WeeChat

```
/server add ft_irc localhost/6667 -password=mypassword
/connect ft_irc
```

### Quick test with netcat

```bash
nc -C 127.0.0.1 6667
PASS mypassword
NICK testnick
USER testuser 0 * :Real Name
JOIN #general
PRIVMSG #general :Hello world!
```

### Makefile rules

| Rule | Description |
|------|-------------|
| `make` | Build the server |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full rebuild |

## Resources

### IRC Protocol references

- [RFC 1459 — Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 — IRC: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [Modern IRC documentation](https://modern.ircdocs.horse/)
- [IRC numeric replies reference](https://www.alien.net.au/irc/irc2numerics.html)
