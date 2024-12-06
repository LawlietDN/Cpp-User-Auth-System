# Cpp-User-Auth-System

## Overview

**Cpp-User-Auth-System** is a console-based user authentication application developed in C++. It allows users to sign up by creating an account and log in using their credentials. User data is stored in a JSON file, leveraging the [nlohmann/json](https://github.com/nlohmann/json) library for data handling.

## Features

- **User Registration:** Create a new account with a unique username and email.
- **User Authentication:** Log in with your username and password.
- **Password Hashing:** Securely store hashed passwords.
- **Data Persistence:** User data is stored in a JSON file (`userData.json`).
- **Input Validation:** Ensures valid email formats and enforces password strength.

## Prerequisites

- **Operating System:** Linux 
- **Compiler:** `g++` (supports C++11 or later)
- **Libraries:**
  - [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/LawlietDN/Cpp-User-Auth-System.git
cd Cpp-User-Auth-System
