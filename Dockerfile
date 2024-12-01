FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    libboost-all-dev \
    libgtest-dev

WORKDIR /app
COPY . .

RUN mkdir -p build && cd build && cmake .. && make

EXPOSE 2080

CMD ["./build/rtype-server"]
