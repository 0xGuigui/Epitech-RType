<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/jdsJk89.png" alt="Project logo"></a>
</p>

<h2 align="center">R-Type</h2>
<div align="center">

[![Language - C++](https://img.shields.io/badge/Language-C%2B%2B-004382?style=for-the-badge&logo=C%2B%2B)](https://)
[![Game - R-Type](https://img.shields.io/badge/Game-R--Type-beedfe?style=for-the-badge&logo=Zalando&logoColor=FFFFFF)](https://)
[![Build - Cmake](https://img.shields.io/badge/Build-Cmake-00a000?style=for-the-badge&logo=CMake)](https://)
<a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ"><img src="https://img.shields.io/static/v1?label=&message=Made+with+a+little+grain+of+salt&color=%23E71D29&style=for-the-badge&logo=Undertale" alt="Made by us with a little grain of salt"></a>

</div>

---

<p align="center"> A R-Type like game made with C++ and SFML
    <br>
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Architecture](#architecture)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>

This project is an R-Type-like game made with C++ and SFML. It was created for an Epitech C++ project and is a multiplayer game that allows you to play with your friends. The game has a client-server architecture, with the server built in C++ and the client built in C++ with SFML.

## 🏁 Getting Started <a name = "getting_started"></a>

### Prerequisites

You need to have CMake installed on your computer.

### Installing

To install the project, you need to clone the repository and build it with CMake.

Clone the repository:
```shell
git clone git@github.com:EpitechPromo2025/B-CPP-500-LIL-5-2-rtype-paul.gervais.git
```

Build the project:
```shell
./scripts/build.sh
```

## 🎈 Usage <a name="usage"></a>

To run the project, you need to run the server and the client.

Run the server:
```shell
./r-type_server
```

Run the client:
```shell
./r-type_client
```

## 🎨 Architecture <a name = "architecture"></a>

The project has a client-server architecture, with the server built in C++ and the client built in C++ with SFML using an Entity System Component architecture.
<br></br>
You can find the architecture of the project in the following image:

## ✍️ Authors <a name = "authors"></a>
- [@Paul Gervais](https://github.com/gagonlaire) - Initial work - Client/Server
- [@Florian Garnier](https://github.com/Suolumi) - ECS - Client
- [@Julien Hennion](https://github.com/Yusisako) - Entity System - Client
- [@Guilhem Jéhanno](https://github.com/Guigui1901) - Entity System - Client
