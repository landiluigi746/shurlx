FROM csantve/alpine-vcpkg AS builder

WORKDIR /app

RUN apk add --no-cache linux-headers perl bash pkgconfig sqlite sqlite-dev

COPY vcpkg.json .

RUN vcpkg install

COPY CMakeLists.txt .
COPY src/ ./src/

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake

RUN cmake --build build --parallel $(nproc)

COPY . .

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/views/ ./views/
COPY --from=builder /app/static/ ./static/
COPY --from=builder /app/bin/shurlx .
COPY --from=builder /usr/lib/ /usr/lib/

EXPOSE ${PORT}

CMD ["./shurlx"]
