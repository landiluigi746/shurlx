# shurlx

shurlx is a lightweight and high-performance URL shortener built with C++,
leveraging the web framework [Crow](https://crowcpp.org/) and [SQLite](https://www.sqlite.org/) for the database. It provides a template-based frontend powered by Crow's [Mustache](https://mustache.github.io/) integration, alongside [HTMX](https://htmx.org/) and [Tailwind CSS](https://tailwindcss.com/) for a minimalist, smooth and interactive user experience.

## Getting started

**Dependencies**

To get started with shurlx, you need to have:

- Docker
- Docker Compose
- vcpkg (optional, only for development)
- cmake (optional, only for development)
- C++23 compiler (optional, only for development)
- clang-format (optional, only for development)

**Installation, configuration and usage**

1. Clone the repository and navigate to the project directory.

```bash
# Clone the repository
git clone https://github.com/landiluigi746/shurlx.git
cd shurlx
```

2. Create a ```.env``` file with your desired configuration for the backend.

```bash
BUILD_TYPE=Release
PORT=8080

# Maximum length of the short code that identifies URLs
MAX_SHORT_CODE_LEN=4

# Maximum number of attempts to generate a unique short code if collision occurs
MAX_REGISTER_ATTEMPTS=16

REQUESTS_PER_MINUTE=24

# Base URL to concatenate the short code to
BASE_URL=http://localhost:8080
```

3. (Optional, only for development) Prepare the local development environment by running the following commands:
```bash
vcpkg install
cmake -S . -B build
```

4. Build and start the docker container with docker compose:
```bash
docker compose up --build -d
```
