*This project has been created as part of the 42 curriculum by mikkayma, atursun, yalp.*

# Webserv

This is when you finally understand why URLs start with HTTP.

## Description
`webserv` is a custom HTTP server implemented in C++98, built from scratch for the 42 curriculum.

The project focuses on understanding core web infrastructure concepts by implementing the server side manually:
- TCP sockets and connection lifecycle
- non-blocking I/O with a single event loop (`poll`)
- HTTP request parsing and HTTP response generation
- route-based configuration (Nginx-like `server` and `location` blocks)
- static file serving, uploads, CGI execution, deletion and redirections

The executable is launched as:

```bash
./webserv [configuration file]
```

In this repository, the default configuration is `default.conf`.

## Project Goals
- Build a resilient server that does not hang on malformed or partial requests.
- Keep all socket I/O non-blocking and event-driven.
- Support real browser usage, not only synthetic tests.
- Implement and validate status-code behavior (`200`, `301`, `403`, `404`, `405`, `413`, `500`, etc.).
- Compare behavior against NGINX whenever interpretation is unclear.

## Implemented Features

### HTTP and Routing
- Methods: `GET`, `POST`, `DELETE`
- Route matching with configurable `location` blocks
- Method allow-list per route (`allow_methods`)
- URL decoding support for encoded paths
- Query-string aware request path handling

### Static Content and Files
- Static website serving from `www/`
- Per-route `root` and `index` behavior
- Autoindex directory listing (`autoindex on`)
- Custom error pages from `www/error_page/`

### Upload and Delete
- Upload endpoint support via `POST`
- Multipart form-data file extraction and persistence
- Delete files via `DELETE` on configured routes

### CGI
- CGI execution through `fork`, `pipe`, `dup2`, `execve`
- Python CGI configured via `.py` extension
- Additional CGI path for `.bla` extension using `./cgi_tester`
- Request headers propagated as CGI environment variables (`HTTP_*`)
- Query string and body forwarding to CGI process

### Multi-Server Configuration
- Multiple `server` blocks in a single config file
- Concurrent listening on at least:
    - `0.0.0.0:8080`
    - `0.0.0.0:8088`

## How It Works

### 1. Boot Sequence
1. Validate command-line argument count.
2. Open and parse configuration file.
3. Create and configure one listening socket per server block.
4. Switch sockets to non-blocking mode.
5. Enter the `poll` event loop.

### 2. Event Loop Model
- A single `poll` vector tracks listening sockets and connected clients.
- New clients are accepted and added dynamically.
- Incoming bytes are appended into per-client buffers.
- Parsing waits until request completeness is detected.
- After response write, client connection is cleaned up when needed.

### 3. Request Processing Pipeline
1. Receive bytes using `recv`.
2. Detect header/body boundary.
3. Validate body completion using `Content-Length` or chunk terminator.
4. Decode URL path.
5. Match `location` and check method policy.
6. Dispatch to `GET`, `POST`, or `DELETE` handlers.
7. Build and send an HTTP response.

### 4. CGI Pipeline
1. Detect CGI route by extension (`.py`, `.bla`).
2. Build CGI environment variables.
3. Create stdin/stdout pipes.
4. Fork process.
5. Child executes interpreter/script in correct working directory.
6. Parent writes body to CGI stdin and reads CGI stdout.
7. Convert CGI output to final HTTP response.

## Configuration File
The project uses an Nginx-like syntax with `server {}` and `location {}` blocks.

Current repository config: `default.conf`

### Supported directives (used in this project)
- `listen`
- `server_name`
- `root`
- `error_page`
- `client_max_body_size`
- `location`
- `index`
- `allow_methods`
- `autoindex`
- `upload_path`
- `cgi_path`
- `cgi_ext`
- `return` (redirect)

### Example routes from this repository
- `/` -> static index page
- `/cgi-bin` -> Python CGI scripts in `www/cgi-bin`
- `/uploads` -> upload and delete target
- `/test` -> directory listing enabled
- `/old-page` -> `301` redirect to `/new-page`
- `.py` and `.bla` -> extension-based CGI rules

## Instructions

### Requirements
- Unix-like runtime environment (Linux or macOS recommended)
- C++ compiler supporting C++98
- `make`
- Python 3 for `.py` CGI endpoints

Windows users should run with WSL or another Unix-compatible environment.

### Build
```bash
make
```

Makefile rules available:
```bash
make all
make clean
make fclean
make re
```

Compilation flags used by this repository:

```text
-Wall -Wextra -Werror -std=c++98 -g
```

### Run
```bash
./webserv default.conf
```

If the config file is missing or unreadable, startup fails with an error.

### Stop
Press `Ctrl+C` to stop the server gracefully.

## Testing Guide

### Browser tests
- Open `http://localhost:8088/`
- Open `http://localhost:8088/`
- Open `http://localhost:8088/test/` for autoindex
- Open `http://localhost:8088/old-page` and verify redirect to `/new-page`

### cURL tests

Static page:
```bash
curl -i http://localhost:8080/
```

Method restriction check (`405` expected on `/`):
```bash
curl -i -X POST http://localhost:8080/
```

Small body endpoint (`/post_body` has low body limit):
```bash
curl -i -X POST http://localhost:8080/post_body -d "hello"
```

Upload file:
```bash
curl -i -X POST -F "file=@README.md" http://localhost:8088/uploads
```

Delete uploaded file:
```bash
curl -i -X DELETE http://localhost:8088/uploads/README.md
```

Python CGI:
```bash
curl -i "http://localhost:8080/cgi-bin/test.py?name=webserv"
curl -i -X POST http://localhost:8080/cgi-bin/test.py -d "hello=cgi"
```

Custom extension CGI (`.bla`):
```bash
curl -i -X POST http://localhost:8080/YoupiBanane/youpi.bla -d "test=1"
```

### Suggested stress checks
- Repeated concurrent requests with `ab`, `hey`, or custom scripts.
- Upload + CGI + static requests mixed in parallel.
- Large request body attempts to verify `413` handling.

## Known Limitations
- HTTP parser aims at project scope and does not implement full RFC surface.
- Multipart parsing is practical but not a complete MIME implementation.
- Behavior is optimized for required methods/features, not full production hardening.
- HTTPS/TLS is out of scope.

## Resources

### Protocol and Standards
- RFC 9112 (HTTP/1.1): https://datatracker.ietf.org/doc/html/rfc9112
- RFC 9110 (HTTP Semantics): https://datatracker.ietf.org/doc/html/rfc9110
- RFC 3875 (CGI 1.1): https://datatracker.ietf.org/doc/html/rfc3875

### Systems and Network Programming
- Beej's Guide to Network Programming: https://beej.us/guide/bgnet/
- Linux `poll(2)` manual: https://man7.org/linux/man-pages/man2/poll.2.html
- NGINX docs (behavior comparison): https://nginx.org/en/docs/

## AI Usage Statement
AI tools were used in a controlled and review-first way for support tasks, not as a substitute for understanding.

What AI was used for:
- Summarizing RFC sections and protocol terminology
- Brainstorming test scenarios and edge cases
- Refining documentation language and structure

What AI was not used for:
- Blindly generating core server logic without review
- Replacing manual debugging, peer discussion, or validation
- Avoiding ownership of implementation decisions

Every AI-assisted output was checked, discussed, and validated through code review, manual testing, and peer feedback before acceptance.

