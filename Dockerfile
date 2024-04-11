FROM gcc:latest
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    mingw-w64

COPY . /app

RUN cd build && \ 
    cmake -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw64.cmake .. && \
    make