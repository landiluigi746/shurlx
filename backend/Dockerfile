FROM frolvlad/alpine-gxx

WORKDIR /app
COPY . .
ARG BUILD_TYPE=Debug
ENV BUILD_TYPE=${BUILD_TYPE}
RUN apk add --no-cache git make cmake sqlite sqlite-dev && cmake -S . -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} && cmake --build build

EXPOSE 8080

CMD [ "./bin/shurlx" ]
