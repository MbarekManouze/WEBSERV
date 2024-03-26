# WebServ

This project is a simple HTTP server implementation in C++ 98, designed to serve web pages and handle HTTP requests. The server is capable of serving static websites, handling various HTTP methods like GET, POST, and DELETE, supporting file uploads from clients, and more.

## Introduction

Webserv is a project aimed at understanding the intricacies of the HTTP protocol and implementing a basic HTTP server from scratch. The server can be tested using a web browser or tools like Postman, and it adheres to the HTTP 1.1 standard. While the project doesn't require full implementation of the RFC, reading it can provide valuable insights for developing the required features.

## Features

Configuration File: Webserv accepts a configuration file as an argument or uses a default path. This file allows users to specify server settings such as port, host, server names, error pages, and more.

Non-blocking I/O: The server is designed to be non-blocking, ensuring that it never blocks while handling client requests. It utilizes a single select() (or equivalent) for all I/O operations, checking both read and write operations simultaneously.

**HTTP Methods**: Webserv supports essential HTTP methods such as GET, POST, and DELETE, allowing clients to interact with the server and manipulate resources.

**Static Website Hosting**: The server can serve fully static websites, delivering HTML documents, images, style sheets, scripts, and other resources to clients.

**File Uploads**: Clients can upload files to the server, expanding its capabilities beyond simple content delivery.

**Error Handling**: Webserv provides default error pages if none are provided, ensuring a consistent user experience in case of errors.

**CGI Execution**: The server supports CGI execution based on certain file extensions (e.g., .php), enabling dynamic content generation.

## Multiplexing and Socket Management

Webserv utilizes a multiplexing concept, which allows it to efficiently manage multiple client connections using a single select() (or equivalent) call. This approach maximizes the server's responsiveness and scalability by handling I/O operations for all connected clients in a non-blocking manner.

**Socket Handling**: The server creates and manages sockets for incoming client connections, using functions like socket(), bind(), and listen(). Each socket is associated with a file descriptor (FD), which is monitored by the select() function for read and write events.

**Selecting Mechanism**: Webserv employs the select() function to monitor multiple file descriptors simultaneously, including sockets for incoming client connections and file descriptors for other I/O operations. By efficiently polling all relevant descriptors, the server can respond to events in a timely manner without blocking.

## Parsing HTTP Requests

Parsing HTTP requests is a crucial aspect of the server's functionality, as it enables the server to understand and process client requests effectively. Webserv parses incoming HTTP requests to extract relevant information such as request method, URI, headers, and body content.

**Request Parsing**: Upon receiving an HTTP request from a client, Webserv parses the request to extract essential information. This includes parsing the request line to determine the request method and URI, parsing headers to extract additional metadata, and handling the request body if present.

**URI Handling**: Webserv interprets the URI provided in the request to determine the requested resource on the server. This includes mapping the URI to corresponding files or routes specified in the server configuration and handling dynamic routing if applicable.

**Header Processing**: The server parses HTTP headers to extract relevant information such as content type, content length, and any custom headers provided by the client. This information is used to determine how to handle the request and generate an appropriate response.

## Bonus Features

**Cookies and Session Management**: Support cookies and session management for enhanced client-server interaction.

**Multiple CGI**: Handle multiple CGI for increased flexibility in dynamic content generation


## Requirements

**Compiler**: Compile your code with c++ and the flags -Wall -Wextra -Werror.

**Standard**: Your code must comply with the C++ 98 standard and should still compile with the flag -std=c++98.

**External Libraries**: Any external library and Boost libraries are forbidden.

**Testing**: Stress test your server to ensure it stays available at all costs and meets performance expectations.
