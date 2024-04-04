FROM gcc:latest
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake

COPY . /app

RUN cd build && cmake .. && make